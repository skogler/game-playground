#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <string>
#include <boost/filesystem.hpp>

#include "resourcecache.hpp"
#include "resources/material.hpp"
#include "resources/mesh.hpp"
#include "resources/shader.hpp"
#include "resources/texture.hpp"

class ResourceManager
{
public:
	ResourceManager(const boost::filesystem::path & resourceDirectory);
	virtual ~ResourceManager();

	//Resource Caches
	ResourceCache<Texture> textureCache;
	ResourceCache<Shader> shaderCache;
	ResourceCache<Mesh> meshCache;
	ResourceCache<Material> materialCache;
};

#endif /* RESOURCEMANAGER_HPP_ */
