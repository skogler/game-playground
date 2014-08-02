#ifndef SHADERPROGRAM_HPP_
#define SHADERPROGRAM_HPP_

#include <GL/glew.h>
#include <boost/filesystem.hpp>
#include <string>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "core/definitions.hpp"
#include "core/resources/material.hpp"
#include "core/resources/shader.hpp"
#include "graphics/light.hpp"

struct LightId
{
    GLuint position;
    GLuint color;
    GLuint intensity;
    GLuint linearAttenuation;
    GLuint squaredAttenuation;
};

struct MaterialId
{
    GLuint diffuseColor;
    GLuint specularColor;
    GLuint ambient;
};

enum Effect
{
    EFFECT_LIGHTING,
    EFFECT_COLOR,
    EFFECT_TEXTURE
};


class ShaderProgram
{
public:
    ShaderProgram();
    virtual ~ShaderProgram();

    /**
     * Call this after all shaders are attached.
     * Validates the shader program, uploads it to the GPU and allocates needed
     *uniform variables.
     */
    void link();

    /**
     * Binds the shader program so all following render
     * operations are handled by it.
     */
    inline void bind() const
    {
        glUseProgram(programId);
    }
    /**
     * Returns the identifier that is used to access the
     * shader program on the graphics card.
     */
    inline GLuint getId() const
    {
        return programId;
    }

    /**
     * Attaches the specified shader to the program.
     */
    void attachShader(shared_ptr<Shader> shader);

    inline void setModelMatrix(const glm::mat4& modelMatrix)
    {
        glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, &modelMatrix[0][0]);
    }

    inline void setViewMatrix(const glm::mat4& viewMatrix)
    {
        glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, &viewMatrix[0][0]);
    }

    inline void setProjectionMatrix(const glm::mat4& projectionMatrix)
    {
        glUniformMatrix4fv(projectionMatrixId,
                           1,
                           GL_FALSE,
                           &projectionMatrix[0][0]);
    }

    void setMaterial(const Material& material);

    /**
     * Sets the light source at the specified index.
     */
    void setLight(int index, const Light& light);
    /**
     * Adds a light to the list of light sources and returns
     * its inserted index
     */
    int addLight(const Light& light);
    /**
     * Removes all light sources.
     */
    void clearLights();

    bool hasEffect(const Effect effect);
    void addEffect(const Effect effect);

protected:
    std::vector<shared_ptr<Shader> > shaders;
    std::vector<Effect>              effects;

    std::string modelMatrixName;
    std::string viewMatrixName;
    std::string projectionMatrixName;

    GLuint programId;

    GLuint modelMatrixId;
    GLuint viewMatrixId;
    GLuint projectionMatrixId;

    MaterialId materialId;

    std::vector<LightId> lightIds;
    unsigned int         numLights;

    void allocateUniforms();
    void allocateLight();
};

#endif /* SHADERPROGRAM_HPP_ */
