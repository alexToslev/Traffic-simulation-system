
#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"

class Fahrrad: public Fahrzeug
{
public:
	Fahrrad();
	Fahrrad(string name, double maxGeschwindigkeit);

	virtual double dGeschwindigkeit() const override;
	//virtual void vAusgeben() override;
	//virtual void vSimulieren() override;
	//virtual void vAusgeben(ostream& os) override;

	void vZeichnen(const Weg& weg) override;

	virtual ~Fahrrad();

};



#endif /* FAHRRAD_H_ */
