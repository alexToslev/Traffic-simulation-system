#ifndef SRC_STRECKENENDE_H_
#define SRC_STRECKENENDE_H_

#include "Fahrausnahme.h"
#include "Kreuzung.h"
#include <iomanip>


class Streckenende :
    public Fahrausnahme
{
public:
    void vBearbeiten() override;
    virtual ~Streckenende();
    Streckenende(Fahrzeug& fahrzeug, Weg& weg);
};




#endif /* SRC_STRECKENENDE_H_ */
