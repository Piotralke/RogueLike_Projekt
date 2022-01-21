#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
/**
* \brief  Klasa reprezentująca przedmioty w grze
* Statystyki przedmiotów są dodawane do statystyk gracza przy podniesieniu go
*/
class Item
{
	private:
		float damage; /**<\brief Obrażenia */
		float health; /**<\brief ¯ycie*/
		float maxHealth; /**<\brief Maksymalne życie*/
		float fire_delay; /**<\brief Odstęp między strzałem*/
		float shot_speed; /**<\brief Prędkość pocisków*/
		float speed; /**<\brief Szybkość*/
		int money; /**<\brief Ilość monet*/
		int value; /**<\brief Wartość przedmiotu w sklepie*/
		bool flying; /**<\brief Możliwość latania*/
	public:
		sf::RectangleShape item; /**<\brief Prostokąt odpowiedzialny za wykrycie kolizji oraz nadanie teksturki*/
		Item(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, float damage, float health,float maxHealth, float fire_delay, float shot_speed, float speed, int money, int value=0, bool flying=false);
		void giveItem(hero* player);
		void Draw(sf::RenderWindow& window, sf::Font& font);
		int getMoney();
		int getValue();
};