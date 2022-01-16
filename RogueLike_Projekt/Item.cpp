#include "Item.h"

/** \brief Konstruktor dla przedmiotu
 *
 * Przechowuje parametry, które s¹ niezbêdne do dzia³ania przedmiotów
 * @param itemTexture WskaŸnik na teksturê przedmiotu
 * @param position Miejsce na ekranie, w którym ma znajdowaæ siê przedmiot
 * @param size Rozmiar tekstury 
 * @param damage Parametr okreœlaj¹cy ile obra¿eñ ma dodaæ do naszej postaci
 * @param health Parametr okreœlaj¹cy ile ¿ycia ma dodaæ do naszej postaci
 * @param maxHealth Parametr okreœlaj¹cy ile maksymalnego ¿ycia ma dodaæ do naszej postaci
 * @param fire_delay Parametr okreœlaj¹cy ile szybkostrzelnoœci ma dodaæ do naszej postaci
 * @param shot_speed Parametr okreœlaj¹cy ile predkoœci naboju ma dodaæ do naszej postaci
 * @param speed Parametr okreœlaj¹cy ile prêdkoœci ma dodaæ do naszej postaci
 * @param money Parametr okreœlaj¹cy ile monet ma dodaæ do naszej postaci
 * @param value Parametr okreœlaj¹cy ile kosztuje przedmiot(u¿ywany w sklepie)
 * @param flying Parametr okreœlaj¹cy czy ma dodaæ do postaci przechodzenie przez przeszkody
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

/** \brief Funkcja daj¹ca przedmiot graczowi
 *
 * @param WskaŸnik na gracza
 */
void Item::giveItem(hero* player)
{
	player->setStatistics(damage, health,maxHealth, fire_delay, shot_speed, speed, money,flying);
}

/** \brief Funkcja wyœwietlaj¹ca przedmiot
 *
 * Funkcja, która wyœwietla na podane okno przedmiot, u³atwia nam wyœwietlanie tego przedmiotu
 * @param window WskaŸnik na okno, w którym ma wyœwietliæ przedmiot
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

/** \brief Funkcja zwracaj¹ca 
 *
 * @return body.getPosition() Zwraca pozycjê postaci
 */

int Item::getMoney()
{
	return money;
}

/** \brief Funkcja zwracaj¹ca pozycje postaci
 *
 * @return body.getPosition() Zwraca pozycjê postaci
 */

int Item::getValue()
{
	return value;
}