#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Bullet.h"
#include "Animation.h"

class monster : public hero
{
    private:
        int type;
        bool shooting;
    public:
      //  Animation animation;
        monster(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate,float shot_speed, float health, int type, bool shooting)
            :hero(texture,imageCount,switchTime,speed,fire_rate, shot_speed, health), type(type), shooting(shooting) 
        {
            animation(texture, imageCount, switchTime)
        }
        void move(hero player);
        
};