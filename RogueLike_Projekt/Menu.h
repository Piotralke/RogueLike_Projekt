#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
/**
* Klasa reprezentujkaca menu gry
*/
class menu {
	private:
		sf::Texture background; /**< Tekstura t³a menu*/
		sf::Sprite background_s; /**< Zmienna u³¹twiaj¹ca manipulacjê tekstur¹ t³a menu*/
		sf::Texture button; /**<Tekstura przycisku*/
		sf::Sprite button_s; /**<Zmienna u³atwiaj¹ca manipulacjê tekstur¹ przycisku*/
		sf::Texture bestiary; /**<Tekstura bestiariusza*/
		sf::Sprite bestiary_s; /**<Zmienna u³atwiaj¹ca manipulacjê tekstur¹ bestiariusza*/
		sf::Font font; /**<Czcionka u¿ywana w grze*/
		int position; /**<Opcja w menu, która jest aktualnie wybrana*/
		sf::Text play_text; /**<Tekst na przycisku od uruchomienia gry*/
		sf::Text sound_text; /**<Tekst przy opcji w³¹czenia/wy³¹czenia dŸwiêku*/
		sf::Text sound_mark; /**<"X" stawiany w okienku, które okreœla, czy muzyka jest w³¹czona, czy nie*/
		sf::Text bestiary_text; /**<Tekst przy opcji zobaczenia bestiariusza*/
		sf::Text exit_text; /**<Tekst przy opcji wyjœcia z gry*/
		sf::Clock click_delay; /**<Zegar odmierzaj¹cy czas, miêdzy mo¿liwosci¹ zmiany przycisku*/
		bool bestiary_b=false;/**<Zmienna okreœlaj¹ca, czy znajdujemy siê w widoku bestiariusza*/
	public:
		bool sound; /**<Zmienna okreœlaj¹ca, czy odtwarzany jest dŸwiêk*/
		menu(sf::Font& font);
		bool update(sf::RenderWindow& window, sf::Music& mainMusic, sf::Music& bossMusic);
		void Draw(sf::RenderWindow& window);
		sf::Sprite getTexture();
};
