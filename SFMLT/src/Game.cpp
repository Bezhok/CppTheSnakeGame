#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream> // test
#include <algorithm>
#include <memory>
#include "Game.h"
#include "Snake.h"
#include "Fruit.h"

namespace Bezhok {
	using std::vector;
	using std::ios_base;
	using std::shared_ptr;

	Game::Game()
	{
		m_data = std::make_shared<Game_Data>();

		m_data->window.create(sf::VideoMode(WIDTH, HEIGTH), "Snake");
	
		fstream stats_file;
		stats_file.open(m_fname, ios_base::binary | ios_base::in);
		if (stats_file.is_open()) {
			stats_file.read((char*)m_stats, sizeof(m_stats));
			stats_file.close();
		}
	}

	Game::~Game()
	{
		fstream stats_file;
		stats_file.open(m_fname, ios_base::binary | ios_base::out | ios_base::trunc);
		if (stats_file.is_open()) {
			stats_file.write((char*)m_stats, sizeof(m_stats));
			stats_file.close();
		}
		else {
			//error
		}
	}

	void Game::handle_input()
	{
		
	}

	void Game::run()
	{
		Snake m_snake(m_data);
		Fruit apple_o(m_data);

		bool is_pause = false;
		while (m_data->window.isOpen())
		{

			while (m_data->window.pollEvent(m_event))
			{
				switch (m_event.type)
				{
					// closed window
				case sf::Event::Closed:
					m_data->window.close();
					break;

					// pressed key
				case sf::Event::KeyPressed:
					switch (m_event.key.code)
					{
					case sf::Keyboard::Left:
						m_snake.set_direction(m_snake.direction::left);
						break;

					case sf::Keyboard::Right:
						m_snake.set_direction(m_snake.direction::right);
						break;

					case sf::Keyboard::Down:
						m_snake.set_direction(m_snake.direction::bottom);
						break;

					case sf::Keyboard::Up:
						m_snake.set_direction(m_snake.direction::top);
						break;

					case sf::Keyboard::Space:
						m_event.key.code = sf::Keyboard::Unknown;
						is_pause = is_pause ? false : true;
						break;
					default:
						break;
					}

					break;

				default:
					break;
				}

			}

			if (!is_pause) {
				// delay todo
				Sleep(100);

				// logic starts
				bool is_life = m_snake.update(apple_o);
							//m_apple.update();

				// new frame start
				m_data->window.clear(sf::Color::White);
				m_snake.draw();
				apple_o.draw();
				m_data->window.display();

				if (!is_life) {
					// shift array
					for (int i = 0; i < sizeof(m_stats) / sizeof(int);++i) {
						if (m_snake.m_points > m_stats[i]) {
							int temp = m_stats[i];

							m_stats[i] = m_snake.m_points;

							int prev = temp;
							int curr;
							for (int j = i+1; j < sizeof(m_stats) / sizeof(int); ++j) {
								curr = m_stats[j];
								m_stats[j] = prev;
								prev = curr;
							}
							break;
						}
					}
					//
					m_snake.init();
					apple_o.init();

					// todo stop, output stats
					for (int& x : m_stats) {
						std::cout << x << std::endl;
					}
					std::cout << "\n\n";
					is_pause = true;

				}
			}
		}
	}
}