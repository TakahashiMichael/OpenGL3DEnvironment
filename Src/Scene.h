// @file Scene.h

#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <memory>
#include <string>
#include <vector>

class SceneStack;

/*
* シーン基底クラス
*/
class Scene {
public:
	Scene(const char* name);//コンストラクタ
	Scene(const Scene&) = delete; //コピーコンストラクタ
	Scene& operator=(const Scene&) = delete; //コピー代入演算子
	virtual ~Scene(); //デストラクタ

	virtual bool Initialize() = 0 {}
	virtual void ProcessInput() = 0 {}
	virtual void Update(float) = 0 {}
	virtual void Render() = 0 {}
	virtual void Finalize() =0{}

	virtual void Play();
	virtual void Stop();
	virtual void Show();
	virtual void Hide();

	const std::string& Name()const; //変数のgetter
	bool IsActive() const;  //変数のgetter
	bool IsVisible() const; //変数のgetter

private:
	std::string name;
	bool isVisible = true; //何に使うかわからない
	bool isActive = true; //アクティブかどうか

};
using ScenePtr = std::shared_ptr<Scene>; //別名を生成


/*
* シーン管理クラス
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