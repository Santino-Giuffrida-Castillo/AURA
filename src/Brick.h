#pragma once
#include "Consts.h"
struct Brick
{
	double x;
	double y;
	double width;
	double height;
	bool isBroken;

};

Brick initBrick(int brickAmount, Brick previousBrick);
Brick initBrick(int brickAmount);
void drawBricks(Brick bricks[brickAmount][brickAmount], int brickAmount);
void fillRow(Brick bricks[brickAmount][brickAmount]);
