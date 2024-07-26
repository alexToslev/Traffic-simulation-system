#include "Verhalten.h"

Verhalten::Verhalten(Weg& weg):p_pWeg(&weg)
{

}

Verhalten::~Verhalten()
{

}

double Verhalten::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	return 0;

}

Weg* Verhalten::getWeg()const
{
	return p_pWeg;
}

