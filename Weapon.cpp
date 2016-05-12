#include "Weapon.h"
#include "surface.h"

using namespace Tmpl8;

Weapon::Weapon(void)
{
	bootsGraphic = new Surface("assets/weapons/pegasus_boots.png");
	swordGraphic = new Surface("assets/weapons/sword.png");
	masterSwordGraphic = new Surface("assets/weapons/mastersword.png");
	active = false;
}

void Weapon::Draw(Surface* m_Screen)
{
	graphic->TransparentCopyTo(m_Screen, x, y);
}

void Weapon::SetWeaponType(WeaponType type)
{
	weaponType = type;

	if(weaponType == SWORD)
	{
		graphic = swordGraphic;
	}
	if(weaponType == BOOTS)
	{
		graphic = bootsGraphic;
	}
	if(weaponType == MASTERSWORD)
	{
		graphic = masterSwordGraphic;
	}
}

void Weapon::SetSpawnPos(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
}

Weapon::~Weapon(void)
{
}
