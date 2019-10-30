#include <Windows.h>
#include "GLFWEW.h"
#include "TitleScene.h"
#include "Sound.h"
#include <iostream>

/*
* GPU�ŏ����������錾
*
* Windows.h �ɂ�����
*/
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}


int main()
{
	
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	//CreateWindow
	window.Init(1280,720,u8"�A�N�V�����Q�[��");

	//SoundSystemInitialize;
	Sound::EngineInitialize();

	SceneStack& sceneStack = SceneStack::Instance();
	//CreateTitleScene
	sceneStack.Push(std::make_shared<TitleScene>());
	while (!window.ShouldClose())
	{
		window.Update();

		//�I������
		if (window.IsKeyPressed(GLFW_KEY_ESCAPE)) {
			if (MessageBox(nullptr,"�Q�[�����I�����܂���?","�I��",MB_OKCANCEL)==IDOK) {
				break;
			}
		}

		const float deltaTime = static_cast<float>(window.DeltaTime());
		sceneStack.Update(deltaTime);

		//Delete BackBuffer
		glClearColor(0.1f,0.2f,0.8f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//GL�R���e�L�X�g�̃p�����[�^��ݒ�.
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		sceneStack.Render();

		window.SwapBuffers();
		Sound::EngineUpdate(deltaTime);

	}//while(!window.SholdClose())
	
	return 0;
}