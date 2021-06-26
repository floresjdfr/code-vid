#include "configReader.h"
#include "unistd.h"
#include <time.h>
using namespace std;

void *showMap(void *arg){
    while(1){
        system("clear");
        printParedes();
        sleep(1);
    }
}

void *placeAgent(void *arg)
{
    struct agente *agent = (struct agente *)arg;
coordenadas:
    int x = rand() % tamañoMapa[0];
    int y = rand() % tamañoMapa[1];
    if (mapa[x][y].esPared)
        goto coordenadas;
    mapa[x][y].agentes.push_back(*agent);
    return NULL;
}

void startThreads()
{
    pthread_t viewThread;//thread encargado de mostrar en pantalla
    
    threads = new pthread_t[agentesCount];
    pthread_create(&viewThread, NULL, showMap, NULL);
    int threadCounter = 0;
    for (auto &group : *agentes)
    {
        for (auto &agente : group)
        {
            pthread_create(&threads[threadCounter], NULL, placeAgent, &agente);
            threadCounter++;
        }
    }
    
    for (int i = 0; i < threadCounter; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_join(viewThread, NULL);
}

int main(int argc, char const *argv[])
{
    srand((unsigned)time(0));
    readMapa();
    readCodeVid();
    readAgents();
    startThreads();

    return 0;
}