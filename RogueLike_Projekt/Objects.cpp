#include "Objects.h"
/** \brief Konstruktor dla obiektów
 *
 * Konstruktor zapisuje podane mu parametry do pól obiektu
 * @param itemTexture Tekstura obiektu
 * @param position Pozycja, na której obiekt ma byæ umieszczony
 * @param size Rozmiar obiektu
 * @param shootable Okreœla, czy przez dany obiekt mo¿e przelecieæ pocisk
 * @param shootable Okreœla, czy wejœcie w kolizjê z obiektem spowoduje przejœcie na kolejny poziom
 */
Object::Object(sf::Texture* itemTexture, sf::Vector2f position, sf::Vector2f size, bool shootable, bool go_down)
{
	shape.setSize(size);
	shape.setOrigin(shape.getSize() / 2.0f);
	shape.setPosition(position);
	shape.setTexture(itemTexture);
	this->shootable = shootable;
	this->go_down = go_down;
}
/** \brief Funkcja wyœwietlaj¹ca obiekty
 *
 * Funkcja, która wyœwietla na podane okno obiekt
 * @param window WskaŸnik na okno, w którym ma zostaæ wyœwietlony obiekt
 */
void Object::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}