#pragma once
struct Player
{
	double x;
	double y;
	double width;
	double height;

};

void movePlayer(Player& player);
Player initPlayer();
void drawPlayer(Player player);