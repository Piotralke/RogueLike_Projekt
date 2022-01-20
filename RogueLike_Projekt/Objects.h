#pragma once
#include "Collision.h"
#include <SFML/Graphics.hpp>
/**
*  Klasa reprezentuj�ca obiekty na mapie gry
*/
class Object {
private:
	
public:
	bool shootable; /**< Zmienna okre�laj�ca, czy przez dany obiekt mo�emy strzela�*/
	bool go_down; /**< Zmienna okre�laj�ca, czy przy kolizji z danym obiektem przejdziemy na nast�pny poziom (U�ywane w przypadku utworzenia drabiny po pokonaniu bossa)*/
	sf::RectangleShape shape; /**<Prostok�t b�d�cy obszarem do wykrywania kolizji oraz do pobrania tekstury i wy�wietlania obiektu w grze*/
	Object(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, bool shootable, bool go_down=false);
	void Draw(sf::RenderWindow& window);
};