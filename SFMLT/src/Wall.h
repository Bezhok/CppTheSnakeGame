#pragma once
#include "GameObject.h"
#include <vector>

namespace Bezhok {
	using std::vector;

	class Wall : public GameObject
	{
	public:
		struct block {
			int x;
			int y;
		};

		Wall(game_data_ref data);
		~Wall();

		/* set standart wall */
		virtual void reset();

		/* generate wall */
		void init(vector<block>& coordinates);

		/* draw */
		virtual void draw() override;

		virtual bool update() override;

		vector<block>& get_coordinates()
		{
			return m_coordinates;
		}
		vector<block> m_coordinates;
	private:
		
	};
}


