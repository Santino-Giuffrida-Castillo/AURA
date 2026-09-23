#include <sl.h>
#include "Game.h" // Incluimos tu cabecera modular

int main()
{
    const int width = 1200;
    const int height = 900;

    slWindow(width, height, "Brick Breaker + Meme Player", false);

    //// Instanciamos el manager que contiene tus dos videos reales
    //VideoManager misVideos;

    // Ejecuta tu función de carga masiva (reproduce audios y levanta texturas)
    /*initVideoSystem(misVideos);*/

    while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
    {
        // Fondo por defecto
        slSetBackColor(0.0, 0.0, 0.0);

        // Esta sola función de Game.cpp controla el Enter, el Tab, el audio y dibuja los frames
        /*controlAndDrawVideos(misVideos, width, height);*/




        slRender();
    }

    slClose();
    return 0;
}