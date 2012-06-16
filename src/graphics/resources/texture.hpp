#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <string>
#include <boost/filesystem.hpp>
#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& name);
	virtual ~Texture();
	inline GLuint get_id() { return id; }

protected:
	GLuint id;

	void loadFromFile(const std::string& filename);
private:
	static boost::filesystem::path searchDirectory;
};

#endif /* TEXTURE_HPP_ */
