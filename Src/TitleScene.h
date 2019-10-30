//@file Title Scene.h

//Include Guard
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED




//Include Header
#include "Scene.h"
#include "Sprite.h"
#include <vector>

//Define TitleScene class
/*
* �^�C�g�����
*/
class TitleScene : public Scene
{
public:
	//�f�t�H���g�R���X�g���N�^��h���N���X�Őݒ肷��
	TitleScene() : Scene("TitleScene") {}
	virtual ~TitleScene() = default;

	virtual bool Initialize()override;
	virtual void ProcessInput()override;
	virtual void Update(float)override;
	virtual void Render()override;
	virtual void Finalize()override{}

private:
	std::vector<Sprite> sprites;
	SpriteRenderer spriteRenderer;

};//class TitleScene




#endif // !TITLESCENE_H_INCLUDED
