// Template, major revision 3
// IGAD/NHTV - Jacco Bikker - 2006-2009

#include "string.h"
#include "surface.h"
#include "stdlib.h"
#include "template.h"
#include "game.h"
#include "map.h"
#include "Link.h"

map* Map = new map();
Link* link = new Link();
using namespace Tmpl8;


void Game::Init()
{
	Map->SetTarget(m_Screen);
	link->SetTarget(m_Screen);
	link->GetMap(Map);
}

void Game::Tick( float a_DT )
{
	Update();
}

void Game::Draw()
{
	Map->draw();
	link->Draw();
	link->Update();
	Map->Update();
	CollisionCheck();

	link->rupee->TransparentCopyTo(m_Screen, 480, 0);

	char text[300];
	sprintf(text, "%d", link->rupees);
    m_Screen->Print(text, 497 ,5,0xffffff);

	if(Map->currentTileSetRow == 3 && Map->currentTileSetColumn == 2)
	{
		Map->shopKeeper->TransparentCopyTo(m_Screen, Map->shopKeeperX, Map->shopKeeperY);

		if(Map->shopKeeperOpen)
		{
			Map->shopImage->CopyTo(m_Screen, 100, 100);
		}
	}
}

int Game::Update()
{
	for (int i = 0; i <10 ; i++) // force a repeat of the clear screen to slow things down
		m_Screen->Clear( 0 );  

	if(hitTimer >= 300)
		hitTimer == 300;

	hitTimer++;

	Draw();
	return 0;
};

void Game::CollisionCheck()
{
	if(Map->containsWeapon)
	{
		if(link->CheckCollide(link->x, link->y, link->graphic->GetWidth(), link->graphic->GetHeight(), Map->mapWeapon->x, Map->mapWeapon->y, Map->mapWeapon->graphic->GetWidth(), Map->mapWeapon->graphic->GetHeight()))
		{
			for(int i = 0; i <3; i++)
			{
				link->weapons[i]->active = false;
			}

			link->weapons[link->weaponsObtained] = Map->mapWeapon;
			link->weapons[link->weaponsObtained]->active = true;
			link->weaponsObtained++;
			if(Map->mapWeapon->weaponType == Map->mapWeapon->SWORD || Map->mapWeapon->weaponType == Map->mapWeapon->MASTERSWORD)
			{
				link->hasSword = true;
			}
			Map->containsWeapon = false;
			Map->mapWeapon = NULL;
		}
	}
	if(Map->containsEnemies)
	{
		for(int i = 0; i < 5; i++)
		{
			if(link->CheckCollide(link->x, link->y, link->graphic->GetWidth(), link->graphic->GetHeight(), Map->GetGuardX(i), Map->GetGuardY(i), Map->GetGuardWidth(i), Map->GetGuardHeight(i)))
			{
				Map->SetGuardSpeedOff(i);
				
				if(hitTimer >= 300)
				{
					hitTimer = 0;
					link->health -= 1;
				}

				if(link->hasSword)
				{
					if(GetAsyncKeyState(0x5A))
					{
						if(Map->IsGuardAlive(i))
						{
							link->meleeAttack = true;
							Map->RemoveGuard(i);
							link->rupees += 2;
						}	
					}
				}
			}
			else
			{
				Map->SetGuardSpeedOn(i);
			}
		}
	}
	if(Map->currentTileSetRow == 3 && Map->currentTileSetColumn == 2)
	{
		if(link->CheckCollide(link->x, link->y, link->graphic->GetWidth(), link->graphic->GetHeight(), Map->shopKeeperX, Map->shopKeeperY, Map->shopKeeper->GetWidth(), Map->shopKeeper->GetHeight()))
		{
			if(GetAsyncKeyState(0x5A))
			{
				Map->shopKeeperOpen = true;
			}
			if(Map->shopKeeperOpen)
			{
				if(link->rupees >= 20 && GetAsyncKeyState(0x48))
				{
					link->maxHealth += 2;
					link->rupees -= 20;
				}
			}
		}
		else
			Map->shopKeeperOpen = false;
	}
}
