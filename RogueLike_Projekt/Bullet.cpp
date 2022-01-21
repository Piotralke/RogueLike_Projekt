#include "Bullet.h"

/** \brief  Konstruktor dla naboju
 *
 * Konstruktor zapisuje parametry podane jako parametry do danego obiektu
 * @param size Rozmiar tekstury naboju
 * @param position Pozycja startowa naszego naboju
 * @param shot_speed Parametr określający prędkość pocisku 
 * @param damage Parametr określający obrażenia
 * @param shooting_direction Wektor wskazujący kierunek, w którym pocisk ma przemierzać
 * @param texture Wskaźnik na teksture naboju
 * @param rotation Kąt pod jakim obrucona jest tekstura pocisku 
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

/** \brief  Funkcja przemieszczająca nabój
 *
 * @param deltaTime Zmienna określająca ile czasu minęło pomiędzy klatkami gry (umożliwia ona płynniejsze działanie gry, ponieważ niezależnie od wykorzystanie zasobów komputera gra nie powinna przyspieszać, ani zwalniać)
 */

void Bullet::fire(float deltaTime)
{
	bullet.move({ directionNormalized.x * shot_speed * deltaTime, directionNormalized.y * shot_speed * deltaTime });	
}

/** \brief  Funkcja wyświetlająca nabój
 *
 * Funkcja, która wyświetla na podane okno nabój, ułatwia nam wyświetlanie naboju
 * @param window Wskaźnik na okno, w którym ma wypisać statystyki
 */

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(bullet);
}

/** \brief  Funkcja zwracająca obrażenia naboju
 *
 * @return body.getPosition() Zwraca obrażenia naboju
 */

float Bullet::getDamage()
{
	return damage;
}