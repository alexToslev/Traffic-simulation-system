#include "Kreuzung.h"
#include "Weg.h"
#include<limits>
#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <ctime>
//using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

Kreuzung::Kreuzung() : Simulationsobjekt()
{
	cout << "Default Kreuzung" << " ID = " <<p_iID <<" Name: " << p_sName << endl;
}

Kreuzung::Kreuzung(string sName, double dTankstelle) : Simulationsobjekt(sName), p_dTankstelle(dTankstelle)
{
	cout << "Kreuzung" << " ID = " <<p_iID <<" Name: " << p_sName << endl;
}

Kreuzung::~Kreuzung()
{
	cout << "Kreuzung geloescht"<<endl;
}

//setting rueckwegs zu hinwegs und umgekehrts, sets start und ziel Kreuzung
//KreuzungZiel ist ZielKreuzung fuer Hinweg
//StartKreuzung ist ZielKreuzung fuer Rueckweg
void Kreuzung::vVerbinde(string sNameHinWeg, string sNameRueckWeg, double dLaenge, shared_ptr<Kreuzung> pStartKeruzung, shared_ptr<Kreuzung> pZielKeruzung, Tempolimit geschwindigkeitsBegernzung, bool bUeberholverbot)
{
	shared_ptr<Weg> pWegHin = make_shared<Weg>(sNameHinWeg, dLaenge, geschwindigkeitsBegernzung, bUeberholverbot);
	shared_ptr<Weg> pWegRueck = make_shared<Weg>(sNameRueckWeg, dLaenge, geschwindigkeitsBegernzung, bUeberholverbot);
	pWegHin->setRueckWeg(pWegRueck);
	pWegRueck->setRueckWeg(pWegHin);

	//start kreuzunga e otkadeto tragva hinweg, a ot zielkreuzunga tragva wegrueck
	weak_ptr<Kreuzung> pKreuzungStart = pStartKeruzung;
	weak_ptr<Kreuzung> pKreuzungZiel = pZielKeruzung;

	pWegHin->setZielkreuzung(pKreuzungZiel);
	pWegRueck->setZielkreuzung(pKreuzungStart);

	pStartKeruzung->p_pWege.push_back(pWegHin);
	pZielKeruzung->p_pWege.push_back(pWegRueck);
}

void Kreuzung::vTanken(Fahrzeug& fahrzeug)
{
	if(p_dTankstelle > 0)
	{
		double getankt = fahrzeug.dTanken(numeric_limits<double>::infinity());
		cout <<endl <<"Kreuzung "<<getName() << " ------------Getankt:" << getankt <<endl<<flush;
		p_dTankstelle = p_dTankstelle - getankt;
		if(p_dTankstelle<0)
		{
			p_dTankstelle=0;
		}
	}


}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeitpunkt)
{
	vTanken(*pFahrzeug);
	p_pWege.front()->vAnnahme(move(pFahrzeug), dStartzeitpunkt);	//Fahrzeug wird parkend an den ersten abgehenden Weg stellt
}

void Kreuzung::vSimulieren()
{
	list<std::shared_ptr<Weg>>::iterator it;
	for(it=p_pWege.begin(); it != p_pWege.end(); it++){

		(*it)->vSimulieren();

	}
}

//vrashta sluchaen pat no ne tozi po koito e doshal, ako e zadanena ulica se vrashta po obratniq pat
shared_ptr<Weg> Kreuzung::pZuefaelligerWeg(Weg& ankommendeWeg)
{

	if(p_pWege.size() == 1)
	{
		cout <<ankommendeWeg.getName()<<" ist Sackgasse"<<endl<<flush;
		return ankommendeWeg.getRueckWeg();
	}
	else
	{
		int i = 1;
		shared_ptr<Weg> pZuefaelligeWeg;
		auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		while(i<=p_pWege.size())
		{
			static std::mt19937 device(millisec_since_epoch);
			cout << "Zufaelliger Weg milisec" << millisec_since_epoch <<endl;
			std::uniform_int_distribution<int> dist(1, p_pWege.size());
			cout << "Zufaelliger Weg p_pWege.size() " << p_pWege.size() <<endl;
			int iRandomWegNumber = dist(device);
			cout << "Zufaelliger Weg iRandomWegNumber " << iRandomWegNumber <<endl;
		//	auto iterator = p_pWege.begin();	//ds gibt die erste element

//			advance(iterator, iRandomWegNumber);	//statt for schleife, es fortschreiten die Iterator mit iRandomWegNumber
			for (auto it = p_pWege.begin(); it != p_pWege.end(); it++, i++)
			{
				if (i == iRandomWegNumber)
				{
					pZuefaelligeWeg = *it; //zwischengespeichern
					break;
				}
			}
			cout << "Zufaelliger Weg Iterator Weg " << (*pZuefaelligeWeg).getName() << " ||||||| " <<(*ankommendeWeg.getRueckWeg()).getName()<<endl;
			if(pZuefaelligeWeg != ankommendeWeg.getRueckWeg())
			{
				return pZuefaelligeWeg;
			}
			cout << " Ankommende weg ist gewaelt wie die zufaellige Weg --- Anfang neue Zyklus" << endl << flush;
			//i++;
		}
		return pZuefaelligeWeg;

	}



	return 0;
}








//if((*iterator) != ankommendeWeg.getRueckWeg())
//{
//	return (*iterator);
//}


