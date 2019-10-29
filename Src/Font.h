/*
* @font.h
*/
#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <GL/glew.h>
#include "Sprite.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>

/*
* ビットマップフォント描画class
*/
class FontRenderer
{
public:
	FontRenderer() = default;
	~FontRenderer() = default;
	FontRenderer(const FontRenderer&) = delete;//コピーコンストラクタ
	FontRenderer& operator=(const FontRenderer&) = delete;//コピー代入演算子
	//コピーされると危険なデータを扱うクラスでは
	//コピー禁止をしておくと良い

	bool Init(size_t maxChar);							//初期化
	bool LoadFromFile(const char* path);				//テクスチャの読み込み
	void BeginUpdate();									//文字の追加を開始
	bool AddString(const glm::vec2&, const wchar_t*);	//文字を追加
	void EndUpdate();									//追加を終了
	void Draw(const glm::vec2&)const;					//描画
	float LineHeight()const;							//フォントの高さを返す

private:
	SpriteRenderer spriteRenderer;
	std::vector<Texture::Image2DPtr>textures;
	float lineHeight = 0;
	float base = 0;

	///文字情報
	struct CharacterInfo
	{
		int id = -1;
		int page = 0;
		glm::vec2 uv = glm::vec2(0);
		glm::vec2 size = glm::vec2(0);
		glm::vec2 offset = glm::vec2(0);
		float xadvance = 0;
	};

	std::vector<CharacterInfo> characterInfoList;///<文字情報のリスト.

};


#endif // !FONT_H_INCLUDED
