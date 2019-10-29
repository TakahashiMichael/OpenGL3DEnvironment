//Scene.cpp

#include "Scene.h"
#include <iostream>


//�� About Scene Stack Class ��--------------------------------------------------------------------------------------
/*
* �R���X�g���N�^ 
*
* @param name: �V�[����
*/
Scene::Scene(const char* name) :name(name) 
{
	//DebugLog
	std::cout << "Scene constructer:" << name << std::endl;
}

/*
* �f�X�g���N�^/
*/
Scene::~Scene()
{
	
	//DebugLog
	std::cout << "Scene Destructer:" << name << std::endl;

	//�f�X�g���N�^�ŌĂ΂���`�̓t�@�C�i���C�Y�֐��ɋL������
	Finalize();
}

/*
* �V�[�����������҂ɂ���
*/
void Scene::Play() 
{
	//DebugLog
	std::cout << "Scene Play:" << name << std::endl;

	isActive = true;
}

/*
* �V�[�����~��Ԃɂ���.
*/
void Scene::Stop()
{
	//DebugLog
	std::cout << "Scene Stop:" << name << std::endl;
	isActive = false;
}

/*
* �V�[����\������.
*/
void Scene::Show()
{
	//DebugLog
	std::cout << "Scene Show:" << name << std::endl;
	isVisible = true;
}

/*
* �V�[�����\���ɂ���.
*/
void Scene::Hide()
{
	//DebugLog
	std::cout << "Scene Hide:" << name << std::endl;

	isVisible = false;
}

/*
* �V�[�������擾���� 
*
* @return �V�[����
*/
const std::string& Scene::Name()const
{
	return name;
}

/*
* �V�[���̊�����Ԃ𒲂ׂ�
*
* @reutrn value true: �������
* @return value false: ��~���
*/
bool Scene::IsActive()const
{
	return isActive;
}

/*
* �V�[���̕`���Ԃ𒲂ׂ�
*
* @return value true �\�����
* @return value false ��\�����
*/
bool Scene::IsVisible()const
{
	return isVisible;
}
//�� About Scene Class ��--------------------------------------------------------------------------------------



//�� About Scene Stack Class ��--------------------------------------------------------------------------------------

/*
* �V�[���X�^�b�N���擾����.
*
* @return �V�[���X�^�b�N
*
*/
SceneStack& SceneStack::Instance()
{
	static SceneStack instance;
	return instance;
}

/*
* �R���X�g���N�^.
*/
SceneStack::SceneStack()
{
	//�V�[�����̗e�ʊm��
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

//�� About Scene Stack Class ��--------------------------------------------------------------------------------------
