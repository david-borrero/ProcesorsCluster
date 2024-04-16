/** @file program.cc
    @brief Código principal
*/

#include "Cluster.hh"
#include "AreaProcesosPendientes.hh"


int main()
{

    Cluster cluster;
    cluster.configurar_cluster();

    AreaProcesosPendientes area_espera;
    area_espera.leer();

    string comando;
    cin >> comando;

    string id_procesador;
    string id_prioridad;
    int id_proceso;
    Proceso p;
    int n;
    while (comando != "fin")
    {

        if (comando == "cc" or comando == "configurar_cluster")
        {
            cout << "#" << comando << endl;
            cluster.configurar_cluster();
        }

        else if (comando == "mc" or comando == "modificar_cluster")
        {
            cin >> id_procesador;

            cout << "#" << comando << " " << id_procesador << endl;
            cluster.modificar(id_procesador);
        }

        else if (comando == "ap" or comando == "alta_prioridad")
        {
            cin >> id_prioridad;
            cout << "#" << comando << " " << id_prioridad << endl;

            area_espera.anadir_prioridad(id_prioridad);

        }

        else if (comando == "bp" or comando == "baja_prioridad")
        {
            cin >> id_prioridad;
            cout << "#" << comando << " " << id_prioridad << endl;

            area_espera.eliminar_prioridad(id_prioridad);
        }

        else if (comando == "ape" or comando == "alta_proceso_espera")
        {
            cin >> id_prioridad;
            p.leer();
            cout << "#" << comando << " " << id_prioridad << ' ' << p.consultar_id() << endl;

            area_espera.anadir_proceso(p, id_prioridad);

        }

        else if (comando == "app" or comando == "alta_proceso_procesador")
        {
            cin >> id_procesador;
            p.leer();
            cout << "#" << comando << " " << id_procesador << ' ' << p.consultar_id() << endl;

            cluster.alta_proceso_procesador(p, id_procesador);
        }

        else if (comando == "bpp" or comando == "baja_proceso_procesador")
        {
            cin >> id_procesador >> id_proceso;
            cout << "#" << comando << " " << id_procesador << ' ' << id_proceso << endl;

            cluster.baja_proceso_procesador(id_proceso, id_procesador);
        }

        else if (comando == "epc" or comando == "enviar_procesos_cluster")
        {
            cin >> n;
            cout << "#" << comando << " " << n << endl;

            area_espera.enviar_procesos_cluster(cluster, n);
        }

        else if (comando == "at" or comando == "avanzar_tiempo")
        {
            cin >> n;
            cout << "#" << comando << " " << n << endl;

            cluster.avanzar_tiempo_procesadores(n);
        }

        else if (comando == "ipri" or comando == "imprimir_prioridad")
        {
            cin >> id_prioridad;
            cout << "#" << comando << " " << id_prioridad << endl;

            area_espera.imprimir_prioridad(id_prioridad);
        }

        else if (comando == "iae" or comando == "imprimir_area_espera")
        {
            cout << "#" << comando << endl;
            area_espera.imprimir();
        }

        else if (comando == "ipro" or comando == "imprimir_procesador")
        {
            cin >> id_procesador;
            cout << "#" << comando << " " << id_procesador << endl;

            cluster.imprimir_procesador(id_procesador);
        }

        else if (comando == "ipc" or comando == "imprimir_procesadores_cluster")
        {
            cout << "#" << comando << endl;
            cluster.imprimir_procesadores();
        }

        else if (comando == "iec" or comando == "imprimir_estructura_cluster")
        {
            cout << "#" << comando << endl;
            cluster.imprimir();
        }

        else if (comando == "cmp" or comando == "compactar_memoria_procesador")
        {
            cin >> id_procesador;
            cout << "#" << comando << " " << id_procesador << endl;

            cluster.compactar_memoria_procesador(id_procesador);
        }

        else if (comando == "cmc" or comando == "compactar_memoria_cluster")
        {
            cout << "#" << comando << endl;
            cluster.compactar_memoria_cluster();
        }


        cin >> comando;

    }

}
