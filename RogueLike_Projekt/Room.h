#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "Hero.h"
#include "Collision.h"
#include "Monster.h"
#include "Objects.h"
#include "Boss.h"
#include "Item.h"
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

    std::vector<Item> noValueItems;
    std::vector<Item> valueItems;
    std::vector<Item> shopItems;
    std::vector<Item> itemRoomVec;

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
    sf::Texture trollTexture;
    sf::Texture towerTexture;
    
    //object textures
    sf::Texture rockTexture;
    sf::Texture bonesTexture;
    sf::Texture holeTexture;
    sf::Texture barrelTexture;
    sf::Texture crateTexture;
    sf::Texture ladderTexture;
    //boss texture
    sf::Texture necromancerTexture;
    sf::Texture brother1Texture;
    sf::Texture brother2Texture;
    //aroows textures
    sf::Texture arrow_texture;
    sf::Texture fire_ball_texture;
    sf::Texture skull_texture;
    sf::Texture slime_ball_texture;
    sf::Texture bone_texture;
    sf::Texture cannon_ball_texture;
    //item textures
    sf::Texture boots1Texture;
    sf::Texture boots2Texture;
    sf::Texture gloves1Texture;
    sf::Texture gloves2Texture;
    sf::Texture helmetTexture;
    sf::Texture wingsTexture;
    sf::Texture sword1Texture;
    sf::Texture sword2Texture;
    sf::Texture chestplateTexture;
    sf::Texture axeTexture;
    sf::Texture grailTexture;
    sf::Texture ring1Texture;
    sf::Texture ring2Texture;

    sf::Texture small_healPotTexture;
    sf::Texture big_healPotTexture;
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
    void read_from_file(hero& player, std::vector<monster>& monsterVEC, std::vector<Object>& objectVEC, std::vector<boss>& bossVec, std::vector<Item>& itemVec, int& skeleton_count);
    void pick_room_layout(hero& player, Collision kolizja, sf::RenderWindow& window, std::vector<Bullet>& heroB, std::vector<Bullet>& monsterB,
        std::vector<monster>& monsterVEC, std::vector<Object>& objectVEC, std::vector<boss>& bossVec, std::vector<Item>& itemVec, int& skeleton_count);
    int getRoomType(hero& player);
};
