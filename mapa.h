#ifndef MAPA_H
#define MAPA_H

#include <cstdio>
#include "cubo3D.h"
#include "jogador.h"
#include "veiculos.h"
#include "SomEfeitos.h"
#include <sstream>
using std::stringstream;
#include <string>
using std::string;


//Texturas 
#include "texturas/texParede.h"
#include "texturas/texChao.h"
#include "texturas/texChao2.h"
#include "texturas/texDestroi_Veiculos.h"
#include "texturas/texVeiculo.h"
#include "texturas/texFundo.h"
#include "texturas/texInicio.h"
#include "texturas/texDerrota.h"
#include "texturas/texVitoria.h"

#define tamMapa_i 27
#define tamMapa_j 15

//Texturas
#define QUANT_TEX 10
float tam_veiculo = 0.7;
unsigned int id_texturas[QUANT_TEX]; //nomes identificadores de textura

void textura(){
	glGenTextures(QUANT_TEX, id_texturas); //gera nomes identificadores de texturas
	
	glBindTexture(GL_TEXTURE_2D, id_texturas[0]); //Textura linhas divisao da pista
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURA_chao2, TEXTURA_chao2, 0, GL_RGB, GL_UNSIGNED_BYTE, chao2_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, id_texturas[1]); //Textura parede
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURA_parede, TEXTURA_parede, 0, GL_RGB, GL_UNSIGNED_BYTE, parede_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, id_texturas[2]); //Textura chao
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURA_chao, TEXTURA_chao, 0, GL_RGB, GL_UNSIGNED_BYTE, chao_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, id_texturas[3]); //Textura ParedeDestroiVeiculos
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEX_Destroi_Veiculos, TEX_Destroi_Veiculos, 0, GL_RGB, GL_UNSIGNED_BYTE, Destroi_Veiculos_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	//Textura do Veiculo
	glBindTexture(GL_TEXTURE_2D, id_texturas[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURA_veiculo, TEXTURA_veiculo, 0, GL_RGB, GL_UNSIGNED_BYTE,  veiculo_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	
	//Textura do fundo
	glBindTexture(GL_TEXTURE_2D, id_texturas[5]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURA_fundo, TEXTURA_fundo, 0, GL_RGB, GL_UNSIGNED_BYTE,  fundo_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	
	//Textura tela instrucoes
	glBindTexture(GL_TEXTURE_2D, id_texturas[6]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURA_tela_instrucoes, TEXTURA_tela_instrucoes, 0, GL_RGB, GL_UNSIGNED_BYTE,  inicio_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
	//Textura derrota
	glBindTexture(GL_TEXTURE_2D, id_texturas[7]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURA_derrota, TEXTURA_derrota, 0, GL_RGB, GL_UNSIGNED_BYTE,  derrota_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	//Textura vitoria
	glBindTexture(GL_TEXTURE_2D, id_texturas[8]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURA_vitoria, TEXTURA_vitoria, 0, GL_RGB, GL_UNSIGNED_BYTE,  vitoria_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
  
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

/*
- Mapa
	- Chao: 0
	- Parede: 2
	- Destroi Veiculos: 3
	- area vazia: 9
*/

int mapa[tamMapa_i][tamMapa_j] =   {{9, 9, 9, 9, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
								    {9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
								    {9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
									{9, 9, 9, 9, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
																						
};

// Plano de fundo
void background() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);
    glBindTexture(GL_TEXTURE_2D, id_texturas[5]);
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2i(0, 0); glVertex2i(-1, -1);
    glTexCoord2i(1, 0); glVertex2i(1, -1);
    glTexCoord2i(1, 1); glVertex2i(1, 1);
    glTexCoord2i(0, 1); glVertex2i(-1, 1);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glDepthMask(GL_TRUE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void tela_instrucoes(int id){
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
    	glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
 		glDisable(GL_LIGHTING);
    	glDepthMask(GL_FALSE);
    	glBindTexture(GL_TEXTURE_2D, id_texturas[id]);
    	glBegin(GL_QUADS);
	    glColor3f(1.0, 1.0, 1.0);
	    glTexCoord2i(0, 0); glVertex2i(-1, -1);
	    glTexCoord2i(1, 0); glVertex2i(1, -1);
	    glTexCoord2i(1, 1); glVertex2i(1, 1);
	    glTexCoord2i(0, 1); glVertex2i(-1, 1);
	    glEnd();
	    glEnable(GL_DEPTH_TEST);
	    glEnable(GL_LIGHTING);
	    glDepthMask(GL_TRUE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}


void desenhaVeiculo(float i, float j, int R, int G, int B){
	//corpo
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, id_texturas[4]);
		glColor3f(R, G, B);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (0.6, 1.5, 1);
		draw_object_smooth();
		glRotatef(0.0, 0.0 , 0.0 , 1.0);
		//lado direito
		glPushMatrix();
			glColor3f(0, 0, 0);
			glTranslatef(0.55, 0, 0);
			glScalef (0.3, 0.8, 0.6);
			draw_object_smooth();
		glPopMatrix();
		//lado esquerda.
		glPushMatrix();
			glColor3f(0, 0, 0);
			glTranslatef(-0.55, 0, 0);
			glScalef (0.3, 0.8, 0.6);
			draw_object_smooth();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
    glPopMatrix();
}

void desenhaVidaVeiculo(float i, float j, int R, int G, int B){
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, id_texturas[4]);
		glColor3f(R, G, B);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (0.5, 0.8, tam_veiculo);
		draw_object_smooth();
		glRotatef(0.0, 0.0 , 0.0 , 1.0);
		
		glPushMatrix();
			glColor3f(0, 0, 0);
			glTranslatef(0.55, 0, 0);
			glScalef (0.3, 0.7, 0.6);
			draw_object_smooth();
		glPopMatrix();

		glPushMatrix();
			glColor3f(0, 0, 0);
			glTranslatef(-0.55, 0, 0);
			glScalef (0.3, 0.7, 0.6);
			draw_object_smooth();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);

    glPopMatrix();
}
 	

void criaMapa(Jogador jogador, Veiculo veiculo1, Veiculo veiculo2, Veiculo veiculo3, Veiculo veiculo4, Veiculo veiculo5, Veiculo veiculo6){
	GLfloat w = 1.0, h = 1.0, x = 0, y = 0; 
	for (int i = 0; i < tamMapa_i; i++){
		for (int j = 0; j < tamMapa_j; j++){
			if (mapa[i][j] == 0.0){
				//cria o chao.
				glBindTexture(GL_TEXTURE_2D, id_texturas[2]);
				chao(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 1.0){
				//cria linhas divisao da pista.
				glBindTexture(GL_TEXTURE_2D, id_texturas[0]);
				chao2(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 2.0){
				//cria Paredes laterais.
				glBindTexture(GL_TEXTURE_2D, id_texturas[1]);
				parede(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 3.0){
				//cria Parede 3.
				glBindTexture(GL_TEXTURE_2D, id_texturas[3]);
				Parede_Destroi_Veiculos(i, j, x, y, h, w);
			}
		}
	}
	
	
	//Se o jogador ou veiculo vivo, cria jogador ou veiculo.
	if(jogador.vivo){
		desenhaVeiculo(jogador.I, jogador.J, jogador.R, jogador.G, jogador.B);
	}
	
	if(veiculo1.vivo){
		desenhaVeiculo(veiculo1.I, veiculo1.J, veiculo1.R, veiculo1.G, veiculo1.B);
	}
	
	if(veiculo2.vivo){
		desenhaVeiculo(veiculo2.I, veiculo2.J, veiculo2.R, veiculo2.G, veiculo2.B);
	}
	
	if(veiculo3.vivo){
		desenhaVeiculo(veiculo3.I, veiculo3.J, veiculo3.R, veiculo3.G, veiculo3.B);
	}
	
	if(veiculo4.vivo){
		desenhaVeiculo(veiculo4.I, veiculo4.J, veiculo4.R, veiculo4.G, veiculo4.B);
	}

	if(veiculo5.vivo){
		desenhaVeiculo(veiculo5.I, veiculo5.J, veiculo5.R, veiculo5.G, veiculo5.B);
	}

	if(veiculo6.vivo){
		desenhaVeiculo(veiculo6.I, veiculo6.J, veiculo6.R, veiculo6.G, veiculo6.B);
	}

}
#endif