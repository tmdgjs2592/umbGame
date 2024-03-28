#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <vector>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800
#define RAIN_LENGTH 20

bool checkBorderLeft(sf::Sprite entity)
{
    if (entity.getPosition().x < 0)
    {
        return false;
    }
    return true;
}

bool checkBorderBottom(sf::Sprite entity)
{
    if (entity.getPosition().y > SCREEN_HEIGHT)
    {
        return false;
    }
    return true;
}

bool checkBorderRight(sf::Sprite entity)
{
    if (entity.getPosition().x + entity.getGlobalBounds().width > 1024)
    {
        return false;
    }
    return true;
}

int randRainGen() //pick a random raindrop in the raindrop vector
{
    int range = RAIN_LENGTH;
    int xpos = rand() % range;

    return xpos;
}
std::vector<sf::Sprite> rainSpawner(std::vector<sf::Sprite> raindrops, sf::Sprite rain) {
    for (int i = 0; i < RAIN_LENGTH; i++)
    {
        raindrops.push_back(rain);
    }
    for (int i = 1; i < RAIN_LENGTH; i++)
    {
        raindrops[i].setPosition(rand() % SCREEN_WIDTH, -10);
    }

    return raindrops;
}

bool bordercolli(sf::Sprite entity) {
    if(entity.getPosition().x + entity.getGlobalBounds().width > 1024 || entity.getPosition().x < 0){
        return 1;
    }
    return 0;
}

bool turn() {
    int num = rand() % 2;
    if (num == 0)
        return true;
    return false;

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Umbrella");
    sf::Texture background;
    sf::Texture dog_texture;
    sf::Texture drop_texture;
    sf::Texture bird_texture;

    drop_texture.setSmooth(true);
    drop_texture.setRepeated(true);

    if (!dog_texture.loadFromFile("C:/Users/tmdgj/Projects/umbGame/images/tempdog.png") || !drop_texture.loadFromFile("C:/Users/tmdgj/Projects/umbGame/images/drop.png") 
        || !bird_texture.loadFromFile("C:/Users/tmdgj/Projects/umbGame/images/bird.png") || !background.loadFromFile("C:/Users/tmdgj/Projects/umbGame/images/back.png"))
    {
        return EXIT_FAILURE;
    }
    srand(time(NULL));

    sf::Sprite back;
    back.setTexture(background);
    back.scale(5, 5);
    back.setPosition(0, 0);
    

    sf::Sprite dog;
    dog.setPosition(200, 600);
    dog.setTexture(dog_texture);
    dog.setScale(0.5, 0.5);
    float xv = 0.05f;

    sf::Sprite bird;
    bird.setTexture(bird_texture);
    bird.setScale(0.6, 0.6);
    bird.setPosition(400, 400);

    sf::Sprite rain;
    rain.setTexture(drop_texture);
    rain.setScale(0.10, 0.10);

    sf::Clock clock;
    float timer = 0.0f;
    float timerMax = 1.0f;
    float yv = 0.15f;
    float b_xv = 0;
    
    std::vector<sf::Sprite> raindrops(20, sf::Sprite(drop_texture));
    for (int i = 0; i < RAIN_LENGTH; i++) {
        raindrops[i].setPosition(rand() % SCREEN_WIDTH, -10);
        raindrops[i].setScale(0.1, 0.1);
    }
    

    while (window.isOpen())
    {
        sf::Event event; //read for an event from the user
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && checkBorderLeft(bird)) {
            bird.move(-0.1, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && checkBorderRight(bird)) {
            bird.move(0.1, 0);
        }

        if (bordercolli(dog)) {
            xv = -xv;
        }
       
        timer += clock.restart().asSeconds();

        if (timer >= timerMax) {
            if (turn()) {
                xv = -xv;
            }
            timer = 0.0f;
        }

        dog.move(xv, 0);

        int num = randRainGen();

        for (int j = 0; j < num; j++)
        {
            if (checkBorderBottom(raindrops[j]) && (raindrops[j].getPosition().y != bird.getPosition().y))
            {
                raindrops[j].move(0, yv);
            }
            else {
                int xpos = raindrops[j].getPosition().x;
                raindrops[j].setPosition(xpos, -10);
            }
        }

        window.clear();
        window.draw(back);
        window.draw(dog);
        window.draw(bird);
        for (int j = 0; j < RAIN_LENGTH; j++)
        {
            window.draw(raindrops[j]);
        }
        window.display();
    }

    return 0;
}