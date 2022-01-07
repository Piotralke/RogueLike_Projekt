#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class menu {
	private:
		sf::Texture background;
		sf::Sprite background_s;
		sf::Texture button;
		sf::Sprite button_s;
		sf::Texture bestiary;
		sf::Sprite bestiary_s;
		sf::Font font;
		int position;
		sf::Text play_text;
		sf::Text sound_text;
		sf::Text sound_mark;
		sf::Text bestiary_text;
		sf::Text exit_text;
		sf::Clock click_delay;
		bool bestiary_b=false;
	public:
		bool sound;
		menu(sf::Font& font);
		bool update(sf::RenderWindow& window, sf::Music& mainMusic, sf::Music& bossMusic);
		void Draw(sf::RenderWindow& window);
		sf::Sprite getTexture();
};
