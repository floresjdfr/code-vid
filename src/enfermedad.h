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

int enfermarSiVacunado()
{
    int randomN = rand() % 100 + 1;
    if (randomN > porcentajeEficiencia)
        return 1;
    return 0;
}

int enfermar(struct agente *i, struct agente *j)
{
    float probabilidad = tasaContagio[i->tipo - 1][j->tipo - 1];
    int randomN = rand() % 100 + 1;
    if (randomN < (int)probabilidad)
    {
        j->estado = 'e';
        if (morir())
            j->deathCountDown = deathCount;
        else
            j->healCountDown = healCount;
        return 1;
    }
    return 0;
}

void transmitirEnfermedad(int x, int y, struct agente *agent)
{
    if (mapa[x][y].agentes->size() > 0)
    {
        struct agente *inMap = &(*mapa[x][y].agentes->rbegin()).second;
        if (agent->estado == 'e')
        {

            if (inMap->estado == 's')
            {
                enfermar(agent, inMap);
                return;
            }
            if (inMap->estado == 'c')
            {
                if (reinfeccion)
                    enfermar(agent, inMap);
                return;
            }
            if (inMap->estado == 'v')
            {
                if (enfermarSiVacunado)
                    enfermar(agent, inMap);
                return;
            }
            return;
        }
        if (agent->estado == 's')
        {
            if (inMap->estado == 'e')
            {
                enfermar(inMap, agent);
                return;
            }
            return;
        }
        if (agent->estado == 'c')
        {
            if (reinfeccion)
            {
                if (inMap->estado == 'e')
                {
                    enfermar(inMap, agent);
                    return;
                }
            }
            return;
        }
        if (agent->estado == 'v')
            if (inMap->estado == 'e')
                if (enfermarSiVacunado)
                    enfermar(inMap, agent);
    }
}

void iniciarEnfermedad(struct agente *agent)
{
    if (agent->estado == 'e')
    {
        if (morir())
        {
            agent->deathCountDown = deathCount;
            return;
        }
        agent->healCountDown = healCount;
    }
}
