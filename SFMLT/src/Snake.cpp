#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "Wall.h"

namespace Bezhok {
	Snake::Snake(game_data_ref data)
		: GameObject(data)
	{
		m_texture.loadFromFile("images/green.png");
		m_sprite.setTexture(m_texture);
		auto size = m_sprite.getTexture()->getSize();
		m_sprite.setScale(float(Game::BLOCK_SIZE) / size.x, float(Game::BLOCK_SIZE) / size.y);

		reset();
	}

	void Snake::reset()
	{
		// clear snake
		m_points = 0;
		m_items.clear();
		m_cur_direction = START_DIRECTION;
		m_items.push_back(snake_block{ START_X, START_Y });
	}

	void Snake::draw()
	{
		// window.draw every sequence
		for (unsigned int i = 0; i < m_items.size(); ++i) {
			m_sprite.setPosition(float(Game::BLOCK_SIZE * m_items[i].x), float(Game::BLOCK_SIZE * m_items[i].y));
			m_data->window.draw(m_sprite);
		}
	}

	bool Snake::update()
	{
		move();

		// if head on body
		for (unsigned int i = 1; i < m_items.size(); ++i) {
			if (m_items[i].y == m_items[0].y && m_items[i].x == m_items[0].x) {
				return false;
			}
		}

		// if head on block
		for (int i = 0; i < int(m_data->wall->get_blocks().size()); ++i) {
			if (m_data->wall->get_blocks()[i].y == m_items[0].y && m_data->wall->get_blocks()[i].x == m_items[0].x) {
				return false;
			}
		}

		// if snake head on apple
		if (m_items[0].y == m_data->fruit->m_y && m_items[0].x == m_data->fruit->m_x) {
			m_data->fruit->reset();
			++(*this);
			m_points += m_data->fruit->get_points();
		}

		return true;
	}

	void Snake::move()
	{
		snake_block head = m_items[0];
		m_previous = m_items.back();

		switch (m_cur_direction)
		{
		case direction::top:
			--head.y;
			break;
		case direction::bottom:
			++head.y;
			break;
		case direction::left:
			--head.x;
			break;
		case direction::right:
			++head.x;
			break;
		default:
			break;
		}

		// if off the border
		if (head.x < 0) head.x = Game::BLOCKS_COUNT_X;
		else head.x %= Game::BLOCKS_COUNT_X;

		if (head.y < 0) head.y = Game::BLOCKS_COUNT_Y;
		else head.y %= Game::BLOCKS_COUNT_Y;

		// shift vector
		m_items.insert(m_items.begin(), head);
		m_items.pop_back();
	}

	void Snake::set_direction(direction dir)
	{
		m_cur_direction = dir;
	}

	Snake::direction Snake::get_direction()
	{
		return m_cur_direction;
	}

	int Snake::len()
	{
		return m_items.size();
	}

	Snake& Snake::operator++()
	{
		m_items.push_back(snake_block{m_previous.x, m_previous.y});
		return *this;
	}

	Snake::snake_block& Snake::operator[](int i)
	{
		return m_items[i];
	}

	void Snake::handle_input(sf::Keyboard::Key key)
	{
		switch (key) //TODO touch
		{
		case sf::Keyboard::A:
		case sf::Keyboard::Left:
			//can not move forward or back
			if (m_cur_direction == GameObject::direction::top || m_cur_direction == GameObject::direction::bottom)
				set_direction(GameObject::direction::left);
			break;

		case sf::Keyboard::D:
		case sf::Keyboard::Right:
			if (m_cur_direction == GameObject::direction::top || m_cur_direction == GameObject::direction::bottom)
				set_direction(GameObject::direction::right);
			break;

		case sf::Keyboard::S:
		case sf::Keyboard::Down:
			if (m_cur_direction == GameObject::direction::left || m_cur_direction == GameObject::direction::right)
				set_direction(GameObject::direction::bottom);
			break;

		case sf::Keyboard::W:
		case sf::Keyboard::Up:
			if (m_cur_direction == GameObject::direction::left || m_cur_direction == GameObject::direction::right)
				set_direction(GameObject::direction::top);
			break;

		default:
			break;
		}
	}
}
