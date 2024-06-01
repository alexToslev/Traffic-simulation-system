#include "Fahren.h"

Fahren::Fahren(Weg& weg) : Verhalten(weg)
{

}

Fahren::~Fahren()
{

}
//kolko propatuva za tekushtiq vremevi interval bez da nadvishava kraq na patq
double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	if(p_pWeg->getLaenge() > aFzg.getAbschnittStrecke())
	{
		double dStreckeFuerdZeitIntervall = dZeitIntervall * aFzg.dGeschwindigkeit();
		double dRestlicheStrecke = p_pWeg->getLaenge() - aFzg.getAbschnittStrecke();
		if(dStreckeFuerdZeitIntervall > dRestlicheStrecke)
		{
			return dRestlicheStrecke;
		}
		return dStreckeFuerdZeitIntervall;

	}
	else
	{
		Streckenende* streckenende = new Streckenende(aFzg, *p_pWeg);
		throw streckenende;
	}

}

