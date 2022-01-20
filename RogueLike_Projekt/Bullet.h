#pragma once
#include "Collision.h"
#include <SFML/Graphics.hpp>
/** Klasa reprezentuje obiekt, który jest pociskiem wystzrliwanym przez gracza, b¹dŸ przeciwnika
* 
*/
class Bullet
{
	private:
		float shot_speed; /**< Szybkoœæ poruszania siê pocisku*/
		float damage;	/**< Obra¿enia pocisku*/
		sf::Vector2f direction; /**< Wektor, w którym kikerunku pocisk ma lecieæ */
		sf::Vector2f directionNormalized;	/**<Znormalizowany wektor kierunku strza³u*/
	public:
		sf::RectangleShape bullet;	/**< Prostok¹t bêd¹cy obszarem do wykrywania kolizji oraz do pobrania tekstury i wyœwietlania pocisku w grze*/
		Bullet(sf::Vector2f size, sf::Vector2f position, float shot_speed, float rate_of_fire, sf::Vector2f direction, sf::Texture *texture, float rotation);
		void fire(float deltaTime);
		void Draw(sf::RenderWindow& window);
		float getDamage();
};