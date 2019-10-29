#include <Windows.h>
#include "GLFWEW.h"
#include "TitleScene.h"

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
	window.Init(1280,720,u8"�A�N�V�����Q�[��");

	SceneStack& sceneStack = SceneStack::Instance();
	sceneStack.Push(std::make_shared<TitleScene>());
	while (!window.ShouldClose())
	{
		window.Update();
		const float deltaTime = static_cast<float>(window.DeltaTime());
		sceneStack.Update(deltaTime);
		sceneStack.Render();

		window.SwapBuffers();

	}//while(!window.SholdClose())
	
	return 0;
}