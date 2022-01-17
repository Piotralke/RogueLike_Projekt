#pragma once
#include<SFML/Graphics.hpp>
#include"Monster.h"

class boss : public monster
{
private:
	sf::Clock spawn_delay_clock;
	bool triple_shot;
	bool spawn;
	bool special_movement;
	bool can_shot=true;
public:
	boss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health,
		float damage, sf::Vector2f size, sf::Vector2f position, bool shooting, bool flying, bool resurection,bool triple_shot, bool spawn, bool special_movement, sf::Texture* arrow, sf::Vector2i bullet_size)
		:monster(texture, imageCount,switchTime, speed, fire_rate, shot_speed, health,
			damage, size, position, shooting, flying, resurection, arrow, bullet_size), triple_shot(triple_shot),spawn(spawn), special_movement(special_movement){}
	void Update(float deltaTime, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, sf::Texture* ghostTexture, sf::Texture* demonTexture);
};