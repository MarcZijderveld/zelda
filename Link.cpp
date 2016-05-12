#include "template.h"
#include "surface.h"
#include "game.h"
#include "map.h"
#include "Link.h"
#include "SDL.h"
#include "SDL_syswm.h"

using namespace Tmpl8;

int movementSpeed = 1;
map* mapReference;

int lastX = 0,
	lastY = 0,
	spriteCounter = 0,
	currentSprite = 0;

Link::Link(void)
{
	//forward sprites
	forward[0] = new Surface("assets/link/link_forward1.png");
	forward[1] = new Surface("assets/link/link_forward2.png");
	forward[2] = new Surface("assets/link/link_forward3.png");
	forward[3] = new Surface("assets/link/link_forward4.png");
	forward[4] = new Surface("assets/link/link_forward5.png");
	forward[5] = new Surface("assets/link/link_forward6.png");
	forward[6] = new Surface("assets/link/link_forward7.png");

	//sword forward sprites
	swordforward[0] = new Surface("assets/link/link_swordforward1.png");
	swordforward[1] = new Surface("assets/link/link_swordforward2.png");
	swordforward[2] = new Surface("assets/link/link_swordforward3.png");
	swordforward[3] = new Surface("assets/link/link_swordforward4.png");
	swordforward[4] = new Surface("assets/link/link_swordforward5.png");
	swordforward[5] = new Surface("assets/link/link_swordforward6.png");

	//back sprites
	back[0] = new Surface("assets/link/link_down1.png");
	back[1] = new Surface("assets/link/link_down2.png");
	back[2] = new Surface("assets/link/link_down3.png");
	back[3] = new Surface("assets/link/link_down4.png");
	back[4] = new Surface("assets/link/link_down5.png");
	back[5] = new Surface("assets/link/link_down6.png");
	back[6] = new Surface("assets/link/link_down7.png");

	//sword back sprites
	swordback[0] = new Surface("assets/link/link_downsword1.png");
	swordback[1] = new Surface("assets/link/link_downsword2.png");
	swordback[2] = new Surface("assets/link/link_downsword3.png");
	swordback[3] = new Surface("assets/link/link_downsword4.png");
	swordback[4] = new Surface("assets/link/link_downsword5.png");
	swordback[5] = new Surface("assets/link/link_downsword6.png");

	//left sprites
	left[0] = new Surface("assets/link/link_left1.png");
	left[1] = new Surface("assets/link/link_left2.png");
	left[2] = new Surface("assets/link/link_left3.png");
	left[3] = new Surface("assets/link/link_left4.png");
	left[4] = new Surface("assets/link/link_left5.png");
	left[5] = new Surface("assets/link/link_left6.png");
	left[6] = new Surface("assets/link/link_left7.png");

	//sword left sprites
	swordleft[0] = new Surface("assets/link/link_swordleft1.png");
	swordleft[1] = new Surface("assets/link/link_swordleft2.png");
	swordleft[2] = new Surface("assets/link/link_swordleft3.png");
	swordleft[3] = new Surface("assets/link/link_swordleft4.png");
	swordleft[4] = new Surface("assets/link/link_swordleft5.png");
	swordleft[5] = new Surface("assets/link/link_swordleft6.png");

	//right sprites
	right[0] = new Surface("assets/link/link_right1.png");
	right[1] = new Surface("assets/link/link_right2.png");
	right[2] = new Surface("assets/link/link_right3.png");
	right[3] = new Surface("assets/link/link_right4.png");
	right[4] = new Surface("assets/link/link_right5.png");
	right[5] = new Surface("assets/link/link_right6.png");
	right[6] = new Surface("assets/link/link_right7.png");

	//sword right sprites
	swordright[0] = new Surface("assets/link/link_swordright1.png");
	swordright[1] = new Surface("assets/link/link_swordright2.png");
	swordright[2] = new Surface("assets/link/link_swordright3.png");
	swordright[3] = new Surface("assets/link/link_swordright4.png");
	swordright[4] = new Surface("assets/link/link_swordright5.png");
	swordright[5] = new Surface("assets/link/link_swordright6.png");

	heart = new Surface("assets/link/link_heart.png");
	halfHeart = new Surface("assets/link/link_halfheart.png");
	emptyHeart = new Surface("assets/link/link_emptyheart.png");
	rupee = new Surface("assets/link/rupee.png");

	//start position
	x = 185;
	y = 255;
	health = 8;
	maxHealth = 8;
	weaponsObtained = 0;
	rupees = 0;
	hasSword = false;
	meleeAttack = false;

	for(int i = 0; i < 7; i++)
	{
		current[i] = back[i];
	}
	graphic = current[0];

	weapons[0] = new Weapon();
	weapons[0]->active = false;
	weapons[1] = new Weapon();
	weapons[1]->active = false;
	weapons[2] = new Weapon();
	weapons[2]->active = false;
}

void Link::GetMap(map* Map)
{
	mapReference = Map;
}

void Link::Draw()
{
	graphic->TransparentCopyTo(m_Screen, x, y);

	for(int i = 0; i < 3; i++)
	{
		if(weaponsObtained > 0)
		{
			if(weapons[i]->active)
			{
				weapons[i]->graphic->TransparentCopyTo(m_Screen, 70, 3);
			}
		}
	}

	for(int i = 0; i < maxHealth; i += 2)
	{
		if(health - i >= 2)
		{
			heart->TransparentCopyTo(m_Screen,i* 8,2);
		}
		else if(health - i == 1)
		{
			halfHeart->TransparentCopyTo(m_Screen,i* 8,2);
		}
		else
			emptyHeart->TransparentCopyTo(m_Screen,i* 8,2);
	}
}

Direction lastDirection;

void Link::ToggleSprites(Direction direction)
{
	lastDirection = direction;

	switch(direction)
	{
		case LEFTMOVE:
			
			if(meleeAttack)
			{
				for(int i = 0; i < 6; i++)
				{
					current[i] = swordleft[i];
				}
			}
			else
			{
				for(int i = 0; i < 7; i++)
				{
					current[i] = left[i];
				}
			}
			break;
		case RIGHTMOVE:
			if(meleeAttack)
			{
				for(int i = 0; i < 6; i++)
				{
					current[i] = swordright[i];
				}
			}
			else
			{
				for(int i = 0; i < 7; i++)
				{
					current[i] = right[i];
				}
			}
			break;
		case FORWARD:
			if(meleeAttack)
			{
				for(int i = 0; i < 6; i++)
				{
					current[i] = swordforward[i];
				}
			}
			else
			{
				for(int i = 0; i < 7; i++)
				{
					current[i] = forward[i];
				}
			}
			break;
		case BACK:
			if(meleeAttack)
			{
				for(int i = 0; i < 6; i++)
				{
					current[i] = swordback[i];
				}
			}
			else
			{
				for(int i = 0; i < 7; i++)
				{
					current[i] = back[i];
				}
			}
			break;
	}
}

void Link::SpriteCycle()
{
	if(spriteCounter >= 5)
	{
		currentSprite++;
		graphic = current[currentSprite];

		if(meleeAttack)
		{
			if(currentSprite == 5)
			{
				currentSprite = 0;		
				meleeAttack = false;
			}
		}
		else
		{
			if(currentSprite == 6)
			{
				currentSprite = 0;		
			}
		}

		spriteCounter = 0;
	}
}

void Link::Update()
{
	if(meleeAttack)
	{
		ToggleSprites(lastDirection);
		spriteCounter++;
	}

	lastX = x;
	lastY = y;

	if(!meleeAttack)
	{
		if(GetAsyncKeyState(0x31))
		{
			if(weapons[0]->weaponType == weapons[0]->SWORD)
			{
				weapons[0]->active = true;
			}
			if(weapons[1]->weaponType == weapons[1]->MASTERSWORD)
			{
				weapons[1]->active = false;
			}
			if(weapons[2]->weaponType == weapons[2]->BOOTS)
			{
				weapons[2]->active = false;
			}
		}
		if(GetAsyncKeyState(0x32))
		{
			if(weapons[0]->weaponType == weapons[0]->SWORD)
			{
				weapons[0]->active = false;
			}
			if(weapons[1]->weaponType == weapons[1]->MASTERSWORD)
			{
				weapons[1]->active = true;
			}
			if(weapons[2]->weaponType == weapons[2]->BOOTS)
			{
				weapons[2]->active = false;
			}
		}
		if(GetAsyncKeyState(0x33))
		{
			if(weapons[0]->weaponType == weapons[0]->SWORD)
			{
				weapons[0]->active = false;
			}
			if(weapons[1]->weaponType == weapons[1]->MASTERSWORD)
			{
				weapons[1]->active = false;
			}
			if(weapons[2]->weaponType == weapons[2]->BOOTS)
			{
				weapons[2]->active = true;
			}
		}

		//-----Controls are WSDA
		//Up
		if(GetAsyncKeyState(0x57))	
		{
			spriteCounter++;
			y -= movementSpeed;
			ToggleSprites(FORWARD);
		}
		//Down
		else if(GetAsyncKeyState(0x53))
		{
			spriteCounter++;
			y += movementSpeed;
			ToggleSprites(BACK);
		}
		//Left
		else if(GetAsyncKeyState(0x41))
		{
			spriteCounter++;
			x -= movementSpeed;
			ToggleSprites(LEFTMOVE);
		}
		//Right
		else if(GetAsyncKeyState(0x44))
		{
			spriteCounter++;
			x += movementSpeed;
			ToggleSprites(RIGHTMOVE);
		}
		else
		{
			currentSprite = 0;
			graphic = current[currentSprite];
		}
	}
	//Check for the solid data on the Yaxis
	if(mapReference->CheckSolids(lastX, y))
	{
		y = lastY;
	}

	//Check for the solid data on the Xaxis
	if(mapReference->CheckSolids(x, lastY))
	{
		x = lastX;
	}

	SpriteCycle();
	CheckEdges();


	for(int i = 0; i < 3; i++)
	{

		if(weapons[i]->weaponType == weapons[i]->BOOTS && GetAsyncKeyState(0x51))
		{
			movementSpeed = 1000;
		}
		else
			movementSpeed = 1;
	}
}

void Link::CheckEdges()
{
	if(x <= 5)
	{
		mapReference->SetNextTileSet(0, -1);
		x = 490;
	}
	if(x >= 495)
	{
		mapReference->SetNextTileSet(0, 1);
		x = 10;
	}
	if(y >= 495)
	{
		mapReference->SetNextTileSet(1, 0);
		y = 10;
	}
	if(y <= 5)
	{
		mapReference->SetNextTileSet(-1, 0);
		y = 490;
	}
}


Link::~Link(void)
{
}
