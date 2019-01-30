#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Game.h"


namespace Bezhok {
	using std::vector;

	class GameMenu
	{
	public:
		enum MenuState {
			main, statistics
		};

		GameMenu(game_data_ref data);
		~GameMenu();

		/* draw menu */
		void draw();

		/* handle input */
		void handle_input(sf::Keyboard::Key key);

		/* return id of clicked level */
		int choosen_level();
	private:
		game_data_ref m_data;
		vector<sf::RectangleShape> m_levels;
		MenuState m_state = MenuState::main;

		sf::RectangleShape m_records_b;
		sf::Sprite m_play_b;
		sf::Texture m_play_b_texture;

		/* check mouse position */
		bool is_on_sprite(sf::Sprite obj);
		bool is_on_rect(sf::RectangleShape obj);
	};
}


