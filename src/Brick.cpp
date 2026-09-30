#include "Brick.h"
#include <sl.h>
//Rellena en xy
Brick initBrick(int brickAmount, Brick previousBrick, Brick previousUpperBrick)
{
	Brick brick = initBrick(brickAmount);
	brick.x = previousBrick.x + brick.width + 1;
	brick.y = previousUpperBrick.y + brick.height + 1;

	brick.left = brick.x - brick.width / 2;
	brick.right = brick.x + brick.width / 2;
	brick.top = brick.y + brick.height / 2;
	brick.bottom = brick.y - brick.height / 2;
	return brick;
}

//Rellena x
Brick initBrick(int brickAmount, Brick previousBrick)
{
	Brick brick = initBrick(brickAmount);
	brick.x = previousBrick.x + brick.width + 1;
	brick.left = brick.x - brick.width / 2;
	brick.right = brick.x + brick.width / 2;
	return brick;
}
//Primer ladrillo en y
Brick initBrickUpper(int brickAmount,Brick previousUpperBrick)
{
	Brick brick = initBrick(brickAmount);
	brick.y = previousUpperBrick.y + brick.height + 1;
	brick.top = brick.y + brick.height / 2;
	brick.bottom = brick.y - brick.height / 2;
	return brick;
}
//Primer ladrillo x
Brick initBrick(int brickAmount)
{
	Brick brick;
	brick.width = WIDTH / brickAmount - 1;
	brick.height = (HEIGHT / 2) / brickAmount - 1;
	brick.x = SCREEN_LEFTH + (brick.width / 2) + 1;
	brick.y = WIDTH / 3;
	brick.active = true;
	brick.left = brick.x - brick.width / 2;;
	brick.right = brick.x + brick.width / 2;;
	brick.top = brick.y + brick.height / 2;
	brick.bottom = brick.y - brick.height / 2;
	return brick;
}

void putSkin(Brick bricks[brickAmount][brickAmount], bool skin[brickAmount][brickAmount])
{
	for (int i = 0; i < brickAmount; i++)
	{
		for (int j = 0; j < brickAmount; j++)
		{
			bricks[i][j].active = skin[brickAmount - 1 - i][j];
		}
	}
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
			if (bricks[i][j].active)
			{
				slRectangleFill(bricks[i][j].x, bricks[i][j].y, bricks[i][j].width, bricks[i][j].height);
			}
		}
		
	}
	
}