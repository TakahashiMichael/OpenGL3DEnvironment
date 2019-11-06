//MainGameScene.h

#ifndef MAINGAMESCENE_H_INCLUDED
#define MAINGAMESCENE_H_INCLUDED

#include "Scene.h"
#include "Mesh.h"
#include "Terrain.h"

/*
* ÉÅÉCÉìÉQÅ[ÉÄâÊñ 
*/
class MainGameScene : public Scene
{
public:
	MainGameScene() :Scene("MainGameScene") {}
	virtual ~MainGameScene() = default;

	virtual bool Initialize()override;
	virtual void ProcessInput()override;
	virtual void Update(float)override;
	virtual void Render()override;
	virtual void Finalize()override {}

private:
	bool flag =false;
	Mesh::Buffer meshBuffer;
	Terrain::HeightMap heightMap;


	struct Camera {
		glm::vec3 target = glm::vec3(100.0f, 0.0f, 100.0f);
		glm::vec3 position = glm::vec3(100.0f, 50.0f, 150.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 velocity = glm::vec3(0);

	};//struct Camera

	Camera camera;
};//class MainGameScene



#endif // !MAINGAMESCENE_H_INCLUDED
