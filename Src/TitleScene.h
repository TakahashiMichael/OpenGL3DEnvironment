//@file Title Scene.h

//Include Guard
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED




//Include Header
#include "Scene.h"

//Define TitleScene class
/*
* タイトル画面
*/
class TitleScene : public Scene
{
public:
	//デフォルトコンストラクタを派生クラスで設定する
	TitleScene() : Scene("TitleScene") {}
	virtual ~TitleScene() = default;

	virtual bool Initialize()override { return true; }
	virtual void ProcessInput()override;
	virtual void Update(float)override{}
	virtual void Render()override{}
	virtual void Finalize()override{}

};//class TitleScene




#endif // !TITLESCENE_H_INCLUDED
