#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <GL/glew.h>

#include "utils/config.h"
#include "graphics/mesh.hpp"
#include "graphics/shadermanager.hpp"

#include <boost/chrono.hpp>
#include <cmath>
#include <string>

int main() {


	 //OpenGL Context settings: depthBits, stencilBits, AA, major & minor version
	 sf::ContextSettings contextSettings(24, 8, 4, 4, 2);
	 sf::RenderWindow window(sf::VideoMode(800, 600, 32), PROJECT_NAME, sf::Style::Close, contextSettings);
	 window.setFramerateLimit(60);

	 GLenum err = glewInit();
	 if (GLEW_OK != err)
	 {
	 return 1;
	 }

	 std::string filename = "resources/models/test/test.m42";
	 Mesh m(filename);
	 m.upload();
	 ShaderManager shaderManager(std::string("resources/shaders"));

	 GLuint vertexShader = shaderManager.loadVertexShader("default");
	 GLuint fragmentShader = shaderManager.loadFragmentShader("default");
	 GLuint program = shaderManager.createProgramFromShaders(vertexShader, fragmentShader);
	 glUseProgram(program);

	 while (window.isOpen())
	 {
	 m.draw();
	 window.display();
	 }



	return 0;
}

