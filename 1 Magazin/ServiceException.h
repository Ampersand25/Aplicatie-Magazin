#pragma once

#include <string> // pentru std::string

using std::string;

class ServiceException
{
private:
	const string msg; // mesajul de eroare/exceptie al unui obiect de clasa ServiceException

public:
	/*
	* Constructorul default al unui obiect de clasa ServiceException
	* Folosind calificativul delete nu vom putea apela constructorul default pe un obiect de clasa ServiceException
	*/
	ServiceException() = delete;

	/*
	* Constructor al unui obiect de clasa ServiceException care primeste un string msg
	* si instantiaza un obiect de clasa ServiceException care sa aiba ca si camp/atribut privat msg o copie a valorii stringului msg
	*/
	ServiceException(const string& msg) : msg{ msg } {

	}

	/*
	* Constructorul de copiere (il setam ca si constructor default = implicit)
	*/
	ServiceException(const ServiceException& ot) = default;

	/*
	* Functie de tipul getter care returneaza/intoarce atributul privat msg al obiectului de clasa ServiceException
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire: referinta constanta la un string
	* Postconditii: getMessage() = referinta constanta la atributul privat msg (string) al obiectului de clasa ServiceException pentru care s-a apelat metoda
	*/
	const string& getMessage() const noexcept;
};