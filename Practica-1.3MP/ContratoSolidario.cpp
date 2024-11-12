#include "ContratoSolidario.h"

ContratoSolidario::ContratoSolidario(long int dni, Fecha f, const char* tiPa, float p, int m, const char* nac,const char* ong, float porc) : ContratoMovil(dni, f,tiPa, p, m, nac) {
	this->ong = new char[strlen(ong) + 1];
	strcpy(this->ong, ong);
	this->porcentaje = porc;
}

ContratoSolidario::~ContratoSolidario() {
	delete[] this->ong;
}

float ContratoSolidario::factura() const{
	float fact = ContratoMovil::factura();
	fact = (100 - porcentaje) * fact / 100;
	return fact;
}

void ContratoSolidario::mostrarFactura() const{
	cout << "La factura total del contrato es de: " << ContratoMovil::factura() << "$ un " << porcentaje << " % se va a la ONG " << ong << " así que la empresa se queda con " << factura() << "$" << endl;

}
