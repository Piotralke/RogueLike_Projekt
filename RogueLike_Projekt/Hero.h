#pragma once
#include "Animation.h"
#include "Bullet.h"
#include "Collision.h"
#include "SFML/Graphics.hpp"
/**
* \brief Klasa reprezentująca gracza
*/
class hero
{
protected:
    float speed;    /**<\brief Prędkość poruszania się*/
    float maxHealth; /**<\brief Maksymalne życie*/
    float health;   /**<\brief Aktualne życie*/
    float damage; /**<\brief Obrażenia*/
    int money=0; /**<\brief Ilość monet*/ 
    bool faceRight; /**<\brief Zmienna określające, w którym kierunku patrzy się gracz*/
    unsigned int row=0; /**<\brief Zmienna określająca, który wiersz animacji ma być wykonywany*/
    float fire_rate; /**<\brief Odstęp pomiędzy możliwośćią strzału*/
    float shot_speed; /**<\brief Szybkość pocisków*/
    sf::Clock fire_delay_clock; /**<\brief Zegar odmieżający czas pomiędzy wystrzałem pocisku*/
    bool flying;    /**<\brief Zmienna określająca możliwość latania*/
    sf::Texture* arrow; /**<\brief Tekstura pocisku*/
    sf::RectangleShape wings; /**<\brief Prostokąt pobierający teksturę skrzydeł, która pojawia się, gdy gracz może latać*/
public:
    int x = 5, y = 5;   /**<\brief Pozycja pokoju, w którym znajduje się gracz*/
    sf::RectangleShape body; /**<\brief Prostokąt odpowiedzialny za wykrywanie kolizji gracza oraz wyświetlanie jego tekstury*/
    Animation animation;    /**<\brief Animacja postaci*/
    hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health,
        float damage, sf::Vector2f size, sf::Vector2f position, bool flying, sf::Texture* arrow, sf::Texture* wings_t=NULL);
    void DrawStats(sf::RenderWindow& window, sf::Font& font);
    void Draw(sf::RenderWindow& window);
    void DrawMenu(sf::RenderWindow& window, float deltaTime);
    void Update(float deltaTime, std::vector<Bullet> &bulletVec);
    sf::Vector2f GetPosition();
    float getDamage();
    float getHealth();
    float getSpeed();
    float getShotSpeed();
    float getFireDelay();
    int getMoney();
    bool getFlying();
    void getHit(float damage);
    void setStatistics(float damage, float health,float maxHealth, float fire_delay, float shot_speed, float speed,int money,bool flying);
};