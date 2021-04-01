#pragma once

#include "Product.h"

class TestingRepo
{
private:
	// metode/functii private

	/*
	* Functie de test care verifica daca un produs p are atributul name identic cu name, atributul type identic cu type, atributul price identic cu price si atributul producer identic cu producer
	*/
	void testFunction(const Product& p, const string& name, const string& type, const double& price, const string& producer) const noexcept;
	
	/*
	* Metoda care testeaza functia addProduct din repo
	*/
	void runTestsRepoAddProduct() const;
	
	/*
	* Metoda care testeaza functia deleteProduct din repo
	*/
	void runTestsRepoDeleteProduct() const;
	
	/*
	* Metoda care testeaza functia modifyProduct din repo
	*/
	void runTestsRepoModifyProduct() const;
	
	/*
	* Metoda care testeaza functia searchProduct din repo
	*/
	void runTestsRepoSearchProduct() const;

public:
	// metode/functii publice

	/*
	* Constructorul default al unui obiect de clasa TestingRepo
	*/
	TestingRepo() = default;

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa TestingRepo)
	*/
	TestingRepo(const TestingRepo& ot) = delete;

	/*
	* Procedura (subrutina procedurala) care ruleaza teste pentru layerul/stratul de infrastructure = infrastructura (persistena a datelor, adica repository = repozitoriu)
	*/
	void runTestsRepo() const;
};

