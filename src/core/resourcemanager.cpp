#include "resourcemanager.hpp"

#include "utils/logger.hpp"
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <vector>
namespace fs = boost::filesystem;
using std::vector;
using std::string;

const std::string ResourceManager::MODELS_DIR    = "models";
const std::string ResourceManager::TEXTURES_DIR  = "textures";
const std::string ResourceManager::MATERIALS_DIR = "materials";
const std::string ResourceManager::SHADERS_DIR   = "shaders";

ResourceManager::ResourceManager(const fs::path& resourceDirectory) :
    textureCache(resourceDirectory / TEXTURES_DIR, "dds"),
    materialCache(resourceDirectory / MATERIALS_DIR, "m42mat"),
    meshCache(resourceDirectory / MODELS_DIR, "m42"),
    shaderCache(resourceDirectory / SHADERS_DIR, "")
{
}

ResourceManager::~ResourceManager()
{
}

shared_ptr<Mesh> ResourceManager::getMesh(const string& name)
{
    shared_ptr<Mesh>    mesh = meshCache.get(name);
    vector<std::string> mats = mesh->getUsedMaterials();
    for (vector<string>::const_iterator iter = mats.begin();
         iter != mats.end();
         ++iter)
    {
        mesh->setMaterial(*iter, getMaterial(*iter));
    }
    return mesh;
}

shared_ptr<Material> ResourceManager::getMaterial(const string& name)
{
    shared_ptr<Material> mat = materialCache.get(name);

    if (mat->getType() == MATERIAL_TYPE_TEXTURE)
    {
        mat->setTexture(getTexture(mat->getTextureName()));
    }
    return mat;
}

shared_ptr<Texture> ResourceManager::getTexture(const string& name)
{
    return textureCache.get(name);
}

shared_ptr<Shader> ResourceManager::getShader(const string& name)
{
    return shaderCache.get(name);
}
