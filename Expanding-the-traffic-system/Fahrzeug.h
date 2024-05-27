
#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include<iostream>
#include<string>
#include<iomanip>
#include<limits>
#include "Simulationsobjekt.h"
#include "Weg.h"
#include "SimuClient.h"
// Fahrzeug.h
using namespace std;

class Verhalten;
class Weg;	//nqma li da se poluchi rekursiq shtoto i vav weg se deklarira ppsto
class Fahren;
class Parken;

extern double dGlobaleZeit;
//erstellen wir die Fahryeug class, die ein generisches fahryeug ist
class Fahrzeug : public Simulationsobjekt
{

//protected variables koennen von die Vererbte Klassen aufgerufen werden
protected:
	double p_dMaxGeschwindigkeit = 0;
	double p_dGesamtStrecke = 0;
	double p_dGesamtZeit = 0;	//die gesamte Fahrzeit des Objektes
	unique_ptr<Verhalten> p_pVerhalten;
	double p_dStreckeGefahrenZeitIntervall = 0;	//Strecke in einen Weg fuer ein Zeit Intervall
	double p_dAbschnittStrecke = 0;	//laufende Strecke in einen Weg


public:
	//default konstruktor
	Fahrzeug();
	//konstruktor mit parameters: eindeutiger ID und name
	Fahrzeug(string name);
	//konstruktor mit parameters: eindeutiger ID, name und maxgeschwindigkeit
	Fahrzeug(string name, double maxGeschwindigkeit);
	Fahrzeug(const Fahrzeug &fahrzeug) = delete;	//man kann nicht direkt Fahrzeug erstellen, weil Fahrzeug abstrakt ist, aber pointing to the objekt; nicht kopieren mit copy constructor byte fuer byte

	virtual void vAusgeben();
	static void vKopf();	//Aufruf mit der Name des Class

	virtual void vSimulieren();

	virtual double dTanken(double dMenge = numeric_limits<double>::infinity());

	virtual double dGeschwindigkeit() const;

	virtual void vAusgeben(ostream& os) const;
	//friend ostream& operator<<(ostream& os, const Fahrzeug& fahrzeug);
	friend bool operator<(const Fahrzeug& fahrzeug1, const Fahrzeug& fahrzeug2);
	Fahrzeug& operator=(const Fahrzeug& fahrzeug);

	void vNeueStrecke(Weg& weg);
	void vNeueStrecke(Weg& weg, double dStartzeitpunkt);

	double getAbschnittStrecke();

	virtual void vZeichnen(const Weg& weg);

	//standart destruktor
	virtual ~Fahrzeug();
};
//ueberladung von << operator, die erlaubt die Ausgabe von Fahrzeug daten
ostream& operator<<(ostream& os, const Fahrzeug& fahrzeug);



#endif
