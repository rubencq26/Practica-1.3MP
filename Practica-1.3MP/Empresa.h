#ifndef EMPRESA_H
#define EMPRESA_H

#include "Fecha.h"         // Definici�n de la clase Fecha
#include "Cliente.h"       // Definici�n de la clase Cliente
#include "Contrato.h"      // Definici�n de la clase Contrato
#include "ContratoTP.h"    // Definici�n de la clase ContratoTP
#include "ContratoMovil.h" // Definici�n de la clase ContratoMovil

using namespace std;

class Empresa {
private:
    Cliente* clientes[100];   // Array est�tico (tama�o 100) de punteros a Clientes
    int ncli;                 // N�mero de clientes actuales en el array
    const int nmaxcli;  // Capacidad m�xima del array clientes (100)

    Contrato** contratos;     // Array din�mico de punteros a Contratos (capacidad variable)
    int ncon;                 // N�mero de contratos actuales en el array
    int nmaxcon;              // Capacidad del array contratos, que crece din�micamente (10, 20, 40, ...)

protected:
    int buscarCliente(long int dni) const;  // Busca un cliente por su DNI, devuelve la posici�n o -1 si no existe

    int altaCliente(Cliente* c);            // A�ade el cliente al array clientes, devuelve la posici�n o -1 si no cabe

public:
    Empresa();                              // Constructor de la clase Empresa
    virtual ~Empresa();                     // Destructor de la clase Empresa

    // M�todos principales:
    void crearContrato();                   // Crea un nuevo contrato
    bool cancelarContrato(int idContrato);  // Cancela un contrato si existe (true si se cancela, false si no)
    bool bajaCliente(long int dni);         // Da de baja a un cliente si existe (true si lo da de baja, false si no)

    // M�todos adicionales:
    int descuento(float porcentaje) const;  // Aplica un descuento a ciertos contratos y devuelve el n�mero de afectados
    int nContratosTP() const;               // Devuelve el n�mero de contratos de tipo TP (Tarifa Plana)
    void ver() const;

    void cargarDatos();                     // Carga datos iniciales de prueba (3 clientes y 7 contratos)
};

#endif // EMPRESA_H
