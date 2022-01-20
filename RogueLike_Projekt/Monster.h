#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Bullet.h"
#include "Animation.h"
#define PI 3.141592;
/**
* Klasa reprezentuj�ca przeciwnik�w
*/
class monster : public hero
{
    protected:
        bool shooting; /**<Zmienna okre�laj�ca, czy przeciwnik mo�e strzela�*/
        sf::Clock animation_clock; /**<Zegar odmie�aj�cy czas do zmianu animacji*/
        sf::Clock jump_clock;   /**<Zegar odmie�aj�cy czas co jaki potw�r wykona specjalny ruch*/
        sf::Clock rotate_clock; /**<Zegar odmie�aj�cy czas zmieny kierunku poruszania si�*/
        sf::Clock shot_clock; /**< Zegar oidmie�aj�cy czas od wystrzelenia pocisku*/
        float memSpeed; /**<Zmienna zapami�tuj�ca poczatkow� warto�� szybko�ci poruszania si�*/
        float memHealth; /**<Zmienna zapami�tuj�ca pocz�tkow� warto�� �ycia*/
        bool dead = false;  /**<Zmienna okreslajaca, czy dany przeciwnik zosta� pokonany (u�ywane dla szkielet�w, kt�re odradzaj� si�, je�li w pokoju jest wi�cej przeciwnik�w)*/
        bool teleport;  /**<Zmienna okre�laj�ca, czy dany przeciwnik mo�e sie teleportowa�*/
        sf::Vector2f bullet_size;   /**<Zmienna okre�laj�ca wymniary tekstury pocisku*/
        int test=0; /**<Zmienna u�ywana do okre�lania stanu w jakim aktualnie jest przeciwnik, by mo�na by�o okre�li� kolejn� czynno�� jak� mo�e wykona�*/
    public:
        bool resurection;   /**<Zmienna okre�laj�ca, czy przeciwnik, mo�e si� odrodzi�*/
        monster(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health, 
            float damage, sf::Vector2f size, sf::Vector2f position, bool shooting, bool flying, bool resurection, sf::Texture* arrow, sf::Vector2i bullet_size, bool teleport = false)
            :hero(texture, imageCount, switchTime, speed, fire_rate, shot_speed, health,damage, size, position,flying, arrow),
            shooting(shooting), resurection(resurection), memHealth(health), memSpeed(speed), bullet_size(bullet_size), teleport(teleport) {}
        sf::Vector2f getDirVec(hero player);
        float getDirDeg(sf::Vector2f);
        void Update(float deltaTime, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, int& skeleton_count,int& dead_skeleton);
        void Draw(sf::RenderWindow& window);
        
};