#include<iostream>
#include<memory>
#include<vector>
#include<iomanip>
#include<cmath>
#include<limits>
#include<algorithm>
#include"Fahrzeug.h"
#include"PKW.h"
#include"Fahrrad.h"
using namespace std;

double dGlobaleZeit = 0.0; //current global time
/**
 * erzeugt Fahrzeugs mit smart Pointers; gibt Smart Pointers zu vector
 * @param empty
 * @return void
 */
void vAufgabe_1(){
	Fahrzeug f1;
	Fahrzeug f2 ("car1");
	Fahrzeug* f3= new Fahrzeug ();

	unique_ptr<Fahrzeug> unqptrF4 = make_unique<Fahrzeug>("Citroen DS");
	unique_ptr<Fahrzeug> unqptrF5 = make_unique<Fahrzeug>("Mercedes Benz");

	shared_ptr<Fahrzeug> shrdptrF6 = make_shared<Fahrzeug>("VW");
	shared_ptr<Fahrzeug> shrdptrF7 = make_shared<Fahrzeug>("Renault Bulgar");
	cout << "shrdptrF6 vor Speicherung in shrdptrF6cpy " << shrdptrF6.use_count() << endl;

	shared_ptr<Fahrzeug> shrdptrF6cpy = shrdptrF6;
	cout << "shrdptrF6 nach Speicherung in shrdptrF6cpy " << shrdptrF6.use_count() << endl;

	vector<unique_ptr<Fahrzeug>> vct1;
	vct1.push_back(move(unqptrF4));
	vct1.push_back(move(unqptrF5));
	vct1.clear();

	vector<shared_ptr<Fahrzeug>> vct2;
	vct2.push_back(shrdptrF6);
	vct2.push_back(move(shrdptrF7));
	vct2.clear();


	delete f3;

	cout << endl;
}
/**
 * user gibt parameters zu 3 Fahrzeugs; sie sind simuliert in bestimmte Zeitspanne und Takt laenge; ausgegebt die simulierte Verten der Fahrzeugen
 * @param empty
 * @return void
 */
void vAufgabe_1a()
	{
		vector<unique_ptr<Fahrzeug>> vctFahrzeugListe;
		string l_sName;
		double l_dMaxGeschwindigkeit;
		for(int i=1; i<=3; i++){
			cout << i << ". Fahrzeugsname = ";
			cout.flush();
			getline(cin >> ws, l_sName);
			//cout << endl;
			cout << i << ". " << l_sName<< " Maximal Geschwindigkeit = ";
			cout.flush();
			cin >> l_dMaxGeschwindigkeit;
			//cout << endl;

			unique_ptr<Fahrzeug> unqptrFahrzeug = make_unique<Fahrzeug>(l_sName, l_dMaxGeschwindigkeit);
			vctFahrzeugListe.push_back(move(unqptrFahrzeug));
		}


		double dZeittakt = 1.0/6.0, dZeitspanne = 1;
		Fahrzeug::vKopf();

		for(dGlobaleZeit=0; dGlobaleZeit<=dZeitspanne; dGlobaleZeit=dGlobaleZeit+dZeittakt){
			cout << " dGlobalzeit " << dGlobaleZeit << endl;
			for(int i=0; i<3; i++){
				vctFahrzeugListe[i]->vSimulieren();
				vctFahrzeugListe[i]->vAusgeben();
				cout << endl;

			}
		}

		cout << endl;
	}
/**
 * user sagt wie viel Fahrzeugs simuliert werden in bestimmte Zeitspanne und Takt laenge; ausgegebt die simulierte Werten der Fahrzeugen;
 * beruecksichtig sind die Verbrauch und die abnehmende Geschwindigkeit des Fahrraeder
 * @param empty
 * @return void
 */
void vAufgabe_2()
{
	int iAnzahlPKW = 0;
	int iAnzahlFahrrad = 0;
	cout << "Anzahl PKW = ";
	cin >> iAnzahlPKW;
	cout << "Anzahl Fahrraeder = ";
	cin >> iAnzahlFahrrad;

	vector<unique_ptr<Fahrzeug>> vctFahrzeug;

	/*
	unique_ptr<Fahrzeug> unqptrFahrzeugpPKWrad = make_unique<PKW>("vw Golf", 120, 10, 55);
	vctPKWFahrrad.push_back(move(unqptrFahrzeugpPKWrad));
	unqptrFahrzeugpPKWrad = make_unique<PKW>("wartburg", 100, 20, 50);
	vctPKWFahrrad.push_back(move(unqptrFahrzeugpPKWrad));

	unqptrFahrzeugpPKWrad = make_unique<Fahrrad>("leader", 40);
	vctPKWFahrrad.push_back(move(unqptrFahrzeugpPKWrad));
	unqptrFahrzeugpPKWrad = make_unique<Fahrrad>("rector", 30);
	vctPKWFahrrad.push_back(move(unqptrFahrzeugpPKWrad));
	*/

	string sNametemp;
	double dMaxGeschwindigkeittemp, dVerbrauchtemp, dTankVolumetemp;

	for(int i=1; i<=iAnzahlPKW; i++){
		cout << i << ". PKW name = ";
		cout.flush();
		getline(cin >> ws, sNametemp);
		cout << i << ". " << sNametemp<< " Maximal Geschwindigkeit, Verbrauch und Tankvolume = ";
		cout.flush();
		cin >> dMaxGeschwindigkeittemp >> dVerbrauchtemp >> dTankVolumetemp;

		unique_ptr<Fahrzeug> unqptrPKW = make_unique<PKW>(sNametemp, dMaxGeschwindigkeittemp, dVerbrauchtemp, dTankVolumetemp);
		vctFahrzeug.push_back(move(unqptrPKW));
		cout << endl;
	}

	for(int i=1; i<=iAnzahlFahrrad; i++){
		cout << i << ". Fahrrad name = ";
		cout.flush();
		getline(cin >> ws, sNametemp);
		//cout << endl;
		cout << i << ". " << sNametemp<< " Maximal Geschwindigkeit = ";
		cout.flush();
		cin >> dMaxGeschwindigkeittemp;

		unique_ptr<Fahrrad> unqptrFahrrad = make_unique<Fahrrad>(sNametemp, dMaxGeschwindigkeittemp);
		vctFahrzeug.push_back(move(unqptrFahrrad));
		cout << endl;
	}

	double dZeittakt = 1.0, dSimulationZeitspanne = 9.0;
	double dTankZeit = 3.0;		//je 3 Stunden muessen die PKWs getankt werden
	int iVctSize = vctFahrzeug.size();
	Fahrzeug::vKopf();
	for(dGlobaleZeit=0; dGlobaleZeit<=dSimulationZeitspanne; dGlobaleZeit=dGlobaleZeit+dZeittakt){
		cout << " dGlobalzeit " << dGlobaleZeit << endl;
		for(int i=0; i < iVctSize; i++){
			vctFahrzeug[i]->vSimulieren();
			vctFahrzeug[i]->vAusgeben();
			//je 3 Stunden muessen die PKWs getankt werden
			double dEpsilon = 0.05;
			if((fmod(dGlobaleZeit, dTankZeit) <= dEpsilon) && (dGlobaleZeit != 0)){		//TODO kak da proveri dali e PKW i kade trabva da se polzwa modul
				vctFahrzeug[i]->dTanken(numeric_limits<double>::infinity());
			}
			 cout << endl;
		}
		cout << endl;

	}

cout << endl;
}
/**
 * due ueberladete Operators sind getestet
 * @param empty
 * @return void
 */
void vAufgabe_3()
{
	cout << "vAufgabe_3" << endl;
	PKW* pkw1 = new PKW("Opel", 180.0, 7.0, 55.0);
	Fahrrad* rad1 = new Fahrrad("Scott", 50);
	PKW* pkw2 = pkw1;		// ueberladete operator =
	cout << *pkw2 << endl;		// ueberladete Ausgabeoperator <<

	dGlobaleZeit = 3;
	pkw1->vSimulieren();
	pkw2->vSimulieren();
	rad1->vSimulieren();
	pkw1->vKopf();
	//pkw1->vAusgeben();
	cout << *pkw1 << endl << *rad1 << endl << *pkw2 << endl;	// ueberladete Ausgabeoperator <<

	/*rad1->vSimulieren();
	rad1->vKopf();
	rad1->vAusgeben();*/

	cout << "Vergleich von PKW- und Fahrradgesamtstrecken mit dem ueberladeten operator < (0 - falsch, 1 - richtig): " << endl << "pkw1<rad1? = ";
	cout <<((Fahrzeug*)(&pkw1)<(Fahrzeug*)(&rad1)) << endl;	 //casting - umwandlung von pkw in Fahrzeug
	cout << "rad1<pkw1? = ";
	cout <<((Fahrzeug*)(&rad1)<(Fahrzeug*)(&pkw1)) << endl;

	delete pkw1;
	delete pkw2;
	delete rad1;

}

/*
void vAufgabe_Probe() {
    Fahrzeug* pF1 = new PKW("Audi", 150, 8, 55);
    dGlobaleZeit = 0.0;
    Fahrzeug::vKopf();
    dGlobaleZeit = 5.0;
    cout << endl << "Globalezeit = " << dGlobaleZeit << endl;
    pF1->vSimulieren();
    std::cout << *pF1 << endl;
    delete pF1;
    char c;
    std::cin >> c;
}
*/
/*
void vAufgabe_AB1() {

    int l = 0; // Laufindex für gezielte AUsgabe
    vector<int> ausgabe{13};
    double dTakt = 0.4;

    std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(make_unique <PKW>("Audi", 229, 9.6, 55));
    vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 24.7));
    for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dTakt)
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
            Fahrzeug::vKopf();
        }

        for (int i = 0; i < (int) vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken(numeric_limits<double>::infinity());
            }
            if (itL != ausgabe.end()) {
                std::cout << *vecFahrzeuge[i] << endl;
            }
        }
        l++;
    }
    char c;
    std::cin >> c;
}
*/
static void vPrintoutDelimeter(){
	cout <<"=========================================================================" << endl;
}
int main()
{
	vAufgabe_1();
	vPrintoutDelimeter();
	vAufgabe_1a();
	vPrintoutDelimeter();
	vAufgabe_2();
	vPrintoutDelimeter();
	vAufgabe_3();
//	vPrintoutDelimeter();
//	vAufgabe_Probe();
//	vAufgabe_AB1();


/*

*/

}

