#ifndef CONTRATOSOLIDARIO_H
#define CONTRATOSOLIDARIO_H

#include "ContratoMovil.h"
#include <iostream>
#include <string.h>

using namespace std;

class ContratoSolidario : public ContratoMovil {
	char* ong;
	float porcentaje;

public:
	ContratoSolidario(long int dni, Fecha f, const char* tiPa, float p, int m, const char* nac,const char* ong, float porc);
	virtual ~ContratoSolidario();
	float factura() const;
	void mostrarFactura() const;

};

#endif