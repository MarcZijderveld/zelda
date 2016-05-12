#include "map.h"
#include "Link.h"
#include "Guard.h"
#include <fstream>
#include "template.h"
#include "string.h"
#include "surface.h"
#include "Weapon.h"
#include "game.h"
#include "FreeImage.h"

#include <sstream>

using namespace std;
using namespace Tmpl8;

int tilesize = 8;
int imageSize = 512;
int tilesPerRow = 64;

int uniqueTiles = 1;

int levelArray[64][64];
int solidDataArray[512];
int enemyDataArray[64][64];
int dropDataArray[64][64];
int enemyCount = 0;

Tmpl8::Surface* tiles[512];

Guard* guards[5];

map::map(void)
{
	currentTileSetRow = 3;
	currentTileSetColumn = 2;

	shopKeeper = new Surface("assets/shopKeeper.png");
	shopImage = new Surface("assets/shopKeeperImage.png");

	shopKeeperX = 10;
	shopKeeperY = 260;

	shopKeeperOpen = false;

	map::loadLevel();
}

void map::loadLevel(void)
{
	LoadNextTileSet();
}

void map::LoadNextTileSet()
{
	containsWeapon = false;
	containsEnemies = false;
	enemyCount = 0;

	for(int i = 0; i < 512 ; i++)
	{
		solidDataArray[i] = 0;
	}

	for (int row = 0; row < tilesPerRow; row++)
	{
		for (int column = 0; column < tilesPerRow; column++)
		{
			enemyDataArray[row][column] = 0;
			dropDataArray[row][column] = 0;
		}
	}

	for(int i = 0; i < 5; i++)
	{
		if(guards[i] != NULL)
		{
			delete guards[i];
			guards[i] = NULL;
		}
	}

	std::ifstream inBinFile; 
	string link = "";
	link += "assets/tileset";
	link += to_string((long long)currentTileSetRow);
	link += to_string((long long)currentTileSetColumn);
	link += "/LEVELDATA.BIN";
	inBinFile.open(link, ios::in | ios::binary);

	for (int row = 0; row < tilesPerRow; row++)
	{
		for (int column = 0; column < tilesPerRow; column++)
		{
			inBinFile.read (reinterpret_cast<char*> (&levelArray[row][column]), sizeof(int));
		}
	} 
	inBinFile.close();

	std::ifstream tilesBinFile; 
	link = "";
	link += "assets/tileset";
	link += to_string((long long)currentTileSetRow);
	link += to_string((long long)currentTileSetColumn);
	link +=  "/TILES.BIN";
	tilesBinFile.open(link, ios::in | ios::binary);
	tilesBinFile.read (reinterpret_cast<char*> (&uniqueTiles), sizeof(int));
	tilesBinFile.close();

	for(int i = 0; i < uniqueTiles ; i++)
	{
		tiles[i] = new Tmpl8::Surface(combineChar(i));
	}

	std::ifstream solidDataBin; 
	link = "";
	link += "assets/tileset";
	link += to_string((long long)currentTileSetRow);
	link += to_string((long long)currentTileSetColumn);
	link +=  "/SOLIDDATA.BIN";
	solidDataBin.open(link, ios::in | ios::binary);
	for(int i = 0; i < uniqueTiles ; i++)
	{
		solidDataBin.read (reinterpret_cast<char*> (&solidDataArray[i]), sizeof(int));
	}

	solidDataBin.close();

	std::ifstream enemyDataBin; 
	link = "";
	link += "assets/tileset";
	link += to_string((long long)currentTileSetRow);
	link += to_string((long long)currentTileSetColumn);
	link +=  "/SPAWNLOCATIONS.BIN";
	enemyDataBin.open(link, ios::in | ios::binary);

	for (int row = 0; row < tilesPerRow; row++)
	{
		for (int column = 0; column < tilesPerRow; column++)
		{
			enemyDataBin.read (reinterpret_cast<char*> (&enemyDataArray[row][column]), sizeof(int));
		}
	} 
	enemyDataBin.close();

	std::ifstream weaponDataBin; 
	link = "";
	link += "assets/tileset";
	link += to_string((long long)currentTileSetRow);
	link += to_string((long long)currentTileSetColumn);
	link +=  "/WEAPONS.BIN";
	weaponDataBin.open(link, ios::in | ios::binary);

	for (int row = 0; row < tilesPerRow; row++)
	{
		for (int column = 0; column < tilesPerRow; column++)
		{
			weaponDataBin.read (reinterpret_cast<char*> (&dropDataArray[row][column]), sizeof(int));
		}
	} 
	weaponDataBin.close();

	SpawnEnemies();

	SpawnWeapons();
}

void map::SetNextTileSet(int rowOffset, int columnOffset)
{
	currentTileSetRow += rowOffset;
	currentTileSetColumn += columnOffset;

	LoadNextTileSet();
}

char* map::combineChar(int index)
{
	char* type = ".png";
	char number[(((sizeof index) * CHAR_BIT) + 2)/3 + 2];
	sprintf(number, "%d", index);
	char* msgHeader = new char[strlen(type)+1];
	memcpy(msgHeader,type,strlen(type)+1);
	msgHeader[strlen( type )] = '\0';

	char* retVal = new char[strlen(number)+strlen(msgHeader)+1];
	*retVal = '\0';

	// Assemble the string
	string link = "";
	link = "";
	link += "assets/tileset";
	link += to_string((long long)currentTileSetRow);
	link += to_string((long long)currentTileSetColumn);
	link += "/";
	strcat(retVal,(char*)link.c_str());
	strcat(retVal,number);
	strcat(retVal,msgHeader);
	return retVal;
}

void map::draw()
{
	for (int x = 0; x < tilesPerRow; x++)
	{
		for ( int y = 0; y < tilesPerRow; y++)
		{
			tiles[levelArray[x][y]]->CopyTo(m_Screen,x * tilesize,y * tilesize);
		}
	}

	for(int i = 0; i < enemyCount; i++)
	{
		if(guards[i]->alive)
			guards[i]->Draw(m_Screen);
	}

	if(mapWeapon != NULL && containsWeapon)
	{
		mapWeapon->Draw(m_Screen);
	}
}

void map::SpawnWeapons()
{
	for (int x = 0; x < tilesPerRow; x++)
	{
		for ( int y = 0; y < tilesPerRow; y++)
		{
			if(dropDataArray[x][y] == 1)
			{
				containsWeapon = true;
				mapWeapon = new Weapon();
				mapWeapon->SetWeaponType(mapWeapon->SWORD);
				mapWeapon->SetSpawnPos(x * tilesize, y * tilesize);
			}
			if(dropDataArray[x][y] == 2)
			{
				containsWeapon = true;
				mapWeapon = new Weapon();
				mapWeapon->SetWeaponType(mapWeapon->MASTERSWORD);
				mapWeapon->SetSpawnPos(x * tilesize, y * tilesize);
			}
			if(dropDataArray[x][y] == 3)
			{
				containsWeapon = true;
				mapWeapon = new Weapon();
				mapWeapon->SetWeaponType(mapWeapon->BOOTS);
				mapWeapon->SetSpawnPos(x * tilesize, y * tilesize);
			}
		}
	}
}

void map::SpawnEnemies()
{
	if(enemyCount <= 5)
	{
		for (int x = 0; x < tilesPerRow; x++)
		{
			for ( int y = 0; y < tilesPerRow; y++)
			{
				if(enemyDataArray[x][y] == 1)
				{
					guards[enemyCount] = new Guard();
					guards[enemyCount]->SetPos(x * tilesize, y * tilesize);
					guards[enemyCount]->GetMap(this);
					enemyCount++;
				}
				if(enemyCount > 1)
				{
					containsEnemies = true;
				}
			}
		}
	}	
}

void map::Update()
{
	for(int i = 0; i < enemyCount; i++)
	{
		if(guards[i] != NULL)
			guards[i]->Update();
	}
}

bool map::CheckSolids(int charX, int charY)
{
	int tileX = (charX + 4) / tilesize;
	int tileY = (charY + 6) / tilesize;

	if(IsSolid(tileX, tileY) || IsSolid(tileX + 1, tileY) || IsSolid(tileX, tileY + 1) || IsSolid(tileX + 1, tileY + 1))
		return true;
	else
		return false;
}

bool map::IsSolid(int tileX, int tileY)
{
	for(int i = 0; i < 512; i++)
	{
		if(solidDataArray[i] == levelArray[tileX][tileY])
			return true;
	}

	return false;
}

int map::GetGuardX(int i)
{
	if(guards[i] != NULL)
		return guards[i]->x;
}

int map::GetGuardY(int i)
{
	if(guards[i] != NULL)
		return guards[i]->y;
}

int map::GetGuardWidth(int i)
{
	if(guards[i] != NULL)
		return guards[i]->graphic->GetWidth();
}

int map::GetGuardHeight(int i)
{
	if(guards[i] != NULL)
		return guards[i]->graphic->GetHeight();
}

void map::SetGuardSpeedOff(int index)
{
	if(guards[index] != NULL)
		guards[index]->movementSpeed = 0;
}

void map::SetGuardSpeedOn(int index)
{
	if(guards[index] != NULL)
		guards[index]->movementSpeed = guards[index]->prevSpeed;
}

bool map::IsGuardAlive(int index)
{
	if(guards[index] != NULL)
		return guards[index]->alive;
}

void map::RemoveGuard(int index)
{
	if(guards[index] != NULL)
		guards[index]->alive = false;
}

map::~map(void)
{
}
