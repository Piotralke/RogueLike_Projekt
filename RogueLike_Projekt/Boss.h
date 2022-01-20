#pragma once
#include<SFML/Graphics.hpp>
#include"Monster.h"
#include "Collision.h"
#include "Objects.h"
/**
*	Klasa reprezentuj¹ca bossów
*/
class boss : public monster
{
private:
	sf::Clock spawn_delay_clock; /**<Zegar odmierzaj¹cy czas miêdzy mo¿liwoœci¹ przyzywania przeciwników */
	bool triple_shot;	/**<Zmienna okreœlaj¹ca, czy przeciwnik strzela potrójnym strza³em*/
	bool spawn;	/**<Zmienna okreœlaj¹ca, czy przeciwnik mo¿e przyzywaæ pomocników */
	bool special_movement;	/**<Zmienna okreœlaj¹ca, czy przeciwnik posiada specjalny sposób poruszania siê*/
	bool can_shot=true; /**<Zmienna okreœlaj¹ca, czy przeciwnik mo¿e strzelaæ w danej chwili*/
	sf::Vector2f randomDir = {1.0f,0.0f};	/**<Zmienna okreœlaj¹ca losowy kierunek poruszania siê*/
	bool running=false;	/**<Zmienna okreœlaj¹ca, czy przeciwnik szar¿uje w stronê gracza*/
public:
	boss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health,
		float damage, sf::Vector2f size, sf::Vector2f position, bool shooting, bool flying, bool resurection,bool triple_shot, bool spawn, bool special_movement, sf::Texture* arrow, sf::Vector2i bullet_size)
		:monster(texture, imageCount,switchTime, speed, fire_rate, shot_speed, health,
			damage, size, position, shooting, flying, resurection, arrow, bullet_size), triple_shot(triple_shot),spawn(spawn), special_movement(special_movement){}
	void Update(float deltaTime, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, sf::Texture* ghostTexture, sf::Texture* demonTexture, std::vector<Object>& objectVec, std::vector<sf::RectangleShape>& wallVec);
};