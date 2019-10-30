//file TitleScene.cpp

#include "Filename.h"
#include "TitleScene.h"
#include "MainGameScene.h"
#include "GLFWEW.h"




/*
* Initialize Scene
*
* return value true: Success
* return value false :Unsuccess
*/
bool TitleScene::Initialize()
{
	spriteRenderer.Init(1000,FILENAME_SHADER_VERT_SPRITE,FILENAME_SHADER_FRAG_SPRITE);
	sprites.reserve(100);
	Sprite sprTitleBG(Texture::Image2D::Create(FILENAME_TGA_TITLE_BG));
	sprTitleBG.Scale(glm::vec2(1));
	sprites.push_back(sprTitleBG);

	Sprite sprTitleLogo(Texture::Image2D::Create(FILENAME_TGA_TITLE_LOGO));
	sprTitleLogo.Scale(glm::vec2(1));
	sprites.push_back(sprTitleLogo);


	return true;
}//func TitleScene::Initialize




/*
* Process Player Input
*/
void TitleScene::ProcessInput()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	if (window.GetGamePad().buttonDown& GamePad::START) {
		SceneStack::Instance().Replace(std::make_shared<MainGameScene>());
	}
}//func TetleScene::ProcessInput

/*
* Update Scene
*
* @param deltaTime : Elapsed time scene last time
*/
void TitleScene::Update(float deltaTime)
{
	spriteRenderer.BeginUpdate();
	for (const Sprite& e : sprites) {
		spriteRenderer.AddVertices(e);
	}
	spriteRenderer.EndUpdate();
}//func TitleScene::Update

/*
* Draw scene
*/
void TitleScene::Render()
{
	const GLFWEW::Window& window = GLFWEW::Window::Instance();
	const glm::vec2 screenSize(window.Width(),window.Height());
	spriteRenderer.Draw(screenSize);

}//func TitleScene::Render