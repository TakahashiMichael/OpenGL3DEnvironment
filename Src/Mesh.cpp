// @file Mesh.cpp

#define NOMINMAX
#include "Mesh.h"
#include "SkeletalMesh.h"
#include "json11.hpp"
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
		if (!vbo.Create(GL_ARRAY_BUFFER,vboSize)) {
			return false;
		}
		if (!ibo.Create(GL_ELEMENT_ARRAY_BUFFER,iboSize)) {
			return false;
		}


		return true;
	}

}//namespace Mesh.