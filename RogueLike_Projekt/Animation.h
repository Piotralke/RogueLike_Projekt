#pragma once
#include <SFML/Graphics.hpp>
/**
* Klasa odpowiedzialna za odtwarzanie animacji przeciwników, gracza itp 
*/
class Animation {
private:
    sf::Vector2u imageCount; /**<Iloœæ obraznków w jednej animacji*/
    sf::Vector2u currentImage;  /**<Aktualny obrazek, na którym jest animacja*/
    float totalTime;    /**<£¹czny czas wyœwietlania jednej animacji*/
    float switchTime;   /**<Czas co jaki zmieniany jest obrazek*/
public:
    sf::IntRect uvRect; /**<Obszar, ktory jest wielkoœci jednego obrazka z ca³ego pliku zawieraj¹cego animacjê*/
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
        void Update(int row, float deltaTime, bool faceRight);
};