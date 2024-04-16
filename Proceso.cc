/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"

Proceso::Proceso()
{
    id = 0;
    n_memoria = 0;
    tiempo = 0;
}

void Proceso::avanzar_tiempo(const int& tiempo)
{
    this->tiempo -= tiempo;
}

int Proceso::consultar_id() const
{
    return id;
}

int Proceso::consultar_memoria() const
{
    return n_memoria;
}

int Proceso::consultar_tiempo() const
{
    return tiempo;
}

void Proceso::leer()
{
    cin >> id >> n_memoria >> tiempo;
}

void Proceso::escribir() const
{
    cout << id << ' ' << n_memoria << ' ' << tiempo << endl;
}
