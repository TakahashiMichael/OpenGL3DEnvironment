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
* ���b�V���Ɋւ���@�\���i�[���閼�O���.
*/
namespace Mesh {

	/*
	* ���b�V���o�b�t�@������������
	*
	* @param vboSize VBO�̃o�C�g�T�C�Y.
	* @param iboSize IBO�̃o�C�g�T�C�Y.
	*
	* @retrun value true :����������.
	* @return value false :���������s.
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