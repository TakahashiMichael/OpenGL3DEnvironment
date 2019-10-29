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
}

/*
* デストラクタ/
*/
Scene::~Scene()
{
	//デストラクタで呼ばれる定義はファイナライズ関数に記入する
	Finalize();
}

/*
* シーンを活動招待にする
*/
void Scene::Play() 
{
	isActive = true;
}

/*
* シーンを停止状態にする.
*/
void Scene::Stop()
{
	isActive = false;
}

/*
* シーンを表示する.
*/
void Scene::Show()
{
	isVisible = true;
}

/*
* シーンを非表示にする.
*/
void Scene::Hide()
{
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