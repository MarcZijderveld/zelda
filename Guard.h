#pragma once
#include "map.h"
#include "Link.h"

namespace Tmpl8 
{
	class Surface;
}
class Guard
{

	public:
		Tmpl8::Surface* graphic;
		Tmpl8::Surface* forward[2];
		Tmpl8::Surface* back[2];
		Tmpl8::Surface* right[2];
		Tmpl8::Surface* left[2];
		Tmpl8::Surface* current[2];

		int x;
		int y;
		int movementSpeed;
		int health;
		map* mapReference;
		int lastX;
		int	lastY;
		int currentSprite;
		int spriteCounter;
		int prevSpeed;
		bool alive;

		void Draw(Tmpl8::Surface* m_Screen);
		void Update();
		void Movement();
		void SetPos(int x, int y);
		void GetMap(map* Map);
		void SpriteCycle();
		void ToggleSprites(Direction direction);

		Guard(void);
		~Guard(void);
};

