/** @file Cluster.hh
    @brief Especificación de la classe Cluster
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH

#include "Procesador.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include "BinTree.hh"
#include <set>
#include <queue>
#endif



/** @class Cluster
    @brief Representa un arbol binario de procesadores
 */
class Cluster
{

public:

    //Constructoras

    /** @brief Creadora por defecto

        Se ejecuta automáticamente cuando se declara un clúster
        \pre <em>cierto</em>
        \post El resultado es un clúster
    */
    Cluster();


    //Modificadoras

    /** @brief Busca el procesador del parámetro implícito más adecuado para añadir un proceso

        Busca el procesador en el que no exista este proceso y que tenga el hueco mas ajustado al proceso p. En caso de empate, el que quede con
        más memoria libre y si aún hay empate, el que esté más cerca de la raíz del árbol y si persiste el empate, el que esté más a la izquierda
        \pre El parámetro implícito está inicializado
        \post Devuelve false si no existe ningún procesador que cumpla las condiciones, y true si lo encuentra. Además, si lo encuentra, lo añade al procesador correspondiente
    */
    bool buscar_procesador(const Proceso& p);

    /** @brief Modifica el clúster

        Comprueba que el procesador exista, que no tenga procesos activos.
        Si las cumple todas, lee un nuevo clúster y lo añade al procesador indicado pero si no cumple alguna,
        salta un error
        \pre El parámetro implícito está inicializado
        \post Si es posible, se ha modificado el clúster con el nuevo, si no, salta un error
    */
    void modificar(const string& procesador);

    /** @brief Da de alta un proceso en un procesador del clúster

        Comprueba que el procesador exista en el clúster, que no tenga procesos con el mismo identificador
        y que el proceso pueda entrar en la memoria del procesador. Si se cumple, el proceso se añade al procesador,
        si no, salta un error.
        \pre El parámetro implícito está inicializado
        \post Se ha dado de alta el proceso en el procesador correspondiente si es posible, si no, salta un error
    */
    void alta_proceso_procesador(const Proceso& p, const string& procesador);

    /** @brief Da de baja un proceso en un procesador del clúster

        Comprueba que el procesador exista en el clúster y que el proceso exista en el procesador. Si se cumple, el proceso se elimina del procesador,
        si no, salta un error.
        \pre El parámetro implícito está inicializado
        \post Se ha dado de baja el proceso en el procesador correspondiente si es posible, si no, salta un error
    */
    void baja_proceso_procesador(const int& proceso, const string& procesador);

    /** @brief Avanza el tiempo

        \pre tiempo >= 0. El parámetro implícito está inicializado
        \post Se ha anvazado el tiempo. Todos los procesos que han terminado se eliminan
    */
    void avanzar_tiempo_procesadores(const int& tiempo);

    /** @brief Compacta la memoria de un procesador
     *
        Comprueba que el procesador exista. Si lo hace, compacta su memoria, si no lo hace, salta un error
        \pre El parámetro implícito está inicializado
        \post Se ha compactado la memoria del procesador
    */
    void compactar_memoria_procesador(const string& procesador);

    /** @brief Compacta la memoria del clúster

        \pre El parámetro implícito está inicializado
        \post Se ha compactado la memoria de todos los procesadores del clúster
    */
    void compactar_memoria_cluster();



    //Lectura

    /** @brief Lee y configura un clúster

        Lee los procesadores del clúster, sus connexiones y la memoria de cada uno de ellos
        \pre Hay preparados en el canal estandar de entrada los datos del clúster
        \post Se ha guardado el cluster en el parámetro implícito
    */
    void configurar_cluster();



    //Escritura

    /** @brief Imprime un procesador del clúster

        Comprueba que el procesador exista en el clúster y imprime los datos del procesador,
        si no salta un error
        \pre El parámetro implícito está inicializado
        \post Se ha escrito por el canal estandar de salida el procesador si este existe, si no salta un error
    */
    void imprimir_procesador(const string& procesador) const;

    /** @brief Imprime un clúster

        \pre El parámetro implícito está inicializado
        \post Se ha escrito por el canal estandar de salida la estructura del clúster
    */
    void imprimir() const;

    /** @brief Imprime los procesadores del clúster

        \pre El parámetro implícito está inicializado
        \post Se ha escrito por el canal estandar de salida los procesadores por orden creciente de identificador
    */
    void imprimir_procesadores() const;



private:

    /** @brief Arbol binario de procesadores */
    BinTree<string> arbol;

    /** @brief Mapa con los procesadores i sus procesos*/
    map<string, Procesador> procesadores;

    /** @brief Función immersiva de busqueda_procesador

        Recorrido por amplitud para encontra
        \pre a.size() != 0 y s.size() > 1
        \post Devuelve la string de s que estamos buscando en a
    */
    static string busqueda(const BinTree<string>& a, const set<string>& s);

    /** @brief Función immersiva de modificar

        \pre <em>cierto<em>
        \post Se ha modificado el arbol a a partir del procesador con id id_procesador
    */
    static bool i_modificar(const BinTree<string>& arbol_nuevo, const string& id_procesador, BinTree<string>& a);

    /** @brief Función immersiva de imprimir

        \pre <em>cierto<em>
        \post Se ha escrito el arbol a por el canal estandar de salida
    */
    static void i_imprimir(const BinTree<string>& a);

    /** @brief Función immersiva de configurar_cluster

        \pre <em>cierto<em>
        \post Se ha guardado en a y p los datos preparados en el canal estandar de entrada
    */
    static void i_configurar_cluster(BinTree<string>& a, map<string, Procesador>& p);

};
#endif
