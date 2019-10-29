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
* �r�b�g�}�b�v�t�H���g�`��class
*/
class FontRenderer
{
public:
	FontRenderer() = default;
	~FontRenderer() = default;
	FontRenderer(const FontRenderer&) = delete;//�R�s�[�R���X�g���N�^
	FontRenderer& operator=(const FontRenderer&) = delete;//�R�s�[������Z�q
	//�R�s�[�����Ɗ댯�ȃf�[�^�������N���X�ł�
	//�R�s�[�֎~�����Ă����Ɨǂ�

	bool Init(size_t maxChar);							//������
	bool LoadFromFile(const char* path);				//�e�N�X�`���̓ǂݍ���
	void BeginUpdate();									//�����̒ǉ����J�n
	bool AddString(const glm::vec2&, const wchar_t*);	//������ǉ�
	void EndUpdate();									//�ǉ����I��
	void Draw(const glm::vec2&)const;					//�`��
	float LineHeight()const;							//�t�H���g�̍�����Ԃ�

private:
	SpriteRenderer spriteRenderer;
	std::vector<Texture::Image2DPtr>textures;
	float lineHeight = 0;
	float base = 0;

	///�������
	struct CharacterInfo
	{
		int id = -1;
		int page = 0;
		glm::vec2 uv = glm::vec2(0);
		glm::vec2 size = glm::vec2(0);
		glm::vec2 offset = glm::vec2(0);
		float xadvance = 0;
	};

	std::vector<CharacterInfo> characterInfoList;///<�������̃��X�g.

};


#endif // !FONT_H_INCLUDED
