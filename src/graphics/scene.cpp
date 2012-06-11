#include "scene.hpp"
#include "mesh.hpp"
#include "shadermanager.hpp"
#include <string>
#include <iostream>
#include <list>
using std::string;
using std::list;

Scene::Scene(Camera * camera) :
    camera(camera),
    modelMatrix(0),
    viewMatrix(0),
    projectionMatrix(0),
    mm(1.0f),
    vm(1.0f)

{
    std::string filename = "resources/models/monkey.m42";
    Mesh * mesh = new Mesh(filename);
    mesh->upload();

    RenderedEntity  * monkey = new RenderedEntity();
    monkey->set_mesh(mesh);
    entities.push_back(monkey);

    ShaderManager shaderManager(string("resources/shaders"));

    GLuint vertexShader = shaderManager.loadVertexShader("default");
    GLuint fragmentShader = shaderManager.loadFragmentShader("default");
    GLuint program = shaderManager.createProgramFromShaders(vertexShader, fragmentShader);
    glUseProgram(program);

    modelMatrix = glGetUniformLocation(program, "modelMatrix");
    viewMatrix = glGetUniformLocation(program, "viewMatrix");
    projectionMatrix = glGetUniformLocation(program, "projectionMatrix");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

Scene::~Scene()
{
    if(camera != NULL)
    {
        delete camera;
    }
}

void Scene::render() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // set the view matrix = model matrix of the camera
    glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, &camera->get_modelMatrix()[0][0]);
    // set the projection matrix
    glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, &camera->get_projectionMatrix()[0][0]);

    for (list<RenderedEntity*>::const_iterator i = entities.begin(); i != entities.end(); ++i)
    {
        // set the model matrix for each rendered entity
        glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &(*i)->get_modelMatrix()[0][0]);
        (*i)->render();
    }
}

