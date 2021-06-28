#include "vacunar.h"
using namespace std;
#define MAX_TIPO_2 7

//Funcion encargada de verificar si el punto x, y se encuentra dentro del mapa
//Retorna 1 si la posicion 'i' esta fuera del mapa
//Retorna 2 si la posicion 'j' esta fuera del mapa
//Retorna 3 si ambas estan fuera del mapa
//Retorna 0 si no esta fuera del mapa
int isOutMap(int x, int y)
{
    if ((x < 0 | x >= tamañoMapa[1]) && !(y < 0 | y >= tamañoMapa[0]))
        return 1;
    if (!(x < 0 | x >= tamañoMapa[1]) && (y < 0 | y >= tamañoMapa[0]))
        return 2;
    if ((x < 0 | x >= tamañoMapa[1]) && (y < 0 | y >= tamañoMapa[0]))
        return 3;
    return 0;
}

//Funcion que verifica si el punto x, y es una pared
//Retorna 0 si no es pared o 1 si es o esta fuera del mapa
int isWall(int x, int y)
{
    if (!isOutMap(x, y))
        return (mapa[x][y].esPared);
    return 1;
}

//Funcion utilizada para obtener una direccion random a la hora de poner los agentes en el mapa al iniciar la simulacion
//Returna un pair el cual es el identificador de la direccion y seguido de un vector director el cual indica hacia donde dirigiste.
pair<string, vector<int>> getRandomDirection()
{
    int option = rand() % 8 + 1;
    //option = option % 10;
    switch (option)
    {
    case 1:
    {
        pair<string, vector<int>> direccion("DOWN", mapDirecciones["DOWN"]);
        return direccion;
        break;
    }
    case 2:
    {
        pair<string, vector<int>> direccion("UP", mapDirecciones["UP"]);
        return direccion;
        break;
    }
    case 3:
    {
        pair<string, vector<int>> direccion("RIGHT", mapDirecciones["RIGHT"]);
        return direccion;
        break;
    }
    case 4:
    {
        pair<string, vector<int>> direccion("LEFT", mapDirecciones["LEFT"]);
        return direccion;
        break;
    }
    case 5:
    {
        pair<string, vector<int>> direccion("UP_LEFT", mapDirecciones["UP_LEFT"]);
        return direccion;
        break;
    }
    case 6:
    {
        pair<string, vector<int>> direccion("UP_RIGHT", mapDirecciones["UP_RIGHT"]);
        return direccion;
        break;
    }
    case 7:
    {
        pair<string, vector<int>> direccion("DOWN_LEFT", mapDirecciones["DOWN_LEFT"]);
        return direccion;
        break;
    }
    case 8:
    {
        pair<string, vector<int>> direccion("DOWN_RIGHT", mapDirecciones["DOWN_RIGHT"]);
        return direccion;
        break;
    }
    default:
    {
        break;
    }
    }
    return pair<string, vector<int>>("UNKNOWN", *(new vector<int>));
}

//Funcion encargada de cambiar la direccion de un punto x, y
//Recibe como argumentos el punto x, y. El siguiente punto x, y hacia donde se pretende mover y un string con el 'label' identificando el movimiento del agente
//Returna la futura direccion hacia donde el agente se movera
string changeDirection(int x, int y, int nextX, int nextY, string opcion)
{
    if (opcion == "UP")
    {
        return "DOWN";
    }
    if (opcion == "DOWN")
    {
        return "UP";
    }
    if (opcion == "RIGHT")
    {
        return "LEFT";
    }
    if (opcion == "LEFT")
    {
        return "RIGHT";
    }
    if (opcion == "UP_LEFT")
    {
        if (int n = isOutMap(nextX, nextY)) //En caso que siguiente salga del mapa
        {
            if (n == 2)
            {
                return "UP_RIGHT";
            }
            if (n == 1)
            {
                return "DOWN_LEFT";
            }
            return "DOWN_RIGHT";
        }
        else //En caso que siguiente sea pared
        {
            //Toma las dos opciones que tiene para revotar y verifica en cual de las dos no hay pared
            vector<int> direccion1 = mapDirecciones["UP_RIGHT"];
            int nextX1 = x + direccion1[0];
            int nextY1 = y + direccion1[0];

            vector<int> direccion2 = mapDirecciones["DOWN_LEFT"];
            int nextX2 = x + direccion2[0];
            int nextY2 = y + direccion2[0];

            if (isWall(nextX1, nextY1) && !isWall(nextX2, nextY2))
                return "DOWN_LEFT";
            if (!isWall(nextX1, nextY1) && isWall(nextX2, nextY2))
                return "UP_RIGHT";
            return "DOWN_RIGHT";
        }
    }
    if (opcion == "UP_RIGHT")
    {
        if (int n = isOutMap(nextX, nextY)) //En caso que salga del mapa
        {
            if (n == 2)
            {
                return "UP_LEFT";
            }
            if (n == 1)
            {
                return "DOWN_RIGHT";
            }
            return "DOWN_LEFT";
        }
        else //En caso que siguiente sea pared
        {
            //Toma las dos opciones que tiene para revotar y verifica en cual de las dos no hay pared
            vector<int> direccion1 = mapDirecciones["DOWN_RIGHT"];
            int nextX1 = x + direccion1[0];
            int nextY1 = y + direccion1[0];

            vector<int> direccion2 = mapDirecciones["UP_LEFT"];
            int nextX2 = x + direccion2[0];
            int nextY2 = y + direccion2[0];

            if (isWall(nextX1, nextY1) && !isWall(nextX2, nextY2))
                return "UP_LEFT";
            if (!isWall(nextX1, nextY1) && isWall(nextX2, nextY2))
                return "DOWN_RIGHT";
            return "DOWN_LEFT";
        }
    }
    if (opcion == "DOWN_LEFT")
    {
        if (int n = isOutMap(nextX, nextY)) //En caso que salga del mapa
        {
            if (n == 2)
            {
                return "DOWN_RIGHT";
            }
            if (n == 1)
            {
                return "UP_LEFT";
            }
            return "UP_RIGHT";
        }
        else //En caso que siguiente sea pared
        {
            //Toma las dos opciones que tiene para revotar y verifica en cual de las dos no hay pared
            vector<int> direccion1 = mapDirecciones["UP_LEFT"];
            int nextX1 = x + direccion1[0];
            int nextY1 = y + direccion1[0];

            vector<int> direccion2 = mapDirecciones["DOWN_RIGHT"];
            int nextX2 = x + direccion2[0];
            int nextY2 = y + direccion2[0];

            if (isWall(nextX1, nextY1) && !isWall(nextX2, nextY2))
                return "DOWN_RIGHT";
            if (!isWall(nextX1, nextY1) && isWall(nextX2, nextY2))
                return "UP_LEFT";
            return "UP_RIGHT";
        }
    }
    if (opcion == "DOWN_RIGHT")
    {
        if (int n = isOutMap(nextX, nextY)) //En caso que salga del mapa
        {
            if (n == 2)
            {
                return "DOWN_LEFT";
            }
            if (n == 1)
            {
                return "UP_RIGHT";
            }
            return "UP_LEFT";
        }
        else //En caso que siguiente sea pared
        {
            //Toma las dos opciones que tiene para revotar y verifica en cual de las dos no hay pared
            vector<int> direccion1 = mapDirecciones["UP_RIGHT"];
            int nextX1 = x + direccion1[0];
            int nextY1 = y + direccion1[0];

            vector<int> direccion2 = mapDirecciones["DOWN_LEFT"];
            int nextX2 = x + direccion2[0];
            int nextY2 = y + direccion2[0];

            if (isWall(nextX1, nextY1) && !isWall(nextX2, nextY2))
                return "DOWN_LEFT";
            if (!isWall(nextX1, nextY1) && isWall(nextX2, nextY2))
                return "UP_RIGHT";
            return "UP_LEFT";
        }
    }
    return "";
}

int getRandomVelocity(int maxV, int minV)
{
    return rand() % (maxV - minV + 1) + minV;
}

int kill(struct agente *agent, int velocidad)
{
    if (agent->deathCountDown != -1000 && agent->estado == 'e')
    {
        if (agent->deathCountDown > -1000 && agent->deathCountDown < 0)
        {
            agent->vivo = 0;
            return 1; //Muere
        }
        agent->deathCountDown -= velocidad;
        return 0; //Aun no muere
    }
    return 0; //Aun no muere
}
int trustGod(struct agente *agent, int velocidad) //Tiempo para curar
{
    if (agent->healCountDown != -1000)
    {
        if (agent->healCountDown > -1000 && agent->healCountDown < 0)
        {
            agent->estado = 'c';
            agent->healCountDown = -1000;
            return 1; //Se curo gracias a dios
        }
        agent->healCountDown -= velocidad;
        return 0; //Aun no
    }
    return 0; //Aun no
}

//***************************************  Funciones encargadas de mover el agente TIPO 1

void moveTipo1(int x, int y) //Posicion actual del agente
{
    struct agente *mapAgent = &(*mapa[x][y].agentes)[pthread_self()];
    iniciarEnfermedad(mapAgent);
    while (mapAgent->vivo)
    {
        mapAgent = &(*mapa[x][y].agentes)[pthread_self()];
        if (duracionSimulacion == 0)
            pthread_exit(0);
        int velocidad = getRandomVelocity(mapAgent->velocidadMaxima, mapAgent->velocidadMinima);
        aplicarVacuna(mapAgent);
        reducirVacunaCountDown(mapAgent, velocidad);
        if (kill(mapAgent, velocidad)) //matar si esta enfermo y dios decidio matarlo
            break;
        trustGod(mapAgent, velocidad); //curar si asi lo decidio dios
        sleep(velocidad);

        int nextX = mapAgent->posX + mapAgent->dirX;
        int nextY = mapAgent->posY + mapAgent->dirY;

        if (isOutMap(nextX, nextY) || isWall(nextX, nextY))
        {
            string newDirection = changeDirection(x, y, nextX, nextY, mapAgent->dirLabel);
            struct agente cpy = *mapAgent;
            cpy.dirLabel = newDirection;
            cpy.dirX = mapDirecciones[newDirection][0];
            cpy.dirY = mapDirecciones[newDirection][1];

            pthread_mutex_lock(&mapaMutex);
            mapa[x][y].agentes->erase(pthread_self());
            transmitirEnfermedad(x, y, &cpy);
            mapa[x][y].agentes->insert(pair<long, struct agente>(pthread_self(), cpy));
            pthread_mutex_unlock(&mapaMutex);
            continue;
        }
        //se guarda copia del agente
        struct agente cpy = *mapAgent;
        cpy.posX = nextX;
        cpy.posY = nextY;

        //Se borra el agente del actual cuadrante del mapa
        pthread_mutex_lock(&mapaMutex);
        mapa[x][y].agentes->erase(pthread_self());

        //Se inserta el nuevo agente en el nuevo cuadrante
        x = nextX;
        y = nextY;
        transmitirEnfermedad(x, y, &cpy);
        mapa[x][y].agentes->insert(pair<long, struct agente>(pthread_self(), cpy));
        pthread_mutex_unlock(&mapaMutex);
    }
    mapa[x][y].agentes->erase(pthread_self());
}

//***************************************  Funciones encargadas de mover el agente TIPO 2

//Funcion que crea una ruta de puntos aleatorios iniciando en x, y
//Returna un vector con pares de puntos
vector<pair<int, int>> crearRuta(int x, int y)
{
    vector<pair<int, int>> ruta;
    ruta.push_back(pair<int, int>(x, y));
    for (int i = 0; i < MAX_TIPO_2 - 1; i++)
    {
        int x = rand() % tamañoMapa[0];
        int y = rand() % tamañoMapa[1];
        while (isWall(x, y) || isOutMap(x, y))
        {
            x = rand() % tamañoMapa[0];
            y = rand() % tamañoMapa[1];
        }
        pair<int, int> tmp;
        tmp.first = x;
        tmp.second = y;
        ruta.push_back(tmp);
    }
    return ruta;
}

int isPositive(int n)
{
    return n > 0;
}
int isNegative(int n)
{
    return n < 0;
}
int isZero(int n)
{
    return n == 0;
}

//Funcion que toma el punto actual posX, posY y utiliza un punto destino desX, desY para calcular el vector director para moverse hacia ese punto
//Retorna un vector con vector[0]=x, vector[1]=y indicando el vector de la direccion
vector<int> calcularDireccion(int posX, int posY, int desX, int desY)
{
    int resX = desX - posX;
    int resY = desY - posY;

    if (isPositive(resX) && isZero(resY))
        return mapDirecciones["DOWN"];
    if (isNegative(resX) && isZero(resY))
        return mapDirecciones["UP"];
    if (isZero(resX) && isPositive(resY))
        return mapDirecciones["RIGHT"];
    if (isZero(resX) && isNegative(resY))
        return mapDirecciones["LEFT"];
    if (isNegative(resX) && isNegative(resY))
        return mapDirecciones["UP_LEFT"];
    if (isNegative(resX) && isPositive(resY))
        return mapDirecciones["UP_RIGHT"];
    if (isPositive(resX) && isNegative(resY))
        return mapDirecciones["DOWN_LEFT"];
    if (isPositive(resX) && isPositive(resY))
        return mapDirecciones["DOWN_RIGHT"];
    return *(new vector<int>); //linea solo para quitar error
}

//Funcion que se encarga de avanzar desde el punto actual hasta el punto destino
//retorna 0 si hay error o 1 si fue correctamente ejecutado
int avanzarTipo2(int *x, int *y, int desX, int desY)
{
    struct agente *mapAgent = &(*mapa[*x][*y].agentes)[pthread_self()];
    while (*x != desX && *y != desY) //Mientras el punto actual no sea igual al punto destino
    {
        mapAgent = &(*mapa[*x][*y].agentes)[pthread_self()];
        if (!mapAgent->vivo)
        {
            return 0;
        }
        if (duracionSimulacion == 0)
            return 0;
        int velocidad = getRandomVelocity(mapAgent->velocidadMaxima, mapAgent->velocidadMinima);
        sleep(velocidad);
        aplicarVacuna(mapAgent);
        reducirVacunaCountDown(mapAgent, velocidad);
        if (kill(mapAgent, velocidad)) //matar si esta enfermo y dios decidio matarlo
            return 0;
        trustGod(mapAgent, velocidad); //curar si asi lo decidio dios

        struct agente cpy = *mapAgent;
        vector<int> direccion = calcularDireccion(*x, *y, desX, desY); //Calcula la vector director hacia el destino
        int nextX = *x + direccion[0];
        int nextY = *y + direccion[1];
        if (isWall(nextX, nextY) || isOutMap(nextX, nextY))
            return 0;
        //En caso de avanzar exitosamente a la siguiente posicion se procede...
        cpy.posX = nextX;
        cpy.posY = nextY;

        //Borra el agente en la posicion actual y lo agrega a la nueva posicion
        pthread_mutex_lock(&mapaMutex);
        mapa[*x][*y].agentes->erase(pthread_self());
        transmitirEnfermedad(nextX, nextY, &cpy);
        mapa[nextX][nextY].agentes->insert(pair<long, struct agente>(pthread_self(), cpy));
        pthread_mutex_unlock(&mapaMutex);
        *x = nextX;
        *y = nextY;
    }

    return 1; //Exito
}

//Funcion utilizada para mover el agente tipo 2 siguiendo la ruta hacia adelante
void adelante(vector<pair<int, int>>::iterator iter, vector<pair<int, int>>::iterator end, int *x, int *y, vector<pair<int, int>> *vec, string *direccion)
{
    struct agente *mapAgent = &(*mapa[*x][*y].agentes)[pthread_self()];
    for (; iter != end; ++iter)
    {
        mapAgent = &(*mapa[*x][*y].agentes)[pthread_self()];
        if (!mapAgent->vivo)
            break;
        int rs = avanzarTipo2(x, y, (*iter).first, (*iter).second);
        if (!rs)
        {
            //vec->erase(iter, end);
            *direccion = "REVERSA";
        }
    }
}

//Funcion utilizada para mover el agente tipo 2 siguiendo la ruta en reversa
void reversa(vector<pair<int, int>>::iterator iter, vector<pair<int, int>>::iterator end, int *x, int *y, vector<pair<int, int>> *vec, string *direccion)
{
    struct agente *mapAgent = &(*mapa[*x][*y].agentes)[pthread_self()];
    for (; iter != end; ++iter)
    {
        mapAgent = &(*mapa[*x][*y].agentes)[pthread_self()];
        if (!mapAgent->vivo)
            break;
        int rs = avanzarTipo2(x, y, (*iter).first, (*iter).second);
        if (!rs)
        {
            //vec->erase(iter, end);
            *direccion = "ADELANTE";
        }
    }
}

void moveTipo2(int x, int y)
{
    vector<pair<int, int>> ruta = crearRuta(x, y);
    int i = 0;
    string direccionI = "ADELANTE";
    struct agente *mapAgent = &(*mapa[x][y].agentes)[pthread_self()];
    iniciarEnfermedad(mapAgent);
    while (mapAgent->vivo)
    {
        if (direccionI == "ADELANTE")
        {
            adelante(ruta.begin(), ruta.end(), &x, &y, &ruta, &direccionI);
        }
        else
        {
            reversa(ruta.begin(), ruta.end(), &x, &y, &ruta, &direccionI);
        }
    }
    mapa[x][y].agentes->erase(pthread_self());
}

//***************************************  Funciones encargadas de mover el agente TIPO 3

//Funcion que se encarga de avanzar desde el punto actual hasta el punto destino
//retorna 0 si hay error o 1 si fue correctamente ejecutado
int avanzarTipo3(int *x, int *y, int desX, int desY)
{
    struct agente *mapAgent = &(*mapa[*x][*y].agentes)[pthread_self()];
    int velocidad = getRandomVelocity(mapAgent->velocidadMaxima, mapAgent->velocidadMinima);
    sleep(velocidad);
    aplicarVacuna(mapAgent);
    reducirVacunaCountDown(mapAgent, velocidad);
    if (kill(mapAgent, velocidad)) //matar si esta enfermo y dios decidio matarlo
        return 0;
    trustGod(mapAgent, velocidad);   //curar si asi lo decidio dios
    while (*x != desX && *y != desY) //Mientras el punto actual no sea igual al punto destino
    {
        struct agente cpy = *mapAgent;
        vector<int> direccion = calcularDireccion(*x, *y, desX, desY); //Calcula la vector director hacia el destino
        int nextX = *x + direccion[0];
        int nextY = *y + direccion[1];
        if (isWall(nextX, nextY) || isOutMap(nextX, nextY))
            return 0;
        //En caso de avanzar exitosamente a la siguiente posicion se procede...
        cpy.posX = nextX;
        cpy.posY = nextY;

        //Borra el agente en la posicion actual y lo agrega a la nueva posicion
        pthread_mutex_lock(&mapaMutex);
        mapa[*x][*y].agentes->erase(pthread_self());
        transmitirEnfermedad(nextX, nextY, &cpy);
        mapa[nextX][nextY].agentes->insert(pair<long, struct agente>(pthread_self(), cpy));
        pthread_mutex_unlock(&mapaMutex);
        *x = nextX;
        *y = nextY;
    }
    return 1; //Exito
}

void moveTipo3(int x, int y)
{
    struct agente *mapAgent = &(*mapa[x][y].agentes)[pthread_self()];
    iniciarEnfermedad(mapAgent);
    while (mapAgent->vivo)
    {
        if (duracionSimulacion == 0)
            pthread_exit(0);
        //Obtiene posicion random
        int desX = rand() % tamañoMapa[0];
        int desY = rand() % tamañoMapa[1];
        while (isWall(desX, desY) || isOutMap(desX, desY))
        {
            desX = rand() % tamañoMapa[0];
            desY = rand() % tamañoMapa[1];
        }
        avanzarTipo3(&x, &y, desX, desY);
    }
    mapa[x][y].agentes->erase(pthread_self());
    return;
}

//***************************************  Funciones encargadas de mover el agente TIPO 4
void moveTipo4(int x, int y)
{
    struct agente *mapAgent = &(*mapa[x][y].agentes)[pthread_self()];
    iniciarEnfermedad(mapAgent);
    while (mapAgent->vivo)
    {
        if (duracionSimulacion == 0)
            pthread_exit(0);
        //Aunque este agente no se mueve, se calcula una velocidad para utilizar el mismo codigo
        int velocidad = getRandomVelocity(mapAgent->velocidadMaxima, mapAgent->velocidadMinima);
        sleep(velocidad);
        aplicarVacuna(mapAgent);
        reducirVacunaCountDown(mapAgent, velocidad);
        if (kill(mapAgent, velocidad)) //matar si esta enfermo y dios decidio matarlo
        {
            mapa[x][y].agentes->erase(pthread_self());
            continue;
        }
        trustGod(mapAgent, velocidad); //curar si asi lo decidio dios
    }
}
