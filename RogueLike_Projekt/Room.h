#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "Hero.h"
#include "Collision.h"
#include "Monster.h"
#include "Objects.h"
#include "Boss.h"
#define SIZE 11

class room
{
protected:
    struct room_properties
    {
        int exist;
        int type;
        bool visited;
        std::string sciezka;
    };
    room_properties grid[SIZE][SIZE];
    sf::Texture doors_t;
    sf::Texture doors_bs_t;
    sf::Texture doors_sh_t;
    sf::Texture doors_it_t;
    //monster textures
    sf::Texture wizardTexture;
    sf::Texture skeletonTexture;
    sf::Texture zombieTexture;
    sf::Texture demonTexture;
    sf::Texture spiderTexture;
    sf::Texture elfTexture;
    sf::Texture slimeTexture;
    
    //object textures
    sf::Texture rockTexture;
    sf::Texture bonesTexture;
    sf::Texture holeTexture;
    //boss texture
    sf::Texture necromancerTexture;
    //aroows textures
    sf::Texture arrow_texture;
    sf::Texture fire_ball_texture;
    sf::Texture skull_texture;
    sf::Texture slime_ball_texture;
public:
    sf::Texture ghostTexture;
    sf::Texture background_t;
    sf::Sprite background_s;
    sf::RectangleShape minimap_room;
    sf::RectangleShape hero_m;
    sf::Texture minimap_rt;
    sf::Texture hero_minimap;
    void init_Texture();
    int check_doors(int i, int j);
    void Draw(sf::RenderWindow& window, sf::RectangleShape& door);
    void read_from_file(hero& player, std::vector<monster>& monsterVEC, std::vector<Object>& objectVEC, std::vector<boss>& bossVec, int& skeleton_count);
    void pick_room_layout(hero& player, Collision kolizja, sf::RenderWindow& window, std::vector<Bullet>& heroB, std::vector<Bullet>& monsterB,
        std::vector<monster>& monsterVEC, std::vector<Object>& objectVEC, std::vector<boss>& bossVec, int& skeleton_count);
};
