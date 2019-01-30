#include <ctime>
#include <algorithm>
#include "Wall.h"

namespace Bezhok {
	Wall::Wall(game_data_ref data)
		: GameObject(data)
	{
		m_texture.loadFromFile("images/white.png");
		m_sprite.setTexture(m_texture);
		auto size = m_sprite.getTexture()->getSize();
		m_sprite.setScale(float(Game::BLOCK_SIZE) / size.x, float(Game::BLOCK_SIZE) / size.y);
	}

	Wall::~Wall()
	{
	}

	void Wall::reset()
	{
		m_blocks.clear();
	}

	void Wall::init(vector<block>& coordinates)
	{
		m_blocks = coordinates;
	}

	void Wall::draw()
	{
		for (int i = 0; i < m_blocks.size(); ++i) {
			m_sprite.setPosition(Game::BLOCK_SIZE *m_blocks[i].x, Game::BLOCK_SIZE * m_blocks[i].y);
			m_data->window.draw(m_sprite);
		}
	}

	bool Wall::update()
	{
		return true;
	}
}

