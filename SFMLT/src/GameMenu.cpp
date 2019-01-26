#include "SFML/Graphics.hpp"
#include "GameMenu.h"
#include "Wall.h"
#include <istream>
#include <string>
#include <iostream>//test
namespace Bezhok {
	using std::ifstream;
	using std::string;
	using std::getline;
	using std::vector;
	using std::to_string;

	GameMenu::GameMenu(game_data_ref data)
		: m_data {data}
	{
		int levels_count = 5;
		for (int i = 0; i < levels_count; ++i) {
			sf::RectangleShape level_box;
			level_box.setSize(sf::Vector2f(30, 30));
			level_box.setFillColor(sf::Color(0, 0, 0));
			level_box.setPosition(i*Game::BLOCK_SIZE * 3 + 5, Game::BLOCK_SIZE * 3 + 5);
			m_levels.push_back(level_box);
		}

		m_play_b_texture.loadFromFile("images/play-button.png");
		m_play_b.setTexture(m_play_b_texture);
		m_play_b.setScale(0.1f, 0.1f);
		m_play_b.setPosition((Game::WIDTH / 2) - m_play_b_texture.getSize().x * 0.05,
			(Game::HEIGTH / 2) - m_play_b_texture.getSize().y * 0.05);
	}

	GameMenu::~GameMenu()
	{
	}

	void GameMenu::draw()
	{
		sf::RectangleShape background;
		background.setSize(sf::Vector2f(Game::WIDTH, Game::HEIGTH));
		background.setFillColor(sf::Color(51, 51, 55, 150));
		m_data->window.draw(background);

		sf::Text text;
		sf::Font font;
		font.loadFromFile("arial.ttf");
		text.setFont(font);

		if (m_state == MenuState::main) {
			text.setString("Levels You can choose any");
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::Black);
			m_data->window.draw(text);

			m_data->window.draw(m_play_b);

			// levels icons
			for (int i = 0; i < m_levels.size(); ++i) {
				// level num
				sf::Text text;
				sf::Font font;
				font.loadFromFile("arial.ttf");
				text.setFont(font);
				text.setString(to_string(i + 1).c_str());
				text.setCharacterSize(24);
				text.setFillColor(sf::Color::White);

				// set center position
				text.setPosition(
					m_levels[i].getPosition() +
					sf::Vector2f(m_levels[i].getSize().x / 4, m_levels[i].getSize().y / 32)
				);

				m_data->window.draw(m_levels[i]);
				m_data->window.draw(text);
			}

			m_data->window.draw(m_play_b);

			// stats button
			m_stats_b.setSize(sf::Vector2f(120, 40));
			m_stats_b.setFillColor(sf::Color(0, 0, 0));
			m_stats_b.setPosition(5, Game::HEIGTH - m_stats_b.getSize().y - 5);
			m_data->window.draw(m_stats_b);

			text.setString("Records");
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::White);
			text.setPosition(
				m_stats_b.getPosition() +
				sf::Vector2f(m_stats_b.getSize().x / 8, m_stats_b.getSize().y / 16)
			);
			m_data->window.draw(text);

		}
		else if (m_state == MenuState::statistics) {

			// stats button
			m_stats_b.setSize(sf::Vector2f(120, 40));
			m_stats_b.setFillColor(sf::Color(0, 0, 0));
			m_stats_b.setPosition(5, Game::HEIGTH - m_stats_b.getSize().y - 5);
			m_data->window.draw(m_stats_b);

			text.setString("Back");
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::White);
			text.setPosition(
				m_stats_b.getPosition() +
				sf::Vector2f(m_stats_b.getSize().x / 4, m_stats_b.getSize().y / 16)
			);
			m_data->window.draw(text);

			// output stats
			for (int i = 0; i < Game::STATS_COUNT; ++i) {
				sf::Text text;
				sf::Font font;
				font.loadFromFile("arial.ttf");
				text.setFont(font);
				text.setString(to_string(m_data->stats[i]).c_str());
				text.setCharacterSize(24);
				text.setFillColor(sf::Color::Black);
				text.setPosition(Game::WIDTH/2 - Game::BLOCK_SIZE, i*Game::BLOCK_SIZE * 2);

				m_data->window.draw(text);
			}
		}
	}

	void GameMenu::handle_input()
	{
		// switch to statistics
		if (m_stats_b.getGlobalBounds().contains(
			sf::Mouse::getPosition(m_data->window).x,
			sf::Mouse::getPosition(m_data->window).y) &&
			m_state == MenuState::main
			) {
			m_state = MenuState::statistics;
		}
		else if (m_stats_b.getGlobalBounds().contains(
			sf::Mouse::getPosition(m_data->window).x,
			sf::Mouse::getPosition(m_data->window).y) &&
			m_state == MenuState::statistics
			) {
			m_state = MenuState::main;
		}
		else if (m_play_b.getGlobalBounds().contains(
			sf::Mouse::getPosition(m_data->window).x,
			sf::Mouse::getPosition(m_data->window).y)
		) {
			m_data->pause = false;
		}
	}

	int GameMenu::choosen_level()
	{
		for (int i = 0; i < m_levels.size(); ++i) {
			if (m_levels[i].getGlobalBounds().contains(
				sf::Mouse::getPosition(m_data->window).x,
				sf::Mouse::getPosition(m_data->window).y)
				) {
				return i;
			}
		}

		// if not clicking
		return -1;
	}
}
