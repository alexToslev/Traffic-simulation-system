#include "Fahrzeug.h"

int Fahrzeug::p_iMaxID = 0;

Fahrzeug::Fahrzeug():p_iID(++p_iMaxID)
	{
		cout << "default Konstruktor, erzeugtes Fahrzeug " << p_sName << " ID=" << p_iID << endl;
	}

Fahrzeug::Fahrzeug(string name) :
		p_sName(name),
		p_iID(++p_iMaxID)

	{
		cout << "Konstruktor nur mit Name, erzeugtes Fahrzeug " << p_sName << " ID=" << p_iID << endl;
	}

Fahrzeug::Fahrzeug(string name, double maxGeschwindigkeit) :
		p_sName(name),
		p_iID(++p_iMaxID),
		p_dMaxGeschwindigkeit((maxGeschwindigkeit>0) ? maxGeschwindigkeit:0)

	{
		cout << "Konstruktor mit Name und maxGeschwindigkeit, erzeugtes Fahrzeug " << p_sName << " maxGeschwindigkeit=" << p_dMaxGeschwindigkeit << " ID=" << p_iID << endl;
	}

void Fahrzeug::vAusgeben()
	{
		cout<< setfill(' ');
		cout << resetiosflags(ios::left) << setiosflags(ios::right) << setw(6) << p_iID << setw(20) << p_sName << setw(20) << setprecision(1) << fixed << dGeschwindigkeit() << setw(15) << setprecision(1) << fixed << p_dGesamtStrecke;
	}

void Fahrzeug::vKopf()
	{
	//TODO sled vsiako setvane da resetvam flagovete
		cout << setiosflags(ios::left) << setw(6) << "ID" << setiosflags(ios::right) << setw(20) << "Name" << setw(20) << "Geschwindigkeit" << setw(16) << "Gesamtstrecke" << setw(15) << "Tankinhalt" << setw(17) << "Gesamtverbrauch" <<endl;
		cout << setfill('-') << setw(96) << "\n"; // 96 weil \n ist 2 Symbolen
		cout << resetiosflags(ios::showbase);
	}

void Fahrzeug::vSimulieren()
	{
		double dZeitSeitLetztenSimulationsSchritt = dGlobaleZeit - p_dZeit;		//wie viel Zeit muss es simuliert sein bis GlobaleZeit
		if(dZeitSeitLetztenSimulationsSchritt>0){
			p_dGesamtZeit = p_dGesamtZeit + dZeitSeitLetztenSimulationsSchritt;
			//TODO: replace p_dMaxGeschwindigkeit with function
			p_dGesamtStrecke = p_dGesamtStrecke + dGeschwindigkeit() * dZeitSeitLetztenSimulationsSchritt;
			p_dZeit = dGlobaleZeit;		//nach Simulation muessen wir p_dZeit aktualizieren
		}

	}

double Fahrzeug::dTanken(double dMenge){
	return 0;
}
/**
 * Ausgibt Fahrzeug p_dMaxGeschwindigkeit
 * @param os output stream
 * @return double maximum Geschwindigkeit
 */
double Fahrzeug::dGeschwindigkeit() const{
	return p_dMaxGeschwindigkeit;
}
/**
 * Ausgibt Fahrzeug Daten
 * @param os output stream
 * @return void
 */
void Fahrzeug::vAusgeben(ostream& os) const{
	cout<< setfill(' ');
	cout << resetiosflags(ios::left) << setiosflags(ios::right) << setw(6) << p_iID << setw(20) << p_sName << setw(20) << setprecision(1) << fixed << dGeschwindigkeit() << setw(15) << setprecision(1) << fixed << p_dGesamtStrecke;

}
/**
 * ueberladen operator<<
 * @param os output stream
 * @param Fahrzeug const reference
 * @return os output stream
 */
ostream& operator<<(ostream& os, const Fahrzeug& fahrzeug){
	//cout<< setfill(' ');
	//cout << setiosflags(ios::right) << setw(6) << fahrzeug.p_iID << setw(20) << fahrzeug.p_sName << setw(20) << setprecision(1) << fixed << fahrzeug.dGeschwindigkeit() << setw(15) << setprecision(1) << fixed << fahrzeug.p_dGesamtStrecke;

	fahrzeug.vAusgeben(os);
	return os;
}
/**
 * ueberladen operator <
 * @param fahrzeug1
 * @param fahrzeug2
 * @return bool true if fahrzeug1<fahrzeug2, false otherwise
 */
bool operator<(const Fahrzeug& fahrzeug1, const Fahrzeug& fahrzeug2){
	if(fahrzeug1.p_dGesamtStrecke < fahrzeug2.p_dGesamtStrecke){
		return true;
	}
	return false;
}
/**
 * ueberladen operator =; copies all attributes except ID
 * @param fahrzeug
 * @return Fahrzeug this Fahrzeug
 */
Fahrzeug& Fahrzeug::operator =(const Fahrzeug& fahrzeug){
	p_sName = fahrzeug.p_sName;
	p_dMaxGeschwindigkeit = fahrzeug.p_dMaxGeschwindigkeit;
	p_dGesamtStrecke = fahrzeug.p_dGesamtStrecke;
	p_dGesamtZeit = fahrzeug.p_dGesamtZeit;
	p_dZeit = fahrzeug.p_dZeit;

	return *this;
}

//Standard Destruktor
Fahrzeug::~Fahrzeug()
	{
		cout << "Destruktor, geloeschtes Fahrzeug " << p_sName << " ID=" << p_iID << endl;
	}



