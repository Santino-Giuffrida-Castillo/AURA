#pragma once
struct Ball
{
	double x;
	double y;
	double width;
	double height;
	double left;
	double right;
	double top;
	double bottom;
	double velX;
	double velY;
};

void moveBall(Ball& ball);
void drawBall(Ball ball);
void updateBall(Ball& ball);
Ball initBall();