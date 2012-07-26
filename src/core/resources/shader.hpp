#ifndef SHADER_HPP_
#define SHADER_HPP_

#include "core/definitions.hpp"

#include <boost/filesystem.hpp>
#include <GL/glew.h>

enum ShaderType
{
	VERTEX,
	FRAGMENT,
	GEOMETRY
};

class Shader
{
public:
	Shader(const boost::filesystem::path& filepath);
	virtual ~Shader();

	GLuint getShaderId() const
	{
		return shaderId;
	}

    inline ShaderType getType() const
    {
        return type;
    }

protected:
    ShaderType type;
    GLuint shaderId;

    void loadFromFile(const boost::filesystem::path & path);
};

#endif /* SHADER_HPP_ */
