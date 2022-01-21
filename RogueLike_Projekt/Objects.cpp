#include "Objects.h"
/** \brief  Konstruktor dla obiektów
 *
 * Konstruktor zapisuje podane mu parametry do pól obiektu
 * @param itemTexture Tekstura obiektu
 * @param position Pozycja, na której obiekt ma być umieszczony
 * @param size Rozmiar obiektu
 * @param shootable Określa, czy przez dany obiekt może przelecieć pocisk
 * @param shootable Określa, czy wejście w kolizję z obiektem spowoduje przejście na kolejny poziom
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
/** \brief  Funkcja wyświetlająca obiekty
 *
 * Funkcja, która wyświetla na podane okno obiekt
 * @param window Wskaźnik na okno, w którym ma zostać wyświetlony obiekt
 */
void Object::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}