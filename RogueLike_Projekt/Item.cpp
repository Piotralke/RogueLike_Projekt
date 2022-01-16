#include "Item.h"

/** \brief Konstruktor dla przedmiotu
 *
 * Przechowuje parametry, kt�re s� niezb�dne do dzia�ania przedmiot�w
 * @param itemTexture Wska�nik na tekstur� przedmiotu
 * @param position Miejsce na ekranie, w kt�rym ma znajdowa� si� przedmiot
 * @param size Rozmiar tekstury 
 * @param damage Parametr okre�laj�cy ile obra�e� ma doda� do naszej postaci
 * @param health Parametr okre�laj�cy ile �ycia ma doda� do naszej postaci
 * @param maxHealth Parametr okre�laj�cy ile maksymalnego �ycia ma doda� do naszej postaci
 * @param fire_delay Parametr okre�laj�cy ile szybkostrzelno�ci ma doda� do naszej postaci
 * @param shot_speed Parametr okre�laj�cy ile predko�ci naboju ma doda� do naszej postaci
 * @param speed Parametr okre�laj�cy ile pr�dko�ci ma doda� do naszej postaci
 * @param money Parametr okre�laj�cy ile monet ma doda� do naszej postaci
 * @param value Parametr okre�laj�cy ile kosztuje przedmiot(u�ywany w sklepie)
 * @param flying Parametr okre�laj�cy czy ma doda� do postaci przechodzenie przez przeszkody
 */

Item::Item(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, float damage, float health,float maxHealth, float fire_delay, float shot_speed, float speed, int money, int value, bool flying)
{
	item.setSize(size);
	item.setOrigin(item.getSize() / 2.0f);
	item.setPosition(position);
	item.setTexture(itemTexture);
	this->damage = damage;
	this->health = health;
	this->maxHealth = maxHealth;
	this->fire_delay = fire_delay;
	this->shot_speed = shot_speed;
	this->speed = speed;
	this->money = money;
	this->value = value;
	this->flying = flying;
}

/** \brief Funkcja daj�ca przedmiot graczowi
 *
 * @param Wska�nik na gracza
 */
void Item::giveItem(hero* player)
{
	player->setStatistics(damage, health,maxHealth, fire_delay, shot_speed, speed, money,flying);
}

/** \brief Funkcja wy�wietlaj�ca przedmiot
 *
 * Funkcja, kt�ra wy�wietla na podane okno przedmiot, u�atwia nam wy�wietlanie tego przedmiotu
 * @param window Wska�nik na okno, w kt�rym ma wy�wietli� przedmiot
 */

void Item::Draw(sf::RenderWindow& window, sf::Font& font)
{
	window.draw(item);
	if (value > 0)
	{
		sf::Text price_text;
		std::string price_string;
		price_text.setFont(font);
		price_text.setCharacterSize(8);
		price_text.setFillColor(sf::Color::White);
		price_string = std::to_string(value);
		price_text.setString(price_string);
		price_text.setPosition({ item.getPosition().x - 7.0f,item.getPosition().y+7.0f });
		window.draw(price_text);
	}
}

/** \brief Funkcja zwracaj�ca 
 *
 * @return body.getPosition() Zwraca pozycj� postaci
 */

int Item::getMoney()
{
	return money;
}

/** \brief Funkcja zwracaj�ca pozycje postaci
 *
 * @return body.getPosition() Zwraca pozycj� postaci
 */

int Item::getValue()
{
	return value;
}