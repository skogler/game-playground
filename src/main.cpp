#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <GL/gl.h>

#include "utils/config.h"
#include "graphics/mesh.hpp"
using namespace std;

int main()
{
    //OpenGL Context settings: depthBits, stencilBits, AA, major & minor version
    sf::ContextSettings contextSettings(24, 8, 4, 4, 2);
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), PROJECT_NAME, sf::Style::Close, contextSettings);
    window.setFramerateLimit(60);
    string filename = "test.m42";
    Mesh m(filename);

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
        }

        window.display();
    }

    return 0;
}

