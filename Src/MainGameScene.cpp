#include "MainGameScene.h"

#include "GLFWEW.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

/*
* Initialize Scene
*/
bool MainGameScene::Initialize()
{
	meshBuffer.Init(1'000'000 * sizeof(Mesh::Vertex),3'000'000 * sizeof(GLushort));

	return true;
}

/*
* Process Player Input
*
*
*/
void MainGameScene::ProcessInput()
{

}

/*
* Update Scene
*
* @param deltaTime : 
*/
void MainGameScene::Update(float deltaTime)
{

}

/*
* Draw Scene
*/
void MainGameScene::Render()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();

	glEnable(GL_DEPTH_TEST);
	const glm::vec3 cameraPos(-5, 3, 5);
	const glm::vec3 targetPos(0, 0, 0);
	const glm::mat4 matView = glm::lookAt(cameraPos, targetPos, glm::vec3(0, 1, 0));
	const float aspectRatio =
		static_cast<float>(window.Width()) / static_cast<float>(window.Height());
	const glm::mat4 matProj =
		glm::perspective(glm::radians(30.0f), aspectRatio, 1.0f, 1000.0f);
	const glm::mat4 matModel(1);
	Mesh::Draw(meshBuffer.GetFile("Cube"), matProj * matView, matModel);

}