#pragma once
struct Ball
{
	double x;
	double y;
	double width;
	double height;

};

void moveBall(Ball& ball);
void drawBall(Ball ball);
Ball initBall();