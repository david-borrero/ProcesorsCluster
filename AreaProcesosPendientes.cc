/** @file AreaProcesosPendientes.cc
    @brief Código de la clase AreaProcesosPendientes
*/

#include "AreaProcesosPendientes.hh"
#include "Proceso.hh"
#include "Cluster.hh"

AreaProcesosPendientes::AreaProcesosPendientes()
{
    area = map<string, Prioridad>();
}

bool AreaProcesosPendientes::existe_proceso(const int& proceso, const string& prioridad) const
{
    map<string, Prioridad>::const_iterator it = area.find(prioridad);
    set<int>::const_iterator it2 = (it -> second).procesos.find(proceso);

    if (it2 == (it -> second).procesos.end()) return false;
    return true;
}

bool AreaProcesosPendientes::tiene_procesos(const string& prioridad) const
{
    map<string, Prioridad>::const_iterator it = area.find(prioridad);
    if ((it -> second).l.empty()) return false;
    else return true;
}

void AreaProcesosPendientes::anadir_proceso(const Proceso& p, const string& prioridad)
{
    map<string, Prioridad>::iterator it = area.find(prioridad);
    if (it == area.end()) cout << "error: no existe prioridad" << endl;
    else {
        if (existe_proceso(p.consultar_id(), prioridad)) cout << "error: ya existe proceso" << endl;
        else {
            (it -> second).l.push_back(p);
            (it -> second).procesos.insert(p.consultar_id());
        }
    }
}

void AreaProcesosPendientes::anadir_prioridad(const string& prioridad)
{
    map<string, Prioridad>::iterator it = area.find(prioridad);
    if (it != area.end()) cout << "error: ya existe prioridad" << endl;
    else {
        Prioridad v;
        v.colocados = v.rechazados = 0;
        area[prioridad] = v;
    }
}

void AreaProcesosPendientes::eliminar_prioridad(const string& prioridad)
{
    map<string, Prioridad>::const_iterator it = area.find(prioridad);
    if (it == area.end()) cout << "error: no existe prioridad" << endl;
    else {
        if (tiene_procesos(prioridad)) cout << "error: prioridad con procesos" << endl;
        else {
            area.erase(it);
        }
    }
}

void AreaProcesosPendientes::leer()
{
    int n;
    cin >> n;

    string prio;
    for (int i = 0; i < n; ++i) {
        cin >> prio;
        Prioridad v;
        v.colocados = v.rechazados = 0;
        area[prio] = v;
    }
}

void AreaProcesosPendientes::imprimir_prioridad(const string& prioridad) const
{
    map<string, Prioridad>::const_iterator it = area.find(prioridad);
    if (it == area.end()) cout << "error: no existe prioridad" << endl;
    else {
        list<Proceso>::const_iterator itl = (it -> second).l.begin();
        while (itl != (it -> second).l.end()) {
            (*itl).escribir();
            ++itl;
        }
        cout << (it -> second).colocados << ' ' << (it -> second).rechazados << endl;
    }
}

void AreaProcesosPendientes::imprimir() const
{
    map<string, Prioridad>::const_iterator it = area.begin();
    while (it != area.end()) {
        cout << it -> first << endl;
        list<Proceso>::const_iterator itl = (it -> second).l.begin();
        while (itl != (it -> second).l.end()) {
            (*itl).escribir();
            ++itl;
        }
        cout << (it -> second).colocados << ' ' << (it -> second).rechazados << endl;
        ++it;
    }
}

void AreaProcesosPendientes::enviar_procesos_cluster(Cluster& cluster, int& n)
{
    map<string,Prioridad>::iterator it = area.begin();
    while (it != area.end() and n > 0) {
        int total = (it -> second).l.size();
        while (n > 0 and total > 0) {
            if (cluster.buscar_procesador((it -> second).l.front())) {
                (it -> second).procesos.erase((it -> second).l.front().consultar_id());
                (it -> second).l.pop_front();
                ++(it -> second).colocados;
                --n;
            }
            else {
                Proceso p = (it -> second).l.front();
                (it -> second).l.pop_front();
                (it -> second).l.push_back(p);
                ++(it -> second).rechazados;
            }
            --total;
        }
        ++it;
    }
}
