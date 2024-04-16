/** @file Proceso.hh
    @brief Especificación de la classe Proceso
*/

#ifndef PROCESO_HH
#define PROCESO_HH

#ifndef NO_DIAGRAM
#include <iostream>
using namespace std;
#endif

/** @class Proceso
    @brief Representa un proceso que ocupa un número de espacios de memoria
 */
class Proceso
{

private:

    /** @brief Entero identificador de cada proceso */
    int id;

    /** @brief Entero que indica el numero de posiciones de memoria que ocupa
    */
    int n_memoria;

    /** @brief Tiempo previsto que tardara el proceso en ejecutarse */
    int tiempo;

public:

    //Constructoras

    /** @brief Creadora por defecto

        Se ejecuta automáticamente cuando se declara un proceso
        \pre <em>cierto</em>
        \post El resultado es un proceso
    */
    Proceso();



    //Modificadoras


    /** @brief Avanza el tiempo

        \pre tiempo >= 0. El parámetro implícito está inicializado
        \post Se ha anvazado el tiempo del parámetro implícito.
    */
    void avanzar_tiempo(const int& tiempo);



    //Consultoras

    /** @brief Consulta el identificador del parámetro implícito

        \pre El parámetro implícito está inicializado
        \post Devuelve el identificador del parámetro implícito
    */
    int consultar_id() const;

    /** @brief Consulta la memoria que ocupa el parámetro implícito

        \pre El parámetro implícito está inicializado
        \post Devuelve la memoria que ocupa el parámetro implícito
    */
    int consultar_memoria() const;

    /** @brief Consulta el tiempo que tarda el parámetro implícito

        \pre El parámetro implícito está inicializado
        \post Devuelve el tiempo que tarda el parámetro implícito
    */
    int consultar_tiempo() const;



    // Lectura

    /** @brief Lee un proceso

        Permite leer un proceso desde el canal de entrada
        \pre Hay preparados en el canal estandar de entrada los datos de un proceso
        \post El contenido de la entrada es guardado en el parámetro implícito
    */
    void leer();



    //Escriptura

    /** @brief Escribe los datos del proceso

        \pre El parámetro implícito está inicializado
        \post Se han escrito por el canal estandar de salida los datos del proceso
    */
    void escribir() const;

};
#endif
