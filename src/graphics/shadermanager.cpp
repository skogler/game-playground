#include "shadermanager.hpp"

#include <boost/filesystem.hpp>

#include <GL/gl.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <streambuf>
using namespace std;
namespace fs = boost::filesystem;

ShaderManager::ShaderManager(const string& searchDirectory):
    searchDirectory(searchDirectory)
{
    if(!fs::is_directory(searchDirectory))
    {
        throw string(string("Shader directory not found or invalid: ") + searchDirectory);
    }
}

ShaderManager::~ShaderManager()
{
    for (vector<GLuint>::iterator i = loadedShaders.begin(); i != loadedShaders.end(); ++i)
    {
        glDeleteShader(*i);
    }
}

GLuint ShaderManager::loadFragmentShader(const string & name)
{
    GLuint shaderId = glCreateShader(GL_FRAGMENT_SHADER);
    fs::path filename (name + string(".frag"));
    loadShader(filename, shaderId);
    return shaderId;
}

GLuint ShaderManager::loadVertexShader(const string & name)
{
    GLuint shaderId = glCreateShader(GL_VERTEX_SHADER);
    fs::path filename (name + string(".vert"));
    loadShader(filename, shaderId);
    return shaderId;
}

void ShaderManager::loadShader(const fs::path & filename, const GLuint shaderId)
{
    fs::path full_path = searchDirectory / filename;
    if (!fs::exists(full_path))
    {
        throw string("Shader file not found: ") + filename.string();
    }

    string shaderCode;
    ifstream file(full_path.string().c_str(), ios::in);
    if(file.good())
    {
        shaderCode = string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    }

    cout << "Compiling shader: " << filename << endl;
    char const * pShaderCode = shaderCode.c_str();
    glShaderSource(shaderId, 1, &pShaderCode , NULL);
    glCompileShader(shaderId);

    GLint result = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if(result != GL_TRUE)
    {
        int infoLogLength;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        string errorMessage;
        errorMessage.resize(infoLogLength);
        glGetShaderInfoLog(shaderId, infoLogLength, NULL, &errorMessage[0]);
        cerr << errorMessage << endl;
    }
}


GLuint ShaderManager::createProgramFromShaders(const GLuint vertexShader, const GLuint fragmentShader)
{
    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint result = GL_FALSE;

    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if(result != GL_TRUE)
    {
        int infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        string errorMessage;
        errorMessage.resize(infoLogLength);
        glGetProgramInfoLog(program, infoLogLength, NULL, &errorMessage[0]);
        cerr << errorMessage << endl;
    }
    return program;
}

