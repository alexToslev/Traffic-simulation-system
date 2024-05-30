
#ifndef SRC_KREUZUNG_H_
#define SRC_KREUZUNG_H_

#include "Simulationsobjekt.h"
#include "Fahrzeug.h"
#include <list>
#include <memory>
#include <string>
#include<random>


class Weg;
class Kreuzung : public Simulationsobjekt
{
private:
    double p_dTankstelle;
    list <shared_ptr<Weg>>p_pWege;

public:
    Kreuzung();
    Kreuzung(string sName,double dTank);
    virtual ~Kreuzung();

    static void vVerbinde(string SNameHinWeg, string sNameRueckWeg, double dLaenge, shared_ptr<Kreuzung> pStartKeruzung, const shared_ptr<Kreuzung> pZielKeruzung, Tempolimit geschwindigkeitsBegernzung, bool bUeberholverbot = true);

    list <shared_ptr<Weg>> getP_pWege()
    {
    	return p_pWege;
    }
    double getdTankstelle()
    {
    	return p_dTankstelle;
    }

    void vTanken(Fahrzeug&);
    void vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeitpunkt);
    void vSimulieren();

    shared_ptr<Weg> pZuefaelligerWeg(Weg& ankommendeWeg);

};



#endif /* SRC_KREUZUNG_H_ */
