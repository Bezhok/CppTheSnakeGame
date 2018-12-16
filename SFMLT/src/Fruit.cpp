#include "Fruit.h"
#include <ctime>
#include <algorithm>

namespace Bezhok {
	Fruit::Fruit(game_data_ref data)
		: GameObject(data)
	{
		m_texture.loadFromFile("images/red.png");
		m_sprite.setTexture(m_texture);

		init();
	}

	int Fruit::get_points()
	{
		return m_points;
	}

	void Fruit::init()
	{
		srand(static_cast<unsigned int>(time(0)));
		m_x = rand() % Game::BLOCKS_COUNT_X;
		m_y = rand() % Game::BLOCKS_COUNT_Y;
	}

	void Fruit::spawn(Snake& snake)
	{
		srand(static_cast<unsigned int>(time(0)));

		// spawn if only this place is free
		bool is_free_space;
		do {
			is_free_space = true;
			m_x = rand() % Game::BLOCKS_COUNT_X;
			m_y = rand() % Game::BLOCKS_COUNT_Y;

			// respawn if it has spawned on the snake
			for (int i = 0; i < snake.len(); ++i) {
				if (snake[i].y == m_y && snake[i].x == m_x) {
					is_free_space = false;
					break;
				}
			}
		} while (!is_free_space);
	}

	void Fruit::draw()
	{
		m_sprite.setPosition(Game::BLOCK_SIZE * m_x, Game::BLOCK_SIZE * m_y);
		m_data->window.draw(m_sprite);
	}
}