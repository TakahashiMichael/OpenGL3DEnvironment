// @file Scene.h


/*
* �V�[���N���X�̃x�[�X�@�\
* �X�^�b�N�T�O�̊w�K�p
*/

//Include Guard.
#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

//HeaderInclude 
#include <memory>
#include <string>

//�O���錾
class SceneStack;

/*
* �V�[���̊��N���X
*/
class Scene {
public:
	//�f�t�H���g�֐��̐���
	Scene(const char* name);
	Scene(const Scene&) = delete;//�R�s�[�R���X�g���N�^�폜
	Scene& operator=(const Scene&) = delete;//�R�s�[������Z�q�폜
	virtual ~Scene();

	/*�����֐��ꗗ
	* Initialize	:������
	* ProcessInput	:���͏���
	* Update		:�X�V
	* Render		:�`��
	* Finalize		:�I������
	*/

	 virtual bool Initialize()=0{}
	 virtual void ProcessInput()=0{}
	 virtual void Update(float)=0{}
	 virtual void Render()=0{}
	 virtual void Finalize()=0{}

	 virtual void Play();
	 virtual void Stop();
	 virtual void Show();
	 virtual void Hide();

	 const std::string& Name() const;
	 bool IsActive()const;
	 bool IsVisible()const;



private:
	std::string name;
	bool isActive = true;
	bool isVisible = true;

};

//�|�C���^�^�̖��O���Ē�`
using ScenePtr = std::shared_ptr<Scene>;




#endif //SCENE_H_INCLUDED