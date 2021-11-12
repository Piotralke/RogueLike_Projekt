#pragma once
#include "Animation.h"
#include "Bullet.h"
#include "SFML/Graphics.hpp"

class hero
{
protected:
    float speed;
    float health;
    float damage;
    bool faceRight;
    unsigned int row;
    float fire_rate;
    float shot_speed; 
public:
    int x = 5, y = 5;
    sf::RectangleShape body;
    Animation animation;
    hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health,
        float damage, sf::Vector2f size, sf::Vector2f position);
    void Draw(sf::RenderWindow& window);
    void Update(float deltaTime, std::vector<Bullet> &bulletVec, sf::Clock &fire_delay_clock, sf::Texture *arrow);
    sf::Vector2f GetPosition();
    float getDamage();
    float getHealth();
    float getSpeed();
    float getShotSpeed();
    float getFireDelay();
    void getHit(float damage);
    void setStatistics(float damage, float health, float fire_delay, float shot_speed, float speed);
};