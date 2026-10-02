#pragma once
#include "Consts.h"
#include "Skins.h"
struct Brick
{
	double x;
	double y;
	double width;
	double height;
	double left;
	double right;
	double top;
	double bottom;
	bool active;

};

Brick initBrick(int brickAmount, Brick previousBrick);
Brick initBrick(int brickAmount);
Brick initBrickUpper(int brickAmount, Brick previousUpperBrick);
Brick initBrick(int brickAmount, Brick previousBrick, Brick previousUpperBrick);
void drawBricks(Brick bricks[brickAmount][brickAmount], int brickAmount);
void fillRow(Brick bricks[brickAmount][brickAmount]);
void putSkin(Brick bricks[brickAmount][brickAmount], bool skin[brickAmount][brickAmount]);
