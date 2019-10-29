//file TitleScene.cpp

#include "TitleScene.h"
#include "MainGameScene.h"


/*
* Process Player Input
*/
void TitleScene::ProcessInput()
{
	SceneStack::Instance().Replace(std::make_shared<MainGameScene>());
}