#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace Bezhok {
	class Game;

	class GameObject
	{
	public:
		enum direction {
			top, bottom, left, right
		};

		/* init data */
		GameObject(game_data_ref m_data);

		virtual void draw() = 0;
		virtual void init() = 0;
		virtual bool update() = 0;
	protected:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		game_data_ref m_data;
	};
}