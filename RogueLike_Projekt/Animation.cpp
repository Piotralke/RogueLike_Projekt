#include "Animation.h"

/** \brief Konstruktor dla animacji
 *
 * @param texture Wska�nik na teksture
 * @param imageCount Kontener przechowuj�cy informacje o ilo�ci teskstur zawartych w pliku graficznym animacji postaci (dla bohatera 4,2 - 4oznacza 4 r�ne tekstury dla animacji, a 2 ilo�� r�nych aninmacji)
 * @param switchTime Czas po jakim ma si� zmieni� tekstura(wykorzystywana w animacji)
 */

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
    {
        this->imageCount = imageCount;
        this->switchTime = switchTime;
        totalTime = 0.0f;
        currentImage.x = 0;

        uvRect.width = texture->getSize().x / float(imageCount.x);
        uvRect.height = texture->getSize().y / float(imageCount.y);
    }

/** \brief Funkcja ma za zadanie przemieszczanie si� po ca�ej teksturze
 *
 * @param row Zmienna okre�laj�ca kt�ry wiersz animacji ma zosta� wykonywany (w pliku graficznym ka�da animacja jest w osobnym wierszu). Zale�nie od wykonywanej czynno�ci mo�e by� odtwarzana inna animacja
 * @param deltaTime Zmienna okre�laj�ca ile czasu min�o pomi�dzy klatkami gry (umo�liwia ona p�ynniejsze dzia�anie gry, poniewa� niezale�nie od wykorzystanie zasob�w komputera gra nie powinna przyspiesza�, ani zwalnia�)
 * @param faceRight Parametr okre�laj�cy w kt�r� stron� ma by� skierowana posta�(w lewo lub w prawo)
 */

void Animation::Update(int row, float deltaTime, bool faceRight)
    {
        currentImage.y = row;
        totalTime += deltaTime;

        if (totalTime >= switchTime)
        {
            totalTime -= switchTime;
            currentImage.x++;
            if (currentImage.x >= imageCount.x)
            {
                currentImage.x = 0;
            }
        }

        uvRect.top = currentImage.y * uvRect.height;

        if (faceRight)
        {
            uvRect.left = currentImage.x * uvRect.width;
            uvRect.width = abs(uvRect.width);
        }
        else
        {
            uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
            uvRect.width = -abs(uvRect.width);
        }

    }