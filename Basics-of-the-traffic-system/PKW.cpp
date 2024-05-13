#include "PKW.h"

PKW::PKW()
{
	cout << "default PKW Konstruktor: p_sName = " << Fahrzeug::p_sName; //<< " p_iID = " << p_iID << " p_dMaxGeschwindigkeit = " << p_dMaxGeschwindigkeit << " p_dVerbrauch = " << p_dVerbrauch << " p_dTankvolumen = " << p_dTankvolumen << endl;
}

PKW::PKW(string sName):
Fahrzeug(sName)
{
	cout << "name PKW Konstruktor: p_sName = " << p_sName << " p_iID = " << p_iID  << endl;
}

PKW::PKW(string sName, double dMaxGeschwindigkeit) :
Fahrzeug(sName, dMaxGeschwindigkeit)
{
	cout << "name, MaxGeschwindigkeit PKW: p_sName = " << p_sName << " p_iID = " << p_iID << " p_dMaxGeschwindigkeit = " << p_dMaxGeschwindigkeit << endl;
}
/**
 * initialisiert PKW mit halbe Tankinhalt
 * @param
 * @return
 */
PKW::PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen) :
Fahrzeug(sName, dMaxGeschwindigkeit),
	p_dVerbrauch(dVerbrauch),
	p_dTankvolumen(dTankvolumen),
	p_dTankinhalt(double(dTankvolumen / 2))
{
	cout << "alle Variablen PKW Konstruktor: p_sName = " << p_sName << " p_iID = " << p_iID << " p_dMaxGeschwindigkeit = " << p_dMaxGeschwindigkeit << " p_dVerbrauch = " << p_dVerbrauch << " p_dTankvolumen = " << p_dTankvolumen << endl;
}
/**
 * wenn es gibt Platz den PKW ist getankt mit dem Menge, wenn nicht den PKW wird voll getankt
 * @param double Menge abgetankte fuel
 * @return double Menge
 */
double PKW::dTanken(double dMenge){
	if(dMenge >= (p_dTankvolumen - p_dTankinhalt)){
		dMenge = p_dTankvolumen - p_dTankinhalt;
		p_dTankinhalt = p_dTankvolumen;
		cout << " getankt= " << dMenge << endl;
		return dMenge;
	}
	p_dTankinhalt = p_dTankinhalt + dMenge;
	cout << " Getankt= " << dMenge << endl;
	return dMenge;
}
/**
 * simuliert Fahrzeugs Bewegung, veraendert Tankinhalt abhaengig von der Verbrauch und die gesamte strecke in die entsprechende Takt
 * @param empty
 * @return void
 */
void PKW::vSimulieren(){
	if(p_dTankinhalt <= 0){
		p_dZeit = dGlobaleZeit;	//nur zu sagen dass das Fahrzeug simuliert ist ohne zu bewegen
		return;
	}
	double dGesamtStreckeVorSimulieren = p_dGesamtStrecke;
	Fahrzeug::vSimulieren();

	double dVerbrauchLaufendeTaktSimulation = (p_dVerbrauch/100.0) * (p_dGesamtStrecke - dGesamtStreckeVorSimulieren);
	if(dVerbrauchLaufendeTaktSimulation < p_dTankinhalt){
		p_dTankinhalt = p_dTankinhalt - dVerbrauchLaufendeTaktSimulation;
	}else{
		p_dTankinhalt = 0;
	}

}

void PKW::vAusgeben(){
	Fahrzeug::vAusgeben();
	double dGesamtVerbrauch = (p_dVerbrauch/100.0) * p_dGesamtStrecke;
	cout << setw(16) << setprecision(2) << fixed << p_dTankinhalt << setw(17) << setprecision(2) << fixed << dGesamtVerbrauch;
}

void PKW::vAusgeben(ostream& os) const{
	Fahrzeug::vAusgeben(os);
		double dGesamtVerbrauch = (p_dVerbrauch/100.0) * p_dGesamtStrecke;
		cout << setw(16) << setprecision(2) << fixed << this->p_dTankinhalt << setw(17) << setprecision(2) << fixed << dGesamtVerbrauch;
}


PKW::~PKW()
{
	cout << "Destruktor PKW: p_sName = " << p_sName << " p_iID = " << p_iID <<  " p_dMaxGeschwindigkeit = " << p_dMaxGeschwindigkeit << " p_dVerbrauch = " << p_dVerbrauch << " p_dTankvolumen = " << p_dTankvolumen << endl;
}


