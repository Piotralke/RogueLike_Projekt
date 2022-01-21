#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Bullet.h"
#include "Animation.h"
#define PI 3.141592;
/**
* \brief Klasa reprezentująca przeciwników
*/
class monster : public hero
{
    protected:
        bool shooting; /**<\brief Zmienna określająca, czy przeciwnik może strzelać*/
        sf::Clock animation_clock; /**<\brief Zegar odmieżający czas do zmianu animacji*/
        sf::Clock jump_clock;   /**<\brief Zegar odmieżający czas co jaki potwór wykona specjalny ruch*/
        sf::Clock rotate_clock; /**<\brief Zegar odmieżający czas zmieny kierunku poruszania się*/
        sf::Clock shot_clock; /**< \brief Zegar oidmieżający czas od wystrzelenia pocisku*/
        float memSpeed; /**<\brief Zmienna zapamiętująca poczatkową wartość szybkości poruszania się*/
        float memHealth; /**<\brief Zmienna zapamiętująca początkową wartość życia*/
        bool dead = false;  /**<\brief Zmienna okreslajaca, czy dany przeciwnik został pokonany (używane dla szkieletów, które odradzają się, jeśli w pokoju jest więcej przeciwników)*/
        bool teleport;  /**<\brief Zmienna określająca, czy dany przeciwnik może sie teleportować*/
        sf::Vector2f bullet_size;   /**<\brief Zmienna określająca wymniary tekstury pocisku*/
        int test=0; /**<\brief Zmienna używana do określania stanu w jakim aktualnie jest przeciwnik, by można było określić kolejną czynność jaką może wykonać*/
    public:
        bool resurection;   /**<\brief Zmienna określająca, czy przeciwnik, może się odrodzić*/
        monster(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health, 
            float damage, sf::Vector2f size, sf::Vector2f position, bool shooting, bool flying, bool resurection, sf::Texture* arrow, sf::Vector2i bullet_size, bool teleport = false)
            :hero(texture, imageCount, switchTime, speed, fire_rate, shot_speed, health,damage, size, position,flying, arrow),
            shooting(shooting), resurection(resurection), memHealth(health), memSpeed(speed), bullet_size(bullet_size), teleport(teleport) {}
        sf::Vector2f getDirVec(hero player);
        float getDirDeg(sf::Vector2f);
        void Update(float deltaTime, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, int& skeleton_count,int& dead_skeleton);
        void Draw(sf::RenderWindow& window);
        
};