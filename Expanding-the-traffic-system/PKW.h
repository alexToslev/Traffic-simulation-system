
#ifndef PKW_H_
#define PKW_H_

#include "Fahrzeug.h"
#include<limits>

class PKW: public Fahrzeug
{
private:
	double p_dVerbrauch = 0;	//Liter/100km
	double p_dTankvolumen = 55;	//Liters
	double p_dTankinhalt = double(p_dTankvolumen/2);

public:

	PKW();
	PKW(string sName);
	PKW(string sName, double dMaxGeschwindigkeit);
	PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen);

	virtual void vAusgeben() override;
	virtual double dTanken(double dMenge = numeric_limits<double>::infinity()) override;	// = numeric_limits<double>::infinity()
	virtual void vSimulieren() override;

	virtual void vAusgeben(ostream& os) const override;
	double dGeschwindigkeit()const override ;

	void vZeichnen(const Weg& weg)override;


	virtual ~PKW();
};



#endif /* PKW_H_ */
