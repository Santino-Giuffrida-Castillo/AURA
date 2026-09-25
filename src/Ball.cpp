#include "Ball.h"
#include "Consts.h"
#include <sl.h>

void moveBall(Ball& ball) 
{

}

void drawBall(Ball ball)
{
	slRectangleFill(ball.x, ball.y, ball.width, ball.height);
}
Ball initBall()
{
	Ball ball;
	ball.width = 10;
	ball.height = 10;
	ball.x = WIDTH / 2;
	ball.y = HEIGHT/2;

	return ball;
}