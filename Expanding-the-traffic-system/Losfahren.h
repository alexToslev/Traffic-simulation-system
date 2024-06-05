

#ifndef SRC_LOSFAHREN_H_
#define SRC_LOSFAHREN_H_

#include "Fahrausnahme.h"
class Losfahren :
    public Fahrausnahme
{
public:
	Losfahren(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Losfahren();

    void vBearbeiten() override;

};



#endif /* SRC_LOSFAHREN_H_ */
