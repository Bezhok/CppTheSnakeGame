#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>
#include <string>

namespace Bezhok {
	using std::fstream;
	using std::shared_ptr;

	class Snake;
	class Fruit;
	class GameObject;
	class Wall;
	class GameMenu;

	typedef shared_ptr<Snake> snake_ref;
	typedef shared_ptr<Fruit> fruit_ref;
	typedef shared_ptr<Wall> wall_ref;
	typedef shared_ptr<GameMenu> menu_ref;

	typedef shared_ptr<GameObject> game_object_ref;

	struct Game_Data
	{
		sf::RenderWindow window;
		snake_ref snake;
		fruit_ref fruit;
		wall_ref wall;
		int* records;
		bool pause = false;
	};

	typedef shared_ptr<Game_Data> game_data_ref;

	class Game
	{
	public:
		static const int BLOCK_SIZE = 20;
		static const int BLOCKS_COUNT_X = 30;
		static const int BLOCKS_COUNT_Y = 20;
		static const int WIDTH = BLOCK_SIZE * BLOCKS_COUNT_X;
		static const int HEIGTH = BLOCK_SIZE * BLOCKS_COUNT_Y;
		static const int RECORDS_COUNT = 10;
		/* read records, create m_data */
		Game();

		/* write records */
		~Game();

		/* game cycle */
		void run();
	private:
		int m_records[RECORDS_COUNT] = { 0 };
		const char m_fname[12] = "records.dat";
		game_data_ref m_data;
		int m_level_id;
		menu_ref m_menu;

		/* handle events */
		void handle();

		/* shift records array */
		void add2records(int points);

		/* display new map */
		void init_map(const std::string& fname);
	};
}