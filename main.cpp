
// Bibliotecas utilizadas pelo OpenGL
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif
                
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <mmsystem.h>
#include "mapa.h"
#include "jogador.h"
#include "veiculos.h"
#include "SomEfeitos.h"
#include "vidas.h"
#include <sstream>
using std::stringstream;
#include <string>
using std::string;
       
void init(void);
void keyboard (unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);
bool Colisao(float jogador_I, float jogador_J, float tam_veiculo, float cubo_I, float cubo_J, float tam_cubo);
void textura();
//void AcaoVeiculo_Atingida(Jogador *jogador, Veiculo *veiculo);
void Colisao_Jogador_Parede(unsigned char key, Jogador *jogador);


//controlar estatus do jogo
bool tela_vitoria = false;
bool tela_derrota = false;
bool tela_inicio = true;

static int tela_derrota_execucao = 0;
static int tela_vitoria_execucao = 0;

// Variaveis Globais
int h, w = 0;
float speed = 0.1;

int respaw_veiculos = 199; //Quantas vezes adversarios podem respawnar.
int vidasJogador = 4; //vidas

//Veiculos no mapa, I e J indices na matriz
//I, J, I_de respaw, J_de respaw, Velocidade, R, G, B, vivo.}
Veiculo veiculo1 = {20, 9, 20, 9, speed, 1.0, 0.0, 1.0, true};
Veiculo veiculo2 = {22, 7, 22, 7, speed, 1.0, 1.0, 0.0, true};
Veiculo veiculo3 = {24, 5, 24, 5, speed, 0.0, 1.0, 1.0, true};
Veiculo veiculo4 = {26, 11, 26, 11, speed, 0.0, 1.0, 0.0, true};
Veiculo veiculo5 = {28, 13, 28, 13, speed, 1.0, 1.0, 0.0, true};
Veiculo veiculo6 = {30, 12, 30, 12, speed, 1.0, 0.0, 1.0, true};

//controla movimentos dos Veiculos
int mov_veiculo1, mov_veiculo2, mov_veiculo3, mov_veiculo4, mov_veiculo5, mov_veiculo6; 

// Jogador no mapa, I e J indices na matriz
//I, J, I_de respaw, J_de respaw, Velocidade, R, G, B, Vidas, Vivo.}
Jogador jogador = {2, 9, 2, 9, speed, 1.0, 1.0, 1.0, vidasJogador, true};
     

void init(void){
  glClearColor (0.4, 0.4, 0.4, 0.0);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST); // Habilita o algoritmo Z-Buffer
  textura();
  // Ativa o modelo de sombreamento de Gouraud.
  glShadeModel(GL_SMOOTH);
}

void display(){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa o Buffer de Cores
    glLoadIdentity();
    if (tela_inicio == false && tela_derrota == false && tela_vitoria == false){
		playSons();
	    background();
	    criaMapa(jogador, veiculo1, veiculo2, veiculo3, veiculo4, veiculo5, veiculo6);
	    desenhaVidasJogador(jogador.vida);
	}
	else if (tela_inicio){
		tela_instrucoes(6);
	} 
	else if(tela_derrota){
		tela_derrota_execucao++;
		if(tela_derrota_execucao == 1){
			playAudioDerrota();
		}
		tela_instrucoes(7);
	}
	else if(tela_vitoria){
		tela_vitoria_execucao++;
		Audio_Vitoria = true;
		if(tela_vitoria_execucao == 1){
			playAudioVitoria();
		}
		tela_instrucoes(8);
	}
    glutSwapBuffers();
}

void reshape (int w, int h){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    gluPerspective(45, (float)w/(float)h, 1.0, 100.0);
	// x, y, z da camera
    gluLookAt(9.0,-5.0,14.0, 	
			  9.0,9.3,0.0, 
			  0.0,1.0,0.0);
    glMatrixMode (GL_MODELVIEW);
}

//controles
void keyboard (unsigned char key, int x, int y){
		switch(key){
		  if(tela_derrota == false && tela_vitoria == false){
			case 'd':case 'D':
				jogador.J += jogador.velocidade;
				glutPostRedisplay();
				break;
			case 'a':case 'A':
				jogador.J -= jogador.velocidade;
				glutPostRedisplay();
		  }
				break;
			case 13:
				if(tela_inicio){
					tela_inicio = false;
				} else if(tela_derrota){
					tela_derrota = false;
					exit(EXIT_SUCCESS);
				}
			case 27:
				if(tela_inicio || tela_derrota || tela_vitoria){
				   	exit(EXIT_SUCCESS); 
				}
				break;
			default:
				break;
		}
		Colisao_Jogador_Parede(key, &jogador);
	glutPostRedisplay();
}
void specialKeyboard(int key, int x, int y){
	if(tela_derrota == false && tela_vitoria == false){
		switch(key){
			
			case GLUT_KEY_UP:
				if(tela_derrota == false && tela_vitoria == false){
					if(speed < 0.5){
						speed+=0.1;
						
						printf("Velocidade: %.2f\n",speed);// mostra no console a velocidade
						Jogador *jog = &jogador;
						jog->velocidade = speed;
						
						Veiculo *veiculoA = &veiculo1;
						veiculoA->velocidade = speed;
						Veiculo *veiculoB = &veiculo2;
						veiculoB->velocidade = speed;
						Veiculo *veiculoC = &veiculo3;
						veiculoC->velocidade = speed;
						Veiculo *veiculoD = &veiculo4;
						veiculoD->velocidade = speed;
						Veiculo *veiculoE = &veiculo5;
						veiculoE->velocidade = speed;
						Veiculo *veiculoF = &veiculo6;
						veiculoF->velocidade = speed;
					}
				}
				break;
			case GLUT_KEY_DOWN:
				if(tela_derrota == false && tela_vitoria == false){
					 speed = fmax(speed - 0.1, 0.1);
					 
					 printf("Velocidade: %.2f\n",speed);// mostra no console a velocidade
					 Jogador *jog = &jogador;
					 jog->velocidade = speed;
					
					 Veiculo *veiculoA = &veiculo1;
					 veiculoA->velocidade = speed;
					 Veiculo *veiculoB = &veiculo2;
					 veiculoB->velocidade = speed;
					 Veiculo *veiculoC = &veiculo3;
					 veiculoC->velocidade = speed;
				 	 Veiculo *veiculoD = &veiculo4;
					 veiculoD->velocidade = speed;
					 Veiculo *veiculoE = &veiculo5;
					 veiculoE->velocidade = speed;
					 Veiculo *veiculoF = &veiculo6;
					 veiculoF->velocidade = speed;
				}
				break;
			
			default:
				break;
		}
		glutPostRedisplay();
	}
}


//controle de colisoes

void Colisao_Jogador_Parede(unsigned char key, Jogador *jogador){
	for(int i = 0; i < tamMapa_i; i++){
		for(int j = 0; j < tamMapa_j; j++){
			if(Colisao(jogador->I, jogador->J, tam_veiculo, i * tam_cubo, j * tam_cubo, tam_cubo) == true){				
				//Colide com os cubos.
					if(mapa[i][j] == 2){
						if((key=='a')||(key=='A')) jogador->J += jogador->velocidade;
				    	else if((key=='d')||(key=='D')) jogador->J -= jogador->velocidade;
					}
			}
		}
	}
}



bool Colisao(float jogador_I, float jogador_J, float tam_veiculo, float cubo_I, float cubo_J, float tam_cubo){
	if(jogador_J + tam_veiculo <= cubo_J){
		return false;
	} 
	else if(jogador_J >= cubo_J + tam_cubo){
		return false;
	} 
	else if(jogador_I + tam_veiculo <= cubo_I){
		return false;
	} 
	else if(jogador_I >= cubo_I + tam_cubo){
		return false;
	} 

	return true;
}


void Colisao_Veiculos_Adversarios(int movimentoVeiculo, Veiculo *veiculoAtual, Jogador *jogador){
	for(int i = 0; i < tamMapa_i; i++){
		for(int j = 0; j < tamMapa_j; j++){
			if (Colisao(veiculoAtual->I, veiculoAtual->J, tam_veiculo, i * tam_cubo, j * tam_cubo, tam_cubo) == true){
				if(mapa[i][j] == 3){
					if(movimentoVeiculo==3){
						if(respaw_veiculos > 0){
							veiculoAtual->I = veiculoAtual->I_Origem;
							veiculoAtual->J = veiculoAtual->J_Origem;
							respaw_veiculos--;
						}
						else{
							veiculoAtual->I = 99;
							veiculoAtual->J = 99;
							veiculoAtual->vivo = false;	
						}
					}
				}
			}
			else 
			if(Colisao(veiculoAtual->I, veiculoAtual->J, tam_veiculo, jogador->I * 1.0, jogador->J * 1.0, 1.0) == true){
				Audio_Impacto = true;
				printf("Vida: %d\n", jogador->vida);
				if(jogador->vida > 0){
						jogador->vida--;
						jogador->I = jogador->I_Origem;
						jogador->J = jogador->J_Origem;
						veiculoAtual->I = veiculoAtual->I_Origem;
						veiculoAtual->J = veiculoAtual->J_Origem;
						respaw_veiculos--;
				}
				else{
					   	jogador->I = 99;
						jogador->J = 99;
						jogador->vivo = false;
						tela_derrota = true;
						Audio_Derrota = true;
				}
			}
			glutPostRedisplay();
		}
	}
}


void MovimentoVeiculos(Veiculo *veiculoAtual, Jogador *jogador, int movimento){
	switch(movimento){
		case 3:
			veiculoAtual->I -= veiculoAtual->velocidade;
			glutPostRedisplay();
			break;
		
		default:
			break;
	}
	Colisao_Veiculos_Adversarios(movimento, veiculoAtual, jogador);
}

void Movimento(int v){ //define a direçao dos adversarios
	mov_veiculo1 = 3;
	mov_veiculo2 = 3;
	mov_veiculo3 = 3;
	mov_veiculo4 = 3;
	mov_veiculo5 = 3;
	mov_veiculo6 = 3;
	
	glutPostRedisplay();
	glutTimerFunc(2000, Movimento, 0);
}

void Aguarda_Movimento(int v){
	if (tela_inicio == false){
		MovimentoVeiculos(&veiculo1, &jogador, mov_veiculo1);
		
		MovimentoVeiculos(&veiculo2, &jogador, mov_veiculo2);
		
		MovimentoVeiculos(&veiculo3, &jogador, mov_veiculo3);
		
		MovimentoVeiculos(&veiculo4, &jogador, mov_veiculo4);
		
		MovimentoVeiculos(&veiculo5, &jogador, mov_veiculo5);
		
		MovimentoVeiculos(&veiculo6, &jogador, mov_veiculo6);
		
	}
	glutPostRedisplay();
	glutTimerFunc(16, Aguarda_Movimento, 0);
}


void Verifica_Vitoria(int value){
	if(jogador.vivo && (veiculo1.vivo == false && veiculo2.vivo == false && veiculo3.vivo == false && veiculo4.vivo == false && veiculo5.vivo == false && veiculo6.vivo == false)){
		tela_vitoria = true;
	}
	glutPostRedisplay();
	glutTimerFunc(16, Verifica_Vitoria, 0);
}


int main(int argc, char** argv){
	glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1366,768);
    glutInitWindowPosition(250,150); 
    glutCreateWindow ("Fantasmao_Simulator");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    
    glEnable(GL_LIGHT0); //Ativa a Luz 0 (padrao na cor branca)
    glEnable(GL_COLOR_MATERIAL); //objetos sao iluminados com a cor definida no glColor.

     
    glutTimerFunc(0, Aguarda_Movimento, 0);
    glutTimerFunc(0, Verifica_Vitoria, 0);
    glutTimerFunc(0, Movimento, 0);
    init();
    glutMainLoop();
    
	return EXIT_SUCCESS;
}