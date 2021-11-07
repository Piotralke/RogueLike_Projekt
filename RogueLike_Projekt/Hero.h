#pragma once
#include "Animation.h"
#include "Bullet.h"
#include "SFML/Graphics.hpp"

class hero
{
protected:
    float speed = 20.0f;
    float health;
    float damage;
    Animation animation;
    bool faceRight;
    unsigned int row;
    float fire_rate;
    float shot_speed; 
public:
    int x = 5, y = 5;
    sf::RectangleShape body;
    hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate);
    void Draw(sf::RenderWindow& window);
    void Update(float deltaTime, std::vector<Bullet> &bulletVec, sf::Clock &fire_delay_clock, sf::Texture *arrow);
    sf::Vector2f GetPosition();
    void shot(float vec_x, float vec_y); //albo jakis jeden argument, jasli strzelanie byloby tylko pod katem prostym
        // strzelenie w kierunku w ktorym patrzymy od pozycji gracza
};