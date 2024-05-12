
#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include<iostream>
#include<string>
#include<iomanip>
// Fahrzeug.h
using namespace std;

extern double dGlobaleZeit;
//erstellen wir die Fahryeug class, die ein generisches fahryeug ist
class Fahrzeug
{
//muss private sein weil es nur in dieser Klasse verwendet wird und andere Klassen keinen Zugriff darauf haben dürfen
private:
	//static, weil p_iMaxID muss bis ende des Programs existieren, es gibt zugriff von Konstruktor des Fahrzeuges und es ist eine genauere zelle in die Speicher
	static int p_iMaxID;

//protected variables koennen von die Vererbte Klassen aufgerufen werden
protected:
	string p_sName = "";
	const int p_iID = 0;
	double p_dMaxGeschwindigkeit = 0;
	double p_dGesamtStrecke = 0;
	double p_dGesamtZeit = 0;	//die gesamte Fahrzeit des Objektes
	double p_dZeit = 0;		//die Zeit, zu der das Fahrzeug zuletzt simuliert wurde

public:
	//default konstruktor
	Fahrzeug();
	//konstruktor mit parameters: eindeutiger ID und name
	Fahrzeug(string name);
	//konstruktor mit parameters: eindeutiger ID, name und maxgeschwindigkeit
	Fahrzeug(string name, double maxGeschwindigkeit);
	Fahrzeug(const Fahrzeug &fahrzeug) = delete;	//man kann nicht direkt Fahrzeug erstellen, weil Fahrzeug abstrakt ist, aber pointing to the objekt nicht kopieren mit copy constructor byte fuer byte

	virtual void vAusgeben();
	static void vKopf();	//Aufruf mit der Name des Class

	virtual void vSimulieren();

	virtual double dTanken(double dMenge);

	virtual double dGeschwindigkeit() const;

	virtual void vAusgeben(ostream& os) const;
	//friend ostream& operator<<(ostream& os, const Fahrzeug& fahrzeug);
	friend bool operator<(const Fahrzeug& fahrzeug1, const Fahrzeug& fahrzeug2);
	Fahrzeug& operator=(const Fahrzeug& fahrzeug);


	//standart destruktor
	virtual ~Fahrzeug();
};
//ueberladung von << operator, die erlaubt die Ausgabe von Fahrzeug daten
ostream& operator<<(ostream& os, const Fahrzeug& fahrzeug);



#endif
