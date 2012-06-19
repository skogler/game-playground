#include "resourcemanager.hpp"

#include <map>
#include <boost/shared_ptr.hpp>
namespace fs = boost::filesystem;

ResourceManager::ResourceManager(const std::string & resourceDirectory) :
	resourceDirectory(resourceDirectory),
	shaderDir("shaders")
{
	if (!(fs::exists(this->resourceDirectory) && fs::is_directory(this->resourceDirectory)))
	{
		throw std::runtime_error("Invalid resource directory: " + resourceDirectory);
	}
	createResourceList();
}

ResourceManager::~ResourceManager()
{
}

/**
 * Create the list of resources by adding all files in
 * the resource directory. This should save some time
 * when loading resources since there is no disk access
 * needed to search for a file.
 */
void ResourceManager::createResourceList()
{
	resourceList.clear();
	for(fs::recursive_directory_iterator end, it(resourceDirectory);
			it != end; ++it)
	{
		fs::path item = *it;
		if(fs::is_regular_file(item)) {
			resourceList.push_back(item.string());
		}
	}
}


boost::shared_ptr<Shader> ResourceManager::getShader(const std::string& name)
{
	std::map<std::string, boost::shared_ptr<Shader> >::iterator iter = loadedShaders.find(name);

	if(iter == loadedShaders.end())
	{
		fs::path filename = resourceDirectory / shaderDir / name;



		//TODO: load Shader

	}
	else
	{
		return (*iter).second;
	}
}

boost::shared_ptr<Texture> ResourceManager::getTexture(const std::string& name)
{
}

boost::shared_ptr<Terrain> ResourceManager::getTerrain(const std::string& name)
{
}

boost::shared_ptr<Mesh> ResourceManager::getMesh(const std::string& name)
{
}

boost::shared_ptr<Material> ResourceManager::getMaterial(const std::string& name)
{
}


