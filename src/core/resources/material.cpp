#include "material.hpp"

#include "exceptions/invalidresourceerror.hpp"
#include "utils/logger.hpp"
#include "utils/UIDGenerator.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

using namespace std;

Material::Material(const boost::filesystem::path& path) :
		textureName(""),
		uid(UIDGenerator::instance()->next())
{

	loadFromFile(path);
	Logger::debug(string("Loaded material: ") + path.string());
}

Material::~Material()
{
}

void Material::loadFromFile(const boost::filesystem::path& path)
{
	ifstream f(path.c_str());
	if (f.is_open())
	{
		string line;
		int state = 0;
		while (f.good())
		{
			getline(f, line);
			if (line.length() != 0)
			{
				// set parser state if a new section begins
				switch (line[0])
				{
				case 't':
					state = 1; // type definition
					break;
				case 'd':
					state = 2; // diffuse color
					break;
				case 's':
					state = 3; // specular color
					break;
				case 'a':
					state = 4; // ambient intensity
				case 'i':
					state = 5; // image properties
					break;
				default:
					state = 0;
					break;
				}

				if (state != 0)
				{
					vector<string> parts;
					boost::split(parts, line, boost::algorithm::is_space());
					int l = parts.size();
					if (l != 0)
					{
						if (state == 1) // type
						{
							if (parts[1] == "color")
							{
								type = MATERIAL_TYPE_COLOR;
							}
							else if (parts[1] == "texture")
							{
								type = MATERIAL_TYPE_TEXTURE;
							}
						}
						else if (state == 2) // diffuse color
						{
							if (l == 5)
							{
								try
								{
									//parse values
									diffuse.r = boost::lexical_cast<float>(parts[1]);
									diffuse.g = boost::lexical_cast<float>(parts[2]);
									diffuse.b = boost::lexical_cast<float>(parts[3]);
									diffuse.intensity = boost::lexical_cast<float>(parts[4]);

								} catch (boost::bad_lexical_cast &)
								{
									throw InvalidResourceError(path.string());
								}
							}
							else
							{
								throw InvalidResourceError(path.string());
							}
						}
						else if (state == 3) //specular color
						{
							if (l == 5)
							{
								try
								{
									//parse values
									specular.r = boost::lexical_cast<float>(parts[1]);
									specular.g = boost::lexical_cast<float>(parts[2]);
									specular.b = boost::lexical_cast<float>(parts[3]);
									specular.intensity = boost::lexical_cast<float>(parts[4]);

								} catch (boost::bad_lexical_cast &)
								{
									throw InvalidResourceError(path.string());
								}
							}
							else
							{
								throw InvalidResourceError(path.string());
							}
						}
						else if (state == 4) // ambient intensity
						{
							if (l == 2)
							{
								try
								{

									ambient = boost::lexical_cast<float>(parts[1]);

								} catch (boost::bad_lexical_cast &)
								{
									throw InvalidResourceError(path.string());
								}
							}
							else
							{
								throw InvalidResourceError(path.string());
							}
						}
						else if (state == 5) // texture properties
						{
							if (l == 2)
							{
								textureName = parts[1];
							}
							else
							{
								throw InvalidResourceError(path.string());
							}
						}
					}
				}
			}
		}
	}
	else
	{
		throw InvalidResourceError(path.string());
	}
}
