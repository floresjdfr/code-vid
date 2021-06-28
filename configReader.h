#include "codevidData.h"
using namespace std;

//funcion encargada de utilizar las paredes leidas desde el archivo de configuracion
//y ponerlas sobre el mapa que recibe como argumento
//returna el mismo argumento pero con las paredes insertadas
struct campoMapa **putParedes(struct campoMapa **mapa)
{
    while (!(paredesArray).empty() && cantidadParedes > 0)
    {
        //obtiene los datos de la pared
        auto pared = paredesArray.back();
        paredesArray.pop_back();
        int x1 = get<0>(pared);
        int y1 = get<1>(pared);
        int x2 = get<2>(pared);
        int y2 = get<3>(pared);

        //Configura el mapa la pared
        for (int i = min(y1, y2) - 1; i < max(y1, y2); i++)
        {
            for (int j = min(x1, x2) - 1; j < max(x1, x2); j++)
            {
                mapa[i][j].esPared = -1;
            }
        }
    }
    return mapa;
}

//Funcion encargada de imprimir el mapa
//Nota: solo imprime la cantidad de agentes que hay en una posicion
//Imprime -1 si es pared
void printParedes()
{
    for (int i = 0; i < tamañoMapa[0]; i++)
    {
        for (int j = 0; j < tamañoMapa[1]; j++)
        {
            if (mapa[i][j].esPared)
            {
                cout << "-";
                cout << "|";
            }
            else
            {
                if (mapa[i][j].agentes->size() > 0)
                {
                    map<long, struct agente>::iterator it;

                    for (it = mapa[i][j].agentes->begin(); it != mapa[i][j].agentes->end(); it++)
                    {

                        cout << (*it).second.estado;
                    }
                    cout << "|";
                }
                else
                    cout << "." << "|";
            }
        }
        cout << endl;
    }
}

//Funcion encargada de la lectura de archivo de configuración
//El argumento es un puntero al struct agente
//Retorna un vector de dos dimensiones de struct agente
void readMapa()
{
    ifstream file("mapa.config");
    string line;
    size_t pos = 0;
    string token;
    string delimiter = " ";

    getline(file, line); //Lee la primera linea (tamaño del mapa)

    pos = line.find(delimiter);              //busca la posicion del delimitador
    token = line.substr(0, pos);             //obtiene el primer número del archivo de configuración
    line.erase(0, pos + delimiter.length()); //borra el primer numero para dejar solo al segundo
    tamañoMapa[0] = atoi(token.c_str());
    tamañoMapa[1] = atoi(token.c_str());

    if (file.good())
    {
        getline(file, line); //Lee segunda linea (total de paredes en el mapa)
        cantidadParedes = atoi(line.c_str());
        for (int i = 0; i < cantidadParedes; i++)
        {
            getline(file, line);
            int puntos[4];
            int j = 0;
            while ((pos = line.find(delimiter)) != string::npos)
            {
                token = line.substr(0, pos);             //obtiene el primer número del archivo de configuración
                line.erase(0, pos + delimiter.length()); //borra el primer numero para dejar solo al segundo
                puntos[j] = atoi(token.c_str());
                j++;
            }
            puntos[3] = atoi(line.c_str());
            paredesArray.push_back(make_tuple(puntos[0], puntos[1], puntos[2], puntos[3]));
        }
    }

    mapa = new struct campoMapa *[tamañoMapa[0]];
    for (int i = 0; i < tamañoMapa[0]; i++)
        mapa[i] = new struct campoMapa[tamañoMapa[1]];

    for (int i = 0; i < tamañoMapa[0]; i++)
    { //Inicia el vector de agentes en cada cuadrante del mapa, necesario para no perder informacion y no cree copias
        for (int j = 0; j < tamañoMapa[1]; j++)
        {
            mapa[i][j].agentes = new map<long, struct agente>;
        }
    }
    mapa = putParedes(mapa);
    pthread_mutex_init(&mapaMutex, NULL);
}

//************************************ Code-vid reader
//Funcion encargada de la lectura de archivo de configuración de agentes
//El argumento es un puntero al struct agente
//Retorna un vector de dos dimensiones de struct agente
void readCodeVid()
{
    ifstream file("code-vid.config");
    string line;
    size_t pos = 0;
    string token;
    string delimiter = " ";
    int lineCounter = 0;
    int agentCouter = 0;

    while (getline(file, line))
    {
        if (lineCounter == 0)
            probabilidadMorir = stof(line);
        else if (lineCounter == 1)
            deathCount = stof(line);
        else if (lineCounter == 2)
            healCount = stof(line);

        else if (lineCounter == 3)
        {
            vector<float> fila;
            while ((pos = line.find(delimiter)) != string::npos)
            {
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                fila.push_back(stof(token));
                agentCouter++;
            }
            fila.push_back(stof(line));
            agentCouter++;
            tasaContagio.push_back(fila);
        }
        else if (lineCounter > 3 && agentCouter > 1)
        {
            vector<float> fila;
            while ((pos = line.find(delimiter)) != string::npos)
            {
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                fila.push_back(stof(token));
            }
            fila.push_back(stof(line));
            agentCouter--;
            tasaContagio.push_back(fila);
        }
        else
        {
            reinfeccion = atoi(line.c_str());
        }
        lineCounter++;
    }
}

//************************************* AGENT READER  **************************************************************

//Funcion encargada de la lectura de archivo de configuración de agentes
//El argumento es un puntero al struct agente
//Retorna un vector de dos dimensiones de struct agente
void readAgents()
{
    ifstream file("agentes.config");
    string line;
    size_t pos = 0;
    string token;
    string delimiter = " ";
    int cantidadAgentes;
    int tipoAgente;
    int velocidadMaxima;
    int velocidadMinima;
    char estado;

    getline(file, line);
    cantidadGrupos = atoi(line.c_str());

    for (int i = 0; i < cantidadGrupos; i++)
    {
        getline(file, line);
        cantidadAgentes = atoi(line.c_str());
        getline(file, line);
        tipoAgente = atoi(line.c_str());
        getline(file, line);
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        velocidadMinima = atoi(token.c_str());
        velocidadMaxima = atoi(line.c_str());
        getline(file, line);
        estado = line[0];

        for (int i = 0; i < cantidadAgentes; i++)
        {
            struct agente agent;
            agent.vivo = 1;
            agent.tipo = tipoAgente;
            agent.estado = estado;
            agent.velocidadMaxima = velocidadMaxima;
            agent.velocidadMinima = velocidadMinima;
            agent.vacunado = 0;
            agent.vacunaCountDown = -1000;
            agent.deathCountDown = -1000;
            agent.healCountDown = -1000;
            agent.posX = -1;
            agent.posY = -1;

            agentes.push_back(agent);
            agentesCount++;
        }
    }
}



//************************************* VACUNAS READER  **************************************************************

void readVacunas()
{
    ifstream file("vacunacion.config");
    string line;
    size_t pos = 0;
    string token;
    string delimiter = " ";

    getline(file, line);
    inicioVacunacion = atoi(line.c_str());
    getline(file, line);
    porcentajeEficiencia = atoi(line.c_str());
    getline(file, line);
    duracionHacerEfecto = atoi(line.c_str());
    getline(file, line);
    pos = line.find(delimiter);              
    token = line.substr(0, pos);             
    line.erase(0, pos + delimiter.length()); 
    numeroVacunas = atoi(token.c_str());
    frecuenciaCreacion = atoi(line.c_str());
}