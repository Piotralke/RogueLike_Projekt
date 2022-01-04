#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Bullet.h"
#include "Animation.h"
#define PI 3.141592;

class monster : public hero
{
    protected:
        bool shooting;
        sf::Clock animation_clock;
        sf::Clock jump_clock;
        float memSpeed;
        float memHealth;
        bool dead = false;
    public:
        bool resurection;
        monster(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health, 
            float damage, sf::Vector2f size, sf::Vector2f position, bool shooting, bool flying, bool resurection)
            :hero(texture, imageCount, switchTime, speed, fire_rate, shot_speed, health,damage, size, position,flying), shooting(shooting), resurection(resurection), memHealth(health), memSpeed(speed) {}
        sf::Vector2f getDirVec(hero player);
        float getDirDeg(sf::Vector2f);
        void Update(float deltaTime, sf::Texture* arrow, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, int& skeleton_count,int& dead_skeleton);
        
};