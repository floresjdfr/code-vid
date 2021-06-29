#include "enfermedad.h"

void *iniciarProduccion(void *arg)
{
    pthread_cond_wait(&condVacunacion, &mutexVacunas);
    while (duracionSimulacion > 0)
    {
        for (int i = 0; i < numeroVacunas; i++)
            vacunas.push_back(1);
        sleep(frecuenciaCreacion);
    }
    return NULL;
}

void aplicarVacuna(struct agente *agent)
{
    if (vacunas.size() > 0)
    {
        if (agent->estado == 'e' || agent->estado == 'v')
            return;
        agent->vacunado = 1;
        agent->vacunaCountDown = duracionHacerEfecto;
    }
}

void reducirVacunaCountDown(struct agente* agent, int velocidad){
    if (agent->vacunado && agent->estado != 'v'){
        agent->vacunaCountDown -= velocidad;
        if (agent->vacunaCountDown < 1){
            agent->estado = 'v';
            agent->vacunaCountDown = -1000;
        }
            

    }
}