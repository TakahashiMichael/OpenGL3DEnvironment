//Scene.cpp

#include "Scene.h"
#include <iostream>

/*
* コンストラクタ 
*
* @param name: シーン名
*/
Scene::Scene(const char* name) :name(name) 
{
	//DebugLog
	std::cout << "Scene constructer:" << name << std::endl;
}

/*
* デストラクタ/
*/
Scene::~Scene()
{
	
	//DebugLog
	std::cout << "Scene Destructer:" << name << std::endl;

	//デストラクタで呼ばれる定義はファイナライズ関数に記入する
	Finalize();
}

/*
* シーンを活動招待にする
*/
void Scene::Play() 
{
	//DebugLog
	std::cout << "Scene Play:" << name << std::endl;

	isActive = true;
}

/*
* シーンを停止状態にする.
*/
void Scene::Stop()
{
	//DebugLog
	std::cout << "Scene Stop:" << name << std::endl;
	isActive = false;
}

/*
* シーンを表示する.
*/
void Scene::Show()
{
	//DebugLog
	std::cout << "Scene Show:" << name << std::endl;
	isVisible = true;
}

/*
* シーンを非表示にする.
*/
void Scene::Hide()
{
	//DebugLog
	std::cout << "Scene Hide:" << name << std::endl;

	isVisible = false;
}

/*
* シーン名を取得する 
*
* @return シーン名
*/
const std::string& Scene::Name()const
{
	return name;
}

/*
* シーンの活動状態を調べる
*
* @reutrn value true: 活動状態
* @return value false: 停止状態
*/
bool Scene::IsActive()const
{
	return isActive;
}

/*
* シーンの描画状態を調べる
*
* @return value true 表示状態
* @return value false 非表示状態
*/
bool Scene::IsVisible()const
{
	return isVisible;
}