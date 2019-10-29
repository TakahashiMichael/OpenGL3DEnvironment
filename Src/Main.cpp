#include <Windows.h>
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
	SceneStack& sceneStack = SceneStack::Instance();
	sceneStack.Push(std::make_shared<TitleScene>());

	for (;;) {
		const float deltaTime = 1.0f / 60.0f;
		sceneStack.Update(deltaTime);
		sceneStack.Render();
	}

	return 0;
}