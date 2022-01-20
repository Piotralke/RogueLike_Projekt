#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
/**
* Klasa reprezentuj¹ca przedmioty w grze
* Statystyki przedmiotów s¹ dodawane do statystyk gracza przy podniesieniu go
*/
class Item
{
	private:
		float damage; /**<Obra¿enia */
		float health; /**<¯ycie*/
		float maxHealth; /**<Maksymalne ¿ycie*/
		float fire_delay; /**<Odstêp miêdzy strza³em*/
		float shot_speed; /**<Prêdkoœæ pocisków*/
		float speed; /**<Szybkoœæ*/
		int money; /**<Iloœæ monet*/
		int value; /**<Wartoœæ przedmiotu w sklepie*/
		bool flying; /**<Mo¿liwoœæ latania*/
	public:
		sf::RectangleShape item; /**<Prostok¹t odpowiedzialny za wykrycie kolizji oraz nadanie teksturki*/
		Item(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, float damage, float health,float maxHealth, float fire_delay, float shot_speed, float speed, int money, int value=0, bool flying=false);
		void giveItem(hero* player);
		void Draw(sf::RenderWindow& window, sf::Font& font);
		int getMoney();
		int getValue();
};