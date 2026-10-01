#include "Ball.h"
#include "Consts.h"
#include <iostream>
#include <sl.h>

void moveBall(Ball& ball) 
{
	ball.y += ball.velY * slGetDeltaTime();
	ball.x += ball.velX * slGetDeltaTime();
	updateBall(ball);
}

void updateBall(Ball& ball)
{
	ball.left = ball.x - ball.width / 2;
	ball.right = ball.x + ball.width / 2;
	ball.bottom = ball.y - ball.height / 2;
	ball.top = ball.y + ball.height / 2;
}

void drawBall(Ball ball)
{
	slRectangleFill(ball.x, ball.y, ball.width, ball.height);
}
Ball initBall()
{
	double ang = (rand() % 120) + 30;
	double rad = ang * PI / 180;

	Ball ball;
	ball.width = 10;
	ball.height = 10;
	ball.x = WIDTH / 2;
	ball.y = HEIGHT/ 4;
	ball.left =  ball.x - ball.width/2;
	ball.right = ball.x + ball.width/2;
	ball.bottom = ball.y - ball.height / 2;
	ball.top = ball.y + ball.height / 2;
	ball.velX = cos(rad) * 200;
	ball.velY = sin(rad) * 200;

	return ball;
}