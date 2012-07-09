#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include <string>
#include <boost/filesystem.hpp>

struct Color
{
	float r;
	float g;
	float b;
	float intensity;
};

enum MaterialType
{
	COLOR,
	TEXTURE
};

class Material
{
public:
	Material(const boost::filesystem::path& path);
	virtual ~Material();

	inline MaterialType getType() const { return type; }
	inline const Color & getDiffuse() const { return diffuse; }
	inline const Color & getSpecular() const { return specular; }
	inline const std::string & getTextureName() const { return textureName; }

protected:
	MaterialType type;
	Color diffuse;
	Color specular;
	std::string textureName;

	void loadFromFile(const boost::filesystem::path& path);
};

#endif /* MATERIAL_HPP_ */
