#include "Simulationsobjekt.h"

int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt()
{
}

Simulationsobjekt::Simulationsobjekt(string name):
	p_sName(name),
	p_iID(++p_iMaxID)
{
	cout << "Konstruktor nur mit Name, erzeugtes Simulationsobject " << p_sName << " ID=" << p_iID << endl;
}



void Simulationsobjekt::vAusgeben()
{
	cout<< setfill(' ');
	cout << resetiosflags(ios::left) << setiosflags(ios::right) << setw(6) << p_iID << setw(20) << p_sName << ':';
}

/**
 * Ausgibt Simulationsobject Daten
 * @param os output stream
 * @return void
 */
void Simulationsobjekt::vAusgeben(ostream& os) const{
	cout<< setfill(' ');
	cout << resetiosflags(ios::left) << setiosflags(ios::right) << setw(6) << p_iID << setw(20) << p_sName;

}

/**
 * ueberladen operator<<
 * @param os output stream
 * @param Simulationsobjekt const reference
 * @return os output stream
 */
ostream& operator<<(ostream& os, const Simulationsobjekt& simulationsobject){
	simulationsobject.vAusgeben(os);
	return os;
}

/**
 * ueberladen operator==
 * @param Simulationsobjekt const reference
 * @return true/false
 */
bool Simulationsobjekt::operator==(const Simulationsobjekt& simulationsobjekt)
{
	return (this->p_iID == simulationsobjekt.p_iID);
}

string Simulationsobjekt::getName() const
{
	return p_sName;
}

Simulationsobjekt::~Simulationsobjekt()
{
	cout << "Destruktor, geloeschtes Simulationsobject: " << p_sName << " " << p_iID <<" "<< p_dZeit<< endl;
}




