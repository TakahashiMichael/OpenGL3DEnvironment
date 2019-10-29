/**
* @file Shader.h
*/
#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <memory>

//struct Mesh

namespace Shader {

	class Program;
	using ProgramPtr = std::shared_ptr<Program>;

GLuint Build(const GLchar* vsCode, const GLchar* fsCode);
GLuint BuildFromFile(const char* vsPath, const char* fsPath);


/**
* �V�F�[�_�[�E�v���O����.
*/
class Program
{
public:
  Program();
  static ProgramPtr Create(const char* vsPath,const char*fsPath);
  explicit Program(GLuint programId);
  ~Program();

  void Reset(GLuint programId);
  bool IsNull() const;
  void Use();
  void BindVertexArray(GLuint);
  void BindTexture(GLuint, GLuint);

  void SetViewProjectionMatrix(const glm::mat4&);
  //void Draw(const Mesh&, const glm::vec3& t, const glm::vec3& r, const glm::vec3& s);
  //�X�v���C�g�̃e�N�X�`�����W�̍s����V�F�[�_�[�ɑ��M����
  void SetTextureMatrix(const glm::mat4&);

  //2d�̃J���[��ݒ肷��.
  void SetUniColor(const glm::vec4);


  void SetModelMatrix(const glm::mat4&);

  void SetPointLightIndex(int count, const int* indexList);
  void SetSpotLightIndex(int count, const int* indexList);

  ///�v���O����ID���擾����.
  GLuint Get() const { return id; }

private:
  GLuint id = 0; // �v���O����ID.

  // uniform�ϐ��̈ʒu.
  GLint locMatMVP = -1;
  GLint locMatModel = -1;

  //scale�ɂ���Ẵ��C�g�̕ω���
  GLint locModelScale = -1;

  GLint locPointLightCount = -1;
  GLint locPointLightIndex = -1;
  GLint locSpotLightCount = -1;
  GLint locSpotLightIndex = -1;

  GLint locMatTextur = -1;
  GLint locUniColor = -1;

  glm::mat4 matVP = glm::mat4(1);
 
};

} // namespace Shader

#endif // SHADER_H_INCLUDED
