#ifndef VIDAS_H
#define VIDAS_H
#include "mapa.h"

void desenhaVidasJogador(int vidas){
    glPushMatrix();
    glTranslatef(15.5, 8.5, 0.5);
    glScalef(0.8, 0.8, 0.8);
    float espaco = 1.5;

    for (int i = 0; i < vidas; i++){
        glPushMatrix();
        glTranslatef(i * espaco, 0.0, 0.0);
        desenhaVidaVeiculo(-8.5, 0.0, 1.0, 1.0, 1.0);
        glPopMatrix();
    }

glPopMatrix();
}

#endif