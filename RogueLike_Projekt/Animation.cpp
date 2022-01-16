#include "Animation.h"

/** \brief Konstruktor dla animacji
 *
 * @param texture WskaŸnik na teksture
 * @param imageCount Kontener przechowuj¹cy informacje o iloœci teskstur zawartych w pliku graficznym animacji postaci (dla bohatera 4,2 - 4oznacza 4 ró¿ne tekstury dla animacji, a 2 iloœæ ró¿nych aninmacji)
 * @param switchTime Czas po jakim ma siê zmieniæ tekstura(wykorzystywana w animacji)
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

/** \brief Funkcja ma za zadanie przemieszczanie siê po ca³ej teksturze
 *
 * @param row Zmienna okreœlaj¹ca który wiersz animacji ma zostaæ wykonywany (w pliku graficznym ka¿da animacja jest w osobnym wierszu). Zale¿nie od wykonywanej czynnoœci mo¿e byæ odtwarzana inna animacja
 * @param deltaTime Zmienna okreœlaj¹ca ile czasu minê³o pomiêdzy klatkami gry (umo¿liwia ona p³ynniejsze dzia³anie gry, poniewa¿ niezale¿nie od wykorzystanie zasobów komputera gra nie powinna przyspieszaæ, ani zwalniaæ)
 * @param faceRight Parametr okreœlaj¹cy w któr¹ stronê ma byæ skierowana postaæ(w lewo lub w prawo)
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