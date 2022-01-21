#include "Item.h"

/** \brief  Konstruktor dla przedmiotu
 *
 * Przechowuje parametry, które są niezbędne do działania przedmiotów
 * @param itemTexture Wskaźnik na teksturę przedmiotu
 * @param position Miejsce na ekranie, w którym ma znajdować się przedmiot
 * @param size Rozmiar tekstury 
 * @param damage Parametr określający ile obrażeñ ma dodać do naszej postaci
 * @param health Parametr określający ile życia ma dodać do naszej postaci
 * @param maxHealth Parametr określający ile maksymalnego życia ma dodać do naszej postaci
 * @param fire_delay Parametr określający ile szybkostrzelności ma dodać do naszej postaci
 * @param shot_speed Parametr określający ile predkości naboju ma dodać do naszej postaci
 * @param speed Parametr określający ile prędkości ma dodać do naszej postaci
 * @param money Parametr określający ile monet ma dodać do naszej postaci
 * @param value Parametr określający ile kosztuje przedmiot(używany w sklepie)
 * @param flying Parametr określający czy ma dodać do postaci przechodzenie przez przeszkody
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

/** \brief  Funkcja dająca przedmiot graczowi
 *
 * @param Wskaźnik na gracza
 */
void Item::giveItem(hero* player)
{
	player->setStatistics(damage, health,maxHealth, fire_delay, shot_speed, speed, money,flying);
}

/** \brief  Funkcja wyświetlająca przedmiot
 *
 * Funkcja, która wyświetla na podane okno przedmiot, ułatwia nam wyświetlanie tego przedmiotu
 * @param window Wskaźnik na okno, w którym ma wyświetlić przedmiot
 * @param font Wskaźnik na czcionkę używaną w programie
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

/** \brief  Funkcja zwracająca ilość monet otrzymywanych z danego przedmiotu
 *
 * @return money Zwraca ilość monet 
 */

int Item::getMoney()
{
	return money;
}

/** \brief  Funkcja zwracająca cenę przedmiotu
 *
 * @return value Zwraca cenę przedmiotu
 */

int Item::getValue()
{
	return value;
}