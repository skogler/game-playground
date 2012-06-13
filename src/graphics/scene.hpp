#ifndef SCENE_INC
#define SCENE_INC
#include <list>
#include <string>
using namespace std;
#include "camera.hpp"
#include "mesh.hpp"
#include "renderedentity.hpp"

class Scene
{
public:
	explicit Scene(Camera * camera);
	virtual ~Scene();
	void render() const;

	inline std::list<RenderedEntity*>& getEntities()
		{
			return entities;
		}

private:

	Camera * camera;
	std::string name;
	std::list<RenderedEntity *> entities;

	GLuint modelMatrix;
	GLuint viewMatrix;
	GLuint projectionMatrix;


};

#endif /* end of include guard: SCENE_INC */
