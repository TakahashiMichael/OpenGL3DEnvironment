#include "MainGameScene.h"
#include "Filename.h"
#include "GLFWEW.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>


/*
* Initialize Scene
*/
bool MainGameScene::Initialize()
{
	meshBuffer.Init(1'000'000 * sizeof(Mesh::Vertex),3'000'000 * sizeof(GLushort));
	meshBuffer.LoadMesh(FILENAME_GLTF_GLTF);


	//ハイトマップを作製する
	if (!heightMap.LoadFromFile(FILENAME_TGA_TERRAIN,20.0f,0.5f)) {
		return false;
	}
	if (!heightMap.CreateMesh(meshBuffer,"Terrain"))
	{
		return false;
	}

	return true;
}

/*
* Process Player Input
*
*
*/
void MainGameScene::ProcessInput()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	// カメラ操作.
	const GamePad gamepad = window.GetGamePad();
	glm::vec3 velocity(0);
	if (gamepad.buttons & GamePad::DPAD_LEFT) {
		velocity.x = -1;

	}
	else if (gamepad.buttons & GamePad::DPAD_RIGHT) {
		velocity.x = 1;

	}
	if (gamepad.buttons & GamePad::DPAD_DOWN) {
		velocity.z = 1;

	}
	else if (gamepad.buttons & GamePad::DPAD_UP) {
		velocity.z = -1;

	}
	if (velocity.x || velocity.z) {
		velocity = normalize(velocity) * 20.0f;
	}
	camera.velocity = velocity;
}

/*
* Update Scene
*
* @param deltaTime : 
*/
void MainGameScene::Update(float deltaTime)
{
	//カメラの状態を更新
	if (dot(camera.velocity, camera.velocity)) {
		camera.target += camera.velocity * deltaTime;
		camera.target.y = heightMap.Height(camera.target);
		camera.position = camera.target + glm::vec3(0.0f,50.0f,50.0f);
	}
}

/*
* Draw Scene
*/
void MainGameScene::Render()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();

	glEnable(GL_DEPTH_TEST);

	const glm::mat4 matView = glm::lookAt(camera.position, camera.target, camera.up);
	const float aspectRatio =
		static_cast<float>(window.Width()) / static_cast<float>(window.Height());
	const glm::mat4 matProj =
		glm::perspective(glm::radians(30.0f), aspectRatio, 1.0f, 1000.0f);
	const glm::mat4 matModel(1);



	Mesh::Draw(meshBuffer.GetFile("Cube"), matProj * matView, matModel);

	//Draw HeightMap
	Mesh::Draw(meshBuffer.GetFile("Terrain"),matProj* matView,glm::mat4(1));

	glm::vec3 treePos(110, 0, 110);
	treePos.y = heightMap.Height(treePos);
	const glm::mat4 matTreeModel =
		glm::translate(glm::mat4(1), treePos) * glm::scale(glm::mat4(1), glm::vec3(3));
	Mesh::Draw(meshBuffer.GetFile("Res/red_pine_tree.gltf"), matProj * matView, matTreeModel);

}