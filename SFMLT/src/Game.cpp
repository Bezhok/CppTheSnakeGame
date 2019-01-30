#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>// sleep
#include <thread>// sleep
#include <algorithm>
#include <memory>
#include <string>
#include "Game.h"
#include "Snake.h"
#include "Fruit.h"
#include "Wall.h"
#include "GameMenu.h"

namespace Bezhok {
	using std::vector;
	using std::ios_base;
	using std::make_shared;
	using std::ifstream;
	using std::string;
	using std::to_string;
	using std::getline;

	Game::Game()
	{
		// add smart pointers
		m_data = make_shared<Game_Data>();
		m_data->wall = make_shared<Wall>(m_data);
		m_data->snake = make_shared<Snake>(m_data);
		m_data->fruit = make_shared<Fruit>(m_data);

		m_data->records = m_records;
		m_data->window.create(sf::VideoMode(WIDTH, HEIGTH), "Snake", sf::Style::Titlebar | sf::Style::Close);
		sf::Image icon;
		icon.loadFromFile("images/snake-icon.png");
		m_data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		m_menu = make_shared<GameMenu>(m_data);

		fstream records_file;
		records_file.open(m_fname, ios_base::binary | ios_base::in);
		if (records_file.is_open()) {
			records_file.read((char*)m_records, sizeof(m_records));
			records_file.close();
		}
	}

	Game::~Game()
	{
		fstream records_file;
		records_file.open(m_fname, ios_base::binary | ios_base::out | ios_base::trunc);
		if (records_file.is_open()) {
			records_file.write((char*)m_records, sizeof(m_records));
			records_file.close();
		}
		else {
			//error
		}
	}

	void Game::handle()
	{
		sf::Event e;
		while (m_data->window.pollEvent(e))
		{
			GameObject::direction dir = m_data->snake->get_direction();
			int num;
			switch (e.type)
			{
			// closed window
			case sf::Event::Closed:
				m_data->window.close();
				break;

			// mouse
			case sf::Event::TouchEnded:
			case sf::Event::MouseButtonPressed:
				num = m_menu->choosen_level();
				if (num >= 0) m_level_id = num + 1;
				m_menu->handle_input(e.key.code);
				break;

			// pressed key
			case sf::Event::KeyPressed:
				m_data->snake->handle_input(e.key.code);
				switch (e.key.code)
				{
				case sf::Keyboard::Space:
					e.key.code = sf::Keyboard::Unknown;
					m_data->pause = m_data->pause ? false : true;
					break;
				default:
					break;
				}
				break;

			default:
				break;
			}
		}
	}

	void Game::add2records(int points)
	{
		// shift array
		for (int i = 0; i < sizeof(m_records) / sizeof(int); ++i) {
			if (points > m_records[i]) {
				int temp = m_records[i];

				m_records[i] = m_data->snake->m_points;

				int prev = temp;
				int curr;
				for (int j = i + 1; j < sizeof(m_records) / sizeof(int); ++j) {
					curr = m_records[j];
					m_records[j] = prev;
					prev = curr;
				}
				break;
			}
		}
	}

	void Game::init_map(const string& fname)
	{
		vector<Wall::block> temp;

		// read level's map
		ifstream file(fname.c_str());
		if (file.is_open()) {
			string line;
			for (int y = 0; y < Game::BLOCKS_COUNT_Y && getline(file, line); ++y) {
				for (int i = 0, x = 0; x < Game::BLOCKS_COUNT_X && i < (int)line.size(); ++x, ++i) {
					if (line[i] == '0') {
						temp.push_back(Wall::block{ x,y });
					}
					else if (line[i] == '\t') {
						x += 3;
					}
				}
			}
			file.close();
			m_data->wall->init(temp);
		}
		else {
			//error
		}
	}

	void Game::run()
	{
		m_level_id = 1;
		int prev_level_id = m_level_id;

		string name = "levels/level1.txt"; // for example
		init_map(name);
		m_data->fruit->reset();
		m_data->pause = true;

		while (m_data->window.isOpen())
		{
			handle();

			// delay todo
			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			// logic starts
			bool life = true;
			if (!m_data->pause) {
				life = m_data->snake->update();
			}

			// new frame start
			m_data->window.clear(sf::Color::White);
			m_data->snake->draw();
			m_data->fruit->draw();
			m_data->wall->draw();

			if (m_data->pause) {
				
				m_menu->draw();

				// if chosed new level
				if (prev_level_id != m_level_id) {
					string name;
					name = "levels/level";
					name += to_string(m_level_id);
					name += ".txt";
					init_map(name);
					life = false;
				}
				prev_level_id = m_level_id;
			}

			if (!life) {
				add2records(m_data->snake->m_points);
				m_data->snake->reset();
				m_data->fruit->reset();

				m_data->pause = true;
			}

			m_data->window.display();
		}
	}
}