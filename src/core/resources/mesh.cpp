#include "mesh.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <glm/glm.hpp>
#include "../../utils/logger.hpp"
using namespace std;

Mesh::Mesh(const string& filename) :
		vertexBuffer(0), faceBuffer(0), normalBuffer(0), uploaded(false)
{
	load(filename);
	Logger::debug("Loaded model file: " + filename);
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

void Mesh::render()
{
	// index 0 => vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0,                               // attribute
			3,                               // size
			GL_FLOAT,                        // type
			GL_FALSE,                        // normalized?
			0,                               // stride
			(void*) 0                         // array buffer offset
			);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	// index 2 => normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*) 0                          // array buffer offset
			);

	//FIXME: PERF: use short instead of int
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceBuffer);
	glDrawElements(GL_TRIANGLES, faces.size(), GL_UNSIGNED_INT, (void*) 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Mesh::load(const string& filename)
{
	ifstream f(filename.c_str());
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
				default:
					vector<string> parts;
					boost::split(parts, line, boost::is_any_of(" "));
					int l = parts.size();
					if (l != 0)
					{
						if (state == 1)  // reading vertices
						{
							if (l == 3)
							{
								try
								{
									//parse values
									float x = boost::lexical_cast<float>(parts[0]);
									float y = boost::lexical_cast<float>(parts[1]);
									float z = boost::lexical_cast<float>(parts[2]);
									//add vertice to list
									vertices.push_back(glm::vec3(x, y, z));
								} catch (boost::bad_lexical_cast &)
								{
									//FIXME handle errors properly
									string message = "Invalid model file ";
									message.append(filename);
								}

							}
						}
						else if (state == 2) // reading normals
						{
							if (l == 3)
							{
								try
								{
									//parse values
									float x = boost::lexical_cast<float>(parts[0]);
									float y = boost::lexical_cast<float>(parts[1]);
									float z = boost::lexical_cast<float>(parts[2]);
									//add normal to list
									normals.push_back(glm::vec3(x, y, z));
								} catch (boost::bad_lexical_cast &)
								{
									//FIXME handle errors properly
									string message = "Invalid model file ";
									message.append(filename);
								}

							}

						}
						else if (state == 3) // reading faces
						{
							if (l == 3)
							{
								try
								{
									//parse values (indices of vertices)
									unsigned int a = boost::lexical_cast<unsigned int>(parts[0]);
									unsigned int b = boost::lexical_cast<unsigned int>(parts[1]);
									unsigned int c = boost::lexical_cast<unsigned int>(parts[2]);
									//add face to list
									faces.push_back(a);
									faces.push_back(b);
									faces.push_back(c);
								} catch (boost::bad_lexical_cast &)
								{
									//FIXME handle errors properly
									string message = "Invalid model file ";
									message.append(filename);
								}

							}
						}

					}
					break;
				}
			}

		}
	}
	else
	{
		string message = "Invalid model file ";
		message.append(filename);
	}
}

