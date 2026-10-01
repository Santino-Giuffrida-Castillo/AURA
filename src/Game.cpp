#include "Game.h"
#include <sl.h>
#include "Skins.h"
#include <iostream>
void playGame()
{
    slWindow(WIDTH, HEIGHT, "Brick Breaker + Meme Player", false);

    Player player;
    Ball ball;
    Brick bricks[brickAmount][brickAmount];
    player = initPlayer();
    ball = initBall();
    fillRow(bricks);
    putSkin(bricks, heartSkin);
    int font = slLoadFont("../res/Canterbury.ttf");
    int menuFont = slLoadFont("../res/stocky.ttf");

    while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
    {
        // Fondo por defecto
        slSetBackColor(0.0, 0.0, 1.0);


        movePlayer(player);
        moveBall(ball);
        checkCollisions(bricks, ball, player);
        checkIfBallIsOut(ball, player);
        checkifPlayerLosedOrWined(player, bricks, menuFont);
        if (!player.isWinner && player.lives > 0)
        {
            drawPlayer(player);
            drawBall(ball);
            drawBricks(bricks, brickAmount);
        }
        else
        {
            ball.velX = 0;
            ball.velY = 0;
        }
        showCredits(font);
        slSetForeColor(0.0, 0.0, 0.0, 1.0);

        slRender();
    }

    slClose();
}

void checkCollisions(Brick bricks[brickAmount][brickAmount], Ball& ball, Player& player)
{
    bool collision = false;
    bool touchUp = false;
    bool tochDown = false;
    bool touchUpperLefth = false;
    bool touchUpperRight = false;
    bool touchDownLefth = false;
    bool touchDownrRight = false;
    double penetrationLefth;
    double penetrationRight;
    double penetrationTop;
    double penetrationBottom;
    double minX;
    double minY;

    for (int i = 0; i < brickAmount; i++)
    {
        if (collision)
        {
            break;
        }
        for (int j = 0; j < brickAmount; j++)
        {
            if (bricks[i][j].active && !collision)
            {

                    //Se superpone en y?
                    if (ball.bottom <= bricks[i][j].top && ball.top >= bricks[i][j].bottom)
                    {
                        //Se superpone en x?
                        if (ball.left <= bricks[i][j].right && ball.right >= bricks[i][j].left)
                        {
                            std::cout << "choque" << std::endl;
                            penetrationLefth = ball.right - bricks[i][j].left;
                            penetrationRight = bricks[i][j].right - ball.left;
                            penetrationTop = bricks[i][j].top - ball.bottom;
                            penetrationBottom = ball.top - bricks[i][j].bottom;
                                if (penetrationLefth > penetrationRight)
                                {

                                 minX = penetrationRight;
                                }
                                else
                                {
                                 minX = penetrationLefth;
                                }

                                if (penetrationTop > penetrationBottom)
                                {
                                 minY = penetrationBottom;
                                }
                                else
                                {
                                 minY = penetrationTop;
                                }


                                if (minX > minY)
                                {

                                    if (ball.velY > 0)
                                    {
                                        ball.y -= penetrationBottom;
                                    }
                                    else if (ball.velY < 0)
                                    {
                                        ball.y += penetrationTop;
                                    }

                                    ball.velY = -ball.velY;
                                }
                                else if (minX < minY)
                                {

                                    if (ball.velX > 0)
                                    {
                                        ball.x -= penetrationLefth;
                                    }
                                    else if (ball.velX < 0)
                                    {
                                        ball.x += penetrationRight;
                                    }

                                    ball.velX = -ball.velX;
                                }
                                else
                                {
                                    if (ball.velX > 0)
                                    {
                                        ball.x -= penetrationLefth;
                                    }
                                    else if (ball.velX < 0)
                                    {
                                        ball.x += penetrationRight;
                                    }

                                    if (ball.velY > 0)
                                    {
                                        ball.y -= penetrationBottom;
                                    }
                                    else if (ball.velY < 0)
                                    {
                                        ball.y += penetrationTop;
                                    }

                                    ball.velX *= -1;
                                    ball.velY *= -1;
                                }

                                bricks[i][j].active = false;
                                collision = true;

                                updateBall(ball);
                        }
                    }
            }
        }
    }



    if (ball.left < SCREEN_LEFTH)
    {
        ball.velX *= -1;

    }
    else if (ball.right > WIDTH)
    {
        ball.velX *= -1;

    }
    else if (ball.top > HEIGHT)
    {

        ball.velY *= -1;
    }



    if (ball.bottom <= player.top && ball.top >= player.bottom)
    {
        //Se superpone en x?
        if (ball.left <= player.right && ball.right >= player.left)
        {
            std::cout << "choque con la paleta" << std::endl;
            penetrationLefth = ball.right - player.left;
            penetrationRight = player.right - ball.left;
            penetrationTop = player.top - ball.bottom;
            penetrationBottom = ball.top - player.bottom;
            if (penetrationLefth > penetrationRight)
            {

                minX = penetrationRight;

            }
            else
            {

                minX = penetrationLefth;

            }

            if (penetrationTop < penetrationBottom)
            {

                minY = penetrationTop;

            }

            else
            {

                minY = penetrationBottom;

            }


            if (minX > minY)
            {

                    ball.y = player.top + ball.height / 2;
                    ball.velY = -ball.velY;

                    if (ball.x < ( player.left + (player.width / 3) ) )
                    {
                        ball.velX = -VELX_BALL;
                    }
                    else if (ball.x < ( player.left + (player.width / 3) * 2) )
                    {
                        ball.velX = 0;
                    }
                    else
                    {
                        ball.velX = VELX_BALL;
                    }

            }
            else if (minX < minY)
            {

                if (ball.velX > 0)
                {

                    ball.x -= penetrationLefth;

                }
                else if (ball.velX < 0)
                {

                    ball.x += penetrationRight;

                }

                ball.velX = -ball.velX;
            }
            else
            {
                if (ball.velX > 0)
                {

                    ball.x -= penetrationLefth;

                }
                else if (ball.velX < 0)
                {

                    ball.x += penetrationRight;

                }

                if (ball.velY > 0)
                {

                    ball.y -= penetrationBottom;

                }
                else if (ball.velY < 0)
                {

                    ball.y += penetrationTop;

                }

                ball.velX *= -1;
                ball.velY *= -1;
            }
        }
    }

   
    updateBall(ball);


}

void checkifPlayerLosedOrWined(Player& player, Brick bricks[brickAmount][brickAmount], int font)
{
    int bricksDestroyed = 0;
    if (player.lives == 0)
    {
        std::cout << "Perdiste" << std::endl;
        showLoseScreen(font);

    }

    for (int i = 0; i < brickAmount; i++)
    {
        for (int j = 0; j < brickAmount; j++)
        {
            if (!bricks[i][j].active)
            {
                bricksDestroyed++;
            }
        }
    }
    if (bricksDestroyed == (brickAmount*brickAmount) && (!player.lives == 0))
    {
        std::cout << "Ganaste" << std::endl;
        player.isWinner = true;
        showWinScreen(font);
    }
}

void checkIfBallIsOut(Ball& ball, Player& player)
{
  if (ball.bottom < SCREEN_BOTTOM)
  {
      ball = initBall();
      player.lives--;
  }
}

void uploadVideo(VideoMeme& video, int cantFrames, std::string audioRute, std::string folderPrefix)
{
    if (cantFrames > MAX_FOTOGRAMS) cantFrames = MAX_FOTOGRAMS;
    video.realCantFrames = cantFrames;
    video.sound = slLoadWAV(audioRute.c_str());

    for (int i = 0; i < video.realCantFrames; i++) {
        int numeroFrame = i + 1;
        std::string ceros = "";

// Formato exacto de 5 dígitos (ej: frame_00001 a frame_00010)
        if (numeroFrame < 10) ceros = "0000";         // 4 ceros + 1 dígito = 5 dígitos
        else if (numeroFrame < 100) ceros = "000";     // 3 ceros + 2 dígitos = 5 dígitos
        else if (numeroFrame < 1000) ceros = "00";     // 2 ceros + 3 dígitos = 5 dígitos
        std::string rutaFinal = folderPrefix + ceros + std::to_string(numeroFrame) + ".png";
        video.fotograms[i] = slLoadTexture(rutaFinal.c_str());
    }
}
// Inicializa todos los videos juntos
void initVideoSystem(VideoManager& manager)
{
    uploadVideo(manager.meme, 51, "../res/BaraBaraBara.wav", "res/animacion_feliz/frame_");
    uploadVideo(manager.intro, 174, "../res/ianomenojocontigosolovservo.wav", "res/animacion_triste/intro_");
}
// Función interna para reproducir de forma segura
void playVideo(VideoMeme& video) {
    if (!video.playing) {
        slSoundPlay(video.sound);
        video.playing = true;
        video.actualFrame = 0;
        video.timeCounter = 0;
    }
}
// Función interna para actualizar fotogramas
void advanceFrameVideo(VideoMeme& video) {
    if (!video.playing) return;
    video.timeCounter++;
    if (video.timeCounter % 6 == 0) {
        video.actualFrame++;
        if (video.actualFrame >= video.realCantFrames) {
            video.playing = false;
        }
    }
}
// LA FUNCIÓN MAESTRA: Se encarga de capturar teclas, actualizar lógica y dibujar
void controlAndDrawVideos(VideoManager& manager, double width, double height)
{
    // 1. GESTIÓN DE ENTRADAS DE TECLADO
    if (slGetKey(SL_KEY_ENTER)) {
        if (!manager.enterPressedBefore && !manager.intro.playing) {
            playVideo(manager.meme);
            manager.enterPressedBefore = true;
        }
    }
    else {
        manager.enterPressedBefore = false;
    }

    if (slGetKey(SL_KEY_TAB)) {
        if (!manager.tabPressedBefore && !manager.meme.playing) {
            playVideo(manager.intro);
            manager.tabPressedBefore = true;
        }
    }
    else {
        manager.tabPressedBefore = false;
    }

    // 2. ACTUALIZACIÓN Y DIBUJADO SEGÚN PRIORIDAD
    if (manager.intro.playing) {
        slSprite(manager.intro.fotograms[manager.intro.actualFrame], width * 0.5, height * 0.5, 800, 600);
        advanceFrameVideo(manager.intro);
    }
    else if (manager.meme.playing) {
        slSprite(manager.meme.fotograms[manager.meme.actualFrame], width * 0.5, height * 0.5, 800, 600);
        advanceFrameVideo(manager.meme);
    }
    else {
        // Interfaz base o elementos por defecto del juego si no hay ningún video activo
        slSetForeColor(1, 0, 0, 1);
        slRectangleFill(width * 0.5, height * 0.5, 100, 100);
    }
}
void showLoseScreen(int font)
{
    slSetFont(font, 100);
    slSetForeColor(0.5, 0.5, 0.5, 1);
    slText(100, (HEIGHT / 2 + HEIGHT / 4), "PERDISTE");
}
void showWinScreen(int font)
{
    slSetFont(font, 100);
    slSetForeColor(0.5, 0.5, 0.5, 1);
    slText(100, (HEIGHT / 2 + HEIGHT / 4), "GANASTE");
}

void showCredits(int& font)
{

    slSetFont(font, 20);
    slSetForeColor(0.5, 0.5, 0.5, 1);
    slText(10, 10, "Made by: Santino Giuffrida");
}