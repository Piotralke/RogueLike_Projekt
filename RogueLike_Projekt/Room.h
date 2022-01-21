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
* Klasa odpowiedzialna za operacje zwi¹zane z za³adowaniem uk³adu pokoju, przechodzenia miêdzy pokojami oraz innych zwi¹zanych z pokojami opcji
*/
class room
{
protected:
    /**
    * @brief Struktura zawieraj¹ca parametry pokoju
    * @param room_properties::exist Zmienna okreœlaj¹ca, czy w danym polu macierzy istnieje pokój
    * @param room_properties::type Typ pokoju
    * @param room_properties::visited Zmienna okreœlaj¹ca, czy pokój zosta³ ju¿ odwiedzony
    * @param room_properties::sciezka Zmienna okreœlaj¹ca œcie¿kê do pliku tekstowego zawieraj¹cego uk³ad danego pokoju
    */
    struct room_properties
    {
        int exist; 
        int type; 
        bool visited; 
        std::string sciezka; 
    };
    room_properties grid[SIZE][SIZE]; /**<Macierz, na której generowane s¹ pokoje*/

    std::vector<Item> noValueItems;  /**<Wektor przetrzymuj¹cy przedmioty*/
    std::vector<Item> valueItems;   /**<Wektor przetrzymuj¹cy przedmioty do kupienia*/
    std::vector<Item> shopItems; /**<Wektor przetrzymuj¹cy przemioty, które aktualnie znajduj¹ siê w sklepie*/
    std::vector<Item> itemRoomVec; /**<Wektor przetrzymnuj¹cy przemioty, które aktualnie znajduj¹ siê w pokoju*/

    sf::Texture doors_t;    /**<Tekstura drzwi*/
    sf::Texture doors_bs_t; /**<Tekstura drzwi do pokoju z bossem*/
    sf::Texture doors_sh_t; /**<Tekstura drzwi do sklepu*/
    sf::Texture doors_it_t; /**<Tekstura drzwi do pokoju z przedmiotem*/
    //monster textures
    sf::Texture wizardTexture; /**<Tekstura czarodzieja*/
    sf::Texture skeletonTexture; /**<Tekstura szkieleta*/
    sf::Texture zombieTexture; /**<Tekstura zombie*/
    sf::Texture spiderTexture; /**<Tekstura paj¹ka*/
    sf::Texture elfTexture; /**<Tekstura elfa*/
    sf::Texture slimeTexture; /**<Tekstura glutka*/
    sf::Texture trollTexture; /**<Tekstura trolla*/
    sf::Texture towerTexture; /**<Tekstura wie¿yczki*/
    
    //object textures
    sf::Texture rockTexture; /**<Tekstura kamienia*/
    sf::Texture bonesTexture; /**<Tekstura kupki koœci*/
    sf::Texture holeTexture; /**<Tekstura przepaœci*/
    sf::Texture barrelTexture; /**<Tekstura beczki*/
    sf::Texture crateTexture; /**<Tekstura skrzyni*/
    sf::Texture ladderTexture; /**<Tekstura drabiny*/
    //boss texture
    sf::Texture necromancerTexture; /**<Tekstura nekromanty*/
    sf::Texture brother1Texture; /**<Tekstura 1 z braci*/
    sf::Texture brother2Texture; /**<Tekstura 2 z braci*/
    sf::Texture devilAnimation; /**<Tekstura demona*/
    //aroows textures
    sf::Texture arrow_texture; /**<Tekstura strza³y*/
    sf::Texture fire_ball_texture; /**<Tekstura kuli ognia*/
    sf::Texture skull_texture; /**<Tekstura czaszki*/
    sf::Texture slime_ball_texture; /**<Tekstura kuli glutów*/
    sf::Texture bone_texture; /**<Tekstura koœci*/
    sf::Texture cannon_ball_texture; /**<Tekstura kuli armatniej*/
    //item textures
    sf::Texture boots1Texture; /**<Tekstura 1 butów*/
    sf::Texture boots2Texture; /**<Tekstura 2 butów*/
    sf::Texture gloves1Texture; /**<Tekstura 1 rêkawic*/
    sf::Texture gloves2Texture; /**<Tekstura 2 rêkawic*/
    sf::Texture helmetTexture;  /**<Tekstura he³mu*/
    sf::Texture wingsTexture; /**<Tekstura skrzyde³*/
    sf::Texture sword1Texture; /**<Tekstura 1 miecza*/
    sf::Texture sword2Texture; /**<Tekstura 2 miecza*/
    sf::Texture chestplateTexture; /**<Tekstura napierœnika*/
    sf::Texture axeTexture; /**<Tekstura toporu*/
    sf::Texture grailTexture; /**<Tekstura grala*/
    sf::Texture ring1Texture; /**<Tekstura 1 pierœcienia*/
    sf::Texture ring2Texture; /**<Tekstura 2 pierscienia*/

    sf::Texture small_healPotTexture; /**<Tekstura ma³ej mikstury leczenia*/
    sf::Texture big_healPotTexture; /**<Tekstura du¿ej mikstury leczenia*/
public:
    sf::Texture ghostTexture; /**<Tekstura ducha*/
    sf::Texture demonTexture; /**<Tekstura chochlika*/
    sf::Texture background_t; /**<Tekstura pokoju*/
    sf::Sprite background_s; /**<Zmienna u³atwiaj¹ca manipulowanie tekstur¹ pokoju*/
    sf::RectangleShape minimap_room; /**<Prostok¹t, który reprezentuje pokój na minimapie*/
    sf::RectangleShape hero_m; /**<Prostok¹t, który pobiera teksturê g³owy gracza i okreœla gdzie aktualnie znajduje siê na mapie*/
    sf::Texture minimap_rt; /**<Tekstura pokoju na minimapie*/
    sf::Texture hero_minimap; /**<Tekstura gracza na minimapie*/
    void init_Texture();
    int check_doors(int i, int j);
    void Draw(sf::RenderWindow& window, sf::RectangleShape& door);
    void read_from_file(hero& player, std::vector<monster>& monsterVEC, std::vector<Object>& objectVEC, std::vector<boss>& bossVec, std::vector<Item>& itemVec, int& skeleton_count);
    void load_room_layout(hero& player, Collision kolizja, sf::RenderWindow& window, std::vector<Bullet>& heroB, std::vector<Bullet>& monsterB,
        std::vector<monster>& monsterVEC, std::vector<Object>& objectVEC, std::vector<boss>& bossVec, std::vector<Item>& itemVec, int& skeleton_count);
    int getRoomType(hero& player);
};
