#pragma once

class TestingValidation
{
public:
	/*
	* Constructorul default al unui obiect de clasa TestingValidation
	*/
	TestingValidation() = default;

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa TestingValidation)
	*/
	TestingValidation(const TestingValidation& ot) = delete;

	/*
	* Procedura (subrutina procedurala) care ruleaza teste pentru validarea de produse (layerul de validation = validare a datelor)
	*/
	void runTestsProductValidator() const;
};

