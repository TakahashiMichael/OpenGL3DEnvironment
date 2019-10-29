//Scene.cpp

#include "Scene.h"
#include <iostream>


//▼ About Scene Stack Class ▼--------------------------------------------------------------------------------------
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
//▲ About Scene Class ▲--------------------------------------------------------------------------------------



//▼ About Scene Stack Class ▼--------------------------------------------------------------------------------------

/*
* シーンスタックを取得する.
*
* @return シーンスタック
*
*/
SceneStack& SceneStack::Instance()
{
	static SceneStack instance;
	return instance;
}

/*
* コンストラクタ.
*/
SceneStack::SceneStack()
{
	//シーン数の容量確保
	stack.reserve(16);
}


/*
* Push Scene
*
* @param ptr : new scene
*/
void SceneStack::Push(ScenePtr ptr) 
{
	//CurrentScene Stop
	if (!stack.empty()) {
		Current().Stop();
	}

	stack.push_back(ptr);
	//Debug log
	std::cout << "[Scene Push]:" << ptr->Name() << std::endl;

	//New scene initialize and play
	Current().Initialize();
	Current().Play();
}

/*
* Pop scene
*/
void SceneStack::Pop()
{
	if (stack.empty()) {
		std::cout << "[WARNING]:" << __func__ << ":SceneStack::Pop->Empty" << std::endl;
		return;
	}

	//Stop & Finalize
	Current().Stop();
	Current().Finalize();

	//String for displaying debug log
	const std::string popSceneName = Current().Name();
	stack.pop_back();
	//Debug: displaying popSceneName
	std::cout << "[Scene Pop]:"<<popSceneName << std::endl;

	//
	if (!stack.empty()) {
		Current().Play();
	}
}

/*
* Replace scene
*
* @param ptr : new scene
*/
void SceneStack::Replace(ScenePtr ptr)
{

	Pop();
	Push(ptr);
}

/*
* Get current scene
*
* @return current scene
*/
Scene& SceneStack::Current()
{
	return *stack.back();
}

/*
* Get current scene
*
* @return current scene
*/
const Scene& SceneStack::Current()const
{
	return *stack.back();
}

/*
* Find out if the stack of empty
*
* return value true: stack is empty
* return value false: One or more elements are stored in the stack
*/
bool SceneStack::Empty()const
{
	return stack.empty();
}

/*
* Update scenes
*
* @param deltaTime Elapsed time scene last update
*/
void SceneStack::Update(float deltaTime)
{
	//Process input for the current scene only
	if (!Empty()) {
		Current().ProcessInput();
	}
	//Update all active secens
	for (ScenePtr& e : stack) {
		if (e->IsActive()) {
			e->Update(deltaTime);
		}
	}
}

/*
* Render scene
*/
void SceneStack::Render(){
	for (ScenePtr& e : stack) {
		if (e->IsVisible) {
			e->Render();
		}
	}
}

//▲ About Scene Stack Class ▲--------------------------------------------------------------------------------------
