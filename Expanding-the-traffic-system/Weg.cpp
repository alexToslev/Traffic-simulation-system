#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include <boost/exception/diagnostic_information.hpp>

Weg::Weg():Simulationsobjekt()
{

}

//Weg::Weg(string name, double laenge) :
//	Simulationsobjekt(name),
//	p_dLaenge(laenge)
//{}

Weg::Weg(string name, double laenge, Tempolimit Geschwindigkeitslimit, bool p_dUeberholverbot) :
	Simulationsobjekt(name),
	p_dLaenge(laenge),
	p_eTempolimit(Geschwindigkeitslimit),
	//p_pZielkreuzung(p_pZielkreuzung),
	p_dUeberholverbot(p_dUeberholverbot)
{

}

//Weg::Weg(string name, double laenge) :
//	Simulationsobjekt(name),
//	p_dLaenge(laenge)
//{}
/*
Weg::Weg(string name, double laenge, weak_ptr<Kreuzung> p_pZielkreuzung=nullptr, weak_ptr<Weg> p_pRueckWeg, Tempolimit p_eTempolimit = Autobahn, bool p_dUeberholverbot=true) :
	Simulationsobjekt(name),
	p_dLaenge(laenge),
	p_pZielkreuzung(p_pZielkreuzung),
	p_pRueckWeg(p_pRueckWeg),
	p_eTempolimit(p_eTempolimit),
	p_dUeberholverbot(p_dUeberholverbot)
{

}
*/
double Weg::getTempolimit()
{
	return static_cast<double>(p_eTempolimit);
}

void Weg::vSimulieren()
{
	p_pFahrzeuge.vAktualisieren();
	list<std::unique_ptr<Fahrzeug>>::iterator it;
	for(it=p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++){
		try
		{
			cout <<"Simulieren Fahrzeug "<<(*it)->getName()<<" in Weg "<<getName()<<endl<<flush;
			(*it)->vSimulieren();
//			cout <<"Zeichnen Fahrzeug "<<(*it)->getName()<<" in Weg "<<getName()<<endl<<flush;
			(*it)->vZeichnen(*this);
//			cout <<"Gezeichnet Fahrzeug "<<(*it)->getName()<<" in Weg "<<getName()<<endl<<flush;
		}
		catch (Fahrausnahme* fahrausnahme)	//zashto trqbva da ima pointer
		{
			cout << boost::current_exception_diagnostic_information() << endl;
			fahrausnahme->vBearbeiten();
			delete fahrausnahme;
		}
		p_pFahrzeuge.vAktualisieren();
	}


}

void Weg::vKopf()
{
	cout << setiosflags(ios::left) << setw(6) << "ID" << "|" << setw(20) << "Name" << "|" << setw(20) << "Laenge" << "|" <<  setw(16) << "Fahrzeuge" <<endl;
	cout << setfill('-') << setw(63) << "\n"; // 63 weil \n ist 2 Symbolen
	cout << resetiosflags(ios::showbase);
}

void Weg::vAusgeben(ostream& os) const{
	list<std::unique_ptr<Fahrzeug>>::iterator it2;
	Simulationsobjekt::vAusgeben(os);
	cout << setw(20) << setprecision(1) << fixed << p_dLaenge << "( ";
//	for(it2=p_pFahrzeuge.begin(); it2 != p_pFahrzeuge.end(); it2++){
//		cout << (*it2) << endl;
//	}
	for( auto& pointer : p_pFahrzeuge ) {
		cout << pointer->getName() << " ";
	    //pointer->vAusgeben();
	}

	cout << ")";


	//cout<< setfill(' ');
	//cout << resetiosflags(ios::left) << setiosflags(ios::right) << setw(6) << p_iID << setw(20) << p_sName << setw(20) << setprecision(1) << fixed << dGeschwindigkeit() << setw(15) << setprecision(1) << fixed << p_dGesamtStrecke;

}

double Weg::getLaenge() const
{
	return p_dLaenge;
}
//zavisi kakvo se podade kato parametri na metoda Annahme, pravi Fahrzeuga dvijesht se ili parkiran
//verschieben zu neue Weg, default Fahrend
void Weg::vAnnahme(unique_ptr<Fahrzeug> pFahrzeug)
{
	try
	{
//		if(this != nullptr)
//		{
			cout<<"weg Anname starten"<<endl<<flush;
			pFahrzeug->vNeueStrecke(*this);
			p_pFahrzeuge.push_back(move(pFahrzeug));
//		}
	}
	catch(...)
	{
		cout << boost::current_exception_diagnostic_information() << endl;
	}
}
//fuer Parkende
void Weg::vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeitpunkt)
{
	try
	{
		if(this != nullptr)
		{
			cout<<"wega Anname parken"<<endl<<flush;
			pFahrzeug->vNeueStrecke(*this, dStartzeitpunkt);
			p_pFahrzeuge.push_front(move(pFahrzeug));
		}

	}
	catch(...)
	{
		cout << boost::current_exception_diagnostic_information() << endl;
	}

}

unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug)
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		if ((*it != nullptr) && (**it == fahrzeug))
		{
			unique_ptr<Fahrzeug>pFahrzeugLokal = move(*it); //lokale Variable zum Zwischenspeicherung
			p_pFahrzeuge.erase(it); //Parkende Fahrzeug element wird geloescht
			return pFahrzeugLokal;
		}
	}
	cout<<"Ne vrashta nishto Weg pAbgabe------------------------------------------"<<endl<<flush;
	return nullptr;	//zashto trqbva - trqbva da vrashta neshto ako ne vleze v cikala
}

Weg::~Weg()
{
}



