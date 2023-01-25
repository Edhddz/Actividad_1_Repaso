#include <iostream>
#include <fstream>

#include "Paqueteria.h"
#include "Paquete.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // _WIN32

#define C_0 0

void agregarPaquete();
void eliminarPaquete();
void listarPaquetes();
void guardarRegistroDePaquetes();
void cargarRegistroDePaquetes();
void borrarRegistroLocal();
int menuPrincipal();
void pausa();

enum {AGREGAR = 1, ELIMINAR, MOSTRAR, GUARDAR, RECUPERAR, SALIR};

using namespace std;

void inicializarPrograma();

Paqueteria inventario;

int main()
{
    inicializarPrograma();
    int opcion;
    do
    {
        opcion = menuPrincipal();

        switch(opcion)
        {
        case AGREGAR:agregarPaquete();break;
        case ELIMINAR:eliminarPaquete();break;
        case MOSTRAR:listarPaquetes();break;
        case GUARDAR:guardarRegistroDePaquetes();break;
        case RECUPERAR:cargarRegistroDePaquetes();break;
        case SALIR: borrarRegistroLocal(); cout << "Fin del programa...."; break;
        default: cout << "Opción incorrecta!....";
        }
        pausa();
    }while(opcion != SALIR);

    return 0;
}

void inicializarPrograma(){setlocale(LC_CTYPE, "spanish"); cargarRegistroDePaquetes();}
void pausa(){cout << "Presiona entrar para continuar..."; cin.get();}

void agregarPaquete()
{
    int id;
    string origen, destino;
    float peso;

    cout << "Ingresa el ID del paquete: ";
    cin >> id;
    cin.get();
    cout << "Ingresa el origen del paquete: ";
    getline(cin, origen);
    cout << "Ingresa el destino del paquete: ";
    getline(cin, destino);
    cout << "Ingresa el peso del paquete: ";
    cin >> peso;
    cin.get();

    inventario.insertarInicio(id, origen, destino, peso);

    cout << "Paquete registrado..." <<endl;
}
int menuPrincipal()
{
    int opcion;

    system(CLEAR);
    cout << "Paquetería" <<endl <<endl
         << "1. Agregar Paquete" <<endl
         << "2. Eliminar Paquete" <<endl
         << "3. Mostrar Paquetes Registrados" <<endl
         << "4. Guardar Paquetes" <<endl
         << "5. Recuperar Paquetes" <<endl
         << "6. Salir" <<endl <<endl
         << "Elige una opción: ";
    cin >> opcion;
    cin.get();
    system(CLEAR);

    return opcion;
}
void eliminarPaquete()
{
    cout << "Se eliminó el paquete con el id: " << inventario.eliminarInicio() <<endl;
    listarPaquetes();
}
void listarPaquetes()
{
    if(inventario.cantidadRegistros() > C_0)
    {
        cout << "PAQUETES REGISTRADOS" <<endl <<endl << inventario.mostrarPaquetes();
    }
    else{cout << REGISTRO_VACIO <<endl;}
}
void guardarRegistroDePaquetes()
{
    cout << "Guardando registros..." <<endl;
    inventario.guardarRegistros();
}
void cargarRegistroDePaquetes()
{
    inventario.recuperarRegistros();
    cout << "Registros cargados...";
}
void borrarRegistroLocal(){inventario.liberarMemoria();}
