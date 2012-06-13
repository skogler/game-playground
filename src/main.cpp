#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <GL/glew.h>

#include "utils/config.h"
#include "graphics/mesh.hpp"
#include "graphics/shadermanager.hpp"
#include "graphics/camera.hpp"
#include "graphics/scene.hpp"

#include <glm/glm.hpp>
#include <iostream>
using namespace std;

int main()
{
	//OpenGL Context settings: depthBits, stencilBits, AA, major & minor version
	sf::ContextSettings contextSettings(24, 8, 4, 4, 2);
	sf::RenderWindow window(sf::VideoMode(1024, 768, 32), PROJECT_NAME, sf::Style::Close, contextSettings);
	window.setFramerateLimit(40);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		return 1;
	}

	Camera * camera = new Camera();
	camera->move(-20.0f);
	Scene scene(camera);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		scene.render();
		window.display();
	}

	return 0;
}

