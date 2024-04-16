/** @file Procesador.hh
    @brief Especificación de la classe Procesador
*/

#ifndef PROCESADOR_HH
#define PROCESADOR_HH

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
#include <set>
#include <map>
#endif

/** @class Procesador
    @brief Representa un procesador en el cual habrá una memoria con procesos
 */
class Procesador
{

public:

    //Constructoras

    /** @brief Creadora por defecto

        Se ejecuta automáticamente cuando se declara un procesador
        \pre <em>cierto</em>
        \post El resultado es un procesador
    */
    Procesador();



    //Consultoras

    /** @brief Consulta si el parámetro implícito tiene procesos

        \pre El parámetro implícito está inicializado
        \post Devuelve true si tiene procesos, false si no los tiene
    */
    bool tiene_procesos() const;

    /** @brief Consulta si existe el proceso con identificador id en el parámetro implícito

        \pre El parámetro implícito está inicializado
        \post Devuelve true si el proceso existe, false contrariamente
    */
    bool existe_proceso(const int& proceso) const;

    /** @brief Consulta el hueco más ajustado en el que se puede colocar un proceso

        \pre El parámetro implícito está inicializado. El proceso no existe en el parámetro implícito
        \post Devuelve true si se puede colocar y size = tamaño más ajustado. Devuelve false contrariamente
    */
    bool hueco_ajustado(const int& mem, int& size) const;

    /** @brief Consulta la memoria libre del parámetro implícito

        \pre El parámetro implícito está inicializado
        \post Devuelve el espacio de la memoria que no está ocupada por procesos
    */
    int memoria_libre() const;


    //Modificadoras


    /** @brief Añade un proceso al parámetro implícito

        Comprueba si cabe el error. Si lo hace, lo añade. Si no, salta un error
        \pre El parámetro implícito está inicializado y no tiene un proceso con el mismo id
        \post Se ha añadido el proceso al parámetro implícito
    */
    void anadir_proceso(const Proceso& p);

    /** @brief Elimina un proceso del parámetro implícito

        \pre El parámetro implícito está inicializado y tiene un proceso con el mismo id
        \post Se ha eliminado el proceso del parámetro implícito
    */
    void elimina_proceso(const int& proceso);

    /** @brief Compacta la memoria de un parámetro implícito

        \pre El parámetro implícito está inicializado
        \post Se ha compactado la memoria del parámetro implícito
    */
    void compactar_memoria();

    /** @brief Avanza el tiempo

        \pre tiempo >= 0. El parámetro implícito está inicializado
        \post Se ha anvazado el tiempo. Todos los procesos del parámetro implícito que han terminado se eliminan
    */
    void avanzar_tiempo(const int& tiempo);



    //Lectura

    /** @brief Lee un procesador

        \pre Hay preparados en el canal estandar de entrada los datos de un procesador
        \post Se ha guardado el procesador en el parámetro implícito
    */
    void leer();



    //Escriptura

    /** @brief Escribe los datos del parámetro implícito

        Se escriben los procesos del parámetro implícito por orden creciente de primera posición de memoria
        y los datos de estos procesos
        \pre <em>Cierto<em>
        \post Se ha escrito por el canal estandar de salida los datos del parámetro implícito
    */
    void escribir() const;


private:

    /** @brief Posiciones ocupadas de la memoria*/
    int espacio;

    /** @brief Posiciones totales de memoria */
    int espacio_total;

    /** @brief Mapa que relaciona una posición con el proceso que empieza desde esa posición*/
    map<int, Proceso> memoria;

    /** @brief Mapa que relaciona el identificador de cada proceso del procesador con su posición inicial */
    map<int, int> posicion;

    /** @brief Mapa que relaciona el tamaño de los huecos con sus posiciones iniciales */
    map<int, set<int>> hueco;

    /** @brief Elimina los huecos fusionados

        Elimina los huecos despues de fusionarlos con otro hueco
        \pre Existe un hueco con tamaño = tamano_hueco i posicion_inicial = pos_hueco
        \post Se ha eliminado el hueco que se ha fusionado con otro hueco
    */
    void arreglar(const int& tamano_hueco, const int& pos_hueco);

    /** @brief Consulta si puede colocarse el proceso en la memoria del parámetro implícito

        \pre El parámetro implícito está inicializado y no tiene el proceso
        \post Devuelve -1 si no puede colocarse. Si se puede, devuelve la posicion mas pequeña que deje el hueco mas pequeño
    */
    int puede_colocarse(const int& mem);

};
#endif
