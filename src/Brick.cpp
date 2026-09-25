#include "Brick.h"
#include <sl.h>
Brick initBrick(int brickAmount, Brick previousBrick, Brick previousUpperBrick)
{
	Brick brick = initBrick(brickAmount);
	brick.x = previousBrick.x + brick.width + 1;
	brick.y = previousUpperBrick.y + brick.height + 1;
	return brick;
}
Brick initBrick(int brickAmount, Brick previousBrick)
{
	Brick brick = initBrick(brickAmount);
	brick.x = previousBrick.x + brick.width + 1;
	return brick;
}
Brick initBrickUpper(int brickAmount,Brick previousUpperBrick)
{
	Brick brick = initBrick(brickAmount);
	brick.y = previousUpperBrick.y + brick.height + 1;
	return brick;
}

Brick initBrick(int brickAmount)
{
	Brick brick;
	brick.width = WIDTH / brickAmount - 1;
	brick.height = (HEIGHT / 2) / brickAmount - 1;
	brick.x = SCREEN_LEFTH + (brick.width / 2) + 1;
	brick.y = WIDTH / 3;
	return brick;
}

void fillRow(Brick bricks[brickAmount][brickAmount])
{
	
	for (int i = 0; i < brickAmount; i++)
	{	

		for (int j = 0; j < brickAmount; j++)
		{
			//Primera fila
			if (i == 0)
			{

				//Primer ladrillo
				if (j == 0)
				{
					bricks[i][j] = initBrick(brickAmount);
				}
				//Lo que le sigue de la primera fila
				else
				{
					bricks[i][j] = initBrick(brickAmount, bricks[i][j - 1]);
				}
			}
			//Las siguientes filas 
			else
			{	//Primer ladrillo
				if (j == 0)
				{
					bricks[i][j] = initBrickUpper(brickAmount, bricks[i - 1][j]);
				}
				//Lo que le sigue de la fila
				else
				{
					bricks[i][j] = initBrick(brickAmount,bricks[i][j - 1],bricks[i - 1][j]);
				}
			}

		}

	}
}
void drawBricks(Brick bricks[brickAmount][brickAmount], int brickAmount)
{
	for (int i = 0; i < brickAmount; i++)
	{
		for (int j = 0; j < brickAmount; j++)
		{
			slRectangleFill(bricks[i][j].x, bricks[i][j].y, bricks[i][j].width, bricks[i][j].height);
		}
		
	}
	
}