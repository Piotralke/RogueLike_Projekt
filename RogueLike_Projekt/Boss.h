#pragma once
#include<SFML/Graphics.hpp>
#include"Monster.h"
#include "Collision.h"
#include "Objects.h"
/**
*	\brief Klasa reprezentująca bossów
*/
class boss : public monster
{
private:
	sf::Clock spawn_delay_clock; /**<\brief Zegar odmierzający czas między możliwością przyzywania przeciwników */
	bool triple_shot;	/**<\brief Zmienna określająca, czy przeciwnik strzela potrójnym strzałem*/
	bool spawn;	/**<\brief Zmienna określająca, czy przeciwnik może przyzywać pomocników */
	bool special_movement;	/**<\brief Zmienna określająca, czy przeciwnik posiada specjalny sposób poruszania się*/
	bool can_shot=true; /**<\brief Zmienna określająca, czy przeciwnik może strzelać w danej chwili*/
	sf::Vector2f randomDir = {1.0f,0.0f};	/**<\brief Zmienna określająca losowy kierunek poruszania się*/
	bool running=false;	/**<\brief Zmienna określająca, czy przeciwnik szarżuje w stronę gracza*/
public:
	boss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health,
		float damage, sf::Vector2f size, sf::Vector2f position, bool shooting, bool flying, bool resurection,bool triple_shot, bool spawn, bool special_movement, sf::Texture* arrow, sf::Vector2i bullet_size)
		:monster(texture, imageCount,switchTime, speed, fire_rate, shot_speed, health,
			damage, size, position, shooting, flying, resurection, arrow, bullet_size), triple_shot(triple_shot),spawn(spawn), special_movement(special_movement){}
	void Update(float deltaTime, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, sf::Texture* ghostTexture, sf::Texture* demonTexture, std::vector<Object>& objectVec, std::vector<sf::RectangleShape>& wallVec);
};