// Template, major revision 3, beta
// IGAD/NHTV - Jacco Bikker - 2006-2009

#pragma once

namespace Tmpl8 {
enum {
	LEFT = 0,
	RIGHT
};

class Surface;

class Game
{ 
public:
	void SetTarget( Surface* a_Surface ) { m_Screen = a_Surface; }
	void Init();
	void Tick( float a_DT );
	void KeyDown( unsigned int code ) {}
	void KeyUp( unsigned int code ) {}
	void MouseMove( unsigned int x, unsigned int y ) {}
	void MouseUp( unsigned int button ) {}
	void MouseDown( unsigned int button ) {}
	void Draw(void);
	int  Update();
	void CollisionCheck();

	int hitTimer;

private:
	Surface* m_Screen;
};

};