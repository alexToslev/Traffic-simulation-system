#include "Streckenende.h"
#include <boost/exception/diagnostic_information.hpp>

Streckenende::~Streckenende()
{
}

Streckenende::Streckenende(Fahrzeug& fahrzeug, Weg& weg) : Fahrausnahme(fahrzeug, weg)
{
}

void Streckenende::vBearbeiten()
{
	try
	{
		cout << "Ausnahme: Streckenende, fuer " << p_pFahrzeugExc.getName() << " die befindet sich auf " << p_pWegExc.getName() << endl<<flush;

		shared_ptr<Kreuzung> zielKreuzung = p_pWegExc.getZielkreuzung();
//		cout << "++++1 streckenende bearbeiten "<<endl;
		bLoescheFahrzeug(p_pFahrzeugExc.getName());
//		cout << "++++2 streckenende bearbeiten "<<endl;
		shared_ptr<Weg> neuWeg = (*zielKreuzung).pZuefaelligerWeg(p_pWegExc);
//		cout << "++++3 streckenende bearbeiten "<<endl;
		(*zielKreuzung).vTanken(p_pFahrzeugExc);
//		cout << "++++4 streckenende bearbeiten "<<endl;
		unique_ptr<Fahrzeug> pFahrzeugKopie = p_pWegExc.pAbgabe(p_pFahrzeugExc);	//fahrende Fahrzeuge wird von den List entfernt wenn es die Streckenende erreichen
//		cout << "++++5 streckenende bearbeiten "<<endl;
		//trqbva li da go slagam na patq


		cout << setiosflags(ios::left) << setw(14) << "ZEIT" << setw(40) <<": " <<dGlobaleZeit << endl<<flush
			 << setw(14) << "KREUZUNG" << setw(40) << ": " << (*zielKreuzung).getName() << "  "<<(*zielKreuzung).getdTankstelle()<<endl<<flush
			 << setw(14) << "WECHSEL" << setw(40) << ": " << p_pWegExc.getName() << " -> "<<(*neuWeg).getName()<<endl<<flush
			 << setw(14) << "FAHRZEUG" << setw(40) << ": " << (*pFahrzeugKopie).getName()<<endl<<flush;

		(*neuWeg).vAnnahme(move(pFahrzeugKopie));
	}

	catch(...)
	{
		cout << boost::current_exception_diagnostic_information() << endl;
	}

}

