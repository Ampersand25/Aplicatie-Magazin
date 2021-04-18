#pragma once

#include <string> // pentru std::string

using std::string;

class RepoException
{
private:
	const string msg; // mesajul de eroare/exceptie al unui obiect de clasa RepoException

public:
	/*
	* Constructorul default al unui obiect de clasa RepoException
	* Folosind calificativul delete nu vom putea apela constructorul default pe un obiect de clasa RepoException
	*/
	RepoException() = delete;

	/*
	* Constructor al unui obiect de clasa RepoException care primeste un string msg
	* si instantiaza un obiect de clasa RepoException care sa aiba ca si camp/atribut privat msg o copie a valorii stringului msg
	*/
	RepoException(string msg) : msg{ msg } {
	
	}

	/*
	* Constructorul de copiere (il setam ca si constructor default = implicit)
	*/
	RepoException(const RepoException& ot) = default;

	/*
	* Functie de tipul getter care returneaza/intoarce atributul privat msg al obiectului de clasa RepoException
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire: referinta constanta la un string
	* Postconditii: getMessage() = referinta constanta la atributul privat msg (string) al obiectului de clasa RepoException pentru care s-a apelat metoda
	*/
	const string& getMessage() const noexcept;
};

