#include <Windows.h>

#include "Sound.h"
#include "GLFWEW.h"
#include "TitleScene.h"
#include "SkeletalMesh.h"
#include <iostream>

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}


int main()
{
	//�T�E���h�̃V�X�e���̏�����
	if (!Sound::EngineInitialize())
	{
		std::cerr << "�T�E���h�̏������Ɏ��s" << std::endl;
		return 1;
	}

	GLFWEW::Window& window = GLFWEW::Window::Instance();
	window.Init(1280,720,u8"�A�N�V�����Q�[��");

	//�X�P���^���A�j���[�V�����𗘗p�\�ɂ���.
	Mesh::SkeletalAnimation::Initialize();

	SceneStack& sceneStack = SceneStack::Instance();
	sceneStack.Push(std::make_shared<TitleScene>());


		while (!window.ShouldClose()) {

			window.Update();

			//ESC�L�[�������ꂽ��I���E�B���h�E��\��.
			if (window.IsKeyPressed(GLFW_KEY_ESCAPE)) {
				if (MessageBox(nullptr, "�Q�[�����I�����܂���?", "�I��", MB_OKCANCEL) == IDOK) {
					break;
				}
			}

			//�X�P���^���E�A�j���[�V�����p�̃f�[�^�̍쐬����.
			Mesh::SkeletalAnimation::ResetUniformData();

			const float deltaTime = static_cast<float>(window.DeltaTime());
			sceneStack.Update(deltaTime);

			//�X�P���^���E�A�j���[�V�����p�f�[�^��GPU�������ɓ]��.
			Mesh::SkeletalAnimation::UploadUniformData();

			//�o�b�N�o�b�t�@����������
			glClearColor(0.8f, 0.2f, 0.1f, 0.1f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//GL�R���e�L�X�g�̃p�����[�^��ݒ�.
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);

			sceneStack.Render();

			window.SwapBuffers();
			Sound::EngineUpdate(deltaTime);
		}
		//�X�P���^���E�A�j���[�V�����̗��p���I������.
		Mesh::SkeletalAnimation::Finalize();

	return 0;
}