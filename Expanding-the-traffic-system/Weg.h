
#ifndef SRC_WEG_H_
#define SRC_WEG_H_

#include "Fahrzeug.h"
#include "Tempolimit.h"
#include "Simulationsobjekt.h"
#include<list>
#include<limits>
#include<memory>
#include<iterator>
#include "vertagt_liste.h"

using namespace std;
class Fahrzeug;
class Fahrausnahme;
class Kreuzung;

class Weg: public Simulationsobjekt
{
private:
	double p_dLaenge=0.0;
	//sled iztrivane na pps ili premestvane, iteratora ne moje da se opredeli kakto i naslednika, lipsvat stapki v simulaciqta,
	//zasshtoto elementite sa premesteni nazad ili napred
	vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge;
	//unique_ptr <Fahrzeug> p_pFahrzeuge;
	Tempolimit p_eTempolimit=Autobahn;
	weak_ptr<Kreuzung> p_pZielkreuzung;
	weak_ptr<Weg> p_pRueckWeg;
	bool p_dUeberholverbot = true;

public:
	Weg();
//	Weg(string name, double laenge);
	Weg(string name, double laenge, Tempolimit p_eTempolimit = Autobahn, bool p_dUeberholverbot=true);
	//Weg(string name, double laenge, weak_ptr<Kreuzung> p_pZielkreuzung = nullptr, weak_ptr<Weg> p_pRueckWeg, Tempolimit p_eTempolimit = Autobahn, bool p_dUeberholverbot=true);
	~Weg();

	double getTempolimit();
    void vSimulieren();
    static void vKopf();
    virtual void vAusgeben(ostream& os) const override;
    double getLaenge() const;
    void vAnnahme(unique_ptr<Fahrzeug> pFahrzeug);
    void vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeitpunkt);

    unique_ptr<Fahrzeug>pAbgabe(const Fahrzeug& fahrzeug);

    //benutzen lock zu umwandeln z.b. weak ptr to shared ptr
	const shared_ptr<Weg> getRueckWeg() const {
		//shared_ptr<Weg> shrdRueckWeg= p_pRueckWeg.lock();
		return p_pRueckWeg.lock();
	}

	void setRueckWeg(const weak_ptr<Weg> &pPRueckWeg) {
		p_pRueckWeg = pPRueckWeg;
	}

	const shared_ptr<Kreuzung> getZielkreuzung() const {
		return p_pZielkreuzung.lock();
	}

	void setZielkreuzung(const weak_ptr<Kreuzung> &pPZielkreuzung) {
		p_pZielkreuzung = pPZielkreuzung;
	}

//loka e da se izbqgva zaciklqne s shrd kato se proverqva s wek prosto testva dali s asociirania shrd oshte e validen
   // void vAusgeben(ostream& o = cout)const override;


};



#endif
