#include <Windows.h>
#include "GLFWEW.h"
#include "TitleScene.h"
#include "Sound.h"
#include <iostream>

/*
* GPUで処理を書く宣言
*
* Windows.h において
*/
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}


int main()
{
	
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	//CreateWindow
	window.Init(1280,720,u8"アクションゲーム");

	//SoundSystemInitialize;
	Sound::EngineInitialize();

	SceneStack& sceneStack = SceneStack::Instance();
	//CreateTitleScene
	sceneStack.Push(std::make_shared<TitleScene>());
	while (!window.ShouldClose())
	{
		window.Update();

		//終了処理
		if (window.IsKeyPressed(GLFW_KEY_ESCAPE)) {
			if (MessageBox(nullptr,"ゲームを終了しますか?","終了",MB_OKCANCEL)==IDOK) {
				break;
			}
		}

		const float deltaTime = static_cast<float>(window.DeltaTime());
		sceneStack.Update(deltaTime);

		//Delete BackBuffer
		glClearColor(0.1f,0.2f,0.8f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//GLコンテキストのパラメータを設定.
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		sceneStack.Render();

		window.SwapBuffers();
		Sound::EngineUpdate(deltaTime);

	}//while(!window.SholdClose())
	
	return 0;
}