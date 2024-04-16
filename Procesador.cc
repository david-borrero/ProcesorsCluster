/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador()
{
    espacio = espacio_total = 0;
    memoria = map<int, Proceso>();
    posicion = map<int, int>();
    hueco = map<int, set<int>>();
}

bool Procesador::tiene_procesos() const
{
    return not posicion.empty();
}

int Procesador::memoria_libre() const
{
    return espacio_total - espacio;
}

bool Procesador::existe_proceso(const int& proceso) const
{
    return posicion.find(proceso) != posicion.end();
}

int Procesador::puede_colocarse(const int& mem)
{
    //Busca el hueco mas ajustado al proceso y si existe entra al if
    map<int, set<int>>::iterator it = hueco.lower_bound(mem);
    if (it != hueco.end()) {
        int size = it -> first;
        set<int>::iterator pos_hueco = (it -> second).begin();
        int pos = (*pos_hueco);

        //Elimino la posición del hueco y si era la única y si lo es elimina el tamaño del mapa
        if ((it -> second).size() == 1) hueco.erase(it);
        else (it -> second).erase(pos_hueco);

        //Si el hueco es mas grande que el proceso creo otro hueco mas pequeño
        if (size > mem) {
            int nuevo_hueco = size - mem;
            hueco[nuevo_hueco].insert(pos + mem);
        }
        return pos;
    }
    return -1;
}

void Procesador::anadir_proceso(const Proceso& p)
{
    int pos = puede_colocarse(p.consultar_memoria());
    if (pos == -1) cout << "error: no cabe proceso" << endl;
    else {
        memoria[pos] = p;
        posicion[p.consultar_id()] = pos;
        espacio += p.consultar_memoria();

    }
}

bool Procesador::hueco_ajustado(const int& mem, int& size) const
{
    map<int, set<int>>::const_iterator it = hueco.lower_bound(mem);
    if (it != hueco.end()) {
        size = it -> first;
        return true;
    }
    return false;
}

//Elimina el hueco que se ha fusionado con otro
void Procesador::arreglar(const int& tamano_hueco, const int& pos_hueco)
{
    map<int, set<int>>::iterator it = hueco.find(tamano_hueco);
    (it -> second).erase(pos_hueco);
    if ((it -> second).empty()) hueco.erase(it);
}

void Procesador::elimina_proceso(const int& proceso)
{
    int pos = posicion[proceso];
    int aux = pos;
    map<int, Proceso>::iterator itm = memoria.find(pos);
    Proceso p = (itm -> second);
    int size = p.consultar_memoria();
    espacio -= size;

    //Caso extremo de si solo hay un proceso
    if (memoria.size() == 1) {
        memoria.erase(pos);
        hueco = map<int, set<int>>();
        set<int> s;
        s.insert(0);
        hueco[espacio_total] = s;
        posicion.erase(proceso);
    }
    else {
        if (itm != memoria.begin()) {
            --itm;
            if ((itm -> first) + (itm -> second).consultar_memoria() != pos) {
                size += pos - ((itm -> first) + (itm -> second).consultar_memoria());
                arreglar(pos - ((itm -> first) + (itm -> second).consultar_memoria()), (itm -> first) + (itm -> second).consultar_memoria());
            }
            pos = (itm -> first) + (itm -> second).consultar_memoria();
        }
        //Caso en el que sea el primer proceso pero no este en la posicion 0
        else if (itm -> first != 0) {
            pos = 0;
            size += itm -> first;
            arreglar(itm -> first, 0);
        }
        //Borramos el proceso
        map<int, Proceso>::iterator itm2 = memoria.find(aux);
        itm2 = memoria.erase(itm2);
        posicion.erase(proceso);
        if (itm2 != memoria.end()) {
            if ((itm2 -> first) != aux + p.consultar_memoria()) {
                size += (itm2 -> first) - (aux + p.consultar_memoria());
                arreglar((itm2 -> first) - (aux + p.consultar_memoria()), aux + p.consultar_memoria());
            }
        }
        //Caso en el que estemos en el ultimo proceso pero no ocupemos toda la memoria
        else if (aux + p.consultar_memoria() != espacio_total) {
            size += espacio_total - (aux + p.consultar_memoria());
            arreglar(espacio_total - (aux + p.consultar_memoria()), aux + p.consultar_memoria());
        }
        //Creamos el hueco final que queda de fusionar los huecos cercanos al proceso y el hueco que deja el proceso
        map<int, set<int>>::iterator ith = hueco.find(size);
        if (ith == hueco.end()) {
            set<int> s;
            s.insert(pos);
            hueco[size] = s;
        }
        else (ith -> second).insert(pos);
    }
}



//Cambiar
void Procesador::avanzar_tiempo(const int& tiempo)
{
    map<int, Proceso>::iterator it = memoria.begin();
    while (it != memoria.end()) {
        if ((it -> second).consultar_tiempo() <= tiempo) {
            map<int, Proceso>::iterator i = it;
            ++it;
            elimina_proceso((i -> second).consultar_id());
        }
        else {
            (it -> second).avanzar_tiempo(tiempo);
            ++it;
        }
    }
}

void Procesador::leer()
{
    int n;
    cin >> n;
    espacio_total = n;
    espacio = 0;
    //Hay un hueco de n posiciones
    set<int> s;
    s.insert(0);
    hueco[n] = s;
}

void Procesador::escribir() const
{
    map<int, Proceso>::const_iterator it = memoria.begin();
    while (it != memoria.end()) {
        cout << (it -> first) << " ";
        (it -> second).escribir();
        ++it;
    }
}

//Pasar el if del caso especial fuera del if
void Procesador::compactar_memoria()
{
    if (not hueco.empty() and not memoria.empty()) {
        map<int, Proceso>::iterator it = memoria.begin();
        while (it != memoria.end()) {
            if (it != memoria.begin()) {
                map<int, Proceso>::iterator it2 = it;
                --it2;
                //Compruebo si hay hueco entre el proceso de it y su anterior y si es así muevo el proceso a la posicion correspondiente
                int pos_final = (it2 -> first) + (it2 -> second).consultar_memoria();
                if (pos_final != (it -> first)) {
                    memoria[(it2 -> first) + (it2 -> second).consultar_memoria()] = (it -> second);
                    posicion[(it -> second).consultar_id()] = (it2 -> first) + (it2 -> second).consultar_memoria();
                    it = memoria.erase(it);
                }
                else ++it;

            }
            //Caso especial que miramos el hueco entre la posición 0 y el primer proceso
            else {
                if ((it -> first) != 0){
                    memoria[0] = (it -> second);
                    posicion[(it -> second).consultar_id()] = 0;
                    it = memoria.erase(it);
                }
                else ++it;
            }
        }
        --it;
        hueco.clear();
        set<int> s;
        s.insert((it -> first) + (it -> second).consultar_memoria());
        hueco[memoria_libre()] = s;
    }


}
