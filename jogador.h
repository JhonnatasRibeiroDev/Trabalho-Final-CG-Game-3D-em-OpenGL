#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct{
	float I;
	float J;
	float I_Origem;
	float J_Origem;
	float velocidade;
	float R;
	float G;
	float B;
	int vida;
	bool vivo;
}Jogador;

#endif

