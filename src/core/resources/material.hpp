#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include <string>

class Material
{
public:
	Material(const std::string & filename);
	virtual ~Material();
};

#endif /* MATERIAL_HPP_ */
