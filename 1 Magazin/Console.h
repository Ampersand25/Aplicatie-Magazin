#pragma once

#include "Service.h"

class UI
{
private:
	Service& srv; // referinta la un obiect de clsa Service
	
	/*
	* Procedura care afiseaza/tipareste meniul aplicatiei (lista de comenzi disponibile)
	*/
	void showMenu() const;

	/*
	* Procedura care incearca adaugarea unui produs in magazin
	*/
	void addUI() const;
	
	/*
	* Procedura care incearca stergerea unui produs din magazin
	*/
	void delUI() const;

	/*
	* Procedura care incearca modificarea unui produs din magazin
	*/
	void modifyUI() const;

	/*
	* Procedura care cauta un produs in magazin
	*/
	void searchUI() const;

	/*
	* Procedura care afiseaza toate produsele existente in magazin
	*/
	void printAllUI() const;

	/*
	* Procedura care filtreaza produsele din magazin dupa un anumit criteriu
	*/
	void filterUI() const;

	/*
	* Procedura care sorteaza/ordoneaza produsele existente in magazin dupa un anumit criteriu si o ordine data (crescator sau descrescator)
	*/
	void sortUI() const;
	
	/*
	* Procedura care curata terminalul/consola aplicatiei (sterge continutul de pe ecran)
	*/
	void clearUI() const;

	/*
	* Procedura care adauaga 10 obiecte de clasa Product (10 inregistrari) in lista din repo (adica in magazin)
	*/
	void debugUI() const;
	
public:
	/*
	* Constructorul default de instantiere (care nu primeste niciun argument/parametru)
	* Impiedicam folosirea constructorului default prin "stergerea" lui folosind calificativul delete
	*/
	UI() = delete;

	/*
	* Definim un constructor al clasei care primeste un obiect de clasa Service (referinta la acest obiect)
	* Constructorul va instantia obiectul curent de clasa UI, populand atributul privat srv al acestuia cu obiectul primit ca argument
	*/
	UI(Service& srv) :srv{ srv } {

	}

	/*
	* Constructorul default de copiere
	* Impiedicam copierea obiectelor de clasa UI prin intermediul calificativului delete
	*/
	UI(const UI& ot) = delete;

	/*
	* Procedura care ruleaza aplicatia
	*/
	void runApp() const;
};

