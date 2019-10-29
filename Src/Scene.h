// @file Scene.h

#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <memory>
#include <string>
#include <vector>

class SceneStack;

/*
* �V�[�����N���X
*/
class Scene {
public:
	Scene(const char* name);//�R���X�g���N�^
	Scene(const Scene&) = delete; //�R�s�[�R���X�g���N�^
	Scene& operator=(const Scene&) = delete; //�R�s�[������Z�q
	virtual ~Scene(); //�f�X�g���N�^

	virtual bool Initialize() = 0 {}
	virtual void ProcessInput() = 0 {}
	virtual void Update(float) = 0 {}
	virtual void Render() = 0 {}
	virtual void Finalize() =0{}

	virtual void Play();
	virtual void Stop();
	virtual void Show();
	virtual void Hide();

	const std::string& Name()const; //�ϐ���getter
	bool IsActive() const;  //�ϐ���getter
	bool IsVisible() const; //�ϐ���getter

private:
	std::string name;
	bool isVisible = true; //���Ɏg�����킩��Ȃ�
	bool isActive = true; //�A�N�e�B�u���ǂ���

};
using ScenePtr = std::shared_ptr<Scene>; //�ʖ��𐶐�


/*
* �V�[���Ǘ��N���X
*/
class SceneStack
{
public:
	static SceneStack& Instance();

	void Push(ScenePtr);
	void Pop();
	void Replace(ScenePtr);
	Scene& Current();
	const Scene& Current() const;
	size_t Size() const;
	bool Empty() const;

	void Update(float);
	void Render();

private:
	SceneStack();
	SceneStack(const SceneStack&) = delete;
	SceneStack& operator=(const SceneStack&) = delete;
	~SceneStack() = default;

	std::vector<ScenePtr> stack;
};



#endif //SCENE_H_INCLUDED