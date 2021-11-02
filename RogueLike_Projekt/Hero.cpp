#include "Hero.h"
#include <iostream>

hero::hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
    animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    row = 0;
    faceRight = true;

    body.setSize(sf::Vector2f(16.0f, 28.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(100.0f, 100.0f);
    body.setTexture(texture);
}

void hero::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

void hero::Update(float deltaTime)
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

    /*if (body.getPosition().x < 32)
    {
        y--;
        body.setPosition({ 660, body.getPosition().y });
        std::cout << y << std::endl;
    }
        
    else if (body.getPosition().x > 668)
    {
        y++;
        body.setPosition({ 40, body.getPosition().y });
        std::cout << y << std::endl;
    }
        
    else if (body.getPosition().y < 32)
    {
        x--;
        body.setPosition({ body.getPosition().x, 360 });
        std::cout << x << std::endl;
    }
        
    else if (body.getPosition().y > 368)
    {
        x++;
        body.setPosition({ body.getPosition().x, 40 });
        std::cout << x << std::endl;
    }*/
       



    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
}

sf::Vector2f hero::GetPosition()
{
    return body.getPosition();
}
