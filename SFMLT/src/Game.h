#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <memory>
#include <string>

namespace Bezhok {
	using std::fstream;
	using std::vector;
	using std::shared_ptr;

	class Snake;
	class Fruit;
	class GameObject;
	class Wall;

	typedef shared_ptr<Snake> snake_ref;
	typedef shared_ptr<Fruit> fruit_ref;
	typedef shared_ptr<Wall> wall_ref;

	typedef shared_ptr<GameObject> game_object_ref;

	struct Game_Data
	{
		sf::RenderWindow window;
		snake_ref snake;
		fruit_ref fruit;
		wall_ref wall;
		//vector<game_object_ref> objects;
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
		bool m_pause = false;

		/* handle events */
		void handle();

		/* shift stats array */
		void add2stats(int points);

		/* display new map */
		void init_map(const std::string& fname);
	};
}