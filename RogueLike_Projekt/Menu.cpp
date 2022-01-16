#include "Menu.h"

/** \brief Konstruktor dla menu
 *
 * Konstruktor 
 * @param font WskaŸnik na czcionkê u¿ywan¹ w programie
 */

menu::menu(sf::Font& font)
{
	this->font = font;
	background.loadFromFile("grafiki/menu_background.png");
	background_s.setTexture(background);
	background_s.setPosition({ 0.0f,0.0f });
	button.loadFromFile("grafiki/menu_button.png");
	button_s.setTexture(button);
	button_s.setPosition({ 0.0f,0.0f });
	bestiary.loadFromFile("grafiki/menu_bestiary.png");
	bestiary_s.setTexture(bestiary);
	bestiary_s.setPosition({ 0.0f,0.0f });
	this->position = 0;
	this->sound = true;

	play_text.setFont(font);
	play_text.setCharacterSize(16);
	play_text.setFillColor(sf::Color::White);
	play_text.setString("PLAY");
	play_text.setPosition({ 330.0f,130.0f });

	sound_text.setFont(font);
	sound_text.setCharacterSize(16);
	sound_text.setFillColor(sf::Color::White);
	sound_text.setString("SOUND");
	sound_text.setPosition({ 330.0f,170.0f });

	sound_mark.setFont(font);
	sound_mark.setCharacterSize(16);
	sound_mark.setFillColor(sf::Color::Black);
	sound_mark.setString("X");
	sound_mark.setPosition({ 461.0f,173.0f });

	bestiary_text.setFont(font);
	bestiary_text.setCharacterSize(16);
	bestiary_text.setFillColor(sf::Color::White);
	bestiary_text.setString("BESTIARY");
	bestiary_text.setPosition({ 330.0f,210.0f });

	exit_text.setFont(font);
	exit_text.setCharacterSize(16);
	exit_text.setFillColor(sf::Color::White);
	exit_text.setString("EXIT");
	exit_text.setPosition({ 330.0f,260.0f });
}

/** \brief Funkcja wyœwietlaj¹ca menu
 *
 * Funkcja u³atwiaj¹ca wyœwietlanie wszystkich potrzebnych elementów menu
 * @param window WskaŸnik na okno, w którym ma wyœwietliæ przedmiot
 */

void menu::Draw(sf::RenderWindow& window)
{
	window.draw(background_s);
	window.draw(button_s);
	window.draw(play_text);
	window.draw(sound_text);
	window.draw(bestiary_text);
	window.draw(exit_text);
	window.draw(sound_mark);
}

/** \brief Funkcja 
 *
 * Funkcja 
 * @param window WskaŸnik na okno, w którym ma wyœwietliæ przedmiot
 * @param mainMusic WskaŸnik na g³ówn¹ muzykê gry
 * @param bossMusic WskaŸnik na muzykê odtwarzan¹ podczas walki z Bossem
 */
 
bool menu::update(sf::RenderWindow& window, sf::Music& mainMusic, sf::Music& bossMusic)
{
	if (click_delay.getElapsedTime().asSeconds() >= 0.2)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (position == 0)
				position = 3;
			else
				position--;
			click_delay.restart();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (position == 3)
				position = 0;
			else
				position++;
			click_delay.restart();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			click_delay.restart();
			switch (position)
			{
			case 0:
				return false;
			case 1:
				if (sound)
				{
					sound_mark.setFillColor(sf::Color::White);
					sound = false;
					mainMusic.stop();
					bossMusic.stop();
				}

				else
				{
					sound_mark.setFillColor(sf::Color::Black);
					sound = true;
				}
				break;
			case 2:
				bestiary_b = true;
				while (bestiary_b)
				{
					window.clear();
					window.draw(bestiary_s);
					window.display();
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						bestiary_b = false;
					}
				}
				break;
			case 3:
				mainMusic.stop();
				window.close();
				return false;
				break;
			}
		}
	}
	switch (position)
	{
	case 0:
		play_text.setFillColor(sf::Color::Black);
		sound_text.setFillColor(sf::Color::White);
		bestiary_text.setFillColor(sf::Color::White);
		exit_text.setFillColor(sf::Color::White);
		break;
	case 1:
		play_text.setFillColor(sf::Color::White);
		sound_text.setFillColor(sf::Color::Black);
		bestiary_text.setFillColor(sf::Color::White);
		exit_text.setFillColor(sf::Color::White);
		break;
	case 2:
		play_text.setFillColor(sf::Color::White);
		sound_text.setFillColor(sf::Color::White);
		bestiary_text.setFillColor(sf::Color::Black);
		exit_text.setFillColor(sf::Color::White);
		break;
	case 3:
		play_text.setFillColor(sf::Color::White);
		sound_text.setFillColor(sf::Color::White);
		bestiary_text.setFillColor(sf::Color::White);
		exit_text.setFillColor(sf::Color::Black);
		break;

	}
	
	return true;
}

/** \brief Funkcja zwracaj¹ca teksture guzika
 *
 * @return button_s zwraca teksture guzika
 */

sf::Sprite menu::getTexture()
{
	return button_s;
}
