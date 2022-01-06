#include "Room.h"

void room::init_Texture() {
    wizardTexture.loadFromFile("grafiki/wizard_animation.png");
    ghostTexture.loadFromFile("grafiki/ghost_animation.png");
    skeletonTexture.loadFromFile("grafiki/skeleton_animation.png");
    zombieTexture.loadFromFile("grafiki/zombie_animation.png");
    demonTexture.loadFromFile("grafiki/demon_animation.png");
    spiderTexture.loadFromFile("grafiki/spider_animation.png");
    elfTexture.loadFromFile("grafiki/dark_elf_animation.png");
    slimeTexture.loadFromFile("grafiki/slime_animation.png");
    trollTexture.loadFromFile("grafiki/troll_animation.png");
    towerTexture.loadFromFile("grafiki/tower.png");

    rockTexture.loadFromFile("grafiki/rock.png");
    bonesTexture.loadFromFile("grafiki/bone_pile.png");
    holeTexture.loadFromFile("grafiki/hole.png");
    barrelTexture.loadFromFile("grafiki/barrel.png");
    crateTexture.loadFromFile("grafiki/crate.png");
    ladderTexture.loadFromFile("grafiki/ladder.png");

    necromancerTexture.loadFromFile("grafiki/necromancer.png");
    brother1Texture.loadFromFile("grafiki/brother1.png");
    brother2Texture.loadFromFile("grafiki/brother2.png");

    arrow_texture.loadFromFile("grafiki/arrow.png");
    fire_ball_texture.loadFromFile("grafiki/fire_ball.png");
    skull_texture.loadFromFile("grafiki/skull.png");
    slime_ball_texture.loadFromFile("grafiki/slime_ball.png");
    bone_texture.loadFromFile("grafiki/bone.png");
    cannon_ball_texture.loadFromFile("grafiki/cannon_ball.png");

    small_healPotTexture.loadFromFile("grafiki/small_healPot.png");
    big_healPotTexture.loadFromFile("grafiki/big_healPot.png");

    bootsTexture.loadFromFile("grafiki/boots.png");
    glovesTexture.loadFromFile("grafiki/gloves.png");
    helmetTexture.loadFromFile("grafiki/helmet.png");
    wingsTexture.loadFromFile("grafiki/wings_item.png");

    Item boots(&bootsTexture, { 350.0f,200.0f }, { 16.0f,16.0f }, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 50.0f, 0);
    Item gloves(&glovesTexture, { 350.0f,200.0f }, { 16.0f,16.0f }, 0.0f, 0.0f, 0.0f, -0.5f, 50.0f, 0.0f, 0);
    Item helmet(&helmetTexture, { 350.0f,200.0f }, { 16.0f,16.0f }, 0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0);
  //  Item wings(&wingsTexture, { 350.0f,200.0f }, { 28.0f,32.0f }, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0,true);

    noValueItems.push_back(boots);
    noValueItems.push_back(gloves);
    noValueItems.push_back(helmet);
 //   noValueItems.push_back(wings);
    
    Item bootsv(&bootsTexture, { 350.0f,200.0f }, { 16.0f,16.0f }, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 50.0f, 0,20);
    Item glovesv(&glovesTexture, { 350.0f,200.0f }, { 16.0f,16.0f }, 0.0f, 0.0f, 0.0f, -0.5f, 50.0f, 0.0f, 0,20);
    Item helmetv(&helmetTexture, { 350.0f,200.0f }, { 16.0f,16.0f }, 0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0,20);
    Item wingsv(&wingsTexture, { 350.0f,200.0f }, { 16.0f,16.0f }, 0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0,100, true);

    valueItems.push_back(bootsv);
    valueItems.push_back(glovesv);
    valueItems.push_back(helmetv);
    valueItems.push_back(wingsv);

}

int room::check_doors(int i, int j)
{
    int room_doors = 0b0000;
    if (grid[i][j - 1].exist == 1)
        room_doors ^= 0b0001;   //lewe drzwi
    if (grid[i][j + 1].exist == 1)
        room_doors ^= 0b0010;    //prawe drzwi
    if (grid[i + 1][j].exist == 1)
        room_doors ^= 0b0100;   //dolne drzwi
    if (grid[i - 1][j].exist == 1)
        room_doors ^= 0b1000;   //gorne drzwi
    return room_doors;

}
void room::Draw(sf::RenderWindow& window, sf::RectangleShape& door)
{
    window.draw(door);
}

void room::read_from_file(hero& player, std::vector<monster>& monsterVEC, std::vector<Object>& objectVEC, std::vector<boss>& bossVec, std::vector<Item>& itemVec, int& skeleton_count)
{
    std::ifstream read(grid[player.x][player.y].sciezka);
    
    if (read.is_open())
    {
        
        char znak;
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 21; j++)
            {
                read >> znak;
                if (znak == '0')        //0-9 MONSTER
                {
                   // if (!grid[player.x][player.y].visited)
                    {
                        monster wizard(&wizardTexture, sf::Vector2u(4, 1), 0.1f, 0.0f, 1.5f, 150.0f, 30.0f, 10.0f, { 16.0f,20.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, true, false, false, &fire_ball_texture, { 8,8 });
                        monsterVEC.push_back(wizard);
                    }
                    
                }
                else if (znak == '1')
                {
                   // if (!grid[player.x][player.y].visited)
                    {
                        monster ghost(&ghostTexture, sf::Vector2u(4, 1), 0.1f, 75.0f, 0.0f, 0.0f, 30.0f, 5.0f, { 12.0f,17.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, false, true, false, NULL, { 0,0 });
                        monsterVEC.push_back(ghost);
                    }
                   
                }
                else if (znak == '2')
                {
                  //  if (!grid[player.x][player.y].visited)
                    {
                        monster skeleton(&skeletonTexture, sf::Vector2u(4, 2), 0.1f, 65.0f, 0.0f, 0.0f, 15.0f, 4.0f, { 10.0f,16.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, false, false, true, NULL, { 0,0 });
                        monsterVEC.push_back(skeleton);
                        skeleton_count++;
                    }
                }
                else if (znak == '3')
                {
                 //   if (!grid[player.x][player.y].visited)
                    {
                        monster zombie(&zombieTexture, sf::Vector2u(4, 1), 0.15f, 40.0f, 0.0f, 0.0f, 50.0f, 15.0f, { 20.0f,33.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, false, false, false, NULL, { 0,0 });
                        monsterVEC.push_back(zombie);
                    }
                }
                else if (znak == '4')
                {
                //    if (!grid[player.x][player.y].visited)
                    {
                        monster demon(&demonTexture, sf::Vector2u(4, 1), 0.1f, 110.0f, 0.0f, 0.0f, 10.0f, 6.0f, { 14.0f,22.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, false, false, false, NULL, { 0,0 });
                        monsterVEC.push_back(demon);
                    }
                }
                else if (znak == '5')
                {
                  //  if (!grid[player.x][player.y].visited)
                    {
                        monster spider(&spiderTexture, sf::Vector2u(9, 2), 0.1f, 170.0f, 0.0f, 0.0f, 10.0f, 4.0f, { 14.0f,13.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, false, false, false, NULL, { 0,0 });
                        monsterVEC.push_back(spider);
                    }
                }
                else if (znak == '6')
                {
                  //  if (!grid[player.x][player.y].visited)
                    {
                        monster elf(&elfTexture, sf::Vector2u(4, 2), 0.1f, 150.0f, 2.5f, 170.0f, 30.0f, 9.0f, { 16.0f,20.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, true, false, false, &arrow_texture, { 7,19 });
                        monsterVEC.push_back(elf);
                    }
                }
                else if (znak == '7')
                {
                 //   if (!grid[player.x][player.y].visited)
                    {
                        monster slime(&slimeTexture, sf::Vector2u(4, 3), 0.1f, 0.0f, 1.0f, 110.0f, 25.0f, 5.0f, { 16.0f,16.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, true, false, false, &slime_ball_texture, { 8,9 }, true);
                        monsterVEC.push_back(slime);
                    }
                }
                else if (znak == '8')
                {
               //     if (!grid[player.x][player.y].visited)
                    {
                        monster troll(&trollTexture, sf::Vector2u(4, 1), 0.1f, 70.0f, 2.0f, 130.0f, 20.0f, 7.0f, { 13.0f,18.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, true, false, false, &bone_texture, { 7,15 });
                        monsterVEC.push_back(troll);
                    }
                }
                else if (znak == '9')
                {
                   // if (!grid[player.x][player.y].visited)
                    {
                        monster tower(&towerTexture, sf::Vector2u(1, 1), 0.1f, 0.0f, 2.5f, 200.0f, 50.0f, 10.0f, { 18.0f,30.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, true, false, false, &cannon_ball_texture, { 11,11 });
                        monsterVEC.push_back(tower);
                    }
                }
                else if (znak == 'a')
                {
                    Object rock(&rockTexture, { 50.0f + 30 * j,50.0f + 30 * i }, {30.0f,30.0f}, false);
                    objectVEC.push_back(rock);
                }
                else if (znak == 'b')
                {
                    Object bones(&bonesTexture, { 50.0f + 30 * j,50.0f + 30 * i }, { 30.0f,30.0f }, false);
                    objectVEC.push_back(bones);
                }
                else if (znak == 'c')
                {
                    Object hole(&holeTexture, { 50.0f + 30 * j,50.0f + 30 * i }, { 30.0f,30.0f }, true);
                    objectVEC.push_back(hole);
                }
                else if (znak == 'd')
                {
                    Object barrel(&barrelTexture, { 50.0f + 30 * j,50.0f + 30 * i }, { 30.0f,30.0f }, false);
                    objectVEC.push_back(barrel);
                }
                else if (znak == 'e')
                {
                     Object crate(&crateTexture, { 50.0f + 30 * j,50.0f + 30 * i }, { 30.0f,30.0f }, false);
                     objectVEC.push_back(crate);
                }
                else if (znak == 'A')   //A-E boss
                {
              //      if (!grid[player.x][player.y].visited)
                    {
                        boss necromancer(&necromancerTexture, sf::Vector2u(3, 2), 0.1f, 120.0f, 2.3f, 120.0f, 140.0f, 15.0f, { 27.0f,40.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, true, false, false,true, true, true,&skull_texture, { 10,10 });
                        bossVec.push_back(necromancer);
                    }
                    

                }
                else if (znak == 'B')
                {
            //    if (!grid[player.x][player.y].visited)
                {
                    boss brother1(&brother1Texture, sf::Vector2u(8, 1), 0.1f, 80.0f, 0.0f, 0.0f, 120.0f, 15.0f, { 34.0f,46.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, false, false, false,false, false,false, NULL, { 0,0 });
                    bossVec.push_back(brother1);
                }
                }
                else if (znak == 'C')
                {
         //       if (!grid[player.x][player.y].visited)
                {
                    boss brother2(&brother2Texture, sf::Vector2u(12, 2), 0.1f, 100.0f, 1.4f, 120.0f, 80.0f, 15.0f, { 30.0f,44.0f }, { 50.0f + 30 * j,50.0f + 30 * i }, true, false, false, false, false,true, &arrow_texture, { 7,19 });
                    bossVec.push_back(brother2);
                }
                }
                else if (znak == 'D')
                {

                }
                else if (znak == 'E')
                {

                }
                else if (znak == 'I') //item
                {
                if (!grid[player.x][player.y].visited)
                {
                    int random = rand() % noValueItems.size();
                    noValueItems.at(random).item.setPosition({ 50.0f + 30 * j,50.0f + 30 * i });
                    itemRoomVec.push_back(noValueItems.at(random));
                }   
                }
                else if (znak == 'p') //maly potion
                {
          //      if (!grid[player.x][player.y].visited)
                {
                    Item small_healPot(&small_healPotTexture, { 50.0f + 30 * j,50.0f + 30 * i }, { 16.0f,16.0f }, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f,0); 
                        itemVec.push_back(small_healPot);
                } 
                }
                else if (znak == 'P') //duzy potion
                {
            //    if (!grid[player.x][player.y].visited)
                {
                    Item big_healPot(&big_healPotTexture, { 50.0f + 30 * j,50.0f + 30 * i }, { 16.0f,16.0f }, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f,0);
                    itemVec.push_back(big_healPot);
                }
               
                }
                else if (znak == '$') // item do kupienia(nwm czy bedzie to potrzebne)
                {
                if (!grid[player.x][player.y].visited)
                {
                    int random = rand() % valueItems.size();
                    valueItems.at(random).item.setPosition({ 50.0f + 30 * j,50.0f + 30 * i });
                    shopItems.push_back(valueItems.at(random));
                }
                      
                }
                else if (znak == 'h') // maly potion do kupienia
                {
                if (!grid[player.x][player.y].visited)
                {
                    Item small_healPot(&small_healPotTexture, { 50.0f + 30 * j,50.0f + 30 * i }, { 16.0f,16.0f }, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 5);
                    shopItems.push_back(small_healPot);
                }
                       
                }
                else if (znak == 'H') // duzy potion do kupienia
                {
                if (!grid[player.x][player.y].visited)
                {
                    Item big_healPot(&big_healPotTexture, { 50.0f + 30 * j,50.0f + 30 * i }, { 16.0f,16.0f }, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 10);
                    shopItems.push_back(big_healPot);
                }
                     
                }
            }
        }
    }
}

void room::pick_room_layout(hero& player, Collision kolizja, sf::RenderWindow& window, std::vector<Bullet>& heroB, std::vector<Bullet>& monsterB,
    std::vector<monster>& monsterVEC, std::vector<Object>& objectVEC, std::vector<boss>& bossVec, std::vector<Item>& itemVec, int& skeleton_count)
{
    if (!monsterVEC.empty() || !bossVec.empty())
    {
        doors_t.loadFromFile("grafiki/doors_c.png");
        doors_bs_t.loadFromFile("grafiki/doors_boss_c.png");
        doors_sh_t.loadFromFile("grafiki/doors_shop_c.png");
        doors_it_t.loadFromFile("grafiki/doors_item_c.png");
    }
    else
    {
        doors_t.loadFromFile("grafiki/doors_o.png");
        doors_bs_t.loadFromFile("grafiki/doors_boss_o.png");
        doors_sh_t.loadFromFile("grafiki/doors_shop_o.png");
        doors_it_t.loadFromFile("grafiki/doors_item_o.png");
    }

    sf::RectangleShape doors;
    doors.setSize({ 32, 32 });
    doors.setOrigin(doors.getSize() / 2.0f);
    int room_doors = check_doors(player.x, player.y);
    //losowanie layaout, o ile nie odwiedzony pokoj
    if (room_doors & 0b0001)
    {
        doors.setPosition(19, 200);
        doors.setRotation(-90.0f);
        if (grid[player.x][player.y - 1].type == 2)
        {
            doors.setTexture(&doors_bs_t);
        }
        else if (grid[player.x][player.y - 1].type == 3)
        {
            doors.setTexture(&doors_sh_t);
        }
        else if (grid[player.x][player.y - 1].type == 4)
        {
            doors.setTexture(&doors_it_t);
        }
        else
        {
            doors.setTexture(&doors_t);
        }
        
        Draw(window, doors);
        if (kolizja.check_Collision(player.body, doors) && monsterVEC.empty() && bossVec.empty())
        {
            heroB.clear();
            heroB = std::vector<Bullet>();
            monsterB.clear();
            monsterB = std::vector<Bullet>();
            objectVEC.clear();
            objectVEC = std::vector<Object>();
            if (grid[player.x][player.y].type == 3)
            {
                shopItems = itemVec;
            }
            else if (grid[player.x][player.y].type == 4)
            {
                itemRoomVec = itemVec;
            }
            itemVec.clear();
            itemVec = std::vector<Item>();
            player.y--;
            player.body.setPosition({ 655, player.body.getPosition().y });
            read_from_file(player,monsterVEC,objectVEC,bossVec, itemVec, skeleton_count);
            if (grid[player.x][player.y].type == 3)
            {
                itemVec = shopItems;
            }
            else if (grid[player.x][player.y].type == 4)
            {
                itemVec = itemRoomVec;
            }
            else if (grid[player.x][player.y].type == 2 && bossVec.empty() && monsterVEC.empty())
            {
                Object ladder(&ladderTexture, { 350.0f,200.0f }, { 16.0f,16.0f }, true, true);
                objectVEC.push_back(ladder);
            }
            grid[player.x][player.y].visited = true;
        }

    }
    if (room_doors & 0b0010)
    {
        doors.setPosition(681, 200);
        doors.setRotation(90.0f);
        if (grid[player.x][player.y + 1].type == 2)
        {
            doors.setTexture(&doors_bs_t);
        }
        else if (grid[player.x][player.y + 1].type == 3)
        {
            doors.setTexture(&doors_sh_t);
        }
        else if (grid[player.x][player.y + 1].type == 4)
        {
            doors.setTexture(&doors_it_t);
        }
        else
        {
            doors.setTexture(&doors_t);
        }
        Draw(window, doors);
        if (kolizja.check_Collision(player.body, doors)&&monsterVEC.empty()&&bossVec.empty())
        {
            heroB.clear();
            heroB = std::vector<Bullet>();
            monsterB.clear();
            monsterB = std::vector<Bullet>();
            objectVEC.clear();
            objectVEC = std::vector<Object>();
            if (grid[player.x][player.y].type == 3)
            {
                shopItems = itemVec;
            }
            else if (grid[player.x][player.y].type == 4)
            {
                itemRoomVec = itemVec;
            }
            itemVec.clear();
            itemVec = std::vector<Item>();
            player.y++;
            player.body.setPosition({ 45, player.body.getPosition().y });
            read_from_file(player, monsterVEC, objectVEC,bossVec, itemVec, skeleton_count);
            if (grid[player.x][player.y].type == 3)
            {
                itemVec = shopItems;
            }
            else if (grid[player.x][player.y].type == 4)
            {
                itemVec = itemRoomVec;
            }
            else if (grid[player.x][player.y].type == 2 && bossVec.empty() && monsterVEC.empty())
            {
                Object ladder(&ladderTexture, { 350.0f,200.0f }, { 16.0f,16.0f }, true, true);
                objectVEC.push_back(ladder);
            }
            grid[player.x][player.y].visited = true;
        }
    }
    if (room_doors & 0b0100)
    {
        doors.setPosition(350, 381);
        doors.setRotation(180.0f);
        if (grid[player.x+1][player.y].type == 2)
        {
            doors.setTexture(&doors_bs_t);
        }
        else if (grid[player.x+1][player.y].type == 3)
        {
            doors.setTexture(&doors_sh_t);
        }
        else if (grid[player.x+1][player.y].type == 4)
        {
            doors.setTexture(&doors_it_t);
        }
        else
        {
            doors.setTexture(&doors_t);
        }
        Draw(window, doors);
        if (kolizja.check_Collision(player.body, doors) && monsterVEC.empty() && bossVec.empty())
        {
            heroB.clear();
            heroB = std::vector<Bullet>();
            monsterB.clear();
            monsterB = std::vector<Bullet>();
            objectVEC.clear();
            objectVEC = std::vector<Object>();
            if (grid[player.x][player.y].type == 3)
            {
                shopItems = itemVec;
            }
            else if (grid[player.x][player.y].type == 4)
            {
                itemRoomVec = itemVec;
            }
            itemVec.clear();
            itemVec = std::vector<Item>();
            player.x++;
            player.body.setPosition({ player.body.getPosition().x, 45 });
            
            read_from_file(player, monsterVEC, objectVEC, bossVec, itemVec, skeleton_count);
            if (grid[player.x][player.y].type == 3)
            {
                itemVec = shopItems;
            }
            else if (grid[player.x][player.y].type == 4)
            {
                itemVec = itemRoomVec;
            }
            else if (grid[player.x][player.y].type == 2 && bossVec.empty() && monsterVEC.empty())
            {
                Object ladder(&ladderTexture, { 350.0f,200.0f }, { 16.0f,16.0f }, true, true);
                objectVEC.push_back(ladder);
            }
            grid[player.x][player.y].visited = true;
        }
    }
    if (room_doors & 0b1000)
    {
        doors.setPosition(350, 19);
        doors.setRotation(0.0f);
        if (grid[player.x - 1][player.y].type == 2)
        {
            doors.setTexture(&doors_bs_t);
        }
        else if (grid[player.x - 1][player.y].type == 3)
        {
            doors.setTexture(&doors_sh_t);
        }
        else if (grid[player.x - 1][player.y].type == 4)
        {
            doors.setTexture(&doors_it_t);
        }
        else
        {
            doors.setTexture(&doors_t);
        }
        Draw(window, doors);
        if (kolizja.check_Collision(player.body, doors) && monsterVEC.empty() && bossVec.empty())
        {

            heroB.clear();
            heroB = std::vector<Bullet>();
            monsterB.clear();
            monsterB = std::vector<Bullet>();
            objectVEC.clear();
            objectVEC = std::vector<Object>();
            if (grid[player.x][player.y].type == 3)
            {
                shopItems = itemVec;
            }
            else if (grid[player.x][player.y].type == 4)
            {
                itemRoomVec = itemVec;
            }
            itemVec.clear();
            itemVec = std::vector<Item>();

            player.x--;
            player.body.setPosition({ player.body.getPosition().x, 355 });
            
            read_from_file(player, monsterVEC, objectVEC, bossVec, itemVec,  skeleton_count);
            if (grid[player.x][player.y].type == 3)
            {
                itemVec = shopItems;
            }
            else if (grid[player.x][player.y].type == 4)
            {
                itemVec = itemRoomVec;
            }
            else if (grid[player.x][player.y].type == 2 && bossVec.empty() && monsterVEC.empty())
            {
                Object ladder(&ladderTexture, { 350.0f,200.0f }, { 16.0f,16.0f }, true, true);
                objectVEC.push_back(ladder);
            }
            
            grid[player.x][player.y].visited = true;
        }
    }
}
int room::getRoomType(hero& player)
{
    return grid[player.x][player.y].type;
}