#include "Monster.h"
/** \brief Funkcja zwracaj�ca wektor od przeciwnika do gracza
 *
 * @param player Wska�nik na gracza
 * @return this->GetPosition() - player.GetPosition() zwraca wektor od przeciwnika do gracza
 */
sf::Vector2f monster::getDirVec(hero player)
{
	return this->GetPosition() - player.GetPosition();
}
/** \brief Funkcja zwracaj�ca k�t pod jakim jest dany wektor
 *
 * @param DirVec Wektor od przeciwnika do gracza
 * @return std::atan2f(DirVec.y, DirVec.x) * 180 / PI Zwraca k�t pod jakim jest dany wektor. U�ywane do obracania tekstur pocisk�w
 */
float monster::getDirDeg(sf::Vector2f DirVec)
{
	return std::atan2f(DirVec.y, DirVec.x) * 180 / PI ;
}

/** \brief Funkcja aktualizuj�ca pozycje przeciwnik�w oraz okre�laj�ca ich specjalne umiej�tno�ci
 *
 * G��wna funkcja dla przeciwnik�w, w niej s� sprecyzowane unikalne zachowania dla ka�dego przeciwnika
 * @param deltaTime Zmienna okre�laj�ca ile czasu min�o pomi�dzy klatkami gry (umo�liwia ona p�ynniejsze dzia�anie gry, poniewa� niezale�nie od wykorzystanie zasob�w komputera gra nie powinna przyspiesza�, ani zwalnia�)
 * @param bulletVec Wska�nik na vector naboi potwor�w
 * @param monsterVec Wska�nik na vector potwor�w
 * @param player Wys�ana ca�a nasza g��wna posta�
 * @param skeleton_count Ilo�� szkielet�w na mapie gry
 * @param dead_skeleton	Ilo�� obalonych szkielet�w
 */

void monster::Update(float deltaTime, std::vector<Bullet>& bulletVec, std::vector<monster>& monsterVec, hero player, int& skeleton_count, int& dead_skeleton)
{
	if (shot_clock.getElapsedTime().asSeconds() >= 0.25f && memSpeed == 150.0f && test == 1)
	{
		sf::Vector2f shottingDir = getDirVec(player);
		Bullet newBullet(bullet_size, body.getPosition(), shot_speed, damage, -shottingDir, arrow, getDirDeg(shottingDir) - 90.0f);
		bulletVec.push_back(newBullet);
		test++;
	}
	else if (shot_clock.getElapsedTime().asSeconds() >= 0.5f && memSpeed == 150.0f && test == 2)
	{
		sf::Vector2f shottingDir = getDirVec(player);
		Bullet newBullet(bullet_size, body.getPosition(), shot_speed, damage, -shottingDir, arrow, getDirDeg(shottingDir) - 90.0f);
		bulletVec.push_back(newBullet);
		test = 0;
	}
	if (fire_delay_clock.getElapsedTime().asSeconds() >= fire_rate && shooting == true)
	{
		if (memSpeed == 150.f)
		{
			shot_clock.restart();
			sf::Vector2f shottingDir = getDirVec(player);
			Bullet newBullet(bullet_size, body.getPosition(), shot_speed, damage, -shottingDir, arrow, getDirDeg(shottingDir) - 90.0f);
			bulletVec.push_back(newBullet);
			test = 1;
		}
		else if (shot_speed == 200.0f)
		{
			if (test == 0)
			{
				Bullet newBullet1(bullet_size, body.getPosition(), shot_speed, damage, { 0.0f, -1.0f }, arrow, 0.0f);
				Bullet newBullet2(bullet_size, body.getPosition(), shot_speed, damage, { 0.0f, 1.0f }, arrow, 0.0f);
				Bullet newBullet3(bullet_size, body.getPosition(), shot_speed, damage, { 1.0f, 0.0f }, arrow, 0.0f);
				Bullet newBullet4(bullet_size, body.getPosition(), shot_speed, damage, { -1.0f, 0.0f }, arrow, 0.0f);
				bulletVec.push_back(newBullet1);
				bulletVec.push_back(newBullet2);
				bulletVec.push_back(newBullet3);
				bulletVec.push_back(newBullet4);
				test = 1;
			}
			else if (test == 1)
			{
				Bullet newBullet1(bullet_size, body.getPosition(), shot_speed, damage, { 1.0f, 1.0f }, arrow, 0.0f);
				Bullet newBullet2(bullet_size, body.getPosition(), shot_speed, damage, { 1.0f, -1.0f }, arrow, 0.0f);
				Bullet newBullet3(bullet_size, body.getPosition(), shot_speed, damage, { -1.0f, 1.0f }, arrow, 0.0f);
				Bullet newBullet4(bullet_size, body.getPosition(), shot_speed, damage, { -1.0f, -1.0f }, arrow, 0.0f);
				bulletVec.push_back(newBullet1);
				bulletVec.push_back(newBullet2);
				bulletVec.push_back(newBullet3);
				bulletVec.push_back(newBullet4);
				test = 0;
			}
			
		}
		else
		{
			sf::Vector2f shottingDir = getDirVec(player);
			Bullet newBullet(bullet_size, body.getPosition(), shot_speed, damage, -shottingDir, arrow, getDirDeg(shottingDir) - 90.0f);
			bulletVec.push_back(newBullet);
			
		}
		fire_delay_clock.restart();
	}
	if (speed > 0.0f)
	{
		sf::Vector2f moveDir;
		if (memSpeed == 150.0f)
		{
			sf::Vector2f movement;
			if(rotate_clock.getElapsedTime().asSeconds()<0.8f)
				movement = {0.0f,1.0f};
			if (rotate_clock.getElapsedTime().asSeconds() >= 0.8f)
			{
				movement.y = (-1);
			}
			if (rotate_clock.getElapsedTime().asSeconds() >= 1.6f)
			{
				rotate_clock.restart();
			}
			
			body.move({ movement.x * speed * deltaTime, movement.y * speed * deltaTime });
			
		}
		moveDir = -getDirVec(player);
		if (memSpeed >= 170.0f)
		{
			if (jump_clock.getElapsedTime().asSeconds() >= 2.5f)
			{
				jump_clock.restart();
				speed = memSpeed;
				row = 1;
			}
			else if(jump_clock.getElapsedTime().asSeconds()>=0.9f)
			{
				row = 0;
				speed = 0.01;
			}
			
			sf::Vector2f moveDirNorm = { moveDir.x / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)), moveDir.y / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)) };
			body.move({ moveDirNorm.x * speed * deltaTime, moveDirNorm.y * speed * deltaTime });
		}
		else if(memSpeed!=150.0f)
		{
			sf::Vector2f moveDirNorm = { moveDir.x / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)), moveDir.y / (float)sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2)) };
			body.move({ moveDirNorm.x * speed * deltaTime, moveDirNorm.y * speed * deltaTime });
		}
	}
	if (teleport)
	{
		if (jump_clock.getElapsedTime().asSeconds() >= 2.0f)
		{
			row = 1;
			if (jump_clock.getElapsedTime().asSeconds() >= 2.4 && test == 0)
			{
				int random = rand() % 4;
				switch (random)
				{
				case 0:
					body.setPosition({ 110.0f,110.0f });
					break;
				case 1:
					body.setPosition({ 110.0f,270.0f });
					break;
				case 2:
					body.setPosition({ 570.0f,110.0f });
					break;
				case 3:
					body.setPosition({ 570.0f,270.0f });
					break;
				}
				test = 1;
			}
			else if (jump_clock.getElapsedTime().asSeconds() >= 2.4 && test == 1)
			{
				row = 2;
				test = 2;
			}
			else if (jump_clock.getElapsedTime().asSeconds() >= 2.8 && test == 2)
			{
				row = 0;
				test = 0;
				jump_clock.restart();
				fire_delay_clock.restart();
			}
			
		}
		
	}
	if (getDirVec(player).x < 0) {
		faceRight = true;
	}
	else {
		faceRight = false;
	}
	if (this->resurection == true && this->health <= 0.0f)
	{
		if (this->dead == false)
		{
			dead_skeleton++;
			dead = true;
			animation_clock.restart();
			row = 1;
			speed = 0.0f;
		}
		if (skeleton_count == monsterVec.size() && dead_skeleton == monsterVec.size())
		{
			skeleton_count = 0;
			dead_skeleton = 0;
			monsterVec.clear();
			monsterVec = std::vector<monster>();
		}	
	}
	if (animation_clock.getElapsedTime().asSeconds() >= 10.0f && this->dead == true) {

		speed = memSpeed;
		health = memHealth;
		row = 0;
		dead = false;
		dead_skeleton--;
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}
/** \brief Funkcja wy�wietlaj�ca przeciwnika
 *
 * Funkcja, kt�ra wy�wietla na podane okno przeciwnika
 * @param window Wska�nik na okno, w kt�rym ma zosta� wy�wietlony przeciwnik
 */
void monster::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
