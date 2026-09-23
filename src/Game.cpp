#include "Game.h"
#include <sl.h>
#include <iostream>
void playGame()
{

}

void checkBrickBallCollisions()
{

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