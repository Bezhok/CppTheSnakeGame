#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <memory>
//#include "Snake.h"

namespace Bezhok {
	using std::fstream;
	using std::vector;
	using std::shared_ptr;

	class GameObject;
	class Snake;
	class Fruit;

	struct Game_Data
	{
		sf::RenderWindow window;
		//Snake snake;
		//Fruit fruit;
	};
	typedef shared_ptr<Game_Data> game_data_ref;

	class Game
	{
	public:
		static const int BLOCK_SIZE = 16;
		static const int BLOCKS_COUNT_X = 30;
		static const int BLOCKS_COUNT_Y = 20;
		static const int WIDTH = BLOCK_SIZE * BLOCKS_COUNT_X;
		static const int HEIGTH = BLOCK_SIZE * BLOCKS_COUNT_Y;

		/* read stats, create m_data */
		Game();

		/* write stats */
		~Game();

		/* game cycle */
		void run();

	private:
		int m_stats[10] = { 0 };
		const char m_fname[10] = "stats.dat";
		game_data_ref m_data;
		sf::Event m_event;

		/* handle input events */
		void handle_input();
	};
}