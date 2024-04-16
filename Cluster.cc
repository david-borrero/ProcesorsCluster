/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"

Cluster::Cluster()
{
    arbol = BinTree<string>();
    procesadores = map<string, Procesador>();
}

void Cluster::alta_proceso_procesador(const Proceso& p, const string& procesador)
{
    map<string, Procesador>::iterator it = procesadores.find(procesador);
    if (it == procesadores.end()) cout << "error: no existe procesador" << endl;
    else {
        if ((it -> second).existe_proceso(p.consultar_id())) cout << "error: ya existe proceso" << endl;
        else (it -> second).anadir_proceso(p);
    }
}

void Cluster::baja_proceso_procesador(const int& proceso, const string& procesador)
{
    map<string, Procesador>::iterator it = procesadores.find(procesador);
    if (it == procesadores.end()) cout << "error: no existe procesador" << endl;
    else {
        if (not (it -> second).existe_proceso(proceso)) cout << "error: no existe proceso" << endl;
        else {
            (it -> second).elimina_proceso(proceso);
        }
    }
}

void Cluster::avanzar_tiempo_procesadores(const int& tiempo)
{
    map<string, Procesador>::iterator it = procesadores.begin();
    while (it != procesadores.end()) {
        (it -> second).avanzar_tiempo(tiempo);
        ++it;
    }
}

void Cluster::i_configurar_cluster(BinTree<string>& a, map<string, Procesador>& p)
{
    string id;
    cin >> id;
    if (id != "*"){
        Procesador pro;
        pro.leer();
        p[id] = pro;

        BinTree<string> izquierda;
        BinTree<string> derecha;
        i_configurar_cluster(izquierda, p);
        i_configurar_cluster(derecha, p);
        a = BinTree<string>(id, izquierda, derecha);
    }
}

void Cluster::configurar_cluster()
{
    procesadores = map<string, Procesador>();
    i_configurar_cluster(arbol, procesadores);
}

void Cluster::imprimir_procesador(const string& procesador) const
{
    map<string, Procesador>::const_iterator it = procesadores.find(procesador);
    if (it == procesadores.end()) cout << "error: no existe procesador" << endl;
    else {
        (it -> second).escribir();
    }
}

void Cluster::i_imprimir(const BinTree<string>& a)
{
    if (not a.empty()) {
        cout << "(" << a.value();
        i_imprimir(a.left());
        i_imprimir(a.right());
        cout << ")";
    }
    else cout << " ";
}

void Cluster::imprimir() const
{
    i_imprimir(arbol);
    cout << endl;
}

void Cluster::imprimir_procesadores() const
{
    map<string, Procesador>::const_iterator it = procesadores.begin();
    while (it != procesadores.end()) {
        cout << (it -> first) << endl;
        (it -> second).escribir();
        ++it;
    }
}

bool Cluster::i_modificar(const BinTree<string>& arbol_nuevo, const string& id_procesador, BinTree<string>& a)
{
    if (not a.empty()) {
        BinTree<string> left = a.left();
        BinTree<string> right = a.right();
        string identificador = a.value();
        if (a.value() == id_procesador) {
            if (left.empty() and right.empty()) {
                a = arbol_nuevo;
                return true;
            }
            else return false;
        }
        bool izquierda = i_modificar(arbol_nuevo, id_procesador, left);
        bool derecha = i_modificar(arbol_nuevo, id_procesador, right);
        a = BinTree<string>(identificador, left, right);
        return izquierda and derecha;
    }
    return true;
}

void Cluster::modificar(const string& procesador)
{
    map<string, Procesador> mapa_nuevo;
    BinTree<string> arbol_nuevo;
    i_configurar_cluster(arbol_nuevo, mapa_nuevo);
    map<string, Procesador>::iterator it = procesadores.find(procesador);
    if (it == procesadores.end()) cout << "error: no existe procesador" << endl;
    else if ((it -> second).tiene_procesos()) cout << "error: procesador con procesos" << endl;
    else {
        if (i_modificar(arbol_nuevo, procesador, arbol)) {
            procesadores.erase(it);
            procesadores.insert(mapa_nuevo.begin(), mapa_nuevo.end());
        }
        else cout << "error: procesador con auxiliares" << endl;
    }
}

void Cluster::compactar_memoria_procesador(const string& procesador)
{
    map<string, Procesador>::iterator it = procesadores.find(procesador);
    if (it == procesadores.end()) cout << "error: no existe procesador" << endl;
    else {
        (it -> second).compactar_memoria();
    }
}

void Cluster::compactar_memoria_cluster()
{
    map<string, Procesador>::iterator it = procesadores.begin();
    while (it != procesadores.end()) {
        (it -> second).compactar_memoria();
        ++it;
    }
}

string Cluster::busqueda(const BinTree<string>& a, const set<string>& s)
{
    queue<BinTree<string>> q;
    q.push(a);
    bool trobat = false;
    string x = "";
    //Recorrido en amplitud
    while (not trobat) {
        BinTree<string> aux = q.front();
        set<string>::iterator it = s.find(aux.value());
        if (it != s.end()) {
            trobat = true;
            x = *it;
        }

        if (not aux.left().empty()) q.push(aux.left());
        if (not aux.right().empty()) q.push(aux.right());
        q.pop();
    }
    return x;
}


bool Cluster::buscar_procesador(const Proceso& p)
{
    int mem = p.consultar_memoria();
    map<string, Procesador>::iterator it = procesadores.begin();
    int max = 0;
    int max_memoria = 0;
    set<string> s;
    bool primera_iteracion = true;
    //Recorro todo el cluster y guardo los casos que tengan el hueco más ajustado y la memoria libre sea mayor.
    while (it != procesadores.end()) {
        int hueco;
        if (not (it -> second).existe_proceso(p.consultar_id()) and (it -> second).hueco_ajustado(mem, hueco)) {
            if (primera_iteracion) {
                max = hueco;
                max_memoria = (it -> second).memoria_libre();
                s.insert(it -> first);
                primera_iteracion = false;
            }
            else {
                if (hueco < max) {
                    s.clear();
                    s.insert(it -> first);
                    max = hueco;
                    max_memoria = (it -> second).memoria_libre();
                }
                else if (hueco == max) {
                    if ((it -> second).memoria_libre() > max_memoria) {
                        s.clear();
                        s.insert(it -> first);
                        max_memoria = (it -> second).memoria_libre();
                    }
                    else if ((it -> second).memoria_libre() == max_memoria) s.insert(it -> first);
                }
            }
        }
        ++it;
    }

    //Si el set está vacío, no se ha encontrado ningun procesador que pueda almacenar el proceso
    if (s.size() != 0) {
        string x;

        //Si hay más de un procesador empatado, busco el procesador que esté más cerca de la raíz del cluster y más a la izquierda en caso de empate
        if (s.size() > 1)  x = busqueda(arbol, s);
        else {
            set<string>::const_iterator its = s.begin();
            x = *its;
        }

        it = procesadores.find(x);
        (it -> second).anadir_proceso(p);
        return true;
    }
    return false;
}
