#include "Objects.h"
/** \brief Konstruktor dla obiekt�w
 *
 * Konstruktor zapisuje podane mu parametry do p�l obiektu
 * @param itemTexture Tekstura obiektu
 * @param position Pozycja, na kt�rej obiekt ma by� umieszczony
 * @param size Rozmiar obiektu
 * @param shootable Okre�la, czy przez dany obiekt mo�e przelecie� pocisk
 * @param shootable Okre�la, czy wej�cie w kolizj� z obiektem spowoduje przej�cie na kolejny poziom
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
/** \brief Funkcja wy�wietlaj�ca obiekty
 *
 * Funkcja, kt�ra wy�wietla na podane okno obiekt
 * @param window Wska�nik na okno, w kt�rym ma zosta� wy�wietlony obiekt
 */
void Object::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}