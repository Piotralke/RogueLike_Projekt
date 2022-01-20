#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Bullet.h"
#include "Animation.h"
#define PI 3.141592;
/**
* Klasa reprezentuj¹ca przeciwników
*/
class monster : public hero
{
    protected:
        bool shooting; /**<Zmienna okreœlaj¹ca, czy przeciwnik mo¿e strzelaæ*/
        sf::Clock animation_clock; /**<Zegar odmie¿aj¹cy czas do zmianu animacji*/
        sf::Clock jump_clock;   /**<Zegar odmie¿aj¹cy czas co jaki potwór wykona specjalny ruch*/
        sf::Clock rotate_clock; /**<Zegar odmie¿aj¹cy czas zmieny kierunku poruszania siê*/
        sf::Clock shot_clock; /**< Zegar oidmie¿aj¹cy czas od wystrzelenia pocisku*/
        float memSpeed; /**<Zmienna zapamiêtuj¹ca poczatkow¹ wartoœæ szybkoœci poruszania siê*/
        float memHealth; /**<Zmienna zapamiêtuj¹ca pocz¹tkow¹ wartoœæ ¿ycia*/
        bool dead = false;  /**<Zmienna okreslajaca, czy dany przeciwnik zosta³ pokonany (u¿ywane dla szkieletów, które odradzaj¹ siê, jeœli w pokoju jest wiêcej przeciwników)*/
        bool teleport;  /**<Zmienna okreœlaj¹ca, czy dany przeciwnik mo¿e sie teleportowaæ*/
        sf::Vector2f bullet_size;   /**<Zmienna okreœlaj¹ca wymniary tekstury pocisku*/
        int test=0; /**<Zmienna u¿ywana do okreœlania stanu w jakim aktualnie jest przeciwnik, by mo¿na by³o okreœliæ kolejn¹ czynnoœæ jak¹ mo¿e wykonaæ*/
    public:
        bool resurection;   /**<Zmienna okreœlaj¹ca, czy przeciwnik, mo¿e siê odrodziæ*/
        monster(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health, 
            float damage, sf::Vector2f size, sf::Vector2f position, bool shooting, bool flying, bool resurection, sf::Texture* arrow, sf::Vector2i bullet_size, bool teleport = false)
            :hero(texture, imageCount, switchTime, speed, fire_rate, shot_speed, health,damage, size, position,flying, arrow),
            shooting(shooting), resurection(resurection), memHealth(health), memSpeed(speed), bullet_size(bullet_size), teleport(teleport) {}
        sf::Vector2f getDirVec(hero player);
        float getDirDeg(sf::Vector2f);
        void Update(float deltaTime, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, int& skeleton_count,int& dead_skeleton);
        void Draw(sf::RenderWindow& window);
        
};