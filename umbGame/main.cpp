#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>


#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800
#define RAIN_LENGTH 20

bool bordercolli(sf::Sprite entity) {
    if(entity.getPosition().x + entity.getGlobalBounds().width > 1024 || entity.getPosition().x < 0){
        return 1;
    }
    return 0;
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
    for(int i = 1; i<RAIN_LENGTH;i++)
    {
        raindrops[i].setPosition(rand()%SCREEN_WIDTH,-10);
    }
    
    return raindrops;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Umbrella Game");
    
    //dog texture setup
    sf::Texture dog_texture;
    //dog_texture.loadFromFile("/Users/henrybraid/XCode Projects/Umbrella Game/tempdog.png");
    if(!dog_texture.loadFromFile("/Users/henrybraid/XCode Projects/umbGame/umbGame/images/tempdog.png"))
    {
        return EXIT_FAILURE;
    }
    sf::Sprite dog;
    dog.setPosition(200,600);
    dog.setTexture(dog_texture);
    dog.setScale(0.5,0.5);
    
    //bird texture setup
    sf::Texture bird_texture;
    if(!bird_texture.loadFromFile("/Users/henrybraid/XCode Projects/umbGame/umbGame/images/tempbird.gif.png"))
    {
        return EXIT_FAILURE;
    }
    sf::Sprite bird;
    bird.setTexture(bird_texture);
    bird.setScale(0.60,0.60);
    bird.setPosition(400, 400);
    
    sf::Texture droplet;
    droplet.loadFromFile("/Users/henrybraid/XCode Projects/umbGame/umbGame/images/WaterDrop.png");
    sf::Sprite rain;
    rain.setTexture(droplet);
    rain.setScale(0.175,0.175);
    
    
    std::vector<sf::Sprite> raindrops;
    raindrops = rainSpawner(raindrops, rain);
   
    
    
    
    float xv = 0.05f;
    float b_changex=0;
    float yv=0.15f; //speed of rain falling
    
    
    int clock = 0;
    while(window.isOpen())
    {
        int num = randRainGen();
        clock++;
        sf::Event event; //read for an event from the user
        
        while(window.pollEvent(event))
        {
            
            switch ( event.type )
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed: //read key input
                    
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
        for(int j = 0; j<num; j++)
        {
            if(checkBorderBottom(raindrops[j])&&(raindrops[j].getPosition().y!=bird.getPosition().y))
            {
                raindrops[j].move(0,yv);
            }
            else{
                int xpos=raindrops[j].getPosition().x;
                raindrops[j].setPosition(xpos,-10);
            }
        }
        
            
        if (bordercolli(dog)) {
                    xv = xv * -1.0f;
                }
        dog.move(xv, 0);

        
        window.clear();
        //draw objects
        window.draw(bird);
        window.draw(dog);
        for(int j = 0; j<RAIN_LENGTH; j++)
        {
            window.draw(raindrops[j]);
        }
        window.display();
    }
    return EXIT_SUCCESS;
}

