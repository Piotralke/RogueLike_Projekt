#include "Animation.h"

/** \brief  Konstruktor dla animacji
 *
 * @param texture Wskaźnik na teksture
 * @param imageCount Kontener przechowujący informacje o ilości teskstur zawartych w pliku graficznym animacji postaci (dla bohatera 4,2 - 4oznacza 4 różne tekstury dla animacji, a 2 ilość różnych aninmacji)
 * @param switchTime Czas po jakim ma się zmienić tekstura(wykorzystywana w animacji)
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

/** \brief  Funkcja ma za zadanie przemieszczanie się po całej teksturze
 *
 * @param row Zmienna określająca który wiersz animacji ma zostać wykonywany (w pliku graficznym każda animacja jest w osobnym wierszu). Zależnie od wykonywanej czynności może być odtwarzana inna animacja
 * @param deltaTime Zmienna określająca ile czasu minęło pomiędzy klatkami gry (umożliwia ona płynniejsze działanie gry, ponieważ niezależnie od wykorzystanie zasobów komputera gra nie powinna przyspieszać, ani zwalniać)
 * @param faceRight Parametr określający w którą stronę ma być skierowana postać(w lewo lub w prawo)
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