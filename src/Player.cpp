#include "Player.h"
#include "Consts.h"
#include <sl.h>
void movePlayer(Player& player)
{
	if (slGetKey('a') || slGetKey('A'))
	{
		player.x -= 200 * slGetDeltaTime();
	}
	else if (slGetKey('D') || slGetKey('D'))
	{
		player.x += 200 * slGetDeltaTime();
	}

	if (player.x < SCREEN_LEFTH + player.width / 2)
	{
		player.x = SCREEN_LEFTH + player.width / 2;
	}
	if (player.x > WIDTH - player.width / 2)
	{
		player.x = WIDTH - player.width / 2;
	}
	updatePlayer(player);

}
Player initPlayer()
{
	Player player;
	player.width = 100;
	player.height = 20;
	player.x = WIDTH / 2;
	player.y = 100;
	player.left = player.x - player.width / 2;;
	player.right = player.x + player.width / 2;;
	player.top = player.y + player.height / 2;
	player.bottom = player.y + player.height / 2;
	player.lives = 3;

	return player;
}
void drawPlayer(Player player)
{
	slRectangleFill(player.x, player.y, player.width, player.height);
}
void updatePlayer(Player& player)
{
	player.left = player.x - player.width / 2;;
	player.right = player.x + player.width / 2;;
	player.top = player.y + player.height / 2;
	player.bottom = player.y + player.height / 2;
}