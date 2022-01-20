#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
/**
* Klasa reprezentujkaca menu gry
*/
class menu {
	private:
		sf::Texture background; /**< Tekstura t�a menu*/
		sf::Sprite background_s; /**< Zmienna u��twiaj�ca manipulacj� tekstur� t�a menu*/
		sf::Texture button; /**<Tekstura przycisku*/
		sf::Sprite button_s; /**<Zmienna u�atwiaj�ca manipulacj� tekstur� przycisku*/
		sf::Texture bestiary; /**<Tekstura bestiariusza*/
		sf::Sprite bestiary_s; /**<Zmienna u�atwiaj�ca manipulacj� tekstur� bestiariusza*/
		sf::Font font; /**<Czcionka u�ywana w grze*/
		int position; /**<Opcja w menu, kt�ra jest aktualnie wybrana*/
		sf::Text play_text; /**<Tekst na przycisku od uruchomienia gry*/
		sf::Text sound_text; /**<Tekst przy opcji w��czenia/wy��czenia d�wi�ku*/
		sf::Text sound_mark; /**<"X" stawiany w okienku, kt�re okre�la, czy muzyka jest w��czona, czy nie*/
		sf::Text bestiary_text; /**<Tekst przy opcji zobaczenia bestiariusza*/
		sf::Text exit_text; /**<Tekst przy opcji wyj�cia z gry*/
		sf::Clock click_delay; /**<Zegar odmierzaj�cy czas, mi�dzy mo�liwosci� zmiany przycisku*/
		bool bestiary_b=false;/**<Zmienna okre�laj�ca, czy znajdujemy si� w widoku bestiariusza*/
	public:
		bool sound; /**<Zmienna okre�laj�ca, czy odtwarzany jest d�wi�k*/
		menu(sf::Font& font);
		bool update(sf::RenderWindow& window, sf::Music& mainMusic, sf::Music& bossMusic);
		void Draw(sf::RenderWindow& window);
		sf::Sprite getTexture();
};
