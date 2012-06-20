#include "resourcemanager.hpp"

#include <string>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

ResourceManager::ResourceManager(const fs::path & resourceDirectory) :
		textureCache(resourceDirectory / "textures"),
		materialCache(resourceDirectory / "materials"),
		meshCache(resourceDirectory / "models"),
		shaderCache(resourceDirectory / "shaders")
{
}

ResourceManager::~ResourceManager()
{
}

