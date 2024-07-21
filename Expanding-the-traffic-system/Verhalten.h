#ifndef SRC_VERHALTEN_H_
#define SRC_VERHALTEN_H_

#include "Weg.h"
#include "Fahrzeug.h"
class Verhalten
{
public:
	Verhalten(Weg& weg);
	virtual ~Verhalten();

	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall);
	Weg* getWeg()const;

protected:
	Weg* p_pWeg;

};



#endif /* SRC_VERHALTEN_H_ */
