#include <SFML/Graphics.hpp>
//#include <stdlib.h>
#include <queue>
#include <stack>
#include <iostream>
//#include <time.h>
#include "Animation.h"
#include "Hero.h"
#include "Collision.h"
#include "Bullet.h"
#include "Monster.h"
#include <vector>

#define SIZE 11

class object
{
    private:
        int x, y;
        // tekstura(?)
};

class room 
{
    protected:
        int grid[SIZE][SIZE];
        int room_type;
        sf::Texture doors_t;
        sf::Sprite doors_s;

public:
    sf::Texture background_t;
    sf::Sprite background_s;
    int check_doors(int i, int j)
    {
        int room_doors = 0b0000;
        if (grid[i][j - 1]==1)     
            room_doors ^= 0b0001;   //lewe drzwi
        if (grid[i][j + 1]==1)    
            room_doors ^= 0b0010;    //prawe drzwi
        if (grid[i + 1][j]==1)     
            room_doors ^= 0b0100;   //dolne drzwi
        if (grid[i - 1][j]==1)      
            room_doors ^= 0b1000;   //gorne drzwi
        return room_doors;

    }
    void Draw(sf::RenderWindow& window, sf::RectangleShape& door)
    {
        window.draw(door);
    }
    void pick_room_layout(hero& player,Collision kolizja,sf::RenderWindow& window,int i, int j)
    {
        doors_t.loadFromFile("grafiki/doors_o.png");
        sf::RectangleShape doors;
        doors.setSize({ 32, 32 });
        doors.setOrigin(doors.getSize() / 2.0f);
        int room_doors = check_doors(i, j);
        if (room_doors & 0b0001)
        {
            doors.setPosition(16,200);
            doors.setTexture(&doors_t);
            doors.setRotation(-90.0f);
            Draw(window, doors);
            if (kolizja.check_Collision(player.body, doors))
            {
                player.y--;
                player.body.setPosition({ 655, player.body.getPosition().y });
            }

        }
        if (room_doors & 0b0010)
        {
            doors.setPosition(684, 200);
            doors.setTexture(&doors_t);
            doors.setRotation(90.0f);
            Draw(window, doors);
            if (kolizja.check_Collision(player.body, doors))
            {
                player.y++;
                player.body.setPosition({ 45, player.body.getPosition().y });
            }
        }
        if (room_doors & 0b0100)
        {
            doors.setPosition(350, 384);
            doors.setTexture(&doors_t);
            doors.setRotation(180.0f);
            Draw(window, doors);
            if (kolizja.check_Collision(player.body, doors))
            {
                player.x++;
                player.body.setPosition({ player.body.getPosition().x, 45 });
            }
        }
        if (room_doors & 0b1000)
        {
            doors.setPosition(350, 16);
            doors.setTexture(&doors_t);
            doors.setRotation(0.0f);
            Draw(window, doors);
            if (kolizja.check_Collision(player.body, doors))
            {
                player.x--;
                player.body.setPosition({ player.body.getPosition().x, 355 });
            }
        }
    }

};

class generate_map : public room
{
    protected:
        
        int rooms_counter=0;
        int max_rooms;
        int min_rooms;
        std::queue <int> RoomQueue_i;
        std::queue <int> RoomQueue_j;
        std::stack <int> DeadEnd_i;
        std::stack <int> DeadEnd_j;
        bool placedSpecial = false;

    public:
        generate_map()
        {
            background_t.loadFromFile("grafiki/background.png", sf::IntRect(0, 0, 700, 400));
            background_s.setTexture(background_t);
        }
        void init_grid()
        {
            for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++)
                    grid[i][j] = 0;
        }
        void max_level_counter(int level)
        {
            min_rooms = 20 + level * 1;
            max_rooms = min_rooms + 6;
        }
        int neighbour_count(int i, int j)
        {
            return grid[i - 1][j] + grid[i][j - 1] + grid[i + 1][j] + grid[i][j + 1];
        }
        bool visit(int i, int j)
        {
            
            if (grid[i][j])
                return false;

            int neigbours = neighbour_count(i, j);

            if (neigbours > 1)
                return false;

            if (rooms_counter >= max_rooms)
                return false;

            int random = std::rand() % 2;
            if (i != 5 && j == 5 || i == 5 && j != 5)
            {
                if (random > 0 && i != 5 || random > 0 && j != 5)
                    return false;
            }

            RoomQueue_i.push(i);
            RoomQueue_j.push(j);
            grid[i][j] = 1;
            rooms_counter++;

            return true;
        }
        void wypisz()
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                    std::cout << grid[i][j] << " ";
                std::cout << std::endl;
            }
            
        }
        bool generate_layout()
        {
            int i, j;
            while (rooms_counter < max_rooms && !(rooms_counter >min_rooms))
            {
                if (RoomQueue_i.size() > 0 && RoomQueue_j.size() > 0)
                {
                    i = RoomQueue_i.front();
                    RoomQueue_i.pop();
                    j = RoomQueue_j.front();
                    RoomQueue_j.pop();
                    bool created = false;
                    if (i > 0)
                        created = created | visit(i - 1, j);
                    if (i < SIZE)
                        created = created | visit(i + 1, j);
                    if (j > 0)
                        created = created | visit(i, j - 1);
                    if (j < SIZE)
                        created = created | visit(i, j + 1);
                    if (!created)
                    {
                        DeadEnd_i.push(i);
                        DeadEnd_j.push(j);
                    }
                    if (RoomQueue_i.empty())
                    {
                        RoomQueue_i.push(i);
                        RoomQueue_j.push(j);
                    }
                }
                else if (!placedSpecial)
                {
                    if (rooms_counter >= min_rooms && DeadEnd_i.size() > 2)
                    {
                        placedSpecial = true;
                        room* Boss_room = new room;
                    Boss_room:grid[DeadEnd_i.top()][DeadEnd_j.top()];
                        grid[DeadEnd_i.top()][DeadEnd_j.top()] = 2;
                        DeadEnd_i.pop();
                        DeadEnd_j.pop();

                        room* Shop = new room;
                    Shop:grid[DeadEnd_i.top()][DeadEnd_j.top()];
                        grid[DeadEnd_i.top()][DeadEnd_j.top()] = 3;
                        DeadEnd_i.pop();
                        DeadEnd_j.pop();

                        room* Item_Room = new room;
                    Item_Room:grid[DeadEnd_i.top()][DeadEnd_j.top()];
                        grid[DeadEnd_i.top()][DeadEnd_j.top()] = 4;
                        DeadEnd_i.pop();
                        DeadEnd_j.pop();

                        return true;
                    }
                }
            }
            
        }
};

int main()
{
    Collision kolizja;
    sf::RectangleShape room_collider_top;
    sf::RectangleShape room_collider_left;
    sf::RectangleShape room_collider_right;
    sf::RectangleShape room_collider_down;
    room_collider_top.setSize({642,29});
    room_collider_top.setOrigin(room_collider_top.getSize() / 2.0f);
    room_collider_top.setPosition(350, 16);

    room_collider_left.setSize({ 29,400 });
    room_collider_left.setOrigin(room_collider_left.getSize() / 2.0f);
    room_collider_left.setPosition(16, 200); 

    room_collider_right.setSize({ 29,400 });
    room_collider_right.setOrigin(room_collider_right.getSize() / 2.0f);
    room_collider_right.setPosition(684, 200);

    room_collider_down.setSize({ 642,29 });
    room_collider_down.setOrigin(room_collider_down.getSize() / 2.0f);
    room_collider_down.setPosition(350, 384);

    sf::Texture arrow_texture;
    sf::Texture fire_ball_texture;
    arrow_texture.loadFromFile("grafiki/arrow.png");
    fire_ball_texture.loadFromFile("grafiki/fire_ball.png");
    std::vector<monster> monsterVec;
    sf::RenderWindow window(sf::VideoMode(700, 400), "RogueLike!", sf::Style::Default);
    generate_map* level = new generate_map;
    sf::Texture playerTexture;
    playerTexture.loadFromFile("grafiki/hero_animation.png");
    hero player(&playerTexture, sf::Vector2u(4, 2), 0.1f, 100.0f, 0.5f, 200.0f, 100.0f, 6.0f, { 16.0f,20.0f }, {350.0f,200.0f});
    sf::Texture wizardTexture;
    wizardTexture.loadFromFile("grafiki/wizard_animation.png");
    sf::Texture ghostTexture;
    ghostTexture.loadFromFile("grafiki/ghost_animation.png");
    monster wizard(&wizardTexture, sf::Vector2u(4, 1), 0.1f, 0.0f, 1.5f, 150.0f, 30.0f, 10.0f, { 16.0f,20.0f }, {100.0f,100.0f}, true);
    monster ghost(&ghostTexture, sf::Vector2u(4, 1), 0.1f, 75.0f, 1.5f, 150.0f, 30.0f, 4.0f ,{ 12.0f,17.0f }, {600.0f,100.0f}, false);
    monsterVec.push_back(ghost);
    monsterVec.push_back(wizard);
    sf::RectangleShape kamien;
    kamien.setSize({2,2});
    kamien.setOrigin(kamien.getSize() / 2.0f);
    kamien.setPosition(30.0f, 370.0f);
    kamien.setFillColor(sf::Color());
    std::vector<Bullet> bulletVec;
    std::vector<Bullet> monsterBulletVec;
    srand(time(NULL));
    level->init_grid();
    level->max_level_counter(1);
    level->visit(5, 5);
    level->generate_layout();
    level->wypisz();
    float deltaTime = 0.0f;
    sf::Clock clock;
    sf::Clock fire_delay_clock;
    sf::Clock monster_fire_delay_clock;
    sf::Clock invisibility_clock;
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
        //wizard.Update(deltaTime,monster_fire_delay_clock, &fire_ball_texture, monsterBulletVec,player);
       // ghost.Update(deltaTime,monster_fire_delay_clock, &fire_ball_texture, monsterBulletVec,player);
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
        std::cout << player.getHealth() << std::endl;
        kolizja.check_Collision(player.body, kamien);
        kolizja.check_Collision(player.body, room_collider_top);
        kolizja.check_Collision(player.body, room_collider_left);
        kolizja.check_Collision(player.body, room_collider_right);
        kolizja.check_Collision(player.body, room_collider_down);
       // view.setCenter(player.GetPosition());
        
        window.clear();
       // window.setView(view);
        window.draw(level->background_s);
        level->pick_room_layout(player,kolizja,window, player.x, player.y);
        for (int i = 0; i < bulletVec.size(); i++)
        {
            bulletVec.at(i).Draw(window);
        }
        for (int i = 0; i < monsterBulletVec.size(); i++)
            monsterBulletVec.at(i).Draw(window);
        //window.draw(kamien);
        for (int j = 0; j < monsterVec.size(); j++)
        {
            monsterVec.at(j).Draw(window);
        }
        //wizard.Draw(window);
        //ghost.Draw(window);
        player.Draw(window);
        window.display();
    }

    return 0;
}
