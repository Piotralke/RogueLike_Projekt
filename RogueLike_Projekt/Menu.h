#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
/**
* \brief  Klasa reprezentująca menu gry
*/
class menu {
	private:
		sf::Texture background; /**<\brief  Tekstura tła menu*/
		sf::Sprite background_s; /**<\brief  Zmienna ułątwiająca manipulację teksturą tła menu*/
		sf::Texture button; /**<\brief  Tekstura przycisku*/
		sf::Sprite button_s; /**<\brief  Zmienna ułatwiająca manipulację teksturą przycisku*/
		sf::Texture bestiary; /**<\brief  Tekstura bestiariusza*/
		sf::Sprite bestiary_s; /**<\brief  Zmienna ułatwiająca manipulację teksturą bestiariusza*/
		sf::Font font; /**<\brief  Czcionka używana w grze*/
		int position; /**<\brief  Opcja w menu, która jest aktualnie wybrana*/
		sf::Text play_text; /**<\brief  Tekst na przycisku od uruchomienia gry*/
		sf::Text sound_text; /**<\brief  Tekst przy opcji włączenia/wyłączenia dźwięku*/
		sf::Text sound_mark; /**<\brief  "X" stawiany w okienku, które określa, czy muzyka jest włączona, czy nie*/
		sf::Text bestiary_text; /**<\brief  Tekst przy opcji zobaczenia bestiariusza*/
		sf::Text exit_text; /**<\brief  Tekst przy opcji wyjścia z gry*/
		sf::Clock click_delay; /**<\brief  Zegar odmierzający czas, między możliwoscią zmiany przycisku*/
		bool bestiary_b=false;/**<\brief  Zmienna określająca, czy znajdujemy się w widoku bestiariusza*/
	public:
		bool sound; /**<\brief  Zmienna określająca, czy odtwarzany jest dźwięk*/
		menu(sf::Font& font);
		bool update(sf::RenderWindow& window, sf::Music& mainMusic, sf::Music& bossMusic);
		void Draw(sf::RenderWindow& window);
		sf::Sprite getTexture();
};
