#include "agentsMovement.h"

using namespace std;

void *showMap(void *arg)
{
    while (duracionSimulacion > 0)
    {
        system("clear");
        printParedes();
        usleep(500000);
        //sleep(1);
    }
    return NULL;
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

    if (agent->tipo == 1) //Por el momento solo se mueven los agentes tipo1
        moveTipo1(x, y);
    if (agent->tipo == 2)
        moveTipo2(x, y);
    if (agent->tipo == 3)
        moveTipo3(x, y);
    if (agent->tipo == 4)
        moveTipo4(x, y);
    return NULL;
}
 
void* iniciarSimulationCounter(void *arg){
    int counter = 0;
    while(duracionSimulacion > 0){
        if (counter == inicioVacunacion)
            pthread_cond_signal(&condVacunacion);
        counter++;
        sleep(1);
        duracionSimulacion--;
    }
    return NULL;
}

void startThreads()
{
    pthread_t viewThread; //thread encargado de mostrar en pantalla
    pthread_t simulacionTimerThread;
    pthread_t vacunacion;
    threads = new pthread_t[agentesCount];
    pthread_create(&simulacionTimerThread, NULL, iniciarSimulationCounter, NULL);
    pthread_create(&viewThread, NULL, showMap, NULL);
    pthread_create(&vacunacion, NULL, iniciarProduccion, NULL);
    int counter = 0;
    for (int i = 0; i < agentesCount; i++)
    {
        pthread_create(&threads[counter], NULL, placeAgent, &agentes[i]);
        counter++;
    }
    pthread_join(simulacionTimerThread, NULL);
    pthread_join(vacunacion, NULL);
    pthread_join(viewThread, NULL);
    for (int i = 0; i < counter; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

int main(int argc, char const *argv[])
{
    int duracion = atoi(argv[1]);
    duracionSimulacion = duracion;
    pthread_cond_init(&condVacunacion, NULL);
    pthread_mutex_init(&mutexVacunas, NULL);
    srand((unsigned)time(0));
    readMapa();
    readCodeVid();
    readAgents();
    readVacunas();
    startThreads();


    return 0;
}