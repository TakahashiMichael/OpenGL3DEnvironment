
// @file TitleScene.cpp

#include "TitleScene.h"
#include "MainGameScene.h"
#include "GLFWEW.h"
#include "Filename.h"
#include <iostream>


/*
* �V�[��������������.
*
* @retval true ����������
* @retval false ���������s.�G�[���i�s���ׂɂ��A�v���O�������I�����邱��.
*/
bool TitleScene::Initialize()
{
	spriteRenderer.Init(1000,"Res/Shader/Sprite.vert","Res/Shader/Sprite.frag");
	sprites.reserve(100);
	Sprite spr(Texture::Image2D::Create(FILENAME_TGA_TITLE_LOGO));
	spr.Scale(glm::vec2(1));
	sprites.push_back(spr);
	sound_TitleBGM.Init(FILENAME_WAV_TITLE_BGW);
	sound_TitleBGM.Play();

	fontRenderer.Init(1000);
	fontRenderer.LoadFromFile(FILENAME_FNT_FONT);


	return true;
}

/*
* �V�[�����X�V����.
*
* @param deltaTime �O��̍X�V����̌o�ߎ���(�b).
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
	fontRenderer.AddString(glm::vec2(-w * 0.5f + 32,h * 0.5f -lineHeight),L"�^�C�g�����");
	fontRenderer.AddString(glm::vec2(-128,0),L"�A�N�V�����Q�[��");
	fontRenderer.EndUpdate();
}

/*
* �V�[����`�悷��.
*/
void TitleScene::Render()
{
	const GLFWEW::Window& window = GLFWEW::Window::Instance();
	const glm::vec2 screenSize(window.Width(), window.Height());
	spriteRenderer.Draw(screenSize);
}


// �v���C���[�̓��͂���������
void TitleScene::ProcessInput()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();

	if (window.GetGamePad().buttonDown & GamePad::START) {
		SceneStack::Instance().Replace(std::make_shared<MainGameScene>());
	}
}