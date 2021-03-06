#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <boost/filesystem.hpp>
#include <string>

#include "definitions.hpp"
#include "resourcecache.hpp"

#include "resources/material.hpp"
#include "resources/mesh.hpp"
#include "resources/shader.hpp"
#include "resources/texture.hpp"

class ResourceManager
{
public:
    ResourceManager(const boost::filesystem::path& resourceDirectory);
    virtual ~ResourceManager();

    shared_ptr<Mesh> getMesh(const std::string& name);
    shared_ptr<Material> getMaterial(const std::string& name);
    shared_ptr<Texture> getTexture(const std::string& name);
    shared_ptr<Shader> getShader(const std::string& name);

    static const std::string TEXTURES_DIR;
    static const std::string MATERIALS_DIR;
    static const std::string MODELS_DIR;
    static const std::string SHADERS_DIR;

protected:
    // Resource Caches
    ResourceCache<Texture>  textureCache;
    ResourceCache<Material> materialCache;
    ResourceCache<Mesh>     meshCache;
    ResourceCache<Shader>   shaderCache;
};

#endif /* RESOURCEMANAGER_HPP_ */
