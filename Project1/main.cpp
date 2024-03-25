#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800


bool bordercolli(sf::Sprite entity) {
    if(entity.getPosition().x + entity.getGlobalBounds().width > 1024 || entity.getPosition().x < 0){
        return 1;
    }
    return 0;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
    sf::Image image;
    sf::Texture dog_texture;

    if (!dog_texture.loadFromFile("C:/Users/tmdgj/Projects/umbGame/tempdog.png"))
    {
        return EXIT_FAILURE;
    }

    sf::Sprite dog;
    dog.setPosition(200, 600);
    dog.setTexture(dog_texture);
    dog.setScale(0.5, 0.5);
    float xv = 0.05f;
    while (window.isOpen())
    {
        sf::Event event; //read for an event from the user
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (bordercolli(dog)) {
            xv = xv * -1.0f;
        }
        dog.move(xv, 0);

        // if (some_func){ dog.move(x,0)} else{dog.move(-x.0);}

        window.clear();
        window.draw(dog);
        window.display();
    }

    return 0;
}