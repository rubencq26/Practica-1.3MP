#include "Empresa.h"

Empresa::Empresa() : nmaxcli(100) {
	this->contratos = new Contrato * [10];
	this->ncli = 0;
	this->ncon = 0;
	this->nmaxcon = 10;
}

Empresa::~Empresa() {
	for (int i = 0; i < this->ncon; i++) {//elimino los objetos contratos
		delete this->contratos[i];
	}

	delete[] this->contratos; //elimino el array de punteros

	for (int i = 0; i < this->ncli; i++) {//clientes es una tabla estatica de punteros,a si que elimino los clientes
		delete this->clientes[i];
	}
}

int Empresa::altaCliente(Cliente* c) {
	int pos = -1;
	if (this->ncli < nmaxcli) {
		this->clientes[this->ncli] = c;
		pos = ncli++;
	}
	else {
		cout << "Lo siento el cupo de clientes esta lleno";

	}
	return pos;
}

int Empresa::buscarCliente(long int dni) const {
	int pos = -1;
	for (int i = 0; i < this->ncli; i++) {
		if (this->clientes[i]->getDni() == dni) {
			pos = i;
			break;
		}
	}
	return pos;
}

void Empresa::crearContrato() {
	long int dni;
	int pos;

	cout << "Introduce dni: ";
	cin >> dni;
	pos = this->buscarCliente(dni);
	int dia, mes, anio, minHablados;
	float precio;
	char nacionalidad[100];

	if (pos == -1) {//El cliente no existe y lo debemos crear
		cout << "El cliente no existe\n ";
		char nombre[100];

		Cliente* c;
		cout << "Introduce Nombre: ";
		cin.ignore();
		cin.getline(nombre, 100);

		cout << "Introduce Fecha (dd mm aaaa):\n ";
		cout << "Dia: ";
		cin >> dia;
		cout << "Mes: ";
		cin >> mes;
		cout << "Anio: ";
		cin >> anio;
		c = new Cliente(dni, nombre, Fecha(dia, mes, anio));
		pos = this->altaCliente(c);
	}
	if (ncon == nmaxcon) {
		nmaxcon += 4;
		Contrato** cAux = new Contrato * [nmaxcon];

		for (int i = 0; i < ncon; i++) {
			cAux[i] = contratos[i];
		}

		delete[] contratos;
		contratos = cAux;
	}

	if (pos != -1) {
		int opCon;
		cout << "Tipo de contrato a abrir (1-Tarifa Plana, 2-Movil) : ";
		cin >> opCon;
		if (opCon == 2) {
			cout << "Ha elegido Contrato Movil " << endl;
			cout << "Introduce Fecha (dd mm aaaa): \n";
			cout << "Dia: ";
			cin >> dia;
			cout << "Mes: ";
			cin >> mes;
			cout << "Anio: ";
			cin >> anio;
			cout << "Minutos hablados: ";
			cin >> minHablados;
			cout << "Precio minuto: ";
			cin >> precio;
			cout << "Nacionalidad: ";
			cin >> nacionalidad;


			contratos[this->ncon] = new ContratoMovil(dni, Fecha(dia, mes, anio), precio, minHablados, nacionalidad);
			ncon++;
		}
		else {
			cout << "Ha elegido Contrato Tarifa Plana: " << endl;
			cout << "Introduce Fecha (dd mm aaaa): \n";
			cout << "Dia: ";
			cin >> dia;
			cout << "Mes: ";
			cin >> mes;
			cout << "Anio: ";
			cin >> anio;
			cout << "Minutos hablados: ";
			cin >> minHablados;
			contratos[this->ncon] = new ContratoTP(dni, Fecha(dia, mes, anio), minHablados);
			ncon++;
		}
	}
	cout << endl;
}


void Empresa::cargarDatos() {
	// Fechas de contratos y clientes
	Fecha f1(29, 2, 2001), f2(31, 1, 2002), f3(1, 2, 2002);

	// Creaci n de clientes
	this->clientes[0] = new Cliente(75547001, "Peter Lee", f1);
	this->clientes[1] = new Cliente(45999000, "Juan Perez", Fecha(29, 2, 2000));
	this->clientes[2] = new Cliente(37000017, "Luis Bono", f2);
	this->ncli = 3;  // N mero de clientes a adidos

	// Creaci n de contratos
	this->contratos[0] = new ContratoMovil(75547001, f1, 0.12, 110, "DANES");  // 110m a 0.12 /min
	this->contratos[1] = new ContratoMovil(75547001, f2, 0.09, 170, "DANES");  // 170m a 0.09 /min
	this->contratos[2] = new ContratoTP(37000017, f3, 250);                    // Tarifa plana 250m
	this->contratos[3] = new ContratoTP(75547001, f1, 312);                    // Tarifa plana 312m
	this->contratos[4] = new ContratoMovil(45999000, f2, 0.10, 202, "ESPA OL"); // 202m a 0.10 /min
	this->contratos[5] = new ContratoMovil(75547001, f2, 0.15, 80, "DANES");    // 80m a 0.15 /min
	this->contratos[6] = new ContratoTP(45999000, f3, 400);                    // Tarifa plana 400m
	this->ncon = 7;  // N mero de contratos a adidos
}


bool Empresa::cancelarContrato(int idContrato) {
	int pos = -1;
	for (int i = 0; i < ncon; i++) {
		if (contratos[i]->getIdContrato() == idContrato) {
			pos = i;
			break; // Rompemos el ciclo al encontrar el primer contrato que coincide
		}
	}

	if (pos == -1) {
		return false; // No se encontr  el contrato
	}

	delete contratos[pos]; // Liberamos la memoria del contrato a eliminar

	if (pos != ncon - 1) {
		contratos[pos] = contratos[ncon - 1]; // Movemos el  ltimo contrato a la posici n del eliminado
	}

	ncon--; // Reducimos el contador de contratos
	return true;
}



bool Empresa::bajaCliente(long int dni) {
	int pos = this->buscarCliente(dni);
	if (pos == -1) {
		cout << "No se ha encontrado el cliente ";
		return false;
	}

	delete clientes[pos]; // Liberamos la memoria del cliente

	if (pos != ncli - 1) {
		clientes[pos] = clientes[ncli - 1]; // Movemos el  ltimo cliente a la posici n eliminada
	}

	ncli--; // Reducimos el contador de clientes

	// Cancelamos todos los contratos asociados al cliente
	int i = 0;
	while (i < ncon) {
		if (contratos[i]->getDniContrato() == dni) {
			cancelarContrato(contratos[i]->getIdContrato());
		}
		else {
			i++; // Solo avanzamos el  ndice si no hemos eliminado un contrato
		}
	}

	return true;
}


int Empresa::nContratosTP() const {
	int nConTp = 0;

	for (int i = 0; i < ncon; i++) {
		if (typeid(*contratos[i]) == typeid(ContratoTP)) {
			nConTp++;
		}
	}
	return nConTp;
}

int Empresa::descuento(float porcentaje) const {
	int nAfectados = 0;
	for (int i = 0; i < ncon; i++) {
		if (typeid(*contratos[i]) == typeid(ContratoMovil)) {
			float p = static_cast<ContratoMovil*>(contratos[i])->getPrecioMinuto();
			p = p * (100 - porcentaje) / 100;
			static_cast<ContratoMovil*>(contratos[i])->setPrecioMinuto(p);
			nAfectados++;
		}

	}
	return nAfectados;
}

void Empresa::ver() const {
	const char* meses[] = { "ene", "feb", "mar", "abr", "may", "jun", "jul", "ago", "sep", "oct", "nov", "dic" };
	cout << "La empresa tiene " << this->ncli << " clientes y " << ncon << " contratos\nClientes:\n";
	for (int i = 0; i < ncli; i++) {
		cout << clientes[i]->getNombre() << " (" << clientes[i]->getDni() << " - " << clientes[i]->getFecha().getDia() << " "
			<< meses[clientes[i]->getFecha().getMes() - 1] << " " << clientes[i]->getFecha().getAnio() << ")" << endl;
	}
	cout << "Contratos: " << endl;

	for (int i = 0; i < ncon; i++) {
		if (ContratoTP* tP = dynamic_cast<ContratoTP*>(contratos[i])) {
			cout << tP->getDniContrato() << "(" << tP->getIdContrato() << " - " << tP->getFechaContrato().getDia() << " "
				<< meses[tP->getFechaContrato().getMes() - 1] << " " << tP->getFechaContrato().getAnio() << ") " << tP->getMinutosHablados() << "m, "
				<< tP->getLimiteMinutos() << "(" << tP->getPrecio() << ") -" << tP->factura() << "$" << endl;
		}
		else {
			cout << contratos[i]->getDniContrato() << " (" << contratos[i]->getIdContrato() << " - " << contratos[i]->getFechaContrato().getDia()
				<< " " << meses[contratos[i]->getFechaContrato().getMes() - 1] << " " << contratos[i]->getFechaContrato().getAnio() << ") "
				<< static_cast<ContratoMovil*>(contratos[i])->getMinutosHablados() << "m, " << static_cast<ContratoMovil*>(contratos[i])->getNacionalidad()
				<< " " << static_cast<ContratoMovil*>(contratos[i])->getPrecioMinuto() << " - " << static_cast<ContratoMovil*>(contratos[i])->factura() << "$" << endl;
		}

	}
}