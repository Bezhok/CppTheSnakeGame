#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace Bezhok {
	class Game;
	class Snake;

	class Fruit: public GameObject
	{
	public:
		int m_x, m_y;

		/* init m_data and sprite with texture */
		Fruit(game_data_ref m_data);

		/* get points of this fruit */
		int get_points();

		/* set standart fruit */
		virtual void init() override;

		/* todo */
		virtual bool update() override { return true; };

		/* try to spawn not on another object */
		void spawn();

		/* draw */
		virtual void draw() override;
	private:
		const int m_points = 10;
	};
}

