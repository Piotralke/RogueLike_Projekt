#pragma once
#include "Animation.h"
#include "Bullet.h"
#include "SFML/Graphics.hpp"

class hero
{
protected:
    float speed;
    float maxHealth;
    float health;
    float damage;
    int money=100;
    bool faceRight;
    unsigned int row=0;
    float fire_rate;
    float shot_speed; 
    sf::Clock fire_delay_clock;
    bool flying;
    sf::Texture* arrow;
    sf::Texture wings_t;
    sf::RectangleShape wings;
public:
    int x = 5, y = 5;
    sf::RectangleShape body;
    Animation animation;
    hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health,
        float damage, sf::Vector2f size, sf::Vector2f position, bool flying, sf::Texture* arrow);
    void DrawStats(sf::RenderWindow& window, sf::Font& font);
    void Draw(sf::RenderWindow& window);
    void Update(float deltaTime, std::vector<Bullet> &bulletVec);
    sf::Vector2f GetPosition();
    float getDamage();
    float getHealth();
    float getSpeed();
    float getShotSpeed();
    float getFireDelay();
    int getMoney();
    bool getFlying();
    void getHit(float damage);
    void setStatistics(float damage, float health,float maxHealth, float fire_delay, float shot_speed, float speed,int money,bool flying);
};