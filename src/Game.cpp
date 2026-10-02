#include "Game.h"
#include <sl.h>
#include <iostream>
bool defaultSkin[brickAmount][brickAmount] =
{
    {true, true, true, true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true, true, true, true},
    {true, true, true, true, true, true, true, true, true, true}
};
bool heartSkin[brickAmount][brickAmount] =
{
    {false, false, true,  true,  false, false, true,  true,  false, false},
    {false, true,  true,  true,  true,  true,  true,  true,  true,  false},
    {true,  true,  true,  true,  true,  true,  true,  true,  true,  true },
    {true,  true,  true,  true,  true,  true,  true,  true,  true,  true },
    {false, true,  true,  true,  true,  true,  true,  true,  true,  false},
    {false, false, true,  true,  true,  true,  true,  true,  false, false},
    {false, false, false, true,  true,  true,  true,  false, false, false},
    {false, false, false, false, true,  true,  false, false, false, false},
    {false, false, false, false, false, false,  false, false, false, false},
    {false, false, false, false, false, false, false, false, false, false}

};
bool cheatSkin[brickAmount][brickAmount] =
{
    {false, false, false,  false,  false, false, false,  false,  false, false},
     {false, false, false,  false,  false, false, false,  false,  false, false},
     {false, false, false,  false,  false, false, false,  false,  false, false},
    {false, false, false,  false,  false, false, false,  false,  false, false},
     {false, false, false,  false,  false, false, false,  false,  false, false},
    {false, false, false,  false,  false, false, false,  false,  false, false},
     {false, false, false,  false,  false, false, false,  false,  false, false},
    {false, false, false,  false,  false, false, false,  false,  false, false},
     {false, false, false,  false,  false, false, false,  false,  false, false},
    {false, false, false,  false,  false, false, false,  false,  false, false}

};

void playGame()
{
    slWindow(WIDTH, HEIGHT, "Brick Breaker + Meme Player", false);

    Player player;
    Ball ball;
    Brick bricks[brickAmount][brickAmount];
    bool actualSkin[brickAmount][brickAmount];
    GameMode mode = NORMAL;
    bool destroyedBrick = false;

    for (int i = 0; i < brickAmount; i++)
    {
        for (int j = 0; j < brickAmount; j++)
        {
            actualSkin[i][j] = defaultSkin[i][j];
        }
    }

    player = initPlayer();
    ball = initBall();
    fillRow(bricks);
    putSkin(bricks, defaultSkin);


    int font = slLoadFont("../res/stocky.ttf");
    VideoManager manager;
    initVideoSystem(manager);

    GameState state = MODE_MENU;

    while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
    {
        slSetBackColor(0.0, 0.0, 1.0);

        if (state == PLAYING)
        {
            slSetForeColor(1.0, 1.0, 1.0, 1.0);
            movePlayer(player);
            moveBall(ball);

            checkCollisions(bricks, ball, player, destroyedBrick);
            checkIfBallIsOut(ball, player);

            checkifPlayerLosedOrWon(player, bricks, state);

            drawPlayer(player);
            drawBall(ball);
            drawBricks(bricks, brickAmount);

            if (mode == ESPECIAL)
            {
                controlAndDrawSpecialMode(manager, destroyedBrick, WIDTH, HEIGHT);
            }
        }

        else if (state == LOSE_SCREEN)
        {
            slSetForeColor(0.5, 0.5, 0.5, 1);
            showLoseScreen(font);

            if (slGetKey(SL_KEY_ENTER))
            {
                initGame(player, bricks, ball, actualSkin);
                state = PLAYING;
            }
            else if (slGetKey('R') || slGetKey('r'))
            {
                state = SKIN_MENU;
            }
            else if (slGetKey('Q') || slGetKey('q'))
            {
                state = MODE_MENU;
            }
            else if (slGetKey('C') || slGetKey('c'))
            {
                state = CREDITS;
            }
        }

        else if (state == WIN_SCREEN)
        {
            slSetForeColor(0.5, 0.5, 0.5, 1);
            showWinScreen(font);

            if (slGetKey(SL_KEY_ENTER))
            {
                initGame(player, bricks, ball, actualSkin);
                state = PLAYING;
            }
            else if (slGetKey('R') || slGetKey('r'))
            {
                state = SKIN_MENU;
            }
            else if (slGetKey('Q') || slGetKey('q'))
            {
                state = MODE_MENU;
            }
            else if (slGetKey('C') || slGetKey('c'))
            {
                state = CREDITS;
            }
        }

        else if (state == CREDITS)
        {
            showCredits(font);

            if (slGetKey('f') || slGetKey('F'))
            {
                state = LOSE_SCREEN;
            }
        }

        else if (state == SKIN_MENU)
        {
            choseSkin(actualSkin, font);

            if (slGetKey(SL_KEY_ENTER))
            {
                initGame(player, bricks, ball, actualSkin);
                putSkin(bricks, actualSkin);
                state = PLAYING;
            }
        }

        else if (state == MODE_MENU)
        {
            choseMode(mode, font);

            if (slGetKey(SL_KEY_ENTER))
            {
                state = PLAYING;
            }
        }

        slRender();
    }

    slClose();
}

void checkCollisions(Brick bricks[brickAmount][brickAmount], Ball& ball, Player& player, bool& destroyedBrick)
{
    destroyedBrick = false;
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
                                destroyedBrick = true;
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

void checkifPlayerLosedOrWon( Player& player,Brick bricks[brickAmount][brickAmount],GameState& state)
{
    if (player.lives <= 0)
    {
        state = LOSE_SCREEN;
        return;
    }

    int bricksDestroyed = 0;

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

    if (bricksDestroyed == brickAmount * brickAmount)
    {
        player.isWinner = true;
        state = WIN_SCREEN;
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
    uploadVideo(manager.meme, 51, "../res/BaraBaraBara.wav", "../res/animacion_feliz/frame_");
    uploadVideo(manager.intro, 174, "../res/ianomenojocontigosolovservo.wav", "../res/animacion_triste/intro_");
}

// Función para iniciar videos

void playVideo(VideoMeme& video)
{
    if (!video.playing)
    {
        slSoundPlay(video.sound);

        video.playing = true;
        video.actualFrame = 0;
        video.timeCounter = 0;
        video.elapsedTime = 0.0;
    }
}
//Funcion para parar videos

void stopVideo(VideoMeme& video)
{
    if (video.playing)
    {
        slSoundStop(video.sound);

        video.playing = false;
        video.actualFrame = 0;
        video.timeCounter = 0;
        video.elapsedTime = 0.0;
    }
}

//Cambia los fotogramas 
void advanceFrameVideo(VideoMeme& video)
{
    if (!video.playing) return;

    video.elapsedTime += slGetDeltaTime();

    video.timeCounter++;

    if (video.timeCounter % 6 == 0)
    {
        video.actualFrame++;
    }

    double duration = video.realCantFrames / 10.0;

    if (video.elapsedTime >= duration)
    {
        slSoundStop(video.sound);

        video.playing = false;
        video.actualFrame = 0;
        video.timeCounter = 0;
        video.elapsedTime = 0.0;
    }
}
// Funcion encargada de controlar los videos 
void controlAndDrawSpecialMode(VideoManager& manager, bool destroyedBrick, double width, double height)
{
    // Si está sonando el feliz, tiene prioridad absoluta.
    // Los bloques que destruya mientras tanto se ignoran.
    if (manager.meme.playing)
    {
        slSetForeColor(1.0, 1.0, 1.0, 1.0);

        slSprite(
            manager.meme.fotograms[manager.meme.actualFrame],
            25,
            25,
            50,
            50
        );

        advanceFrameVideo(manager.meme);

        return;
    }

    // Si acaba de destruir un bloque y NO está sonando el feliz:
    // cortamos el triste y ponemos el feliz.
    if (destroyedBrick)
    {
        stopVideo(manager.intro);
        playVideo(manager.meme);

        return;
    }

    // Si no destruyó ningún bloque y está sonando el triste,
    // simplemente seguimos reproduciéndolo.
    if (manager.intro.playing)
    {
        slSetForeColor(1.0, 1.0, 1.0, 1.0);

        slSprite(
            manager.intro.fotograms[manager.intro.actualFrame],
            25,
            25,
            50,
            50
        );

        advanceFrameVideo(manager.intro);

        return;
    }

    // Si no está sonando ninguno, empieza el triste.
    playVideo(manager.intro);
}

void showLoseScreen(int font)
{
    slSetFont(font, 100);
    slSetForeColor(0.5, 0.5, 0.5, 1);
    slText(100, (HEIGHT / 2 + HEIGHT / 4), "PERDISTE");
    slSetFont(font, 50);
    slText(100, (HEIGHT / 2 + HEIGHT / 4) - 50, "Resetear?(ENTER)");
    slText(100, (HEIGHT / 2 + HEIGHT / 4) - 100, "Cambiar skin?(R)");
    slText(100, (HEIGHT / 2 + HEIGHT / 4) - 150, "Cambiar Modo?(Q)");
    slText(100, (HEIGHT / 2 + HEIGHT / 4) - 200, "Mostrar Creditos?(C)");
}

void showWinScreen(int font)
{
    slSetFont(font, 100);
    slSetForeColor(0.5, 0.5, 0.5, 1);
    slText(100, (HEIGHT / 2 + HEIGHT / 4), "GANASTE");
    slSetFont(font, 50);
    slText(100, (HEIGHT / 2 + HEIGHT / 4) - 50, "Resetear?(ENTER)");
    slText(100, (HEIGHT / 2 + HEIGHT / 4) - 100, "Cambiar skin?(R)");
    slText(100, (HEIGHT / 2 + HEIGHT / 4) - 150, "Cambiar Modo?(Q)");
    slText(100, (HEIGHT / 2 + HEIGHT / 4) - 200, "Mostrar Creditos?(C)");

}

void showCredits(int& font)
{

        slSetFont(font, 20);
        slSetForeColor(0.5, 0.5, 0.5, 1);
        slText(5, 500, "Hecho por: Santino Giuffrida");
        slText(5, 450, "Para el desarrollo de este juego se uso:ChatGPT");
        slText(5, 400, "modelo GPT - 5.6 Luna, de OpenAI, en la busqueda de informacion y");
        slText(5, 350, "ayuda en la correccion de errores, se uso mas en la implementacion de");
        slText(5, 300, "material audiovisual(funciones para implementarlo en el juego)");
        slSetFont(font, 30);
        slText(100, 250, "Agradecimientos especiales");
        slSetFont(font, 20);
        slText(5, 220, "Nahuel Suarez: Aporte en solucionar errores y apoyo emocional");
        slText(5, 200, "Sofia Belen Alvarez Franze:Aporte en la idea de como hacer el mapa");
        slText(5, 150, "Lucio Stefano Piccioni:Aporte en la idea de como hacer el mapa");
        slText(5, 100, "Aprete F para salir");
    
}

void initGame(Player& player, Brick bricks[brickAmount][brickAmount], Ball& ball, bool skin[brickAmount][brickAmount])
{
    player = initPlayer();
    fillRow(bricks);
    putSkin(bricks, skin);
    ball = initBall();
}

void choseSkin(bool skin[brickAmount][brickAmount], int font)
{
    slSetFont(font, 40);

    slSetForeColor(1, 1, 1, 1);

    slText(100, 700, "ELEGIR SKIN");

    slSetFont(font, 25);

    slText(100, 500, "1 - Corazon");
    slText(100, 450, "2 - Default");
    slText(100, 400, "ENTER - Confirmar");

    if (slGetKey('1'))
    {
        for (int i = 0; i < brickAmount; i++)
        {
            for (int j = 0; j < brickAmount; j++)
            {
                skin[i][j] = heartSkin[i][j];
            }
        }
    }

    if (slGetKey('2'))
    {
        for (int i = 0; i < brickAmount; i++)
        {
            for (int j = 0; j < brickAmount; j++)
            {
                skin[i][j] = defaultSkin[i][j];
            }
        }
    }
}
void choseMode(GameMode& mode, int font)
{
    slSetFont(font, 40);
    slSetForeColor(1, 1, 1, 1);

    slText(100, 550, "ELEGIR MODO");

    slSetFont(font, 25);

    slText(100, 400, "1 - Normal");
    slText(100, 350, "2 - Especial");
    slText(100, 250, "ENTER - Confirmar");

    if (slGetKey('1'))
    {
        mode = NORMAL;
    }

    if (slGetKey('2'))
    {
        mode = ESPECIAL;
    }
}