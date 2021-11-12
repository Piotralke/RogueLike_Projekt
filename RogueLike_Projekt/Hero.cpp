#include "Hero.h"
#include <iostream>
hero::hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health,
    float damage, sf::Vector2f size, sf::Vector2f position) :
    animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    this->fire_rate = fire_rate;
    this->shot_speed = shot_speed;
    this->health = health;
    this->damage = damage;
    row = 0;
    faceRight = true;

    body.setSize(size);
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    body.setTexture(texture);
}

void hero::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

void hero::Update(float deltaTime, std::vector<Bullet> &bulletVec, sf::Clock &fire_delay_clock, sf::Texture *arrow)
{
    sf::Vector2f movement(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        movement.y -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        movement.y += speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        movement.x -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        movement.x += speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate)
        {
            Bullet newBullet({ 7,19 }, body.getPosition(), shot_speed, damage, {0.0f, -1.0f}, arrow, 0.0f);
            bulletVec.push_back(newBullet);
            fire_delay_clock.restart();
        }

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate)
        {
            Bullet newBullet({ 7,19 }, body.getPosition(), shot_speed, damage, { 0.0f, 1.0f }, arrow, 180.0f);
            bulletVec.push_back(newBullet);
            fire_delay_clock.restart();
        }
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate)
        {
            Bullet newBullet({ 7,19 }, body.getPosition(), shot_speed, damage, { -1.0f, 0.0f }, arrow, -90.0f);
            bulletVec.push_back(newBullet);
            fire_delay_clock.restart();
        }
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate)
        {
            Bullet newBullet({ 7,19 }, body.getPosition(), shot_speed, damage, { 1.0f, 0.0f }, arrow, 90.0f);
            bulletVec.push_back(newBullet);
            fire_delay_clock.restart();
        }
        
    }
    if (movement.x == 0.0f)
    {
        row = 0;
    }
    else
    {
        row = 1;
        if (movement.x > 0.0f)
            faceRight = true;
        else
            faceRight = false;
    }
    if (movement.y != 0.0f)
        row = 1;

    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
}

sf::Vector2f hero::GetPosition()
{
    return body.getPosition();
}

float hero::getDamage()
{
    return damage;
}
float hero::getHealth()
{
    return health;
}
float hero::getSpeed()
{
    return speed;
}
float hero::getShotSpeed()
{
    return shot_speed;
}
float hero::getFireDelay()
{
    return fire_rate;
}
void hero::getHit(float damage)
{
    health -= damage;
}
void hero::setStatistics(float damage, float health, float fire_delay, float shot_speed, float speed)
{
    this->damage += damage;
    this->health += health;
    this->fire_rate += fire_delay;
    this->shot_speed += shot_speed;
    this->speed += speed;
}
