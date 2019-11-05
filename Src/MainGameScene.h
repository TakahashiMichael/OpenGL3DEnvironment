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
};//class MainGameScene

#endif // !MAINGAMESCENE_H_INCLUDED
