#include "Bullet.h"

/** \brief Konstruktor dla naboju
 *
 * Konstruktor zapisuje parametry podane jako parametry do danego obiektu
 * @param size Rozmiar tekstury naboju
 * @param position Pozycja startowa naszego naboju
 * @param shot_speed Parametr okreœlaj¹cy prêdkoœæ pocisku 
 * @param damage Parametr okreœlaj¹cy obra¿enia
 * @param shooting_direction Wektor wskazuj¹cy kierunek, w którym pocisk ma przemierzaæ
 * @param texture WskaŸnik na teksture naboju
 * @param rotation K¹t pod jakim obrucona jest tekstura pocisku 
 */

Bullet::Bullet(sf::Vector2f size, sf::Vector2f position, float shot_speed, float damage, sf::Vector2f shotting_direction, sf::Texture *texture, float rotation)
{
	bullet.setSize(size);
	bullet.setOrigin(bullet.getSize() / 2.0f);
	bullet.setPosition(position);
	bullet.setTexture(texture);
	bullet.setRotation(rotation);
	this->shot_speed = shot_speed;
	this->damage = damage;
	direction = shotting_direction;
	directionNormalized = { direction.x / (float)sqrt(pow(direction.x, 2) + pow(direction.y, 2)), direction.y / (float)sqrt(pow(direction.x, 2) + pow(direction.y, 2)) };
}

/** \brief Funkcja przemieszczaj¹ca nabój
 *
 * @param deltaTime Zmienna okreœlaj¹ca ile czasu minê³o pomiêdzy klatkami gry (umo¿liwia ona p³ynniejsze dzia³anie gry, poniewa¿ niezale¿nie od wykorzystanie zasobów komputera gra nie powinna przyspieszaæ, ani zwalniaæ)
 */

void Bullet::fire(float deltaTime)
{
	bullet.move({ directionNormalized.x * shot_speed * deltaTime, directionNormalized.y * shot_speed * deltaTime });	
}

/** \brief Funkcja wyœwietlaj¹ca nabój
 *
 * Funkcja, która wyœwietla na podane okno nabój, u³atwia nam wyœwietlanie naboju
 * @param window WskaŸnik na okno, w którym ma wypisaæ statystyki
 */

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(bullet);
}

/** \brief Funkcja zwracaj¹ca obra¿enia naboju
 *
 * @return body.getPosition() Zwraca obra¿enia naboju
 */

float Bullet::getDamage()
{
	return damage;
}