#pragma once

class TestingUtils
{
private:
	// metode private (nu pot fi apelate din exteriorul clasei, ci doar din interiorul acesteia)

	/*
	* Metoda privata pentru testarea functiei compareStr din fisierul antet (header) Utils.h
	*/
	void runTestsUtilsCompareStr() const;

	/*
	* Metoda privata pentru testarea functiei isDouble din fisierul antet (header) Utils.h
	*/
	void runTestsUtilsIsDouble() const;

public:
	// metode publice (pot fi apelate atat din interiorul cat si din exteriorul clasei)

	/*
	* Constructorul default al unui obiect de clasa TestingUtils
	*/
	TestingUtils() = default;

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa TestingUtils)
	*/
	TestingUtils(const TestingUtils& ot) = delete;

	/*
	* Metoda care ruleaza teste pentru functiile de pe stratul/layerul Utils (functii utilitare)
	*/
	void runTestsUtils() const;
};