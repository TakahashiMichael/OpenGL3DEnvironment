#include <Windows.h>

#include "Sound.h"
#include "GLFWEW.h"
#include "TitleScene.h"
#include "SkeletalMesh.h"
#include <iostream>

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}


int main()
{
	//サウンドのシステムの初期化
	if (!Sound::EngineInitialize())
	{
		std::cerr << "サウンドの初期化に失敗" << std::endl;
		return 1;
	}

	GLFWEW::Window& window = GLFWEW::Window::Instance();
	window.Init(1280,720,u8"アクションゲーム");

	//スケルタルアニメーションを利用可能にする.
	Mesh::SkeletalAnimation::Initialize();

	SceneStack& sceneStack = SceneStack::Instance();
	sceneStack.Push(std::make_shared<TitleScene>());


		while (!window.ShouldClose()) {

			window.Update();

			//ESCキーが押されたら終了ウィンドウを表示.
			if (window.IsKeyPressed(GLFW_KEY_ESCAPE)) {
				if (MessageBox(nullptr, "ゲームを終了しますか?", "終了", MB_OKCANCEL) == IDOK) {
					break;
				}
			}

			//スケルタル・アニメーション用のデータの作成準備.
			Mesh::SkeletalAnimation::ResetUniformData();

			const float deltaTime = static_cast<float>(window.DeltaTime());
			sceneStack.Update(deltaTime);

			//スケルタル・アニメーション用データをGPUメモリに転送.
			Mesh::SkeletalAnimation::UploadUniformData();

			//バックバッファを消去する
			glClearColor(0.8f, 0.2f, 0.1f, 0.1f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//GLコンテキストのパラメータを設定.
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);

			sceneStack.Render();

			window.SwapBuffers();
			Sound::EngineUpdate(deltaTime);
		}
		//スケルタル・アニメーションの利用を終了する.
		Mesh::SkeletalAnimation::Finalize();

	return 0;
}