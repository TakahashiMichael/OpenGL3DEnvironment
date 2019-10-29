// @file Sprite.h

#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "BufferObject.h"
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <vector>

/*
* �Z�a�\����.
*/
struct Rect
{
	glm::vec2 origin;	///<�������_
	glm::vec2 size;		///<�c���̕�
};

/*
* �X�v���C�g�N���X
*/
class Sprite
{
public:
	Sprite() = default;
	explicit Sprite(const Texture::Image2DPtr&);
	~Sprite() = default;
	Sprite(const Sprite&) = default;
	Sprite& operator=(const Sprite&) = default;
	
	//���W
	void Position(const glm::vec3& pos) { position = pos; }
	const glm::vec3& Position()const { return position; }
	//�g�嗦
	void Scale(const glm::vec2& sca) { scale = sca; }
	const glm::vec2& Scale()const { return scale; }
	//��]
	void Rotation(const float rota) { rotation = rota; }
	float Rotation()const { return rotation; }
	//�F
	void Color(const glm::vec4& col) { color = col; }
	const glm::vec4& Color()const { return color; }
	//��`
	void Rectangle(const Rect& rec) { rect = rec; }
	const Rect& Rectangle()const { return rect; }
	//�e�N�X�`��
	void Texture(const Texture::Image2DPtr& tex);
	const Texture::Image2DPtr& Texture()const { return texture; }


private:
	glm::vec3 position = glm::vec3(0);
	glm::f32 rotation = 0;
	glm::vec2 scale = glm::vec2(1);
	glm::vec4 color = glm::vec4(1);
	Rect rect = { glm::vec2(0,0),glm::vec2(1,1) };
	Texture::Image2DPtr texture;



};//class Sprite

/*
* �X�v���C�g�`��N���X
*
*/
class SpriteRenderer
{
public:
	//default functions
	SpriteRenderer() = default;
	~SpriteRenderer() = default;
	SpriteRenderer(const SpriteRenderer&) = delete;
	SpriteRenderer& operator=(const SpriteRenderer&) = delete;

	//Public functions
	bool Init(size_t maxSpriteCount,const char* vsPath,const char* fsPath);
	void BeginUpdate();
	bool AddVertices(const Sprite&);
	void EndUpdate();
	void Draw(const glm::vec2&)const;
	void Clear();

private:
	BufferObject vbo;
	BufferObject ibo;
	VertexArrayObject vao;
	Shader::ProgramPtr program;
	
	struct Vertex
	{
		glm::vec3 position;		///<���W
		glm::vec4 color;		///<�F
		glm::vec2 texCoord;		///<�e�N�X�`�����W
	};
	std::vector<Vertex> vertices;//���_�f�[�^�z��.

	//�v���~�e�B�u�^
	struct Primitive{
		size_t count;
		size_t offset;
		Texture::Image2DPtr texture;
	};
	std::vector<Primitive>primitives;
};//class SpriteRenderer


#endif // !SPRITE_H_INCLUDED
