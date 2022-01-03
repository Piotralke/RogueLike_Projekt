#pragma once
#include<SFML/Graphics.hpp>
#include"Monster.h"

class boss : public monster
{
private:
	sf::Clock spawn_delay_clock;
	
public:
	boss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health,
		float damage, sf::Vector2f size, sf::Vector2f position, bool shooting, bool flying, bool resurection)
		:monster(texture, imageCount,switchTime, speed, fire_rate, shot_speed, health,
			damage, size, position, shooting, flying, resurection) {}
	void Update(float deltaTime, sf::Texture* arrow, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, sf::Texture* ghostTexture);
};