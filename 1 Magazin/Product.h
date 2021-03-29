#pragma once

#include <string>
#include <iostream>

using std::string;

class Product
{
private:
	// atribute/campuri private (nu pot fi accesate din exteriorul clasei, doar din interiorul acesteia)
	
	string name;     // numele produsului (sir de caractere)
	string type;     // tipul produsului (sir de caractere)
	double price;    // pretul produsului (numar real in virgula flotanta/mobila cu dubla precizie)
	string producer; // producatorul produsului (sir de caractere)

public:
	// metode/functii publice (pot fi accesate din exteriorul clasei)

	/*
	* Constructorul default (il "stergem" prin calificativul delete)
	*/
	Product() = delete;

	/*
	* Constructor care primeste 4 valori (name, type, price si producer) si instantiaza un obiect de clasa Product
	* care sa aiba ca si atribute/campuri private copii ale valorile primite
	*/
	Product(string name, string type, double price, string producer) : name{ name }, type{ type }, price{ price }, producer{ producer } {
		
	}

	/*
	* Constructorul de copiere pentru obiectele de clasa Product
	* Se copiaza atribut cu atribut in obiectul curent campurile obiectului dat ca parametru/argument
	*/
	Product(const Product& ot) : name{ot.name}, type{ot.type}, price{ot.price}, producer{ot.producer} {
		std::cout << "Copiere\n";
	}

	/*
	* Metoda getter pentru a obtine atributul privat name al unui obiect de clasa Product
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): referinta (adresa) constanta la un string
	* Postconditii: metoda intoarce referinta constanta la campul/atributul name al obiectului pentru care se apeleaza
	*/
	const string& getName() const;

	/*
	* Metoda getter pentru a obtine atributul privat type al unui obiect de clasa Product
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): referinta (adresa) constanta la un string
	* Postconditii: metoda intoarce referinta constanta la campul/atributul type al obiectului pentru care se apeleaza
	*/
	const string& getType() const;

	/*
	* Metoda getter pentru a obtine atributul privat price al unui obiect de clasa Product
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): referinta (adresa) constanta la un double (numar real in dubla precizie)
	* Postconditii: metoda intoarce referinta constanta la campul/atributul price al obiectului pentru care se apeleaza
	*/
	const double& getPrice() const;

	/*
	* Metoda getter pentru a obtine atributul privat producer al unui obiect de clasa Product
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): referinta (adresa) constanta la un string
	* Postconditii: metoda intoarce referinta constanta la campul/atributul producer al obiectului pentru care se apeleaza
	*/
	const string& getProducer() const;

	/*
	* Metoda de tip setter pentru a actualiza/modifica campul/atributul privat name al unui obiect de clasa Product cu un nume nou dat ca si parametru
	* Date de intrare: referinta constanta la un string (new_name)
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	*/
	void setName(const string& new_name);

	/*
	* Metoda de tip setter pentru a actualiza/modifica campul/atributul privat type al unui obiect de clasa Product cu un tip nou dat ca si parametru
	* Date de intrare: referinta constanta la un string (new_type)
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	*/
	void setType(const string& new_type);

	/*
	* Metoda de tip setter pentru a actualiza/modifica campul/atributul privat price al unui obiect de clasa Product cu un pret nou dat ca si parametru
	* Date de intrare: referinta constanta la o variabila reala de tip double (new_price)
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	*/
	void setPrice(const double& new_price);

	/*
	* Metoda de tip setter pentru a actualiza/modifica campul/atributul privat producer al unui obiect de clasa Product cu un producator nou dat ca si parametru
	* Date de intrare: referinta constanta la un string (new_producer)
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	*/
	void setProducer(const string& new_producer);

	/*
	* Metoda care compara doua obiecte de clasa Product
	* Date de intrare: referinta constanta la un obiect de clasa Product (ot)
	* Preconditii: -
	* Date de iesire (rezultate): valoare booleana (true sau false)
	* Postconditii: cmpProducts = true  (1) - daca cele doua obiecte de clasa Product au acelasi atribut name (nume) si acelasi atribut producer (producator)
	*                           = false (0) - in caz contrar
	*/
	bool cmpProducts(const Product& ot) const;

	/*
	* Metoda care returneaza forma scrisa (text) a unui obiect de clasa Product (un string care contine valorile atributelor/campurilor private)
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): string (sir de caractere)
	* Postconditii: metoda intoarce un string care contine valorile efective ale campurilor/atributelor obiectului de clasa Product pe care se apeleaza
	*/
	string strProduct() const;
};

