#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <string>
#include <boost/filesystem.hpp>
#include <GL/glew.h>

class Texture
{
	public:
		Texture(const boost::filesystem::path& path);
		virtual ~Texture();
		inline GLuint get_id() { return id; }

	protected:
		GLuint id;

		void loadFromFile(const boost::filesystem::path& path);

};

#endif /* TEXTURE_HPP_ */
