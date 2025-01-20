#ifndef SOMEFEITOS_H
#define SOMEFEITOS_H
#include <mmsystem.h>

bool Audio_Derrota = false;
bool Audio_Vitoria = false;
bool Audio_Impacto = false;

void playSons(){
	if(Audio_Impacto){
		mciSendString("play sons/impacto.wav", NULL, 0, NULL);
		Audio_Impacto = false;
	}
	
}

void playAudioDerrota(){
	if(Audio_Derrota){
		mciSendString("play sons/derrota.wav", NULL, 0, NULL);
		Audio_Derrota = false;
	}
}

void playAudioVitoria(){
	if(Audio_Vitoria){
		mciSendString("play sons/vitoria.wav", NULL, 0, NULL);
		Audio_Vitoria = false;
	}
}


#endif