#pragma once
#include "Animation.h"
#include "Bullet.h"
#include "Collision.h"
#include "SFML/Graphics.hpp"
/**
* Klasa reprezentuj�ca gracza
*/
class hero
{
protected:
    float speed;    /**<Pr�dko�� poruszania si�*/
    float maxHealth; /**<Maksymalne �ycie*/
    float health;   /**<Aktualne �ycie*/
    float damage; /**<Obra�enia*/
    int money=0; /**<Ilo�� monet*/ 
    bool faceRight; /**<Zmienna okre�laj�ce, w kt�rym kierunku patrzy si� gracz*/
    unsigned int row=0; /**<Zmienna okre�laj�ca, kt�ry wiersz animacji ma by� wykonywany*/
    float fire_rate; /**<Odst�p pomi�dzy mo�liwo��i� strza�u*/
    float shot_speed; /**<Szybko�� pocisk�w*/
    sf::Clock fire_delay_clock; /**<Zegar odmie�aj�cy czas pomi�dzy wystrza�em pocisku*/
    bool flying;    /**<Zmienna okre�laj�ca mo�liwo�� latania*/
    sf::Texture* arrow; /**<Tekstura pocisku*/
    sf::RectangleShape wings; /**<Prostok�t pobieraj�cy tekstur� skrzyde�, kt�ra pojawia si�, gdy gracz mo�e lata�*/
public:
    int x = 5, y = 5;   /**<Pozycja pokoju, w kt�rym znajduje si� gracz*/
    sf::RectangleShape body; /**<Prostok�t odpowiedzialny za wykrywanie kolizji gracza oraz wy�wietlanie jego tekstury*/
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