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

void hero::DrawStats(sf::RenderWindow& window, sf::Font& font)
{
    sf::Text health_text;
    std::string health_string;
    health_text.setFont(font);
    health_text.setCharacterSize(8);
    health_text.setFillColor(sf::Color::White);
    health_string = std::to_string(health);
    health_string.erase(health_string.size() - 4, 4);
    health_text.setString(health_string);
    health_text.setPosition({ 740.0f,102.0f });

    sf::Text damage_text;
    std::string damage_string;
    damage_text.setFont(font);
    damage_text.setCharacterSize(8);
    damage_text.setFillColor(sf::Color::White);
    damage_string = std::to_string(damage);
    damage_string.erase(damage_string.size() - 4, 4);
    damage_text.setString(damage_string);
    damage_text.setPosition({ 740.0f,120.0f });

    sf::Text shot_speed_text;
    std::string shot_speed_string;
    shot_speed_text.setFont(font);
    shot_speed_text.setCharacterSize(8);
    shot_speed_text.setFillColor(sf::Color::White);
    shot_speed_string = std::to_string(shot_speed);
    shot_speed_string.erase(shot_speed_string.size() - 4, 4);
    shot_speed_text.setString(shot_speed_string);
    shot_speed_text.setPosition({ 740.0f,140.0f });

    sf::Text fire_rate_text;
    std::string fire_rate_string;
    fire_rate_text.setFont(font);
    fire_rate_text.setCharacterSize(8);
    fire_rate_text.setFillColor(sf::Color::White);
    fire_rate_string = std::to_string(fire_rate);
    fire_rate_string.erase(fire_rate_string.size() - 4, 4);
    fire_rate_text.setString(fire_rate_string);
    fire_rate_text.setPosition({ 740.0f,158.0f });

    sf::Text speed_text;
    std::string speed_string;
    speed_text.setFont(font);
    speed_text.setCharacterSize(8);
    speed_text.setFillColor(sf::Color::White);
    speed_string = std::to_string(speed);
    speed_string.erase(speed_string.size() - 4, 4);
    speed_text.setString(speed_string);
    speed_text.setPosition({ 740.0f,176.0f });

    // y dla coinow 196.0f

    window.draw(health_text);
    window.draw(damage_text);
    window.draw(shot_speed_text);
    window.draw(fire_rate_text);
    window.draw(speed_text);
}

void hero::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

void hero::Update(float deltaTime, std::vector<Bullet> &bulletVec, sf::Texture *arrow)
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
