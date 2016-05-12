#include "surface.h"
#include "Guard.h"
#include "template.h"
#include "game.h"
#include "map.h"
#include "SDL.h"
#include "SDL_syswm.h"

using namespace Tmpl8;

Guard::Guard(void)
{
	forward[0] = new Surface("assets/guard/guard_forward1.png");
	forward[1] = new Surface("assets/guard/guard_forward2.png");

	back[0] = new Surface("assets/guard/guard_down1.png");
	back[1] = new Surface("assets/guard/guard_down2.png");
	
	left[0] = new Surface("assets/guard/guard_left1.png");
	left[1] = new Surface("assets/guard/guard_left2.png");

	right[0] = new Surface("assets/guard/guard_right1.png");
	right[1] = new Surface("assets/guard/guard_right2.png");

	for(int i = 0; i < 2; i++)
	{
		current[i] = left[i];
	}

	graphic = current[0];
	
	movementSpeed = 1;
	prevSpeed = 1;
	currentSprite = 0;
	spriteCounter = 0;
	alive = true;
}

void Guard::Draw(Surface* m_Screen)
{
	graphic->TransparentCopyTo(m_Screen, x, y);
}

void Guard::Update()
{
	Movement();
}

void Guard::Movement()
{
	lastX = x;
	lastY = y;

	x += movementSpeed;
	spriteCounter++;

	if(mapReference->CheckSolids(x, lastY))
	{
		x = lastX;
		movementSpeed = movementSpeed* -1;
		prevSpeed = movementSpeed;

		if(movementSpeed == 1)
			ToggleSprites(RIGHTMOVE);
		else
			ToggleSprites(LEFTMOVE);
	}

	SpriteCycle();
}

void Guard::SpriteCycle()
{
	if(spriteCounter >= 10)
	{
		graphic = current[currentSprite];
		currentSprite++;

		if(currentSprite == 2)
		{
			currentSprite = 0;		
		}
		spriteCounter = 0;
	}
}

void Guard::ToggleSprites(Direction direction)
{
	switch(direction)
	{
		case LEFTMOVE:
			for(int i = 0; i < 2; i++)
			{
				current[i] = left[i];
			}
			break;
		case RIGHTMOVE:
			for(int i = 0; i < 2; i++)
			{
				current[i] = right[i];
			}
			break;
		case FORWARD:
			for(int i = 0; i < 2; i++)
			{
				current[i] = forward[i];
			}
			break;
		case BACK:
			for(int i = 0; i < 2; i++)
			{
				current[i] = back[i];
			}
			break;
	}
}

void Guard::GetMap(map* Map)
{
	mapReference = Map;
}

void Guard::SetPos(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
}

Guard::~Guard(void)
{
}
