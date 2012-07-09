#include "resourcemanager.hpp"

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

using namespace std;

ResourceManager::ResourceManager(const fs::path & resourceDirectory) :
		textureCache(resourceDirectory / "textures", "dds"),
		materialCache(resourceDirectory / "materials", "m42mat"),
		meshCache(resourceDirectory / "models", "m42"),
		shaderCache(resourceDirectory / "shaders", "shader")
{
}

ResourceManager::~ResourceManager()
{
}

shared_ptr<Mesh> ResourceManager::getMesh(const string& name)
{
	shared_ptr<Mesh> mesh = meshCache.get(name);
	vector<std::string> mats = mesh->getUsedMaterials();
	for(vector<string>::const_iterator iter = mats.begin(); iter != mats.end(); ++iter)
	{
		mesh->setMaterial(*iter, materialCache.get(*iter));
	}
	return mesh;
}

shared_ptr<Material> ResourceManager::getMaterial(const string& name)
{
	return materialCache.get(name);
}

shared_ptr<Texture> ResourceManager::getTexture(const string& name)
{
	return textureCache.get(name);
}

shared_ptr<Shader> ResourceManager::getShader(const string& name)
{
	return shaderCache.get(name);
}

