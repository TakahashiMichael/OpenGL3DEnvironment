// @file Mesh.h

#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <GL/glew.h>
#include "BufferObject.h"
#include "Texture.h"
#include "Shader.h"
#include "json11.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

namespace Mesh {
	//先行宣言.
	struct Mesh;
	using MeshPtr = std::shared_ptr<Mesh>;
	class Buffer;
	using BufferPtr = std::shared_ptr<Buffer>;

	/*
	* 頂点データ.
	*/
	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 texCoord;
		glm::vec3 normal;
	};

	/*
	* プリミティブの材質.
	*/
	struct Material
	{
		glm::vec4 baseColor = glm::vec4(1);
		Texture::Image2DPtr texture;
		Shader::ProgramPtr program;
	};

	/*
	* 頂点データの描パラメータ.
	*/
	struct Primitive
	{
		GLenum mode;							///type
		GLsizei count;							///size
		GLenum type;							///type
		const GLvoid* indices;					///indices
		GLint baseVertex = 0;					///vertex
		std::shared_ptr<VertexArrayObject>vao;	///vao
		int material = 0;						///material
	};

	/*
	* メッシュ.
	*/
	struct Mesh
	{
		std::string name;//メッシュ名.
		std::vector<Primitive> primitives;
	};


	/*
	* ファイルクラス
	*/
	struct File
	{
		std::string name;//ファイル名.
		std::vector<Mesh> meshes;
		std::vector<Material> materials;
	};
	using FilePtr = std::shared_ptr<File>;

	/*
	* メッシュ管理クラス.
	*/
	class Buffer
	{
	public:
		Buffer() = default;
		~Buffer() = default;

		bool Init(GLsizeiptr vboSize,GLsizeiptr iboSize);
		GLintptr AddVertexData(const void* data,size_t size);
		GLintptr AddIndexData(const void* data, size_t size);
		Primitive CreatePriitive(
			size_t const,GLenum type,size_t iOffset,size_t vOffset)const;
		Material CreateMaterial(const glm::vec4& color,Texture::Image2DPtr texture)const;
		bool AddMesh(const char* name,const Primitive& primitive,const Material& material);
		FilePtr GetFile(const char* name)const;

	private:
		BufferObject vbo;	//描画用vbo
		BufferObject ibo;	//描画用ibo
		GLintptr vboEnd = 0;
		GLintptr iboEnd = 0;
		std::unordered_map<std::string, FilePtr> files;
		Shader::ProgramPtr progStaticMesh;
	};


}// namespace Mesh


#endif // !MESH_H_INCLUDED
