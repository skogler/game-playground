#ifndef SHADERMANAGER_INC
#define SHADERMANAGER_INC

#include <boost/filesystem.hpp>

#include <GL/glew.h>

#include <string>
#include <vector>

class ShaderManager
{
public:
    explicit ShaderManager (const std::string & searchDirectory);
    virtual ~ShaderManager ();

    GLuint loadVertexShader(const std::string & name);
    GLuint loadFragmentShader(const std::string & name);
    GLuint createProgramFromShaders(const GLuint vertexShader, const GLuint fragmentShader);

protected:
    void loadShader(const boost::filesystem::path & filename, GLuint shaderId);

    boost::filesystem::path searchDirectory;
    std::vector<GLuint> loadedShaders;
};

#endif /* end of include guard: SHADERMANAGER_INC */
