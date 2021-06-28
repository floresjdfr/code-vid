#include "agentsMovement.h"


using namespace std;

void *showMap(void *arg)
{
    while (1)
    {
        system("clear");
        printParedes();
        usleep(500000);
        //sleep(1);
    }
}

void *placeAgent(void *arg)
{
    struct agente *agent = (struct agente *)arg;
    //Obtiene posicion random
    int x = rand() % tamañoMapa[0];
    int y = rand() % tamañoMapa[1];
    while (isWall(x, y) || isOutMap(x, y))
    {
        x = rand() % tamañoMapa[0];
        y = rand() % tamañoMapa[1];
    }
    //Obtiene direccion random
    pair<string, vector<int>> direccion = getRandomDirection();

    //Guarda valores en agente
    agent->posX = x;
    agent->posY = y;
    agent->dirX = get<1>(direccion)[0];
    agent->dirY = get<1>(direccion)[1];
    agent->dirLabel = get<0>(direccion);

    //Inserta agente en mapa/
    mapa[x][y].agentes->insert(pair<long, struct agente>(pthread_self(), *agent));
    
    if (agent->tipo == 1)//Por el momento solo se mueven los agentes tipo1
        moveTipo1(x, y);
    if (agent->tipo == 2)
        moveTipo2(x, y);
    return NULL;
}

void startThreads()
{
    pthread_t viewThread; //thread encargado de mostrar en pantalla
  
    threads = new pthread_t[agentesCount];
    pthread_create(&viewThread, NULL, showMap, NULL);
    int counter = 0;
    for (int i = 0; i < agentesCount; i++)
    {
        pthread_create(&threads[counter], NULL, placeAgent, &agentes[i]);
        counter++;
    }
    pthread_join(viewThread, NULL);
    for (int i = 0; i < counter; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
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