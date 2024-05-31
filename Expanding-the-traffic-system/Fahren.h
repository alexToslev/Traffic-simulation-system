#ifndef SRC_FAHREN_H_
#define SRC_FAHREN_H_

#include "Verhalten.h"
#include "Streckenende.h"

class Fahren :
    public Verhalten
{
public:
    Fahren(Weg& weg);
    virtual ~Fahren();
    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override ;

};



#endif /* SRC_FAHREN_H_ */
