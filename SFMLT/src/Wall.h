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

		/* delete all peaces */
		virtual void reset() override;

		/* generate wall */
		void init(vector<block>& coordinates);

		/* draw */
		virtual void draw() override;

		/*  update (do nothing) */
		virtual bool update() override;

		vector<block>& get_blocks()
		{
			return m_blocks;
		}
	private:
		vector<block> m_blocks;
	};
}


