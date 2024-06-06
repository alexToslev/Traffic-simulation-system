#include "Losfahren.h"

Losfahren::Losfahren(Fahrzeug& fahrzeug, Weg& weg) : Fahrausnahme(fahrzeug, weg)
{
}

Losfahren::~Losfahren()
{
}

void Losfahren::vBearbeiten()
{
	cout << "Ausnahme: Losfahren, fuer " << p_pFahrzeugExc.getName() << " die befindet sich auf " << p_pWegExc.getName() << endl<<flush;

	unique_ptr<Fahrzeug> pFahrzeugKopie = p_pWegExc.pAbgabe(p_pFahrzeugExc); //Parkende Fahrzeug wird abgegeben an pFahrzeugKopie um von die Liste zu entfernen
	p_pWegExc.vAnnahme(move(pFahrzeugKopie)); //Wird auf Weg gesetzt als fahrende fahrzeug wenn die Startzeit kommt

}


