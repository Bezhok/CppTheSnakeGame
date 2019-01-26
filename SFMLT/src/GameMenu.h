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

		void draw();
		void handle_input();
		int choosen_level();
	private:
		game_data_ref m_data;
		vector<sf::RectangleShape> m_levels;
		MenuState m_state = MenuState::main;

		sf::RectangleShape m_stats_b;
		sf::Sprite m_play_b;
		sf::Texture m_play_b_texture;
	};
}


