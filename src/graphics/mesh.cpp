#include "mesh.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <glm/glm.hpp>
#include "../utils/definitions.hpp"
using namespace std;


Mesh::Mesh(string& filename) :
    vboId(0),
    indexVboId(0),
    uploaded(false)
{
    load(filename);
    for (int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i].x << endl;
    }
}


Mesh::~Mesh()
{
    if(uploaded)
    {
        release();
    }
}

void
Mesh::upload()
{

}

void
Mesh::release()
{

}


void
Mesh::draw()
{

}


void Mesh::load(string& filename)
{
    ifstream f(filename.c_str());
    if(f.is_open())
    {
        string line;
        int state = 0;
        while(f.good())
        {
            getline(f, line);
            if(line.length() != 0)
            {
                // set parser state if a new section begins
                switch(line[0])
                {
                    case ' ': break;
                    case '#': break;
                    case 'v': state = 1; break;
                    case 'n': state = 2; break;
                    case 'f': state = 3; break;
                    default: vector<string> parts;
                              boost::split(parts, line, boost::is_any_of(" "));
                              int l = parts.size();
                              if(l != 0)
                              {
                                  if(state == 1)  // reading vertices
                                  {
                                      if(l == 3)
                                      {
                                          try
                                          {
                                              //parse values
                                              float x = boost::lexical_cast<float>(parts[0]);
                                              float y = boost::lexical_cast<float>(parts[1]);
                                              float z = boost::lexical_cast<float>(parts[2]);
                                              //add vertice to list
                                              vertices.push_back(glm::vec3(x, y, z));
                                          }
                                          catch (boost::bad_lexical_cast &)
                                          {
                                              //FIXME handle errors properly
                                              string message = "Invalid model file ";
                                              message.append(filename);
                                              error(message);
                                          }

                                      }
                                  }
                                  else if (state == 2) // reading normals
                                  {
                                      if(l == 3)
                                      {
                                          try
                                          {
                                              //parse values
                                              float x = boost::lexical_cast<float>(parts[0]);
                                              float y = boost::lexical_cast<float>(parts[1]);
                                              float z = boost::lexical_cast<float>(parts[2]);
                                              //add normal to list
                                              normals.push_back(glm::vec3(x, y, z));
                                          }
                                          catch (boost::bad_lexical_cast &)
                                          {
                                              //FIXME handle errors properly
                                              string message = "Invalid model file ";
                                              message.append(filename);
                                              error(message);
                                          }

                                      }

                                  }
                                  else if(state == 3) // reading faces
                                  {
                                      if(l == 3)
                                      {
                                          try
                                          {
                                              //parse values (indices of vertices)
                                              int a = boost::lexical_cast<int>(parts[0]);
                                              int b = boost::lexical_cast<int>(parts[1]);
                                              int c = boost::lexical_cast<int>(parts[2]);
                                              //add face to list
                                              faces.push_back(a);
                                              faces.push_back(b);
                                              faces.push_back(c);
                                          }
                                          catch (boost::bad_lexical_cast &)
                                          {
                                              //FIXME handle errors properly
                                              string message = "Invalid model file ";
                                              message.append(filename);
                                              error(message);
                                          }

                                      }
                                  }

                              } break;
                }
            }

        }
    }
}


