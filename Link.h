#pragma once

namespace Tmpl8 
{
	class Surface;

}


enum Direction
{
	LEFTMOVE,
	RIGHTMOVE,
	FORWARD,
	BACK
};

class Link
{
	public:
		Link(void);
		~Link(void);
		void Draw();
		void Update();
		void GetMap(map* Map);
		void SetTarget( Tmpl8::Surface* a_Surface ) { m_Screen = a_Surface; }
		bool CheckCollide(int x, int y, int oWidth, int oHeight, int xTwo, int yTwo, int oTwoWidth, int oTwoHeight);
		void ToggleSprites(Direction direction);
		void SpriteCycle();
		void CheckEdges();

		//Graphics / Sprites
		Tmpl8::Surface* m_Screen;
		Tmpl8::Surface* graphic;
		Tmpl8::Surface* current[7];
		Tmpl8::Surface* forward[7];
		Tmpl8::Surface* back[7];
		Tmpl8::Surface* right[7];
		Tmpl8::Surface* left[7];

		Tmpl8::Surface* swordforward[7];
		Tmpl8::Surface* swordback[7];
		Tmpl8::Surface* swordright[7];
		Tmpl8::Surface* swordleft[7];

		Tmpl8::Surface* heart;
		Tmpl8::Surface* halfHeart;
		Tmpl8::Surface* emptyHeart;
		Tmpl8::Surface* rupee;

		Weapon* weapons[3];

		int x;
		int y;
		int health;
		int maxHealth;
		int weaponsObtained;
		int rupees;
		bool hasSword;
		bool meleeAttack;
};

