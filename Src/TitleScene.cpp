//file TitleScene.cpp

#include "Filename.h"
#include "TitleScene.h"
#include "MainGameScene.h"
#include "GLFWEW.h"

#include <iostream>


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

	fontRenderer.Init(1000);
	fontRenderer.LoadFromFile(FILENAME_FNT_FONT);

	bgmTitle.Init(FILENAME_WAV_TITLE_BGW);
	bgmTitle.SetLooping(true);
	bgmTitle.Play();
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

	const GLFWEW::Window& window = GLFWEW::Window::Instance();
	const float w = static_cast<float>(window.Width());
	const float h = static_cast<float>(window.Height());
	const float lineHeight = fontRenderer.LineHeight();
	fontRenderer.BeginUpdate();
	fontRenderer.AddString(glm::vec2(-w * 0.5f + 32, h * 0.5f - lineHeight), L"タイトル画面");
	fontRenderer.AddString(glm::vec2(-128, 0), L"アクションゲーム");
	fontRenderer.EndUpdate();
}//func TitleScene::Update

/*
* Draw scene
*/
void TitleScene::Render()
{
	const GLFWEW::Window& window = GLFWEW::Window::Instance();
	const glm::vec2 screenSize(window.Width(),window.Height());
	spriteRenderer.Draw(screenSize);
	fontRenderer.Draw(screenSize);

}//func TitleScene::Render

/*
* Finalize scene
*/
void TitleScene::Finalize()
{
}