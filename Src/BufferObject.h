//file BufferObject.h

#ifndef BUFFEROJECT_H_INCLUDED
#define BUFFEROJECT_H_INCLUDED

#include <GL/glew.h>

/*
* 汎用バッファオブジェクト(VBO ,IBO等)
*/
class BufferObject
{
public:
	BufferObject() = default;
	~BufferObject() { Destroy(); }
	BufferObject(const BufferObject&)=delete;
	BufferObject& operator=(const BufferObject&) = delete;

	bool Create(GLenum target,GLsizeiptr size,const GLvoid* data=nullptr,GLenum usage = GL_STATIC_DRAW);
	bool BufferSubData(GLintptr offset, GLsizeiptr size,const GLvoid* data);
	void Destroy();
	GLuint Id()const { return id; }
	GLsizeiptr Size()const { return size; }

private:
	GLenum target = 0;		//バッファの種類
	GLuint id = 0;			//管理ID
	GLsizeiptr size = 0;	//バッファのバイトサイズ.
};

/*
* VAO用.
*/
class VertexArrayObject
{
public:
	VertexArrayObject() = default; //コンストラクタ
	~VertexArrayObject() { Destroy(); } //デストラクタ
	VertexArrayObject(const VertexArrayObject&) = delete; //コピー代入演算子
	VertexArrayObject& operator=(const VertexArrayObject&) = delete; //=オペレーターの破棄

	bool Create(GLuint vbo,GLuint ibo); //作成
	void Destroy(); //削除
	void ResetVertexAttribPointer()const; //全ての頂点を無効化
	void Bind()const; //割り当て
	void Unbind()const; //割り当て解除
	//
	void VertexAttribPointer(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,size_t offset)const;
	GLuint Id()const { return id; } //ID取得
	GLuint Vbo()const { return vboId; } //VBOの取得
	GLuint Ibo()const { return iboId; } //IBOの取得

private:
	GLuint id = 0;		//管理id
	GLuint vboId = 0;	//vbo id
	GLuint iboId = 0;	//ibo id
};

#endif // !BUFFEROJECT_H_INCLUDED
