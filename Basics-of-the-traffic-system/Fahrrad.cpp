#include "Fahrrad.h"
#include<cmath>

double dFahrradGeschwindigkeit = 0.0;

Fahrrad::Fahrrad(): Fahrzeug(){
	dFahrradGeschwindigkeit = dGeschwindigkeit();
}

Fahrrad::Fahrrad(string name, double maxGeschwindigkeit) : Fahrzeug(name, maxGeschwindigkeit){
	dFahrradGeschwindigkeit = maxGeschwindigkeit;
}
/**
 * modeliert die veraenderung des Geschwindigkeits des Fahrrads - mit 10% je 20 km; aber nicht weniger als 12 km/h
 * @param empty
 * @return double fahrrad Geschwindigkeit
 */
double Fahrrad::dGeschwindigkeit() const{
	int iMalAbnehmen =  (int)(p_dGesamtStrecke/20);
	dFahrradGeschwindigkeit = dFahrradGeschwindigkeit*pow(0.9, iMalAbnehmen);

	if (dFahrradGeschwindigkeit < 12) dFahrradGeschwindigkeit = 12;

	return dFahrradGeschwindigkeit;

}



Fahrrad::~Fahrrad(){}




