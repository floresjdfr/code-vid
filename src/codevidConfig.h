#include "bits/stdc++.h"
#include <pthread.h>
using namespace std;


struct agente{
    int tipo;
    char estado;
    int velocidadMaxima;
    int velocidadMinima;
    int deathCountDown;
    int healCountDown;
    int reContagio;//En caso que haya enfermado no podra volver a enfermar
    int posX;
    int posY;
};

struct campoMapa
{ //cada cuadrado en el mapa de la matriz será un struct campoMapa
    int esPared;
    vector<struct agente> agentes; //Vector donde se guardan los distintos agentes que se guardan los distintos agentes en un momento determinado
};


//configuracion de mapa
int tamañoMapa[2] = {-1, -1}; //[width, height]
int cantidadParedes = 0;
vector<tuple<int, int, int, int>> paredesArray;
struct campoMapa** mapa;//mapa


//configurarion de code-vid
float probabilidadMorir;
int deathCount;
int healCount;
int totalAgentes;
vector<vector<float>> tasaContagio;
int reinfeccion;

//configuracion de agentes
vector<vector<struct agente>>* agentes;
int cantidadGrupos;
int agentesCount = 0;

//configuracion de threads
pthread_t *threads;

