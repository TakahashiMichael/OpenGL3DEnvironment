//file MainGameScene.cpp


#include "MainGameScene.h"
#include "StatusScene.h"
#include "GameOverScene.h"
#include "SkeletalMeshActor.h"
#include "GLFWEW.h"
#include "Filename.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <random>
/**
* �Փ˂���������.
*
* @param a  �Փ˂����A�N�^�[���̂P.
* @param b  �Փ˂����A�N�^�[���̂Q.
* @param p  �Փˈʒu.
*/
void PlayerCollisionHandler(const ActorPtr& a, const ActorPtr& b, const glm::vec3& p)
 {
	const glm::vec3 v = a->colWorld.s.center - p;
	  // �Փˈʒu�Ƃ̋������߂����Ȃ������ׂ�.
		if (dot(v, v) > FLT_EPSILON) {
		    // a��b�ɏd�Ȃ�Ȃ��ʒu�܂ňړ�.
		const glm::vec3 vn = normalize(v);
		float radiusSum = a->colWorld.s.r;
		switch (b->colWorld.type) {
		case Collision::Shape::Type::sphere: radiusSum += b->colWorld.s.r; break;
		case Collision::Shape::Type::capsule: radiusSum += b->colWorld.c.r; break;
		}
		const float distance = radiusSum - glm::length(v) + 0.01f;
		a->position += vn * distance;
		a->colWorld.s.center += vn * distance;
		if (a->velocity.y < 0 && vn.y >= glm::cos(glm::radians(60.0f))) {
			a->velocity.y = 0;
			
			}
		}
		else {
			// �ړ���������(�������߂�����ꍇ�̗�O����).
			const float deltaTime = static_cast<float>(GLFWEW::Window::Instance().DeltaTime());
			const glm::vec3 deltaVelocity = a->velocity * deltaTime;
			a->position -= deltaVelocity;
			a->colWorld.s.center -= deltaVelocity;
	}
}

/*
* �V�[��������������.
*
* @retval true ����������
* @retval false ���������s.�G�[���i�s���ׂɂ��A�v���O�������I�����邱��.
*/
bool MainGameScene::Initialize()
{
	spriteRenderer.Init(1000, "Res/Shader/Sprite.vert", "Res/Shader/Sprite.frag");
	sprites.reserve(100);
	//Sprite spr(Texture::Image2D::Create("Res/Texture/TitleBack.tga"));
	//spr.Scale(glm::vec2(2));
	//sprites.push_back(spr);

	fontRenderer.Init(1000);
	fontRenderer.LoadFromFile(FILENAME_FNT_FONT);


	meshBuffer.Init(1'000'000 * sizeof(Mesh::Vertex), 3'000'000 * sizeof(GLushort));

	lightBuffer.Init(1);
	lightBuffer.BindToShader(meshBuffer.GetStaticMeshShader());
	lightBuffer.BindToShader(meshBuffer.GetTerrainShader());

	meshBuffer.LoadMesh("Res/red_pine_tree.gltf");
	meshBuffer.LoadMesh("Res/jizo_statue.gltf");
	meshBuffer.LoadSkeletalMesh("Res/bikuni.gltf");
	meshBuffer.LoadSkeletalMesh("Res/oni_small.gltf");
	meshBuffer.LoadMesh("Res/wall_stone.gltf");

	//�n�C�g�}�b�v���쐻����
	if (!heightMap.LoadFromFile("Res/Terrain.tga", 20.0f, 0.5f)) {
		return false;
	}
	if (!heightMap.CreateMesh(meshBuffer, "Terrain")) {
		return false;
	}
	glm::vec3 startPos(100, 0, 100);
	startPos.y = heightMap.Height(startPos);
	player = std::make_shared<PlayerActor>(&heightMap, meshBuffer, startPos);

	rand.seed(0);

	// ���C�g��z�u
	lights.Add(std::make_shared<DirectionalLightActor>(
			"DirectionalLight", glm::vec3(0.2f), glm::normalize(glm::vec3(1, -2, -1))));
	for (int i = 0; i < 50; ++i) {
		glm::vec3 color(1, 0.8f, 0.5f);
		glm::vec3 position(0);
		position.x = static_cast<float>(std::uniform_int_distribution<>(80, 120)(rand));
		position.z = static_cast<float>(std::uniform_int_distribution<>(80, 120)(rand));
		position.y = heightMap.Height(position) + 1;
		lights.Add(std::make_shared<PointLightActor>("PointLight", color, position));
		
	}
	lights.Update(0);
	lightBuffer.Update(lights, glm::vec3(0.1f, 0.05f, 0.15f));
	heightMap.UpdateLightIndex(lights);

	// ���n���l��z�u
		for (int i = 0; i < 4; ++i) {
		glm::vec3 position(0);
		position.x = static_cast<float>(std::uniform_int_distribution<>(50, 150)(rand));
		position.z = static_cast<float>(std::uniform_int_distribution<>(50, 150)(rand));
		position.y = heightMap.Height(position);
		glm::vec3 rotation(0);
		rotation.y = std::uniform_real_distribution<float>(0.0f, 3.14f * 2.0f)(rand);
		JizoActorPtr p = std::make_shared<JizoActor>(
			meshBuffer.GetFile("Res/jizo_statue.gltf"), position, i, this);
		p->scale = glm::vec3(3); // �����₷���悤�Ɋg��.
		objects.Add(p);
		
	}
	// �Εǂ�z�u
	{
		const Mesh::FilePtr meshStoneWall = meshBuffer.GetFile("Res/wall_stone.gltf");
		glm::vec3 position = startPos + glm::vec3(3, 0, 3);
		position.y = heightMap.Height(position);
		StaticMeshActorPtr p = std::make_shared<StaticMeshActor>(
			meshStoneWall, "StoneWall", 100, position, glm::vec3(0, 0.5f, 0));
		p->colLocal = Collision::CreateOBB(glm::vec3(0, 0, 0),
			glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1), glm::vec3(2, 2, 0.5f));
		objects.Add(p);
	}
	// �G��z�u.
	{
	const size_t oniCount = 100;
#if 0
	enemies.Reserve(oniCount);
	for (size_t i = 0; i < oniCount; ++i) {
			     // �G�̈ʒu��(50,50)-(150,150)�͈̔͂��烉���_���ɑI��.
				glm::vec3 position(0);
			position.x = std::uniform_real_distribution<float>(50, 150)(rand);
			position.z = std::uniform_real_distribution<float>(50, 150)(rand);
			position.y = heightMap.Height(position);
			      // �G�̌����������_���ɑI��.
				glm::vec3 rotation(0);
			rotation.y = std::uniform_real_distribution<float>(0, glm::pi<float>() * 2)(rand);
			const Mesh::SkeletalMeshPtr mesh = meshBuffer.GetSkeletalMesh("oni_small");
			SkeletalMeshActorPtr p = std::make_shared<SkeletalMeshActor>(
				mesh, "Kooni", 13, position, rotation);
			p->GetMesh()->Play("Run");		
			p->colLocal = Collision::CreateCapsule(
				glm::vec3(0, 0.5f, 0), glm::vec3(0, 1, 0), 0.5f);
			enemies.Add(p);
			
		}
#endif
	}

	return true;
}

/*
* �V�[�����X�V����.
*
* @param deltaTime �O��̍X�V����̌o�ߎ���(�b).
*/
void MainGameScene::Update(float deltaTime)
{
	// �J�����̏�Ԃ��X�V.
	{
			camera.target = player->position;
			camera.position = camera.target + glm::vec3(0, 50, 50);
	}
	player->Update(deltaTime);
	enemies.Update(deltaTime);
	objects.Update(deltaTime);
	lights.Update(deltaTime);

	DetectCollision(player, enemies);
	DetectCollision(player, objects);

	
		  // �v���C���[�̍U������.
		ActorPtr attackCollision = player->GetAttackCollision();
	if (attackCollision) {
		bool hit = false;
		DetectCollision(attackCollision, enemies,
			[this, &hit](const ActorPtr& a, const ActorPtr& b, const glm::vec3& p) {
			SkeletalMeshActorPtr bb = std::static_pointer_cast<SkeletalMeshActor>(b);
			bb->health -= a->health;
			if (bb->health <= 0) {
				bb->colLocal = Collision::Shape{};
				bb->health = 1;
				bb->GetMesh()->Play("Down", false);
				
			}
			else {
				bb->GetMesh()->Play("Hit", false);
				
			}
			hit = true;
			}
		);
		if (hit) {
			attackCollision->health = 0;
			
		}
		
	}
	
		// ���S�A�j���[�V�����̏I������G������.
		for (auto& e : enemies) {
		SkeletalMeshActorPtr enemy = std::static_pointer_cast<SkeletalMeshActor>(e);
		Mesh::SkeletalMeshPtr mesh = enemy->GetMesh();
		if (mesh->IsFinished()) {
			if (mesh->GetAnimation() == "Down") {
				enemy->health = 0;
				
			}
			else {
				mesh->Play("Wait");
				
			}
		}
	}
		  // ���C�g�̍X�V.
			glm::vec3 ambientColor(0.1f, 0.05f, 0.15f);
		lightBuffer.Update(lights, ambientColor);
		//for (auto e : trees) {
		//	const std::vector<ActorPtr> neighborhood = lights.FindNearbyActors(e->position, 20);
		//	std::vector<int> pointLightIndex;
		//	std::vector<int> spotLightIndex;
		//	pointLightIndex.reserve(neighborhood.size());
		//	spotLightIndex.reserve(neighborhood.size());
		//	for (auto light : neighborhood) {
		//		if (PointLightActorPtr p = std::dynamic_pointer_cast<PointLightActor>(light)) {
		//			if (pointLightIndex.size() < 8) {
		//				pointLightIndex.push_back(p->index);
		//				
		//			}
		//			
		//		}
		//		else if (
		//			SpotLightActorPtr p = std::dynamic_pointer_cast<SpotLightActor>(light)) {
		//			if (spotLightIndex.size() < 8) {
		//				spotLightIndex.push_back(p->index);
		//				
		//			}
		//			
		//		}
		//		
		//	}
		//	StaticMeshActorPtr p = std::static_pointer_cast<StaticMeshActor>(e);
		//	p->SetPointLightList(pointLightIndex);
		//	p->SetSpotLightList(spotLightIndex);
		//	
		//}
		  // �G��S�ł�������ړI�B���t���O��true�ɂ���.
			if (jizoId >= 0) {
			if (enemies.Empty()) {
				achivements[jizoId] = true;
				jizoId = -1;
				
			}
		}

	player->UpdateDrawData(deltaTime);
	enemies.UpdateDrawData(deltaTime);
	objects.UpdateDrawData(deltaTime);

	spriteRenderer.BeginUpdate();
	for (const Sprite& e : sprites) {
		spriteRenderer.AddVertices(e);
	}
	spriteRenderer.EndUpdate();

	const GLFWEW::Window& window = GLFWEW::Window::Instance();
	const float w = static_cast<float>(window.Width());
	const float h = static_cast<float>(window.Height());
	const float lineHeight = fontRenderer.LineHeight();
	fontRenderer.BeginUpdate();
	fontRenderer.AddString(glm::vec2(-w * 0.5f + 32, h * 0.5f - lineHeight), L"�^�C�g�����");
	fontRenderer.AddString(glm::vec2(-128, 0), L"�A�N�V�����Q�[��");
	fontRenderer.EndUpdate();
}

/*
* �V�[����`�悷��.
*/
void MainGameScene::Render()
{
	const GLFWEW::Window& window = GLFWEW::Window::Instance();
	const glm::vec2 screenSize(window.Width(), window.Height());
	spriteRenderer.Draw(screenSize);


	glEnable(GL_DEPTH_TEST);

	lightBuffer.Upload();
	lightBuffer.Bind();

	const glm::mat4 matView = glm::lookAt(camera.position, camera.target, camera.up);
	const float aspectRatio =
		static_cast<float>(window.Width()) / static_cast<float>(window.Height());
	const glm::mat4 matProj =
		glm::perspective(glm::radians(30.0f), aspectRatio, 1.0f, 1000.0f);
	glm::vec3 cubePos(100, 0, 100);
	cubePos.y = heightMap.Height(cubePos);
	const glm::mat4 matModel = glm::translate(glm::mat4(1), cubePos);
	
	meshBuffer.SetViewProjectionMatrix(matProj * matView);

	Mesh::Draw(meshBuffer.GetFile("Cube"), matModel);
	Mesh::Draw(meshBuffer.GetFile("Terrain"), glm::mat4(1));

	player->Draw();
	enemies.Draw();
	objects.Draw();

	glm::vec3 treePos(110, 0, 110);
	treePos.y = heightMap.Height(treePos);
	const glm::mat4 matTreeModel =
	glm::translate(glm::mat4(1), treePos) * glm::scale(glm::mat4(1), glm::vec3(3));
	Mesh::Draw(meshBuffer.GetFile("Res/red_pine_tree.gltf"), matTreeModel);

	fontRenderer.Draw(screenSize);
}
/**
* ���n���l�ɐG�ꂽ�Ƃ��̏���.
*
* @param id  ���n���l�̔ԍ�.
* @param pos ���n���l�̍��W.
*
* @retval true  ��������.
* @retval false ���łɐ퓬���Ȃ̂ŏ������Ȃ�����.
*/
bool MainGameScene::HandleJizoEffects(int id, const glm::vec3& pos)
 {
	if (jizoId >= 0) {
		return false;
		
	}
	jizoId = id;
	const size_t oniCount = 8;
	for (size_t i = 0; i < oniCount; i++)
		 {
		glm::vec3 position(pos);
		position.x += std::uniform_real_distribution<float>(-15, 15)(rand);
		position.z += std::uniform_real_distribution<float>(-15, 15)(rand);
		position.y = heightMap.Height(position);
		
			glm::vec3 rotation(0);
		rotation.y = std::uniform_real_distribution<float>(0, 3.14f * 2.0f)(rand);
		const Mesh::SkeletalMeshPtr mesh = meshBuffer.GetSkeletalMesh("oni_small");
		SkeletalMeshActorPtr p = std::make_shared<SkeletalMeshActor>(
			mesh, "Kooni", 13, position, rotation);
		p->GetMesh()->Play("Wait");
		p->colLocal = Collision::CreateCapsule(
			glm::vec3(0, 0.5f, 0), glm::vec3(0, 1, 0), 0.5f);
		enemies.Add(p);
		}
	return true;
}

// �v���C���[�̓��͂���������
void MainGameScene::ProcessInput()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();

	//�v���C���[����.
	player->ProcessInput();

//	if (window.GetGamePad().buttonDown & GamePad::START) {
//		SceneStack::Instance().Replace(std::make_shared<MainGameScene>());
//	}
}