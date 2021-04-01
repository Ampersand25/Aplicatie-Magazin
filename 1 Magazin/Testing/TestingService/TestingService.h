#pragma once

#include "Product.h"

class TestingService
{
private:
	// metode private (pot fi apelate doar din interiorul clasei)

	/*
	* Metoda care testeaza functia cmpStrings din fisierul antet/header Business.h
	*/
	void runTestsServiceCmpStrings() const;

	/*
	* Metoda care testeaza functia verifyIfDouble din fisierul antet/header Business.h
	*/
	void runTestsServiceVerifyIfDouble() const;

	/*
	* Metoda care testeaza functia add din fisierul antet/header Business.h
	*/
	void runTestsServiceAdd() const;

	/*
	* Metoda care testeaza functia del din fisierul antet/header Business.h
	*/
	void runTestsServiceDel() const;

	/*
	* Metoda care testeaza functia modify din fisierul antet/header Business.h
	*/
	void runTestsServiceModify() const;

	/*
	* Metoda care testeaza functia search din fisierul antet/header Business.h
	*/
	void runTestsServiceSearch() const;

	/*
	* Metoda care testeaza functia getAll din fisierul antet/header Business.h
	*/
	void runTestsServiceGetAll() const;

	/*
	* Functie de test care verifica daca un produs p are atributul name identic cu name, atributul type identic cu type, atributul price identic cu price si atributul producer identic cu producer
	*/
	void testFunction(const Product& p, const string& name, const string& type, const double& price, const string& producer) const noexcept;
	
	/*
	* Metoda care testeaza functia filterProducts (de filtrare a produselor dupa un criteriu) din fisierul header/antet Business.h
	*/
	void runTestsServiceFilterProducts() const;

	/*
	* Metoda care testeaza functia sortProducts din fisierul antet/header Business.h
	*/
	void runTestsServiceSortProducts() const;

public:
	// metode publice (pot fi apelate din exteriorul clasei)

	/*
	* Constructorul default al unui obiect de clasa TestingService
	*/
	TestingService() = default;

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa TestingService)
	*/
	TestingService(const TestingService& ot) = delete;

	/*
	* Procedura (subrutina procedurala) care ruleaza teste pentru layerul/stratul de business (services = servicii)
	*/
	void runTestsService() const;
};