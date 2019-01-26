#include <ctime>
#include <algorithm>
#include "Wall.h"

namespace Bezhok {
	Wall::Wall(game_data_ref data)
		: GameObject(data)
	{
		m_texture.loadFromFile("images/white.png");
		m_sprite.setTexture(m_texture);
	}

	Wall::~Wall()
	{
	}

	void Wall::reset()
	{
		//srand(static_cast<unsigned int>(time(0)));

		//m_coordinates.clear();
		//for (int i = 0; i < 5; ++i) {
		//	int x = rand() % Game::BLOCKS_COUNT_X;
		//	int y = rand() % Game::BLOCKS_COUNT_Y;
		//	m_coordinates.push_back(block{x, y});
		//}
	}

	void Wall::init(vector<block>& coordinates)
	{
		m_coordinates = coordinates;
	}

	void Wall::draw()
	{
		for (int i = 0; i < m_coordinates.size(); ++i) {
			m_sprite.setPosition(Game::BLOCK_SIZE *m_coordinates[i].x, Game::BLOCK_SIZE * m_coordinates[i].y);
			m_data->window.draw(m_sprite);
		}
	}

	bool Wall::update()
	{
		return true;
	}
}

