
#ifndef SRC_FAHRAUSNAHME_H_
#define SRC_FAHRAUSNAHME_H_

#include <exception>
#include "Fahrzeug.h"
#include "Weg.h"
using namespace std;
class Fahrausnahme : public exception
{
public:
	Fahrausnahme(Fahrzeug& fahrzeug1, Weg& weg1);
	virtual ~Fahrausnahme();

	virtual void vBearbeiten();

protected:
	Fahrzeug& p_pFahrzeugExc ;
	Weg& p_pWegExc ;
};



#endif /* SRC_FAHRAUSNAHME_H_ */
