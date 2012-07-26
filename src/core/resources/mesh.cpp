#include "mesh.hpp"

#include "exceptions/invalidresourceerror.hpp"
#include "utils/logger.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>


#include <boost/format.hpp>

using namespace std;
using boost::lexical_cast;

Mesh::Mesh(const boost::filesystem::path & path) :
				vertexBuffer(0),
				faceBuffer(0),
				normalBuffer(0),
				uploaded(false)
{
	load(path);
	Logger::debug(string("Loaded model: ") + path.string());
}

Mesh::~Mesh()
{
	if (uploaded)
	{
		release();
	}
}

void Mesh::upload()
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &faceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(unsigned int), &faces[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}

void Mesh::release()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &faceBuffer);
	glDeleteBuffers(1, &normalBuffer);
}

const std::vector<std::string> Mesh::getUsedMaterials() const
{
	vector<string> usedMaterials;
	for(vector<FaceGroup>::const_iterator iter = faceGroups.begin(); iter != faceGroups.end(); ++iter)
	{
		usedMaterials.push_back(iter->materialName);
	}
	return usedMaterials;
}

void Mesh::load(const boost::filesystem::path & path)
{
	try
	{
		ifstream f(path.c_str());
		if (f.is_open())
		{
			string line;
			int state = 0;
			FaceGroup currentFaceGroup;
			currentFaceGroup.start = 0;
			currentFaceGroup.materialName = "fail"; //TODO this should actually display a fail material
			while (f.good())
			{
				getline(f, line);
				if (line.length() != 0)
				{
					// set parser state if a new section begins
					switch (line[0])
					{
					case ' ':
						break;
					case '#':
						break;
					case 'v':
						state = 1;
						break;
					case 'n':
						state = 2;
						break;
					case 'f':
						state = 3;
						break;
					case 'u':
						if (line[1] == 'v')
						{

							state = 4;
							break;
						}
					default: // No state change or comment ==> read data
						vector<string> parts;
						boost::split(parts, line, boost::algorithm::is_space());
						int l = parts.size();
						if (l != 0)
						{
							if (state == 1)  // reading vertices
							{
								if (l == 3)
								{
									//parse values
									float x = lexical_cast<float>(parts[0]);
									float y = lexical_cast<float>(parts[1]);
									float z = lexical_cast<float>(parts[2]);
									//add vertice to list
									vertices.push_back(glm::vec3(x, y, z));
								}
								else
								{
									throw InvalidResourceError(path.string());
								}
							}
							else if (state == 2) // reading normals
							{
								if (l == 3)
								{
									//parse values
									float x = lexical_cast<float>(parts[0]);
									float y = lexical_cast<float>(parts[1]);
									float z = lexical_cast<float>(parts[2]);
									//add normal to list
									normals.push_back(glm::vec3(x, y, z));
								}
								else
								{
									throw InvalidResourceError(path.string());
								}
							}
							else if (state == 3) // reading faces
							{
								if (parts[0] == "usemat")
								{
									// usemat without faces gets ignored
									int size = faces.size() - currentFaceGroup.start;
									if (size != 0)
									{
//										Logger::debug((boost::format("fg: %1% :: faces :: %2%") % currentFaceGroup.materialName % (size/3)).str());
										currentFaceGroup.size = size;
										faceGroups.push_back(currentFaceGroup);
									}
									currentFaceGroup.materialName = parts[1];
									currentFaceGroup.start = faces.size();
								}
								else
								{
									if (l == 3)
									{
										//parse values (indices of vertices)
										unsigned int a = lexical_cast<unsigned int>(parts[0]);
										unsigned int b = lexical_cast<unsigned int>(parts[1]);
										unsigned int c = lexical_cast<unsigned int>(parts[2]);
										//add face to list
										faces.push_back(a);
										faces.push_back(b);
										faces.push_back(c);
									}
									else
									{
										throw InvalidResourceError(path.string());
									}
								}
							}

							else if (state == 4) // reading uv coordinates
							{

								if (l == 2)
								{
									//parse values (pairs of u v texture coordinates)
									float u = lexical_cast<float>(parts[0]);
									float v = lexical_cast<float>(parts[1]);

									uvCoordinates.push_back(glm::vec2(u, v));
								}
								else
								{
									throw InvalidResourceError(path.string());
								}
							}

						}
						break;
					}
				}
			}
			// Push back last face group
			currentFaceGroup.size = faces.size() - currentFaceGroup.start;
			faceGroups.push_back(currentFaceGroup);
		}
		else
		{
			throw InvalidResourceError(path.string());
		}
	} catch (boost::bad_lexical_cast &)
	{
		throw InvalidResourceError(path.string());
	}
}

