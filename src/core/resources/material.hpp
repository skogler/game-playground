#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include <string>
#include <boost/filesystem.hpp>

#include "core/definitions.hpp"
#include "core/resources/texture.hpp"

struct Color
{
	float r;
	float g;
	float b;
	float intensity;
};

enum MaterialType
{
	MATERIAL_TYPE_COLOR = 0,
	MATERIAL_TYPE_TEXTURE = 1
};

class Material
{
	public:
		Material(const boost::filesystem::path& path);
		virtual ~Material();

		int getUid() const
		{
			return uid;
		}

		inline shared_ptr<Texture> getTexture() const
		{
			return texture;
		}

		inline void setTexture(shared_ptr<Texture> texture)
		{
			this->texture = texture;
		}

		inline MaterialType getType() const { return type; }
		inline const Color & getDiffuse() const { return diffuse; }
		inline const Color & getSpecular() const { return specular; }
		inline float getAmbient() const { return ambient; }
		inline const std::string & getTextureName() const { return textureName; }

	protected:
		int uid;
		MaterialType type;
		Color diffuse;
		Color specular;
		float ambient;
		std::string textureName;
		shared_ptr<Texture> texture;

		void loadFromFile(const boost::filesystem::path& path);
};

#endif /* MATERIAL_HPP_ */
