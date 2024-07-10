
#ifndef SRC_SIMULATIONSOBJEKT_H_
#define SRC_SIMULATIONSOBJEKT_H_

#include<iostream>
#include<iomanip>

using namespace std;

class Simulationsobjekt
{
//muss private sein weil es nur in dieser Klasse verwendet wird und andere Klassen keinen Zugriff darauf haben dürfen
private:
	//static, weil p_iMaxID muss bis ende des Programs existieren, es gibt zugriff von Konstruktor des Fahrzeuges und es ist eine genauere zelle in die Speicher
	static int p_iMaxID;

protected:
	string p_sName = "";
	const int p_iID = 0;
	double p_dZeit = 0;		//Simulationszeit

public:
	Simulationsobjekt();
	Simulationsobjekt(string name);
	Simulationsobjekt(const Simulationsobjekt &simulationsobjekt) = delete;	//man kann nicht direkt Simulationsobject erstellen, weil Simulationsobject abstrakt ist, aber pointing to the objekt; nicht kopieren mit copy constructor byte fuer byte


	virtual void vAusgeben();
	virtual void vAusgeben(ostream& os) const;
	bool operator==(const Simulationsobjekt& simulationsobjekt);
	string getName() const; //gets the name of an object


	virtual ~Simulationsobjekt();

};
//ueberladung von << operator, die erlaubt die Ausgabe von Simulationsobject daten
ostream& operator<<(ostream& os, const Simulationsobjekt& simulationsobjekt);


#endif
