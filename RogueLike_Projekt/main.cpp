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
#include "Boss.h"

int main()
{
    
    Collision kolizja;
    sf::RectangleShape room_collider_top;
    sf::RectangleShape room_collider_left;
    sf::RectangleShape room_collider_right;
    sf::RectangleShape room_collider_down;
    std::vector<sf::RectangleShape> roomVec;
    room_collider_top.setSize({642,29});
    room_collider_top.setOrigin(room_collider_top.getSize() / 2.0f);
    room_collider_top.setPosition(350, 19);
    roomVec.push_back(room_collider_top);

    room_collider_left.setSize({ 29,400 });
    room_collider_left.setOrigin(room_collider_left.getSize() / 2.0f);
    room_collider_left.setPosition(19, 200); 
    roomVec.push_back(room_collider_left);

    room_collider_right.setSize({ 29,400 });
    room_collider_right.setOrigin(room_collider_right.getSize() / 2.0f);
    room_collider_right.setPosition(681, 200);
    roomVec.push_back(room_collider_right);

    room_collider_down.setSize({ 642,29 });
    room_collider_down.setOrigin(room_collider_down.getSize() / 2.0f);
    room_collider_down.setPosition(350, 381);
    roomVec.push_back(room_collider_down);


    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Texture arrow_texture;
    sf::Texture fire_ball_texture;
    sf::Texture skull_texture;
    sf::Texture hud_texture;
    sf::Sprite hud_sprite;
    hud_texture.loadFromFile("grafiki/hud.png");
    hud_sprite.setTexture(hud_texture);
    hud_sprite.setPosition({700.0f,0.0f});
    arrow_texture.loadFromFile("grafiki/arrow.png");
    fire_ball_texture.loadFromFile("grafiki/fire_ball.png");
    skull_texture.loadFromFile("grafiki/skull.png");
    std::vector<monster> monsterVec;
    std::vector<Object> objectVec;
    std::vector<boss> bossVec;
    sf::RenderWindow window(sf::VideoMode(800, 400), "RogueLike!");
    generate_map* level = new generate_map;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("grafiki/hero_animation.png");
    hero player(&playerTexture, sf::Vector2u(4, 2), 0.1f, 100.0f, 1.0f, 200.0f, 100.0f, 6.0f, { 16.0f,20.0f }, {350.0f,200.0f},false);
    
    sf::Texture bootsTexture;
    bootsTexture.loadFromFile("grafiki/boots.png");
    Item boots(&bootsTexture, { 200.0f,200.0f }, {16.0f,16.0f},0.0f,0.0f, 0.0f,0.0f,0.0f,50.0f);
    sf::Texture glovesTexture;
    glovesTexture.loadFromFile("grafiki/gloves.png");
    Item gloves(&glovesTexture, { 400.0f,200.0f }, { 16.0f,16.0f }, 0.0f,0.0f, 0.0f, -0.5f, 50.0f, 0.0f);
    sf::Texture helmetTexture;
    helmetTexture.loadFromFile("grafiki/helmet.png");
    Item helmet(&helmetTexture, { 350.0f,300.0f }, { 16.0f,16.0f }, 0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f);
    sf::Texture small_healPotTexture;
    small_healPotTexture.loadFromFile("grafiki/small_healPot.png");
    Item small_healPot(&small_healPotTexture, { 150.0f,300.0f }, { 16.0f,16.0f }, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    sf::Texture big_healPotTexture;
    big_healPotTexture.loadFromFile("grafiki/big_healPot.png");
    Item big_healPot(&big_healPotTexture, { 550.0f,300.0f }, { 16.0f,16.0f }, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    std::vector<Item> itemVec;
    itemVec.push_back(boots);
    itemVec.push_back(gloves);
    itemVec.push_back(helmet);
    itemVec.push_back(small_healPot);
    itemVec.push_back(big_healPot);

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
    sf::Clock invisibility_clock;
    level->wypiszkons();
    level->init_Texture();
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds(); 
        sf::Event event;
        while (window.pollEvent(event)) 
        { 
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.Update(deltaTime,bulletVec,&arrow_texture);
        for (int i = 0; i < bossVec.size(); i++)
        {
            bossVec.at(i).Update(deltaTime, &skull_texture, monsterBulletVec, monsterVec, player,&level->ghostTexture);
        }
        for (int i = 0; i < monsterVec.size(); i++)
        {
            monsterVec.at(i).Update(deltaTime, &fire_ball_texture, monsterBulletVec, player);
        }
        for (int i = 0; i < objectVec.size(); i++)
        {
            kolizja.check_Collision(player.body, objectVec.at(i).shape);
        }

        for (int i = 0; i < bulletVec.size(); i++)
        {
            bulletVec.at(i).fire(deltaTime);

            for (int j = 0; j < roomVec.size(); j++) {
                if (!(bulletVec.empty()) && kolizja.check_Collision(bulletVec.at(i).bullet, roomVec.at(j)))
                {
                    bulletVec.erase(bulletVec.begin() + i);
                    if (i != 0)
                        i--;
                    break;
                }

            }
         
            if (!(bulletVec.empty()))
            for (int k = 0; k < monsterVec.size(); k++)
            {
                if (!(monsterVec.empty()) && kolizja.check_Collision(bulletVec.at(i).bullet, monsterVec.at(k).body))
                {
                    monsterVec.at(k).getHit(player.getDamage());
                    bulletVec.erase(bulletVec.begin() + i);
                    if (i != 0)
                        i--;
              
                    break;
                }
            }

            if (!(bulletVec.empty()))
            for (int l = 0; l < bossVec.size(); l++)
            {
                if (!(bossVec.empty()) && kolizja.check_Collision(bulletVec.at(i).bullet, bossVec.at(l).body))
                {
                    bossVec.at(l).getHit(player.getDamage());
                    bulletVec.erase(bulletVec.begin() + i);
                    if (i != 0)
                        i--;

                    break;
                }
            }

            if (!(bulletVec.empty()))
            for (int m = 0; m < objectVec.size(); m++) {
                if (!(bulletVec.empty()) && objectVec.at(m).shootable==false)
                    if(kolizja.check_Collision(bulletVec.at(i).bullet, objectVec.at(m).shape))
                {
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
            for (int j = 0; j < roomVec.size(); j++) {
                if (!(monsterBulletVec.empty()) && kolizja.check_Collision(monsterBulletVec.at(i).bullet, roomVec.at(j)))
                {
                    monsterBulletVec.erase(monsterBulletVec.begin() + i);
                    if (i != 0)
                        i--;
                    break;
                }

            }

            if (!(monsterBulletVec.empty()) && kolizja.check_Collision(monsterBulletVec.at(i).bullet, player.body))
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
            if(!(monsterBulletVec.empty()))
            for (int m = 0; m < objectVec.size(); m++) {
                if(objectVec.at(m).shootable==false)
                    if (!(monsterBulletVec.empty()) && kolizja.check_Collision(monsterBulletVec.at(i).bullet, objectVec.at(m).shape))
                    {
                        monsterBulletVec.erase(monsterBulletVec.begin() + i);
                        if (i != 0)
                        i--;
                        break;
                    }

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

            if (!(monsterVec.empty()) && !(monsterVec.at(i).getFlying()) )    
            for (int j = 0; j < objectVec.size(); j++)
            {
                kolizja.check_Collision(monsterVec.at(i).body, objectVec.at(j).shape);
            }

            if(!(monsterVec.empty()))
                 for (int k = 0; k < roomVec.size(); k++) {
                    kolizja.check_Collision(monsterVec.at(i).body, roomVec.at(k));
                 }

        }

        for (int i = 0; i < bossVec.size(); i++)
        {
           if (!(bossVec.empty()) && kolizja.check_Collision(bossVec.at(i).body, player.body))
           {
               if (invisibility_clock.getElapsedTime().asSeconds() >= 1.0f)
               {
                   player.getHit(bossVec.at(i).getDamage());
                   invisibility_clock.restart();
               }
           }
         
           if (!(bossVec.empty()) && bossVec.at(i).getHealth() <= 0.0f)
           {
               bossVec.erase(bossVec.begin() + i);
               if (i != 0)
                   i--;
               break;
           }
         
           if (!(bossVec.empty()) && !(bossVec.at(i).getFlying()))
               for (int j = 0; j < objectVec.size(); j++)
               {
                   kolizja.check_Collision(bossVec.at(i).body, objectVec.at(j).shape);
               }
         
           if (!(bossVec.empty()))
               for (int k = 0; k < roomVec.size(); k++) {
                   kolizja.check_Collision(bossVec.at(i).body, roomVec.at(k));
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
        
        for (int i = 0; i < roomVec.size(); i++) {
            kolizja.check_Collision(player.body, roomVec.at(i));
        }
        
        window.clear();
        window.draw(level->background_s);
        level->pick_room_layout(player,kolizja,window, bulletVec, monsterBulletVec, monsterVec, objectVec, bossVec);
        for (int i = 0; i < objectVec.size(); i++)
        {
            objectVec.at(i).Draw(window);
        }
        for (int i = 0; i < bulletVec.size(); i++)
        {
            bulletVec.at(i).Draw(window);
        }
        
        for (int i = 0; i < monsterBulletVec.size(); i++) 
        {
            monsterBulletVec.at(i).Draw(window);
        }    
        for (int i = 0; i < monsterVec.size(); i++)
        {
            monsterVec.at(i).Draw(window);
        }
        for (int i = 0; i < bossVec.size(); i++)
        {
            bossVec.at(i).Draw(window);
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
