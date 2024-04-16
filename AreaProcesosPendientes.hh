/** @file AreaProcesosPendientes.hh
    @brief Especificación de la classe AreaProcesosPendientes
*/

#ifndef AREAPROCESOSPENDIENTES_HH
#define AREAPROCESOSPENDIENTES_HH

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <map>
#include "Cluster.hh"
#include <list>
#include <set>
#include <iostream>
#endif

/** @class AreaProcesosPendientes
    @brief Representa una area donde se guardan los diferentes procesos en orden de prioridad
 */
class AreaProcesosPendientes
{

public:

    //Constructoras

    /** @brief Creadora por defecto

        Se ejecuta automáticamente cuando se declara una area de procesos pendientes
        \pre <em>cierto</em>
        \post El resultado es una area de procesos pendientes
    */
    AreaProcesosPendientes();



    //Consultoras

     /** @brief Consultora de proceso

        Comprueba si un proceso se encuentra en la prioridad correspondiente del area de procesos pendientes
        \pre La prioridad existe en la area de espera i el parámetro implícito está inicializado
        \post Devuelve true si hay un proceso en la prioridad correspondiente
    */
    bool existe_proceso(const int& proceso, const string& prioridad) const;

    /** @brief Indica si la prioridad tiene procesos

        \pre La prioridad existe en la area de espera i el parámetro implícito está inicializado
        \post Devuelve true si la prioridad tiene uno o mas procesos, false contrariamente
    */
    bool tiene_procesos(const string& prioridad) const;



    //Modificadores

    /** @brief Añade un proceso

        Comprueba que la prioridad existe y que no tenga un proceso con el mismo identificador.
        Si es cierto,añade un proceso en la area de procesos pendientes y en la prioridad correspondiente.
        Si no, salta un error
        \pre  El parámetro implícito está inicializado.
        \post Se ha añadido el proceso en la prioridad en la area de procesos pendientes
    */
    void anadir_proceso(const Proceso& p, const string& prioridad);

    /** @brief Añade una prioridad

        Comprueba antes de añadir si la prioridad ya existe. Si existe, salta un error
        \pre El parámetro implícito está inicializado
        \post Se ha añadido la prioridad en la area de procesos pendientes si no existia
    */
    void anadir_prioridad(const string& prioridad);

    /** @brief Elimina una prioridad

        Comprueba antes de eliminar si la prioridad existe en la area y si tiene procesos pendientes.
        Si existe i no tiene procesos pendientes la elimina, si no salta un error
        \pre El parámetro implícito está inicializado
        \post Se ha eliminado la prioridad de la area de procesos pendientes
    */
    void eliminar_prioridad(const string& prioridad);


    /** @brief Envia los procesos al clúster

        Los procesos se intentan colocar en el clúster por orden de prioridad. Dentro de
        una misma prioridad, se intentan colocar primero los procesos más antiguos. Los
        intentos continúan hasta haber colocado n procesos en el clúster o hasta que no
        queden procesos pendientes o hasta que todos los que queden pendientes se hayan
        intentado colocar sin éxito
        \pre El parámetro implícito está inicializado. n >= 0
        \post Se han enviado un máximo de n procesos al clúster
    */
    void enviar_procesos_cluster(Cluster& cluster, int& n);



    //Lectura

    /** @brief Lectura

        Lee una area de proces pendientes con sus respectivas prioridades y procesos
        \pre Hay preparados en el canal estandar de lectura una serie de prioridades
        \post El area de procesos pendientes se guarda en el parámetro implícito ordenado por prioridad
    */
    void leer();



    //Escriptura

    /** @brief Imprimir prioridad

        Comprueba que existe la prioridad. Si existe, imprime los procesos pendientes de esta
        y el numero de procesos colocados en el cluster y el numero de rechazos
        \pre El parámetro implícito está inicializado
        \post Se han escrito los procesos de la prioridad si tiene y el numero de colocados y rechazados
              en el canal estandar de salida
    */
    void imprimir_prioridad(const string& prioridad) const;

    /** @brief Imprime el area de espera

        \pre El parámetro implícito está inicializado. La area de procesos pendientes esta
             ordenada por orden creciente de prioridad
        \post Se ha imprimido por el canal estandar de salida el area de espera por
              orden creciente de prioridad
    */
    void imprimir() const;


private:

    /** @brief Estructura que engloba una lista de procesos, el numero de colocados y rechazados
        y un conjunto
    */
    struct Prioridad {
        list<Proceso> l;
        set<int> procesos;
        int colocados;
        int rechazados;
    };

    /** @brief Mapa que enlaza las prioridades y sus colas de proces y el numero de procesos colocados y rechazados
    */
    map<string, Prioridad> area;

};
#endif
