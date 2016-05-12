#pragma once
#include "Weapon.h"

namespace Tmpl8 
{

class Surface;

}
class map
{
	
public:
	map(void);
	void loadLevel(void);
	void draw(void);
	void SetTarget( Tmpl8::Surface* a_Surface ) { m_Screen = a_Surface; }
	bool IsSolid(int x, int y);
	void LoadNextTileSet();
	void SetNextTileSet(int rowOffset, int columnOffset);
	void SpawnEnemies();
	void SpawnWeapons();
	void Update();
	bool CheckSolids(int charX, int charY);
	char* combineChar(int index);
	int GetGuardX(int i);
	int GetGuardY(int i);
	int GetGuardWidth(int i);
	int GetGuardHeight(int i);
	void SetGuardSpeedOff(int index);
	void SetGuardSpeedOn(int index);
	bool IsGuardAlive(int index);
	void RemoveGuard(int index);
	bool containsWeapon,
         containsEnemies;

	Weapon* mapWeapon;
	Tmpl8::Surface* shopKeeper;
	Tmpl8::Surface* shopImage;

	int shopKeeperX;
	int shopKeeperY;
	bool shopKeeperOpen;

	int currentTileSetRow;
	int currentTileSetColumn;

	~map(void);
private:
	
	Tmpl8::Surface* m_Screen;
};

