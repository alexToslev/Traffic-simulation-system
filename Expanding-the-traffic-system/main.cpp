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
#include"Weg.h"
#include"Simulationsobjekt.h"
#include"SimuClient.h"
#include"SimuClientSocket.h"
#include"vertagt_liste.h"
#include<random>
#include"Kreuzung.h"

#include <exception>
#include <typeinfo>
#include <stdexcept>
#include <boost/exception/diagnostic_information.hpp>

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

void vAufgabe_4()
{
	Weg* weg1 = new Weg("weg", 100.0, Autobahn,true);

	weg1->vKopf();
	cout << endl;
	cout << *weg1 << endl;

	delete weg1;

}

void vAufgabe_5()
{
	Weg weg ("weg", 100, Autobahn,true);
	unique_ptr<Fahrzeug>f1 = make_unique<Fahrzeug>("BMW");
	unique_ptr<Fahrzeug>f2 = make_unique<Fahrzeug>("Audi");
	unique_ptr<Fahrzeug>f3 = make_unique<Fahrzeug>("BMX");

	weg.vAnnahme(move(f1));
	weg.vAnnahme(move(f2));
	weg.vAnnahme(move(f3));
	cout << weg << endl;
	dGlobaleZeit = 1;
	weg.vSimulieren();
	weg.vKopf();
	cout << weg << endl;
}

void vAufgabe_6()
{
	bInitialisiereGrafik(800, 500, "localhost", "8666");
	Weg wegAutobahn ("str1", 500, Autobahn,true);
	Weg wegInnerorts ("str2", 500, Innerorts,true);
	int iKoordinaten[] = { 700, 250, 100, 250 };
	bZeichneStrasse(wegAutobahn.getName(), wegInnerorts.getName(), 500, 2, iKoordinaten);

	unique_ptr<Fahrzeug>f1 = make_unique<PKW>("BMW", 189, 1, 60);
	unique_ptr<Fahrzeug>f2 = make_unique<PKW>("Audi", 180, 6, 45);
	unique_ptr<Fahrzeug>f3 = make_unique<Fahrrad>("BMX", 30);

	unique_ptr<Fahrzeug>f4 = make_unique<PKW>("Toyota", 160, 4, 42);
	unique_ptr<Fahrzeug>f5 = make_unique<PKW>("Mercedes", 210, 5, 70);
	unique_ptr<Fahrzeug>f6 = make_unique<Fahrrad>("Scott", 55);

	wegAutobahn.vAnnahme(move(f1),2);	//parkend, wann zu starten
	wegAutobahn.vAnnahme(move(f2));
	wegAutobahn.vAnnahme(move(f3));

	wegInnerorts.vAnnahme(move(f4));
	wegInnerorts.vAnnahme(move(f5),3);
	wegInnerorts.vAnnahme(move(f6));


	dGlobaleZeit=0;
	for(int i=0; i<=20; i++){
		cout << "takt " << i << "=========================================================================" << endl;
		wegAutobahn.vSimulieren();
		cout << wegAutobahn << endl;

		wegInnerorts.vSimulieren();
		cout << wegInnerorts << endl;

		dGlobaleZeit= dGlobaleZeit + 0.3;
		vSetzeZeit(dGlobaleZeit);
		vSleep(1000);

	}
	vBeendeGrafik();

}

void vAufgabe_6a()
{
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1, 10);
	int zuf = dist(device);

	vertagt::VListe<int> vListRandom;

	for(int i=0; i<=10; i++){
		vListRandom.push_back(zuf);
		zuf = dist(device);
	}
	vListRandom.vAktualisieren();

	cout << "Print nach Aktualisieren:" << endl;
	for(auto it = vListRandom.begin();it!=vListRandom.end();it++){
		cout << *it <<endl;
	}

	for(auto it = vListRandom.begin();it!=vListRandom.end();it++){
		if (*it > 5)
		{
			vListRandom.erase(it);
		}
	}

	cout << "List erase Elemente >5, Print vor Aktualisieren:" << endl;
	for(auto it = vListRandom.begin();it!=vListRandom.end();it++){
		cout << *it <<endl;
	}
	cout << endl;
	vListRandom.vAktualisieren();
	cout << "List erase Elemente >5, Print nach Aktualisieren:" << endl;
	for(auto it = vListRandom.begin();it!=vListRandom.end();it++){
		cout << *it <<endl;
	}
	cout << endl;
	vListRandom.push_front(6);
	vListRandom.push_back(8);
	vListRandom.vAktualisieren();
	cout << "Print nach bearbeitund des Listes und nach aktualisieren: " << endl;
	for (auto it = vListRandom.begin(); it != vListRandom.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;

}

void vAufgabe_7()
{
	bInitialisiereGrafik(1000, 860);
	//, "localhost", "8666"
	/*
	Weg weg12 ("W12", 40, Innerorts);
	Weg weg21 ("W21", 40, Innerorts);

	Weg weg23a ("W23a", 115, Autobahn);
	Weg weg32a ("W32a", 115, Autobahn);

	Weg weg23b ("W23b", 40, Innerorts);
	Weg weg32b ("W32b", 40, Innerorts);

	Weg weg24 ("W24", 55, Innerorts);
	Weg weg42 ("W42", 55, Innerorts);

	Weg weg34 ("W34", 85, Autobahn);
	Weg weg43 ("W43", 85, Autobahn);

	Weg weg44a ("W44a", 130, Landstrasse);
	Weg weg44b ("W44b", 130, Landstrasse);
	*/

	shared_ptr<Kreuzung> kr1 = make_shared<Kreuzung> ("Kr1", 0);
	shared_ptr<Kreuzung> kr2 = make_shared<Kreuzung> ("Kr2", 1000);
	shared_ptr<Kreuzung> kr3 = make_shared<Kreuzung> ("Kr3", 0);
	shared_ptr<Kreuzung> kr4 = make_shared<Kreuzung> ("Kr4", 0);
//	Kreuzung kr1 ("Kr1", 0);
//	Kreuzung kr2 ("Kr2", 1000);
//	Kreuzung kr3 ("Kr3", 0);
//	Kreuzung kr4 ("Kr4", 0);

	/*
	Kreuzung::vVerbinde("W12", "W21", weg12.getLaenge(), kr1, kr2, Innerorts, true);
	Kreuzung::vVerbinde("W23a", "W32a", weg23a.getLaenge(), kr2, kr3, Autobahn, true);
	Kreuzung::vVerbinde("W23b", "W32b", weg23b.getLaenge(), kr2, kr3, Innerorts, true);
	Kreuzung::vVerbinde("W24", "W42", weg24.getLaenge(), kr2, kr4, Innerorts, true);
	Kreuzung::vVerbinde("W34", "W43", weg34.getLaenge(), kr3, kr4, Autobahn, true);
	Kreuzung::vVerbinde("W44a", "W44b", weg44a.getLaenge(), kr4, kr4, Landstrasse, true);
*/
	Kreuzung::vVerbinde("W12", "W21", 40, kr1, kr2, Innerorts, true);
	Kreuzung::vVerbinde("W23a", "W32a", 115, kr2, kr3, Autobahn, true);
	Kreuzung::vVerbinde("W23b", "W32b", 40, kr2, kr3, Innerorts, true);
	Kreuzung::vVerbinde("W24", "W42", 55, kr2, kr4, Innerorts, true);
	Kreuzung::vVerbinde("W34", "W43", 85, kr3, kr4, Autobahn, true);
	Kreuzung::vVerbinde("W44a", "W44b", 130, kr4, kr4, Landstrasse, true);

	int iKoordinatenStr1[] = { 680, 40, 680, 300 };
	int iKoordinatenStr2[] = { 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 };
	int iKoordinatenStr3[] = { 680, 300, 680, 570 };
	int iKoordinatenStr4[] = { 680, 300, 320, 300 };
	int iKoordinatenStr5[] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300 };
	int iKoordinatenStr6[] = { 320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320,300 };


/*
	bZeichneStrasse(weg12.getName(), weg21.getName(), weg12.getLaenge(), 2, iKoordinatenStr1);
	bZeichneStrasse(weg23a.getName(), weg32a.getName(), weg23a.getLaenge(), 6, iKoordinatenStr2);
	bZeichneStrasse(weg23b.getName(), weg32b.getName(), weg23b.getLaenge(), 2, iKoordinatenStr3);
	bZeichneStrasse(weg24.getName(), weg42.getName(), weg24.getLaenge(), 2, iKoordinatenStr4);
	bZeichneStrasse(weg34.getName(), weg43.getName(), weg34.getLaenge(), 5, iKoordinatenStr5);
	bZeichneStrasse(weg44a.getName(), weg44b.getName(), weg44a.getLaenge(), 7, iKoordinatenStr6);
	*/
	bZeichneStrasse("W12", "W21", 40, 2, iKoordinatenStr1);
	bZeichneStrasse("W23a", "W32a", 115, 6, iKoordinatenStr2);
	bZeichneStrasse("W23b", "W32b", 40, 2, iKoordinatenStr3);
	bZeichneStrasse("W24", "W42", 55, 2, iKoordinatenStr4);
	bZeichneStrasse("W34", "W43", 85, 5, iKoordinatenStr5);
	bZeichneStrasse("W44a", "W44b", 130, 7, iKoordinatenStr6);

	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	unique_ptr<Fahrzeug>f1 = make_unique<PKW>("BMW", 200, 7, 50);
	unique_ptr<Fahrzeug>f2 = make_unique<PKW>("Audi", 180, 6, 45);
	unique_ptr<Fahrzeug>f3 = make_unique<Fahrrad>("BMX", 30);

	unique_ptr<Fahrzeug>f4 = make_unique<PKW>("Toyota", 160, 4, 42);
	unique_ptr<Fahrzeug>f5 = make_unique<PKW>("Mercedes", 210, 5, 70);
	unique_ptr<Fahrzeug>f6 = make_unique<Fahrrad>("Scott", 55);

	kr1->vAnnahme(move(f1), 0.01);
	kr1->vAnnahme(move(f2), 0.1);
	kr1->vAnnahme(move(f3), 0.2);
	kr1->vAnnahme(move(f4), 0.3);
	kr1->vAnnahme(move(f5), 0.4);
	kr1->vAnnahme(move(f6), 0.5);

	try
	{
		for(int i=0; i<=100; i++){
			cout << "takt " << i << "=========================================================================" << endl<<flush;
			kr1->vSimulieren();
			cout<<"kreuzung2-----------------"<<endl<<flush;
			kr2->vSimulieren();
			cout<<"kreuzung3-----------------"<<endl<<flush;
			kr3->vSimulieren();
			cout<<"kreuzung4-----------------"<<endl<<flush;
			kr4->vSimulieren();


			dGlobaleZeit= dGlobaleZeit + 0.1;
			vSetzeZeit(dGlobaleZeit);
			vSleep(500);

		}
	}
	catch(...)
	{
	    cout << boost::current_exception_diagnostic_information() << endl<<std::flush;
	};
	vBeendeGrafik();

}
//void Test()
//{
//	vertagt::VListe<int> li;
//	for (int i = 0; i < 10; ++i)
//		li.push_back(i);
//	li.vAktualisieren();
//	for(auto it = li.begin(); it != li.end(); ++it)
//		if (*it % 2 == 1)
//			li.erase(it);
//	li.push_back(10);
//	li.push_front(-1);
//	cout <<"";
//
//	//cout << li;
//}

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
//	vAufgabe_1();
//	vPrintoutDelimeter();
//	vAufgabe_1a();
//	vPrintoutDelimeter();
//	vAufgabe_2();
//	vPrintoutDelimeter();
//	vAufgabe_3();
//	vPrintoutDelimeter();
//	vAufgabe_4();
//	vPrintoutDelimeter();
//	vAufgabe_5();
//	vPrintoutDelimeter();
//	vAufgabe_6();
//	vPrintoutDelimeter();
//	vAufgabe_6a();
//	try
//	{
		vPrintoutDelimeter();
		vAufgabe_7();
//	}
//	catch(...)
//	{
//		cout << boost::current_exception_diagnostic_information() << endl;
//	}

//	Test();


//	vPrintoutDelimeter();
//	vAufgabe_Probe();
//	vAufgabe_AB1();


/*

*/

}

