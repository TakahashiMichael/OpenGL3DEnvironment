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
}

/*
* �f�X�g���N�^/
*/
Scene::~Scene()
{
	//�f�X�g���N�^�ŌĂ΂���`�̓t�@�C�i���C�Y�֐��ɋL������
	Finalize();
}

/*
* �V�[�����������҂ɂ���
*/
void Scene::Play() 
{
	isActive = true;
}

/*
* �V�[�����~��Ԃɂ���.
*/
void Scene::Stop()
{
	isActive = false;
}

/*
* �V�[����\������.
*/
void Scene::Show()
{
	isVisible = true;
}

/*
* �V�[�����\���ɂ���.
*/
void Scene::Hide()
{
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