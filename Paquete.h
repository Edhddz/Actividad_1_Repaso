#ifndef PAQUETE_H_INCLUDED
#define PAQUETE_H_INCLUDED

#include <iostream>
#include <sstream>

#define DEFAULTEXT "undefined"
#define C_0 0

class Paquete
{
    int id;
    std::string origen;
    std::string destino;
    float peso;

public:
    Paquete();
    Paquete(int id, std::string origen, std::string destino, float peso);
    void setId(int id);
    int getId();
    void setOrigen(std::string origen);
    std::string getOrigen();
    void setDestino(std::string destino);
    std::string getDestino();
    void setPeso(float peso);
    float getPeso();
    std::string dameInfo();
};

Paquete::Paquete()
{
    id = C_0;
    origen = DEFAULTEXT;
    destino = DEFAULTEXT;
    peso = C_0;
}

Paquete::Paquete(int id, std::string origen, std::string destino, float peso)
{
    Paquete();

    if(id > C_0){setId(id);}
    if(peso > C_0){setPeso(peso);}
    setOrigen(origen);
    setDestino(destino);
}

void Paquete::setId(int id)
{
    this->id = id;
}
int Paquete::getId()
{
    return id;
}
void Paquete::setOrigen(std::string origen)
{
    this->origen = origen;
}
std::string Paquete::getOrigen()
{
    return origen;
}
void Paquete::setDestino(std::string destino)
{
    this->destino = destino;
}
std::string Paquete::getDestino()
{
    return destino;
}
void Paquete::setPeso(float peso)
{
    this->peso = peso;
}
float Paquete::getPeso()
{
    return peso;
}
std::string Paquete::dameInfo()
{
    std::stringstream ss;

    ss << "Nombre: " << this->getId() <<std::endl
       << "Origen: " << this->getOrigen() <<std::endl
       << "Destino: " << this->getDestino() <<std::endl
       << "Peso: " << this->getPeso() <<std::endl;

    return ss.str();
}

#endif // PAQUETE_H_INCLUDED
