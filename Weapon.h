#pragma once

namespace Tmpl8 
{
	class Surface;
}

class Weapon
{
public:
	enum WeaponType
	{
		SWORD,
		MASTERSWORD,
		BOOTS
	};

	Weapon(void);
	~Weapon(void);

	WeaponType weaponType;
	Tmpl8::Surface* bootsGraphic;
	Tmpl8::Surface* swordGraphic;
	Tmpl8::Surface* masterSwordGraphic;

	Tmpl8::Surface* graphic;

	int x;
	int y;
	int damage;
	bool active;

	void SetWeaponType(WeaponType type);
	void Draw(Tmpl8::Surface* m_Screen);
	void SetSpawnPos(int x, int y);
};

