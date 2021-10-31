#pragma once
#include "Animation.h"
#include "SFML/Graphics.hpp"

class hero
{
protected:
    float speed = 20.0f;
    float health;
    float damage;
    sf::RectangleShape body;
    Animation animation;
    bool faceRight;
    unsigned int row;
    float fire_rate;
    //float shot_speed; (?)
    float range;
public:
    int x = 5, y = 5;
    hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    void Draw(sf::RenderWindow& window);
    void Update(float deltaTime);
    sf::Vector2f GetPosition();
    void shot(float vec_x, float vec_y); //albo jakis jeden argument, jasli strzelanie byloby tylko pod katem prostym
        // strzelenie w kierunku w ktorym patrzymy od pozycji gracza
    void move(int x_dir, int y_dir);
        //modyfikacja pozycji gracza w zaleznosci od kierunku poruszania sie
};