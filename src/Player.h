#pragma once
struct Player
{
	double x;
	double y;
	double width;
	double height;
	double left;
	double right;
	double top;
	double bottom;
	int lives;
	bool isWinner;
};

void movePlayer(Player& player);
Player initPlayer();
void drawPlayer(Player player);
void updatePlayer(Player& player);