#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Animation.h"
#include "Hero.h"
#include "Bullet.h"
#include "Monster.h"
#include "Room.h"
#include "Generator.h"
#include "Item.h"

int main()
{
    Collision kolizja;
    sf::RectangleShape room_collider_top;
    sf::RectangleShape room_collider_left;
    sf::RectangleShape room_collider_right;
    sf::RectangleShape room_collider_down;
    room_collider_top.setSize({642,29});
    room_collider_top.setOrigin(room_collider_top.getSize() / 2.0f);
    room_collider_top.setPosition(350, 19);

    room_collider_left.setSize({ 29,400 });
    room_collider_left.setOrigin(room_collider_left.getSize() / 2.0f);
    room_collider_left.setPosition(19, 200); 

    room_collider_right.setSize({ 29,400 });
    room_collider_right.setOrigin(room_collider_right.getSize() / 2.0f);
    room_collider_right.setPosition(681, 200);

    room_collider_down.setSize({ 642,29 });
    room_collider_down.setOrigin(room_collider_down.getSize() / 2.0f);
    room_collider_down.setPosition(350, 381);

    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Texture arrow_texture;
    sf::Texture fire_ball_texture;
    sf::Texture hud_texture;
    sf::Sprite hud_sprite;
    hud_texture.loadFromFile("grafiki/hud.png");
    hud_sprite.setTexture(hud_texture);
    hud_sprite.setPosition({700.0f,0.0f});
    arrow_texture.loadFromFile("grafiki/arrow.png");
    fire_ball_texture.loadFromFile("grafiki/fire_ball.png");
    std::vector<monster> monsterVec;
    sf::RenderWindow window(sf::VideoMode(800, 400), "RogueLike!");
    generate_map* level = new generate_map;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("grafiki/hero_animation.png");
    hero player(&playerTexture, sf::Vector2u(4, 2), 0.1f, 100.0f, 1.0f, 200.0f, 100.0f, 6.0f, { 16.0f,20.0f }, {350.0f,200.0f});
    sf::Texture wizardTexture;
    wizardTexture.loadFromFile("grafiki/wizard_animation.png");
    sf::Texture ghostTexture;
    ghostTexture.loadFromFile("grafiki/ghost_animation.png");
    monster wizard(&wizardTexture, sf::Vector2u(4, 1), 0.1f, 0.0f, 1.5f, 150.0f, 30.0f, 10.0f, { 16.0f,20.0f }, {100.0f,100.0f}, true);
    monster ghost(&ghostTexture, sf::Vector2u(4, 1), 0.1f, 75.0f, 1.5f, 150.0f, 30.0f, 4.0f ,{ 12.0f,17.0f }, {600.0f,100.0f}, false);
    monsterVec.push_back(ghost);
    monsterVec.push_back(wizard);
    sf::Texture bootsTexture;
    bootsTexture.loadFromFile("grafiki/boots.png");
    Item boots(&bootsTexture, { 200.0f,200.0f }, {16.0f,16.0f},0.0f,0.0f,0.0f,0.0f,50.0f);
    sf::Texture glovesTexture;
    glovesTexture.loadFromFile("grafiki/gloves.png");
    Item gloves(&glovesTexture, { 400.0f,200.0f }, { 16.0f,16.0f }, 0.0f, 0.0f, -0.5f, 50.0f, 0.0f);
    std::vector<Item> itemVec;
    itemVec.push_back(boots);
    itemVec.push_back(gloves);

    sf::RectangleShape kamien;
    kamien.setSize({2,2});
    kamien.setOrigin(kamien.getSize() / 2.0f);
    kamien.setPosition(33.0f, 367.0f);
    kamien.setFillColor(sf::Color());
    std::vector<Bullet> bulletVec;
    std::vector<Bullet> monsterBulletVec;
    srand(time(NULL));
    level->init_grid();
    level->max_level_counter(1);
    level->visit(5, 5);
    level->generate_layout();
    std::cout << level->random_layout(5, 5) << std::endl;
    float deltaTime = 0.0f;
    sf::Clock clock;
    sf::Clock fire_delay_clock;
    sf::Clock monster_fire_delay_clock;
    sf::Clock invisibility_clock;
    level->wypiszkons();
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds(); 
        
        sf::Event event;
        while (window.pollEvent(event)) 
        { 
            if (event.type == sf::Event::Closed)
                window.close();
        }
        player.Update(deltaTime,bulletVec,fire_delay_clock,&arrow_texture);
        for (int j = 0; j < monsterVec.size(); j++)
        {
            monsterVec.at(j).Update(deltaTime, monster_fire_delay_clock, &fire_ball_texture, monsterBulletVec, player);
        }
        for (int i = 0; i < bulletVec.size(); i++)
        {
            bulletVec.at(i).fire(deltaTime);
            if (!(bulletVec.empty()) && kolizja.check_Collision(bulletVec.at(i).bullet, room_collider_top))
            {
                bulletVec.erase(bulletVec.begin() + i);
                if(i!=0)
                    i--;
                break;
            }
            if (!(bulletVec.empty()) && kolizja.check_Collision(bulletVec.at(i).bullet, room_collider_left))
            {
                bulletVec.erase(bulletVec.begin() + i);
                if (i != 0)
                    i--;
                break;
            }
            if (!(bulletVec.empty()) && kolizja.check_Collision(bulletVec.at(i).bullet, room_collider_right))
            {
                bulletVec.erase(bulletVec.begin() + i);
                if (i != 0)
                    i--;
                break;
            }
            if (!(bulletVec.empty()) && kolizja.check_Collision(bulletVec.at(i).bullet, room_collider_down))
            {
                bulletVec.erase(bulletVec.begin() + i);
                if (i != 0)
                    i--;
                break;
            }
            for (int j = 0; j < monsterVec.size(); j++)
            {
                if (!(monsterVec.empty()) && kolizja.check_Collision(bulletVec.at(i).bullet, monsterVec.at(j).body))
                {
                    monsterVec.at(j).getHit(player.getDamage());
                    bulletVec.erase(bulletVec.begin() + i);
                    if (i != 0)
                        i--;
              
                    break;
                }
            }
        }
        for (int i = 0; i < monsterBulletVec.size(); i++)
        {
            monsterBulletVec.at(i).fire(deltaTime);
            if (!(monsterBulletVec.empty()) && kolizja.check_Collision(monsterBulletVec.at(i).bullet, room_collider_top))
            {
                monsterBulletVec.erase(monsterBulletVec.begin() + i);
                if (i != 0)
                    i--;
                break;
            }
            if (!(monsterBulletVec.empty()) && kolizja.check_Collision(monsterBulletVec.at(i).bullet, room_collider_left))
            {
                monsterBulletVec.erase(monsterBulletVec.begin() + i);
                if (i != 0)
                    i--;
                break;
            }
            if (!(monsterBulletVec.empty()) && kolizja.check_Collision(monsterBulletVec.at(i).bullet, room_collider_right))
            {
                monsterBulletVec.erase(monsterBulletVec.begin() + i);
                if (i != 0)
                    i--;
                break;
            }
            if (!(monsterBulletVec.empty()) && kolizja.check_Collision(monsterBulletVec.at(i).bullet, room_collider_down))
            {
                monsterBulletVec.erase(monsterBulletVec.begin() + i);
                if (i != 0)
                    i--;
                break;
            }
            if (kolizja.check_Collision(monsterBulletVec.at(i).bullet, player.body))
            {
                if (invisibility_clock.getElapsedTime().asSeconds() >= 1.0f)
                {
                    player.getHit(monsterBulletVec.at(i).getDamage());
                    invisibility_clock.restart();
                }
                monsterBulletVec.erase(monsterBulletVec.begin() + i);
                if (i != 0)
                    i--;
                break;
            }
        }
        for (int i = 0; i < monsterVec.size(); i++)
        {
            if (!(monsterVec.empty()) && kolizja.check_Collision(monsterVec.at(i).body, player.body))
            {
                if (invisibility_clock.getElapsedTime().asSeconds() >= 1.0f)
                {
                    player.getHit(monsterVec.at(i).getDamage());
                    invisibility_clock.restart();
                }  
            }
            if (!(monsterVec.empty()) && monsterVec.at(i).getHealth() <= 0.0f)
            {
                monsterVec.erase(monsterVec.begin() + i);
                if (i != 0)
                    i--;
                break;
            }
        }
        for (int i = 0; i < itemVec.size(); i++)
        {
            if (!(itemVec.empty()) && kolizja.check_Collision(itemVec.at(i).item, player.body))
            {
                itemVec.at(i).giveItem(&player);
                itemVec.erase(itemVec.begin() + i);
                if (i != 0)
                    i--;
                break;
            }
        }
        //std::cout << "Health: " << player.getHealth() << std::endl;
        //std::cout << "Damage: " << player.getDamage() << std::endl;
        //std::cout << "Speed: " << player.getSpeed() << std::endl;
        //std::cout << "Shot Speed: " << player.getShotSpeed() << std::endl;
        //std::cout << "Fire rate: " << player.getFireDelay() << std::endl;
        //std::cout << std::endl;
        kolizja.check_Collision(player.body, kamien);
        kolizja.check_Collision(player.body, room_collider_top);
        kolizja.check_Collision(player.body, room_collider_left);
        kolizja.check_Collision(player.body, room_collider_right);
        kolizja.check_Collision(player.body, room_collider_down);
        
        window.clear();
        window.draw(level->background_s);
        level->pick_room_layout(player,kolizja,window, bulletVec, monsterBulletVec);
        for (int i = 0; i < bulletVec.size(); i++)
        {
            bulletVec.at(i).Draw(window);
        }
        for (int i = 0; i < monsterBulletVec.size(); i++)
            monsterBulletVec.at(i).Draw(window);
        for (int j = 0; j < monsterVec.size(); j++)
        {
            monsterVec.at(j).Draw(window);
        }
        for (int i = 0; i < itemVec.size(); i++)
        {
            itemVec.at(i).Draw(window);
        }
        player.Draw(window);
        window.draw(hud_sprite);
        player.DrawStats(window, font);
        level->wypisz(window, player);
        window.display();
    }

    return 0;
}
