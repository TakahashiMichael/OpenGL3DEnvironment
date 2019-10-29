// @file Scene.h


/*
* シーンクラスのベース機能
* スタック概念の学習用
*/

//Include Guard.
#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

//HeaderInclude 
#include <memory>
#include <string>

//前方宣言
class SceneStack;

/*
* シーンの基底クラス
*/
class Scene {
public:
	//デフォルト関数の制御
	Scene(const char* name);
	Scene(const Scene&) = delete;//コピーコンストラクタ削除
	Scene& operator=(const Scene&) = delete;//コピー代入演算子削除
	virtual ~Scene();

	/*純粋関数一覧
	* Initialize	:初期化
	* ProcessInput	:入力処理
	* Update		:更新
	* Render		:描画
	* Finalize		:終了処理
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

//ポインタ型の名前を再定義
using ScenePtr = std::shared_ptr<Scene>;




#endif //SCENE_H_INCLUDED