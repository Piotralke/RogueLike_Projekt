#pragma once
#include "Collision.h"
#include <SFML/Graphics.hpp>
/** \brief Klasa reprezentuje obiekt, który jest pociskiem wystzrliwanym przez gracza, bądź przeciwnika
* 
*/
class Bullet
{
	private:
		float shot_speed; /**<\brief  Szybkość poruszania się pocisku*/
		float damage;	/**<\brief  Obrażenia pocisku*/
		sf::Vector2f direction; /**< \brief Wektor, w którym kikerunku pocisk ma lecieć */
		sf::Vector2f directionNormalized;	/**<\brief Znormalizowany wektor kierunku strzału*/
	public:
		sf::RectangleShape bullet;	/**< \brief Prostokąt będący obszarem do wykrywania kolizji oraz do pobrania tekstury i wyświetlania pocisku w grze*/
		Bullet(sf::Vector2f size, sf::Vector2f position, float shot_speed, float rate_of_fire, sf::Vector2f direction, sf::Texture *texture, float rotation);
		void fire(float deltaTime);
		void Draw(sf::RenderWindow& window);
		float getDamage();
};