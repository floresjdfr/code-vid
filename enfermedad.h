#include "configReader.h"
#include <time.h>
#include "unistd.h"

int morir()
{
    float probabilidad = probabilidadMorir;
    int randomN = rand() % 100 + 1;
    if (randomN < (int)probabilidad)
        return 1;
    return 0;
}

int enfermar(struct agente *i, struct agente *j)
{
    float probabilidad = tasaContagio[i->tipo][j->tipo];
    int randomN = rand() % 100 + 1;
    if (randomN < (int)probabilidad)
    {
        j->estado = 'e';
        if (morir())
            j->deathCountDown = deathCount;
        j->healCountDown = healCount;
        return 1;
    }
    return 0;
}

void transmitirEnfermedad(int x, int y, struct agente *agent)
{
    if (mapa[x][y].agentes->size() > 0)
    {
        if (agent->estado == 'e')
        {
            struct agente * inMap = &(*mapa[x][y].agentes->rbegin()).second;
            if (inMap->estado == 'e')
                return;
            if (inMap->estado == 's')
            {
                enfermar(agent, inMap);
                return;
            }
        }
        else
        {
            struct agente * inMap = &(*mapa[x][y].agentes->rbegin()).second;
            if (inMap->estado == 's')
                return;
            if (inMap->estado == 'e')
            {
                enfermar(inMap, agent);
                return;
            }
        }
    }
}
