#ifndef SRC_PARKEN_H_
#define SRC_PARKEN_H_

#include "Verhalten.h"
#include "Losfahren.h"

class Parken :
    public Verhalten
{
public:
	Parken(Weg& weg, double dStartzeitpunkt);
    virtual ~Parken();

    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;

private:
    double p_dStartzeitpunkt;

};



#endif /* SRC_PARKEN_H_ */
