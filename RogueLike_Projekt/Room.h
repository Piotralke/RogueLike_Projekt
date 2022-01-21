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
/**
* \brief Klasa odpowiedzialna za operacje związane z załadowaniem układu pokoju, przechodzenia między pokojami oraz innych związanych z pokojami opcji
*/
class room
{
protected:
    /**
    * @brief  Struktura zawierająca parametry pokoju
    * @param exist Zmienna określająca, czy w danym polu macierzy istnieje pokój
    * @param type Typ pokoju
    * @param visited Zmienna określająca, czy pokój został już odwiedzony
    * @param sciezka Zmienna określająca ścieżkę do pliku tekstowego zawierającego układ danego pokoju
    */
    struct room_properties
    {
        int exist; 
        int type; 
        bool visited; 
        std::string sciezka; 
    };
    room_properties grid[SIZE][SIZE]; /**<\brief Macierz, na której generowane są pokoje*/

    std::vector<Item> noValueItems;  /**<\brief Wektor przetrzymujący przedmioty*/
    std::vector<Item> valueItems;   /**<\brief Wektor przetrzymujący przedmioty do kupienia*/
    std::vector<Item> shopItems; /**<\brief Wektor przetrzymujący przemioty, które aktualnie znajdują się w sklepie*/
    std::vector<Item> itemRoomVec; /**<\brief Wektor przetrzymnujący przemioty, które aktualnie znajdują się w pokoju*/

    sf::Texture doors_t;    /**<\brief Tekstura drzwi*/
    sf::Texture doors_bs_t; /**<\brief Tekstura drzwi do pokoju z bossem*/
    sf::Texture doors_sh_t; /**<\brief Tekstura drzwi do sklepu*/
    sf::Texture doors_it_t; /**<\brief Tekstura drzwi do pokoju z przedmiotem*/
    //monster textures
    sf::Texture wizardTexture; /**<\brief Tekstura czarodzieja*/
    sf::Texture skeletonTexture; /**<\brief Tekstura szkieleta*/
    sf::Texture zombieTexture; /**<\brief Tekstura zombie*/
    sf::Texture spiderTexture; /**<\brief Tekstura pająka*/
    sf::Texture elfTexture; /**<\brief Tekstura elfa*/
    sf::Texture slimeTexture; /**<\brief Tekstura glutka*/
    sf::Texture trollTexture; /**<\brief Tekstura trolla*/
    sf::Texture towerTexture; /**<\brief Tekstura wieżyczki*/
    
    //object textures
    sf::Texture rockTexture; /**<\brief Tekstura kamienia*/
    sf::Texture bonesTexture; /**<\brief Tekstura kupki kości*/
    sf::Texture holeTexture; /**<\brief Tekstura przepaści*/
    sf::Texture barrelTexture; /**<\brief Tekstura beczki*/
    sf::Texture crateTexture; /**<\brief Tekstura skrzyni*/
    sf::Texture ladderTexture; /**<\brief Tekstura drabiny*/
    //boss texture

    sf::Texture necromancerTexture; /**<\brief Tekstura nekromanty*/
    sf::Texture brother1Texture; /**<\brief Tekstura 1 z braci*/
    sf::Texture brother2Texture; /**<\brief Tekstura 2 z braci*/
    sf::Texture devilAnimation; /**<\brief Tekstura demona*/

    //aroows textures
    sf::Texture arrow_texture; /**<\brief Tekstura strzały*/
    sf::Texture fire_ball_texture; /**<\brief Tekstura kuli ognia*/
    sf::Texture skull_texture; /**<\brief Tekstura czaszki*/
    sf::Texture slime_ball_texture; /**<\brief Tekstura kuli glutów*/
    sf::Texture bone_texture; /**<\brief Tekstura kości*/
    sf::Texture cannon_ball_texture; /**<\brief Tekstura kuli armatniej*/

    //item textures
    sf::Texture boots1Texture; /**<\brief Tekstura 1 butów*/
    sf::Texture boots2Texture; /**<\brief Tekstura 2 butów*/
    sf::Texture gloves1Texture; /**<\brief Tekstura 1 rękawic*/
    sf::Texture gloves2Texture; /**<\brief Tekstura 2 rękawic*/
    sf::Texture helmetTexture;  /**<\brief Tekstura hełmu*/
    sf::Texture wingsTexture; /**<\brief Tekstura skrzydeł*/
    sf::Texture sword1Texture; /**<\brief Tekstura 1 miecza*/
    sf::Texture sword2Texture; /**<\brief Tekstura 2 miecza*/
    sf::Texture chestplateTexture; /**<\brief Tekstura napierśnika*/
    sf::Texture axeTexture; /**<\brief Tekstura toporu*/
    sf::Texture grailTexture; /**<\brief Tekstura grala*/
    sf::Texture ring1Texture; /**<\brief Tekstura 1 pierścienia*/
    sf::Texture ring2Texture; /**<\brief Tekstura 2 pierscienia*/

    sf::Texture small_healPotTexture; /**<\brief Tekstura małej mikstury leczenia*/
    sf::Texture big_healPotTexture; /**<\brief Tekstura dużej mikstury leczenia*/
public:
    sf::Texture ghostTexture; /**<\brief Tekstura ducha*/
    sf::Texture demonTexture; /**<\brief Tekstura chochlika*/
    sf::Texture background_t; /**<\brief Tekstura pokoju*/
    sf::Sprite background_s; /**<\brief Zmienna ułatwiająca manipulowanie teksturą pokoju*/
    sf::RectangleShape minimap_room; /**<\brief Prostokąt, który reprezentuje pokój na minimapie*/
    sf::RectangleShape hero_m; /**<\brief Prostokąt, który pobiera teksturę głowy gracza i określa gdzie aktualnie znajduje się na mapie*/
    sf::Texture minimap_rt; /**<\brief Tekstura pokoju na minimapie*/
    sf::Texture hero_minimap; /**<\brief Tekstura gracza na minimapie*/
    void init_Texture();
    int check_doors(int i, int j);
    void Draw(sf::RenderWindow& window, sf::RectangleShape& door);
    void read_from_file(hero& player, std::vector<monster>& monsterVEC, std::vector<Object>& objectVEC, std::vector<boss>& bossVec, std::vector<Item>& itemVec, int& skeleton_count, int level);
    void load_room_layout(hero& player, Collision kolizja, sf::RenderWindow& window, std::vector<Bullet>& heroB, std::vector<Bullet>& monsterB,
        std::vector<monster>& monsterVEC, std::vector<Object>& objectVEC, std::vector<boss>& bossVec, std::vector<Item>& itemVec, int& skeleton_count, int level);
    int getRoomType(hero& player);
};
