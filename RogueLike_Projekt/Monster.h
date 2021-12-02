#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Bullet.h"
#include "Animation.h"
#define PI 3.141592;

class monster : public hero
{
    private:
        bool shooting;
    public:
      //  Animation animation;
        monster(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health, 
            float damage, sf::Vector2f size, sf::Vector2f position, bool shooting)
            :hero(texture, imageCount, switchTime, speed, fire_rate, shot_speed, health,damage, size, position), shooting(shooting) {}
        void Update(float deltaTime, sf::Clock &fire_delay_clock, sf::Texture* arrow, std::vector<Bullet>& bulletVec, hero player);
        sf::Vector2f getDirVec(hero player);
        float getDirDeg(sf::Vector2f);
};