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
    int dirX;
    int dirY;
    string dirLabel;
};

struct campoMapa
{ //cada cuadrado en el mapa de la matriz será un struct campoMapa
    int esPared;
    map<long, struct agente>* agentes; //Vector donde se guardan los distintos agentes que se guardan los distintos agentes en un momento determinado
};


//configuracion de mapa
int tamañoMapa[2] = {-1, -1}; //[width, height]
int cantidadParedes = 0;
vector<tuple<int, int, int, int>> paredesArray;
struct campoMapa** mapa;//mapa
pthread_mutex_t mapaMutex;


//configurarion de code-vid
float probabilidadMorir;
int deathCount;
int healCount;
int totalAgentes;
vector<vector<float>> tasaContagio;
int reinfeccion;

//configuracion de agentes
vector<struct agente> agentes;
int cantidadGrupos;
int agentesCount = 0;

//configuracion de threads
pthread_t *threads;


//Movimiento de agentes
vector<int> DOWN = {1, 0};
vector<int> UP = {-1, 0};
vector<int> RIGHT = {0, 1};
vector<int> LEFT = {0, -1};
vector<int> UP_LEFT = {-1, -1};
vector<int> UP_RIGHT = {-1, 1};
vector<int> DOWN_LEFT = {1, -1};
vector<int> DOWN_RIGHT = {1, 1};

std::map<string, vector<int>> mapDirecciones = {
    {"DOWN", DOWN},
    {"UP", UP},
    {"RIGHT", RIGHT},
    {"LEFT", LEFT},
    {"UP_LEFT", UP_LEFT},
    {"UP_RIGHT", UP_RIGHT},
    {"DOWN_LEFT", DOWN_LEFT},
    {"DOWN_RIGHT", DOWN_RIGHT}};
