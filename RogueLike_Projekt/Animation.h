#pragma once
#include <SFML/Graphics.hpp>
/**
* Klasa odpowiedzialna za odtwarzanie animacji przeciwnik�w, gracza itp 
*/
class Animation {
private:
    sf::Vector2u imageCount; /**<Ilo�� obraznk�w w jednej animacji*/
    sf::Vector2u currentImage;  /**<Aktualny obrazek, na kt�rym jest animacja*/
    float totalTime;    /**<��czny czas wy�wietlania jednej animacji*/
    float switchTime;   /**<Czas co jaki zmieniany jest obrazek*/
public:
    sf::IntRect uvRect; /**<Obszar, ktory jest wielko�ci jednego obrazka z ca�ego pliku zawieraj�cego animacj�*/
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
        void Update(int row, float deltaTime, bool faceRight);
};