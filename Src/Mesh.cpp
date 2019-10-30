// @file Mesh.cpp

#define NOMINMAX
#include "Mesh.h"
#include "SkeletalMesh.h"
#include "json11.hpp"
#include "Filename.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <fstream>
#include <algorithm>
#include <iostream>

/*
* メッシュに関する機能を格納する名前空間.
*/
namespace Mesh {

	/*
	* メッシュバッファを初期化する
	*
	* @param vboSize VBOのバイトサイズ.
	* @param iboSize IBOのバイトサイズ.
	*
	* @retrun value true :初期化成功.
	* @return value false :初期化失敗.
	*/
	bool Buffer::Init(GLsizeiptr vboSize ,GLsizeiptr iboSize)
	{
		/*各オブジェクトを作成*/
		if (!vbo.Create(GL_ARRAY_BUFFER,vboSize)) {
			return false;
		}
		if (!ibo.Create(GL_ELEMENT_ARRAY_BUFFER,iboSize)) {
			return false;
		}
		progStaticMesh = Shader::Program::Create(FILENAME_SHADER_VERT_STATICMESH,FILENAME_SHADER_FRAG_STATICMESH);
		if (progStaticMesh->IsNull()) {
			return false;
		}

		vboEnd = 0;
		iboEnd = 0;
		files.reserve(100);

		AddCube("Cube");

		return true;
	}//func Mesh::Buffer::Init


	/*
	* 頂点データを追加する.
	*
	* @param data Pointer to the data to add;
	* @param size Number of bytes of data to add
	*
	* @return データを追加した位置.
	*			CreatePrimitiveのvOffset パラメータとして使用する
	*/
	GLintptr Buffer::AddVertexData(const void* data,size_t size)
	{
		vbo.BufferSubData(vboEnd, size, data);
		const GLintptr tmp = vboEnd;
		vboEnd += size;
		return tmp;
	}

	/*
	* Add index data
	*
	* @param data : pointer to the data to add;
	* @param size : nomber of bytes of data to add 
	*
	* return データを追加した位置.
	*			プリミティブのindices パラメータとして使うことが出来る.
	*/
	GLintptr Buffer::AddIndexData(const void* data,size_t size)
	{
		ibo.BufferSubData(iboEnd,size,data);
		const GLintptr tmp = iboEnd;
		iboEnd += size;
		return tmp;
	}

	/*
	* Create Primitives
	*
	* @param count	: Number of primitive index data
	* @param type	: Index data type
	* @param iOffset :StartPosition  
	* @param vOffset :StartPosition 
	*
	* @return  :Created Primitive struct
	*/
	Primitive Buffer::CreatePriitive(
		size_t count ,GLenum type ,size_t iOffset ,size_t vOffset)const
	{
		// プリミティブ用のVAOを作成.
		std::shared_ptr<VertexArrayObject> vao = std::make_shared<VertexArrayObject>();
		vao->Create(vbo.Id(), ibo.Id());
		vao->Bind();
		vao->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			vOffset + offsetof(Vertex, position));
		vao->VertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			vOffset + offsetof(Vertex, texCoord));
		vao->VertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			vOffset + offsetof(Vertex, normal));
		vao->Unbind();
		
		// プリミティブのメンバ変数を設定.
		Primitive p;
		p.mode = GL_TRIANGLES;
		p.count = static_cast<GLsizei>(count);
		p.type = type;
		p.indices = reinterpret_cast<const GLvoid*>(iOffset);
		p.baseVertex = 0;
		p.vao = vao;
		p.material = 0; // マテリアルは0番で固定.
		
		return p;
	}

	/*
	* CreateMaterial
	*
	* @param color		: Base Color of the material
	* @param texture	: Material Texture
	*
	* @return : Create material structure
	*/
	Material Buffer::CreateMaterial(
		const glm::vec4& color,Texture::Image2DPtr texture)const
	{
		Material mater;
		mater.baseColor = color;
		mater.texture = texture;
		mater.program = progStaticMesh;

		return mater;
	}//func Buffer::CreateMaterial

	/*
	* Add Mesh
	*
	* @param name
	* @param primitive
	* @param material
	*
	* @return true : Addition success
	* @return false ; Addition failure
	*/
	bool Buffer::AddMesh(
		const char* name,const Primitive& primitive,const Material& material)
	{
		if (files.find(name) != files.end()) {
			std::cerr << "[Warning]funcname=" << __func__ << ",Name already added, name of=" << name << std::endl;
			return false;
		}

		FilePtr fp = std::make_shared<File>();
		fp->name = name;
		fp->materials.push_back(material);
		fp->meshes.resize(1);
		fp->meshes[0].name = name;
		fp->meshes[0].primitives.push_back(primitive);

		files.insert(std::make_pair(fp->name, fp));
		std::cout<< "[Information] Added mesh : func name = "<<__func__<< ":Added mesh name=" <<name <<std::endl;
		return true;
	}//func Mesh::Buffer::AddMesh

	/*
	* ファイルを取得する
	*
	* @param name : The name of the file you want to get
	*
	* @return : mesh with the same name as "name"
	*/
	FilePtr Buffer::GetFile(const char* name)const
	{
		const auto itr = files.find(name);
		if (itr == files.end()) {
			std::cerr<<"[Warning] Func is"<<__func__<<",No mesh with this name is registered. name is"<< name<<std::endl;
			static FilePtr empty = std::make_shared<File>();
			return empty;
		}
		return itr->second;

	}//func Mesh::Buffer::GetFile

	/*
	* Add Cube
	*
	* @param name : Name of cube
	*/
	void Buffer::AddCube(const char* name)
	{
		//    6---7      +Y -Z
		//   /|  /|       |/
		//  / 5-/-4  -X --*-- +X
		// 3---2 /       /|
		// |/  |/     +Z -Y
		// 0---1
		const glm::vec3 basePositions[] = {
		{-1,-1, 1}, { 1,-1, 1}, { 1, 1, 1}, {-1, 1, 1},
		{ 1,-1,-1}, {-1,-1,-1}, {-1, 1,-1}, { 1, 1,-1},
		};
		const glm::vec2 baseTexCoords[] = { { 0, 1}, { 0, 0}, { 1, 0}, { 1, 1} };
		const glm::vec3 normals[] = {
		{ 0, 0, 1}, { 1, 0, 0}, { 0, 0,-1}, {-1, 0, 0},
		{ 0, -1, 0}, { 0, 1, 0} };
		const int planes[6][4] = {
		{ 0, 1, 2, 3}, { 1, 4, 7, 2}, { 4, 5, 6, 7}, { 5, 0, 3, 6},
		{ 5, 4, 1, 0}, { 3, 2, 7, 6} };
		const GLubyte baseIndices[] = { 0, 1, 2, 2, 3, 0 };
		
		std::vector<Vertex> vertices;
		vertices.reserve(4 * 6);
		std::vector<GLubyte> indices;
		indices.reserve(6 * 6);
		//Create vertex data and index data
		for (size_t plane = 0; plane < 6; ++plane) {
			for (size_t i = 0; i < 4; ++i) {
				Vertex v;
				v.position = basePositions[planes[plane][i]];
				v.texCoord = baseTexCoords[i];
				v.normal = normals[plane];
				vertices.push_back(v);
				
			}
			for (size_t i = 0; i < 6; ++i) {
				indices.push_back(static_cast<GLubyte>(baseIndices[i] + (plane * 4)));
				
			}
			
		}

		//Add mesh
		const size_t vOffset =
			AddVertexData(vertices.data(), vertices.size() * sizeof(Vertex));
		const size_t iOffset =
			AddIndexData(indices.data(), indices.size() * sizeof(GLubyte));
		const Primitive p =
			CreatePriitive(indices.size(), GL_UNSIGNED_BYTE, iOffset, vOffset);
		const Material m = CreateMaterial(glm::vec4(1), nullptr);
		AddMesh(name, p, m);

	}//AddCube


	/*
	* Draw mesh
	*
	* @param file	: File to draw
	* @param matVP	: View Projection Matrix to use for drawing
	* @param matM	: Model Matrix to use for drawing
	*/
	void Draw(const FilePtr& file, const glm::mat4& matVP, const glm::mat4& matM) {
		if (!file || file->meshes.empty() || file->materials.empty()) {
			return;
		}

		const Mesh& mesh = file->meshes[0];
		for (const Primitive& p : mesh.primitives) {
			p.vao->Bind();
			const Material& m = file->materials[p.material];
			m.program->Use();
			m.program->SetViewProjectionMatrix(matVP);
			m.program->SetModelMatrix(matM);
			glActiveTexture(GL_TEXTURE0);

			//
			if (m.texture) {
				glBindTexture(GL_TEXTURE_2D,m.texture->Get());
			}else {
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			glDrawElementsBaseVertex(p.mode,p.count,p.type,p.indices,p.baseVertex);
			p.vao->Unbind();
		}
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,0);
		glUseProgram(0);
	}
	

}//namespace Mesh.