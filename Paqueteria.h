#ifndef PAQUETERIA_H_INCLUDED
#define PAQUETERIA_H_INCLUDED

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>

#include "Paquete.h"

#define REGISTRO_VACIO "No se han registrado paquetes"
#define ERROR_DE_APERTURA_DE_ARCHIVO "No fue posible abrir el archivo de registros..."
#define FILE_NAME "inventario.txt"
#define DELIMITADOR_DE_CAMPOS '|'
#define SEPARADOR_DE_REGISTROS '\n'
#define C_0 0
#define PRECISION 2

class Nodo
{
public:
    Paquete* paquete;
    Nodo* siguiente;
};

class Paqueteria
{
    Nodo* inicio;

public:
    Paqueteria();
    void insertarInicio(int& id, std::string& origen, std::string& destino, float& peso);
    int eliminarInicio();
    std::string mostrarPaquetes();
    void liberarMemoria();
    void guardarRegistros();
    void recuperarRegistros();
    int cantidadRegistros();
};

Paqueteria::Paqueteria()
{
    inicio = NULL;
}

void Paqueteria::insertarInicio(int& id, std::string& origen, std::string& destino, float& peso)
{
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->paquete = new Paquete(id, origen, destino, peso);
    nuevoNodo->siguiente = NULL;

    if(inicio == NULL){inicio = nuevoNodo;}
    else
    {
        Nodo* temp = inicio;
        while(temp->siguiente != NULL){temp = temp->siguiente;}
        temp->siguiente = nuevoNodo;
    }
}
int Paqueteria::eliminarInicio()
{
    int valorEliminado;

    valorEliminado = inicio->paquete->getId();
    Nodo* temp = inicio;
    inicio = inicio->siguiente;
    delete temp;

    return valorEliminado;
}
std::string Paqueteria::mostrarPaquetes()
{
    std::stringstream ss;
    int contadorRegistros = C_0;

    Nodo* nodoTemporal = inicio;
    while(nodoTemporal != NULL)
    {
        contadorRegistros++;
        ss <<std::endl << "Registro " << contadorRegistros <<std::endl
           << "ID: " << nodoTemporal->paquete->getId() <<std::endl
           << "Origen: " << nodoTemporal->paquete->getOrigen() <<std::endl
           << "Destino: " << nodoTemporal->paquete->getDestino() <<std::endl
           << "Peso: " << nodoTemporal->paquete->getPeso() <<std::endl;

        nodoTemporal = nodoTemporal->siguiente;
    }
    return ss.str();
}
void Paqueteria::liberarMemoria()
{
    Nodo* nodoABorrar = inicio;
    Nodo* nodoTemporal;

    while(nodoABorrar != NULL)
    {
        nodoTemporal = nodoABorrar;
        nodoABorrar = nodoTemporal->siguiente;
        delete nodoTemporal;
    }
}
int Paqueteria::cantidadRegistros()
{
    int contador = C_0;
    Nodo* nodoActual = inicio;
    Nodo* nodoTemporal;

    while(nodoActual != NULL)
    {
        nodoTemporal = nodoActual;
        nodoActual = nodoTemporal->siguiente;
        contador++;
    }
    return contador;
}
void Paqueteria::guardarRegistros()
{
    int totalRegistros = cantidadRegistros();
    std::ofstream archivoInventario;
    Nodo* nodoTemporal = inicio;

    if(totalRegistros > C_0)
    {
        archivoInventario.open(FILE_NAME, std::ios::out);
        if(archivoInventario.is_open())
        {
            archivoInventario << totalRegistros << DELIMITADOR_DE_CAMPOS;
            archivoInventario << std::fixed << std::setprecision(PRECISION);

            while(nodoTemporal != NULL)
            {
                archivoInventario << nodoTemporal->paquete->getId() << DELIMITADOR_DE_CAMPOS
                                  << nodoTemporal->paquete->getOrigen() << DELIMITADOR_DE_CAMPOS
                                  << nodoTemporal->paquete->getDestino() << DELIMITADOR_DE_CAMPOS
                                  << nodoTemporal->paquete->getPeso() << SEPARADOR_DE_REGISTROS;

                nodoTemporal = nodoTemporal->siguiente;
            }
            archivoInventario.close();
        }
        else{std::cout << ERROR_DE_APERTURA_DE_ARCHIVO;}
    }
    else{std::cout << REGISTRO_VACIO <<std::endl;}
}
void Paqueteria::recuperarRegistros()
{
    std::ifstream archivoInventario;
    int id, posicion, cantidadRegsitros;
    std::string origen, destino, cadena, subcadena;
    float peso;
    char separador;

    archivoInventario.open(FILE_NAME, std::ios::in);

    if(archivoInventario.is_open())
    {
        archivoInventario >> cantidadRegsitros >> separador;
        for(int i = C_0; i<cantidadRegsitros; i++)
        {
            std::getline(archivoInventario, cadena);
            posicion = cadena.find_first_of(DELIMITADOR_DE_CAMPOS, C_0);
            subcadena = cadena.substr(C_0, posicion);
            id = std::stoi(subcadena);
            cadena = cadena.substr(posicion+1);
            posicion = cadena.find_last_of(DELIMITADOR_DE_CAMPOS);
            subcadena = cadena.substr(posicion+1);
            peso = std::stof(subcadena);
            cadena = cadena.substr(C_0, posicion);
            posicion = cadena.find_first_of(DELIMITADOR_DE_CAMPOS, C_0);
            subcadena = cadena.substr(C_0, posicion);
            origen = subcadena;
            destino = cadena.substr(posicion+1);

            insertarInicio(id, origen, destino, peso);
        }
        archivoInventario.close();
    }
    else{std::cout << ERROR_DE_APERTURA_DE_ARCHIVO;}
}

#endif // PAQUETERIA_H_INCLUDED
