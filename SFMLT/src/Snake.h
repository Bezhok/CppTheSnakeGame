#pragma once
#include <vector>
#include "GameObject.h"

namespace Bezhok {
	class Game;
	class Fruit;

	using std::vector;

	class Snake : public GameObject
	{
		struct snake_block {
			int x;
			int y;
		};

	public:
		/* init m_data and sprite with texture */
		Snake(game_data_ref m_data);

		/* set direction */
		void set_direction(direction dir);

		/* get direction */
		direction get_direction();

		/* get len */
		int len();

		/* set standart snake */
		virtual void init() override;

		/* draw */
		virtual void draw() override;

		/* move, check is died, try to eat fruit */
		virtual bool update() override;

		/* add neew item to snake */
		Snake& operator++();

		/* get item */
		snake_block& operator[](int i);

		int m_points;
	private:
		const int START_X = Game::BLOCKS_COUNT_X / 2;
		const int START_Y = Game::BLOCKS_COUNT_Y / 2;
		const direction START_DIRECTION = direction::top;

		direction m_cur_direction;
		vector<snake_block> m_items;
		snake_block m_previous;

		/* process movement */
		void move();
	};
}

