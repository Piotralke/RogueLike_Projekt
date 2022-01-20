#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
/**
* Klasa reprezentuj�ca przedmioty w grze
* Statystyki przedmiot�w s� dodawane do statystyk gracza przy podniesieniu go
*/
class Item
{
	private:
		float damage; /**<Obra�enia */
		float health; /**<�ycie*/
		float maxHealth; /**<Maksymalne �ycie*/
		float fire_delay; /**<Odst�p mi�dzy strza�em*/
		float shot_speed; /**<Pr�dko�� pocisk�w*/
		float speed; /**<Szybko��*/
		int money; /**<Ilo�� monet*/
		int value; /**<Warto�� przedmiotu w sklepie*/
		bool flying; /**<Mo�liwo�� latania*/
	public:
		sf::RectangleShape item; /**<Prostok�t odpowiedzialny za wykrycie kolizji oraz nadanie teksturki*/
		Item(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, float damage, float health,float maxHealth, float fire_delay, float shot_speed, float speed, int money, int value=0, bool flying=false);
		void giveItem(hero* player);
		void Draw(sf::RenderWindow& window, sf::Font& font);
		int getMoney();
		int getValue();
};