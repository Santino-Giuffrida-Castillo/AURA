#include <sl.h>
#include "Game.h" 

int main()
{


    slWindow(WIDTH, HEIGHT, "Brick Breaker + Meme Player", false);

    //// Instanciamos el manager que contiene tus dos videos reales
    //VideoManager misVideos;

    // Ejecuta tu función de carga masiva (reproduce audios y levanta texturas)
    /*initVideoSystem(misVideos);*/
    Player player;
    Ball ball;
    Brick bricks[brickAmount][brickAmount];
    player = initPlayer();
    ball = initBall();
    fillRow(bricks);
    while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
    {
        // Fondo por defecto
        slSetBackColor(0.0, 0.0, 1.0);


        movePlayer(player);


        drawPlayer(player);
        drawBall(ball);
        drawBricks(bricks, brickAmount);

        slSetForeColor(0.0, 0.0, 0.0, 1.0);
        // Esta sola función de Game.cpp controla el Enter, el Tab, el audio y dibuja los frames
        /*controlAndDrawVideos(misVideos, width, height);*/




        slRender();
    }

    slClose();
    return 0;
}