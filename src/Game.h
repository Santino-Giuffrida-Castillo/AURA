#pragma once
#include "Ball.h"
#include "Brick.h"
#include "Player.h"
#include "Consts.h"
#include <string>

const int MAX_FOTOGRAMS = 200;

enum GameState
{
    PLAYING,
    LOSE_SCREEN,
    WIN_SCREEN,
    CREDITS,
    SKIN_MENU,
    MODE_MENU
};

enum GameMode
{
    NORMAL,
    ESPECIAL
};

struct VideoMeme {
    int sound;
    int fotograms[MAX_FOTOGRAMS];
    int realCantFrames;
    bool playing = false;
    int actualFrame = 0;
    int timeCounter = 0;
    double elapsedTime = 0.0;
};

struct VideoManager {
    VideoMeme meme;
    VideoMeme intro;
    double waitTime = 0.0;
};

void playGame();

void showLoseScreen(int font);
void showWinScreen(int font);
void checkifPlayerLosedOrWon(Player& player, Brick bricks[brickAmount][brickAmount], GameState& state);

void initGame(Player& player, Brick bricks[brickAmount][brickAmount], Ball& ball, bool skin[brickAmount][brickAmount]);

void checkCollisions(Brick bricks[brickAmount][brickAmount], Ball& ball, Player& player, bool& destroyedBrick);
void checkIfBallIsOut(Ball& ball, Player& player);

void advanceFrameVideo(VideoMeme& video);
void uploadVideo(VideoMeme& video, int cantFrames, std::string audioRute, std::string folderPrefix);
void playVideo(VideoMeme& video);
void stopVideo(VideoMeme& video);
void initVideoSystem(VideoManager& manager);
void controlAndDrawSpecialMode(VideoManager& manager, bool destroyedBrick, double width, double height);


void showCredits(int& font);
void choseSkin(bool skin[brickAmount][brickAmount], int font);
void choseMode(GameMode& mode, int font);