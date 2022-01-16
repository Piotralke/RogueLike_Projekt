#include "Bullet.h"

/** \brief Konstruktor dla naboju
 *
 * Konstruktor zapisuje parametry podane jako parametry do danego obiektu
 * @param size Rozmiar tekstury naboju
 * @param position Pozycja startowa naszego naboju
 * @param shot_speed Parametr okre�laj�cy pr�dko�� pocisku 
 * @param damage Parametr okre�laj�cy obra�enia
 * @param shooting_direction Wektor wskazuj�cy kierunek, w kt�rym pocisk ma przemierza�
 * @param texture Wska�nik na teksture naboju
 * @param rotation K�t pod jakim obrucona jest tekstura pocisku 
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

/** \brief Funkcja przemieszczaj�ca nab�j
 *
 * @param deltaTime Zmienna okre�laj�ca ile czasu min�o pomi�dzy klatkami gry (umo�liwia ona p�ynniejsze dzia�anie gry, poniewa� niezale�nie od wykorzystanie zasob�w komputera gra nie powinna przyspiesza�, ani zwalnia�)
 */

void Bullet::fire(float deltaTime)
{
	bullet.move({ directionNormalized.x * shot_speed * deltaTime, directionNormalized.y * shot_speed * deltaTime });	
}

/** \brief Funkcja wy�wietlaj�ca nab�j
 *
 * Funkcja, kt�ra wy�wietla na podane okno nab�j, u�atwia nam wy�wietlanie naboju
 * @param window Wska�nik na okno, w kt�rym ma wypisa� statystyki
 */

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(bullet);
}

/** \brief Funkcja zwracaj�ca obra�enia naboju
 *
 * @return body.getPosition() Zwraca obra�enia naboju
 */

float Bullet::getDamage()
{
	return damage;
}