#include <ctime>
#include <algorithm>
#include "Fruit.h"
#include "Game.h"
#include "Snake.h"
#include "Wall.h"

namespace Bezhok {
	Fruit::Fruit(game_data_ref data)
		: GameObject(data)
	{
		m_texture.loadFromFile("images/red.png");
		m_sprite.setTexture(m_texture);
		auto size = m_sprite.getTexture()->getSize();
		m_sprite.setScale(float(Game::BLOCK_SIZE) / size.x, float(Game::BLOCK_SIZE) / size.y);

		reset();
	}

	int Fruit::get_points()
	{
		return m_points;
	}

	void Fruit::reset()
	{
		srand(static_cast<unsigned int>(time(0)));

		// spawn if only this place is free
		bool is_free_space;
		do {
			is_free_space = true;
			m_x = rand() % Game::BLOCKS_COUNT_X;
			m_y = rand() % Game::BLOCKS_COUNT_Y;

			// respawn if it has spawned on the snake or wall
			for (int i = 0; i < m_data->snake->len(); ++i) {
				if (m_data->snake->operator[](i).y == m_y && m_data->snake->operator[](i).x == m_x) {
					is_free_space = false;
					break;
				}
			}
			for (int i = 0; i < (int)m_data->wall->get_blocks().size(); ++i) {
				if (m_data->wall->get_blocks()[i].y == m_y && m_data->wall->get_blocks()[i].x == m_x) {
					is_free_space = false;
					break;
				}
			}

		} while (!is_free_space);
	}

	void Fruit::draw()
	{
		m_sprite.setPosition(float(Game::BLOCK_SIZE * m_x), float(Game::BLOCK_SIZE * m_y));
		m_data->window.draw(m_sprite);
	}
}