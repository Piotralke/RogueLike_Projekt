#pragma once
#include "Animation.h"
#include "Bullet.h"
#include "Collision.h"
#include "SFML/Graphics.hpp"
/**
* Klasa reprezentuj¹ca gracza
*/
class hero
{
protected:
    float speed;    /**<Prêdkoœæ poruszania siê*/
    float maxHealth; /**<Maksymalne ¿ycie*/
    float health;   /**<Aktualne ¿ycie*/
    float damage; /**<Obra¿enia*/
    int money=0; /**<Iloœæ monet*/ 
    bool faceRight; /**<Zmienna okreœlaj¹ce, w którym kierunku patrzy siê gracz*/
    unsigned int row=0; /**<Zmienna okreœlaj¹ca, który wiersz animacji ma byæ wykonywany*/
    float fire_rate; /**<Odstêp pomiêdzy mo¿liwoœæi¹ strza³u*/
    float shot_speed; /**<Szybkoœæ pocisków*/
    sf::Clock fire_delay_clock; /**<Zegar odmie¿aj¹cy czas pomiêdzy wystrza³em pocisku*/
    bool flying;    /**<Zmienna okreœlaj¹ca mo¿liwoœæ latania*/
    sf::Texture* arrow; /**<Tekstura pocisku*/
    sf::RectangleShape wings; /**<Prostok¹t pobieraj¹cy teksturê skrzyde³, która pojawia siê, gdy gracz mo¿e lataæ*/
public:
    int x = 5, y = 5;   /**<Pozycja pokoju, w którym znajduje siê gracz*/
    sf::RectangleShape body; /**<Prostok¹t odpowiedzialny za wykrywanie kolizji gracza oraz wyœwietlanie jego tekstury*/
    Animation animation;    /**<Animacja postaci*/
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