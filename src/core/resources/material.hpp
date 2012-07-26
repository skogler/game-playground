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
	MATERIAL_TYPE_COLOR,
	MATERIAL_TYPE_TEXTURE
};

class Material
{
public:
	Material(const boost::filesystem::path& path);
	virtual ~Material();

	inline MaterialType getType() const { return type; }
	inline const Color & getDiffuse() const { return diffuse; }
	inline const Color & getSpecular() const { return specular; }
	inline float getAmbient() const { return ambient; }
	inline const std::string & getTextureName() const { return textureName; }

protected:
	MaterialType type;
	Color diffuse;
	Color specular;
	float ambient;
	std::string textureName;

	void loadFromFile(const boost::filesystem::path& path);
};

#endif /* MATERIAL_HPP_ */
