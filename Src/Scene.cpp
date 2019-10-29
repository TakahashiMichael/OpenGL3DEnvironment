//Scene.cpp

#include "Scene.h"
#include <iostream>

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