//file BufferObject.h

#ifndef BUFFEROJECT_H_INCLUDED
#define BUFFEROJECT_H_INCLUDED

#include <GL/glew.h>

/*
* �ėp�o�b�t�@�I�u�W�F�N�g(VBO ,IBO��)
*/
class BufferObject
{
public:
	//Default Functions
	BufferObject() = default;
	~BufferObject() { Destroy(); }
	BufferObject(const BufferObject&)=delete;
	BufferObject& operator=(const BufferObject&) = delete;

	//pblic Functions
	bool Create(GLenum target,GLsizeiptr size,const GLvoid* data=nullptr,GLenum usage = GL_STATIC_DRAW);
	bool BufferSubData(GLintptr offset, GLsizeiptr size,const GLvoid* data);
	void Destroy();								///�I������
	GLuint Id()const { return id; }				///Id�擾.
	GLsizeiptr Size()const { return size; }		///�f�[�^�T�C�Y�擾.

private:
	GLenum target = 0;		//�o�b�t�@�̎��
	GLuint id = 0;			//�Ǘ�ID
	GLsizeiptr size = 0;	//�o�b�t�@�̃o�C�g�T�C�Y.
};//class BufferObject



/*
* VAO�p.
*/
class VertexArrayObject
{
public:
	//DefaultFunctions
	VertexArrayObject() = default; //�R���X�g���N�^
	~VertexArrayObject() { Destroy(); } //�f�X�g���N�^
	VertexArrayObject(const VertexArrayObject&) = delete; //�R�s�[������Z�q
	VertexArrayObject& operator=(const VertexArrayObject&) = delete; //=�I�y���[�^�[�̔j��

	//Public functions
	bool Create(GLuint vbo,GLuint ibo); //�쐬
	void Destroy(); //�폜
	void ResetVertexAttribPointer()const; //�S�Ă̒��_�𖳌���
	void Bind()const; //���蓖��
	void Unbind()const; //���蓖�ĉ���
	//
	void VertexAttribPointer(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,size_t offset)const;
	GLuint Id()const { return id; } //ID�擾
	GLuint Vbo()const { return vboId; } //VBO�̎擾
	GLuint Ibo()const { return iboId; } //IBO�̎擾

private:
	GLuint id = 0;		//�Ǘ�id
	GLuint vboId = 0;	//vbo id
	GLuint iboId = 0;	//ibo id

};//class VertexArrayObject

#endif // !BUFFEROJECT_H_INCLUDED
