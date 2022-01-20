#pragma once
#include<SFML/Graphics.hpp>
#include"Monster.h"
#include "Collision.h"
#include "Objects.h"
/**
*	Klasa reprezentuj�ca boss�w
*/
class boss : public monster
{
private:
	sf::Clock spawn_delay_clock; /**<Zegar odmierzaj�cy czas mi�dzy mo�liwo�ci� przyzywania przeciwnik�w */
	bool triple_shot;	/**<Zmienna okre�laj�ca, czy przeciwnik strzela potr�jnym strza�em*/
	bool spawn;	/**<Zmienna okre�laj�ca, czy przeciwnik mo�e przyzywa� pomocnik�w */
	bool special_movement;	/**<Zmienna okre�laj�ca, czy przeciwnik posiada specjalny spos�b poruszania si�*/
	bool can_shot=true; /**<Zmienna okre�laj�ca, czy przeciwnik mo�e strzela� w danej chwili*/
	sf::Vector2f randomDir = {1.0f,0.0f};	/**<Zmienna okre�laj�ca losowy kierunek poruszania si�*/
	bool running=false;	/**<Zmienna okre�laj�ca, czy przeciwnik szar�uje w stron� gracza*/
public:
	boss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float fire_rate, float shot_speed, float health,
		float damage, sf::Vector2f size, sf::Vector2f position, bool shooting, bool flying, bool resurection,bool triple_shot, bool spawn, bool special_movement, sf::Texture* arrow, sf::Vector2i bullet_size)
		:monster(texture, imageCount,switchTime, speed, fire_rate, shot_speed, health,
			damage, size, position, shooting, flying, resurection, arrow, bullet_size), triple_shot(triple_shot),spawn(spawn), special_movement(special_movement){}
	void Update(float deltaTime, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, sf::Texture* ghostTexture, sf::Texture* demonTexture, std::vector<Object>& objectVec, std::vector<sf::RectangleShape>& wallVec);
};