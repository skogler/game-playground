#ifndef SCENE_INC
#define SCENE_INC

#include <list>
#include <string>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "camera.hpp"
#include "mesh.hpp"
#include "renderedentity.hpp"

class Scene
{
public:
	explicit Scene(Camera * camera);
	virtual ~Scene();

	void render() const;

	inline std::list< boost::shared_ptr<RenderedEntity> >& getEntities()
	{
		return entities;
	}

private:
	boost::scoped_ptr<Camera> camera;
	std::string name;
	std::list< boost::shared_ptr<RenderedEntity> > entities;

	GLuint modelMatrix;
	GLuint viewMatrix;
	GLuint projectionMatrix;
};

#endif /* end of include guard: SCENE_INC */
