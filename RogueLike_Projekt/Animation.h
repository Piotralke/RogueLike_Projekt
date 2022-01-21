#pragma once
#include <SFML/Graphics.hpp>
/**
* \brief Klasa odpowiedzialna za odtwarzanie animacji przeciwników, gracza itp 
*/
class Animation {
private:
    sf::Vector2u imageCount; /**<\brief Ilość obraznków w jednej animacji*/
    sf::Vector2u currentImage;  /**<\brief Aktualny obrazek, na którym jest animacja*/
    float totalTime;    /**<\brief £ączny czas wyświetlania jednej animacji*/
    float switchTime;   /**<\brief Czas co jaki zmieniany jest obrazek*/
public:
    sf::IntRect uvRect; /**<\brief Obszar, ktory jest wielkości jednego obrazka z całego pliku zawierającego animację*/
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
        void Update(int row, float deltaTime, bool faceRight);
};