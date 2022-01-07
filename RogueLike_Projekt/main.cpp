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
    
    sf::Texture hud_texture;
    sf::Sprite hud_sprite;
    hud_texture.loadFromFile("grafiki/hud.png");
    hud_sprite.setTexture(hud_texture);
    hud_sprite.setPosition({700.0f,0.0f});
    sf::Texture player_arrow;
    player_arrow.loadFromFile("grafiki/arrow.png");
    std::vector<monster> monsterVec;
    std::vector<Object> objectVec;
    std::vector<boss> bossVec;
    sf::RenderWindow window(sf::VideoMode(800, 400), "RogueLike!");
    generate_map* level = new generate_map;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("grafiki/hero_animation.png");
    hero player(&playerTexture, sf::Vector2u(4, 2), 0.1f, 200.0f, 1.0f, 200.0f, 100.0f, 60.0f, { 16.0f,20.0f }, {350.0f,200.0f},false,&player_arrow);
    
    sf::Texture coinTexture;
    coinTexture.loadFromFile("grafiki/coin.png");
    sf::Texture ladderTexture;
    ladderTexture.loadFromFile("grafiki/ladder.png");
    std::vector<Item> itemVec;
    int levels = 1;
    bool created = false;
    std::vector<Bullet> bulletVec;
    std::vector<Bullet> monsterBulletVec;
    srand(time(NULL));
    level->init_grid();
    level->max_level_counter(levels);
    level->visit(5, 5);
    level->generate_layout();
    //std::cout << level->random_layout(5, 5) << std::endl;
    float deltaTime = 0.0f;
    int skeleton_count = 0;
    int dead_skeleton = 0;
    sf::Clock clock;
    sf::Clock invisibility_clock;
    level->wypiszkons();
    level->init_Texture();
    level->read_from_file(player, monsterVec, objectVec, bossVec, itemVec, skeleton_count);
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds(); 
        sf::Event event;
        while (window.pollEvent(event)) 
        { 
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.Update(deltaTime,bulletVec);
        for (int i = 0; i < bossVec.size(); i++)
        {
            bossVec.at(i).Update(deltaTime, monsterBulletVec, monsterVec, player,&level->ghostTexture);
        }
        for (int i = 0; i < monsterVec.size(); i++)
        {
            monsterVec.at(i).Update(deltaTime, monsterBulletVec, monsterVec, player, skeleton_count, dead_skeleton);
        }

        for (int i = 0; i < objectVec.size(); i++)
        {
            if(objectVec.at(i).go_down == false && player.getFlying() == false)
            {
                kolizja.check_Collision(player.body, objectVec.at(i).shape);
            }
            else if(objectVec.at(i).go_down == true && (kolizja.check_Collision(player.body, objectVec.at(i).shape)))
            {
                levels++;
                level->init_grid();
                level->max_level_counter(levels);
                level->visit(5, 5);
                level->generate_layout();
                player.x = 5;
                player.y = 5;
                level->read_from_file(player, monsterVec, objectVec, bossVec, itemVec, skeleton_count);
                bulletVec.clear();
                bulletVec = std::vector<Bullet>();
                monsterBulletVec.clear();
                monsterBulletVec = std::vector<Bullet>();
                objectVec.clear();
                objectVec = std::vector<Object>();
                itemVec.clear();
                itemVec = std::vector<Item>();
                monsterVec.clear();
                monsterVec = std::vector<monster>();
                bossVec.clear();
                bossVec = std::vector<boss>();
                created = false;
            }

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

            if (!(monsterVec.empty()) && monsterVec.at(i).getHealth() <= 0.0f && monsterVec.at(i).resurection == false)
            {
                int random = rand() % 2;
                if (random == 0)
                {
                    Item coin(&coinTexture, monsterVec.at(i).GetPosition(), { 8.0f,8.0f }, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1);
                    itemVec.push_back(coin);
                }
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
           if (monsterVec.empty() && bossVec.empty() || itemVec.at(i).getMoney() > 0)
           {
               if (!(itemVec.empty()) && itemVec.at(i).item.getGlobalBounds().intersects(player.body.getGlobalBounds()) &&player.getMoney()>=itemVec.at(i).getValue())
               {
                   itemVec.at(i).giveItem(&player);
                   player.setStatistics(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -itemVec.at(i).getValue(),false);
                   itemVec.erase(itemVec.begin() + i);
                   if (i != 0)
                       i--;
                   break;
               }
           }
           
       }

        
        for (int i = 0; i < roomVec.size(); i++) {
            kolizja.check_Collision(player.body, roomVec.at(i));
        }
        
        window.clear();
        window.draw(level->background_s);
        level->pick_room_layout(player,kolizja,window, bulletVec, monsterBulletVec, monsterVec, objectVec, bossVec,itemVec, skeleton_count);
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
            if (monsterVec.empty() && bossVec.empty() || itemVec.at(i).getMoney() > 0)
             itemVec.at(i).Draw(window,font);
        }
        if (level->getRoomType(player) == 2 && bossVec.empty() && monsterVec.empty() && !created)
            {
            Object ladder(&ladderTexture, { 350.0f,200.0f }, { 16.0f,16.0f }, true, true);
            objectVec.push_back(ladder);
            created = true;
            }

        sf::Text lvl_text;
        std::string lvl_string;
        lvl_text.setFont(font);
        lvl_text.setCharacterSize(8);
        lvl_text.setFillColor(sf::Color::White);
        lvl_string = std::to_string(levels);
        lvl_text.setString(lvl_string);
        lvl_text.setPosition({ 740.0f,213.0f });

        player.Draw(window);
        window.draw(hud_sprite);
        window.draw(lvl_text);
        player.DrawStats(window, font);
        level->wypisz(window, player);
        window.display();
    }

    return 0;
}
