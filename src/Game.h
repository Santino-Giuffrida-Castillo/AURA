#pragma once
#include "Ball.h"
#include "Brick.h"
#include "Player.h"
#include "Consts.h"
#include <string>

const int MAX_FOTOGRAMS = 200;
struct VideoMeme {
    int sound;
    int fotograms[MAX_FOTOGRAMS];
    int realCantFrames;
    bool playing = false;
    int actualFrame = 0;
    int timeCounter = 0;
};

struct VideoManager {
    VideoMeme meme;
    VideoMeme intro;
    bool enterPressedBefore = false;
    bool tabPressedBefore = false;
};

void playGame();
void checkCollisions(Brick& brick, Ball& ball, Player& player);
void advanceFrameVideo(VideoMeme& video);
void uploadVideo(VideoMeme& video, int cantFrames, std::string audioRute, std::string folderPrefix);
void playVideo(VideoMeme& video);
void initVideoSystem(VideoManager& manager);
void controlAndDrawVideos(VideoManager& manager, double width, double height);