#include "Parken.h"
#include "Losfahren.h"

Parken::Parken(Weg& weg, double dStartzeitpunkt) : Verhalten(weg), p_dStartzeitpunkt(dStartzeitpunkt)
{
}

Parken::~Parken()
{
}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	if(dGlobaleZeit>=p_dStartzeitpunkt)
	{

		Losfahren* losfahren = new Losfahren(aFzg, *p_pWeg);
		throw losfahren;
	}
	else
	{
	return 0;
	}
}
