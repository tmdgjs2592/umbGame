#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <vector>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800
#define RAIN_LENGTH 30

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

bool checkBorderRight(sf::Sprite entity)
{
    if(entity.getPosition().x + entity.getGlobalBounds().width > 1024)
    {
        return false;
    }
    return true;
}

bool checkBorderLeft(sf::Sprite entity)
{
    if(entity.getPosition().x<0)
    {
        return false;
    }
    return true;
}

bool checkBorderBottom(sf::Sprite entity)
{
    if(entity.getPosition().y>SCREEN_HEIGHT)
    {
        return false;
    }
    return true;
}


bool checkEntityCollision(sf::Sprite entity1, sf::Sprite entity2)
{
    if(entity1.getGlobalBounds().intersects(entity2.getGlobalBounds()))
    {
        return true;
    }
    
    return false;
}



int randRainGen() //pick a random raindrop in the raindrop vector
{
    int range = RAIN_LENGTH;
    int xpos = rand()%range;
    
    return xpos;
}

std::vector<sf::Sprite> rainSpawner(std::vector<sf::Sprite> raindrops, sf::Sprite rain){
    for(int i = 0; i<RAIN_LENGTH;i++)
    {
        raindrops.push_back(rain);
    }
    for(int i = 0; i<RAIN_LENGTH;i++)
    {
        raindrops[i].setPosition(rand()%(SCREEN_WIDTH-10),-10);
    }
    
    return raindrops;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Umbrella Game");
    
    //textures
    sf::Texture background;
    sf::Texture dog_texture;
    sf::Texture bird_texture;
    sf::Texture drop_texture;
    
    
    drop_texture.setSmooth(true);
    drop_texture.setRepeated(true);
    
    
    if(!dog_texture.loadFromFile("/Users/henrybraid/XCode Projects/umbGame/umbGame/images/tempdog.png") ||!bird_texture.loadFromFile("/Users/henrybraid/XCode Projects/umbGame/umbGame/images/tempbird.gif.png")||!drop_texture.loadFromFile("/Users/henrybraid/XCode Projects/umbGame/umbGame/images/WaterDrop.png")||!background.loadFromFile("/Users/henrybraid/XCode Projects/umbGame/umbGame/images/back.png"))
    {
        return EXIT_FAILURE;
    }
    
    sf::Sprite back;
    back.setTexture(background);
    back.scale(5, 5);
    back.setPosition(0, 0);
    
    sf::Sprite dog;
    dog.setPosition(200,685);
    dog.setTexture(dog_texture);
    dog.setScale(0.5,0.5);
    float xv = 0.05f;
    
    sf::Sprite bird;
    bird.setTexture(bird_texture);
    bird.setScale(0.7,0.7);
    bird.setPosition(400, 400);
    
    
    sf::Sprite rain;
    rain.setTexture(drop_texture);
    rain.setScale(0.125,0.125);
    
    
    std::vector<sf::Sprite> raindrops;
    raindrops = rainSpawner(raindrops, rain);
   
    
    sf::Clock clock;
    float timer = 0.0f;
    float timerMax = 1.0f;
    float yv = 0.15f;
    float b_xv = 0;
    int hurt_timer=0; //used to measure how long to flash the dog red... indicating collision with raindrop
    float b_changex=0;
    
    while(window.isOpen())
    {
        
        
        sf::Event event; //read for an event from the user
        
        while(window.pollEvent(event))
        {
            switch ( event.type )
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed: //read key input
                    b_changex=0; //reset direction
                    //read input of A or Left
                    if((event.key.code==sf::Keyboard::A ||event.key.code==sf::Keyboard::Left) &&checkBorderLeft(bird))
                    {
                        b_changex=-30;
                    }
                    //read input of D or Right
                    if((event.key.code==sf::Keyboard::D || event.key.code==sf::Keyboard::Right) &&checkBorderRight(bird))
                    {
                        b_changex=30;
                    }
                    
                    
                    
                    
                    bird.move(b_changex,0);
                    
            }
             
        }
        
        
            
        if (bordercolli(dog)) {
                    xv = xv * -1.0f;
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
        for(int j = 0; j<num; j++)
        {
            if(checkEntityCollision(raindrops[j],dog))
            {
                dog.setColor(sf::Color(255,0,0));
                hurt_timer=0;
            }
            else if(checkBorderBottom(raindrops[j]) && !checkEntityCollision(raindrops[j], bird))
            {
                raindrops[j].move(0,yv);
                continue;
            }
            
            int xpos=rand()%(SCREEN_WIDTH-10);
            raindrops[j].setPosition(xpos,-10);
            
        }
        
        window.clear();
        //draw objects
        window.draw(back);
        window.draw(bird);
        window.draw(dog);
        for(int j = 0; j<RAIN_LENGTH; j++)
        {
            window.draw(raindrops[j]);
        }
        window.display();
        if(hurt_timer>500)
        {
            dog.setColor(sf::Color::White);
        }
        hurt_timer++;
    }
    return EXIT_SUCCESS;
}

