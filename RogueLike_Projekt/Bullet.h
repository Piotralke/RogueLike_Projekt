#pragma once
#include "Collision.h"
#include <SFML/Graphics.hpp>
/** Klasa reprezentuje obiekt, kt�ry jest pociskiem wystzrliwanym przez gracza, b�d� przeciwnika
* 
*/
class Bullet
{
	private:
		float shot_speed; /**< Szybko�� poruszania si� pocisku*/
		float damage;	/**< Obra�enia pocisku*/
		sf::Vector2f direction; /**< Wektor, w kt�rym kikerunku pocisk ma lecie� */
		sf::Vector2f directionNormalized;	/**<Znormalizowany wektor kierunku strza�u*/
	public:
		sf::RectangleShape bullet;	/**< Prostok�t b�d�cy obszarem do wykrywania kolizji oraz do pobrania tekstury i wy�wietlania pocisku w grze*/
		Bullet(sf::Vector2f size, sf::Vector2f position, float shot_speed, float rate_of_fire, sf::Vector2f direction, sf::Texture *texture, float rotation);
		void fire(float deltaTime);
		void Draw(sf::RenderWindow& window);
		float getDamage();
};