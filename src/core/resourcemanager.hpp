#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <string>
#include <list>
#include <map>
#include <boost/shared_ptr.hpp>

#include "../graphics/resources/shader.hpp"
#include "../graphics/resources/texture.hpp"
#include "../graphics/resources/terrain.hpp"
#include "../graphics/resources/mesh.hpp"
#include "../graphics/resources/material.hpp"

class ResourceManager
{
public:
	ResourceManager(const std::string & resourceDirectory);
	virtual ~ResourceManager();

	void setResourceDirectory(const std::string & resourceDirectory);

	boost::shared_ptr<Shader> getShader(const std::string & name);
	boost::shared_ptr<Texture> getTexture(const std::string & name);
	boost::shared_ptr<Terrain> getTerrain(const std::string & name);
	boost::shared_ptr<Mesh> getMesh(const std::string & name);
	boost::shared_ptr<Material> getMaterial(const std::string & name);
protected:
	std::string resourceDirectory;


	std::map<std::string, boost::shared_ptr<Shader> > loadedShaders;
	std::map<std::string, boost::shared_ptr<Texture> > loadedTextures;
	std::map<std::string, boost::shared_ptr<Terrain> > loadedTerrains;
	std::map<std::string, boost::shared_ptr<Mesh> > loadedMeshes;
	std::map<std::string, boost::shared_ptr<Material> > loadedMaterials;
};

#endif /* RESOURCEMANAGER_HPP_ */
