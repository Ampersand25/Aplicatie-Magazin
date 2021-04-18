#pragma once

#include <string> // pentru std::string

using std::string;

class CosException
{
private:
	const string msg; // mesajul de eroare/exceptie al unui obiect de clasa ProductException

public:
	/*
	* Constructorul default al unui obiect de clasa CosException
	* Folosind calificativul delete nu vom putea apela constructorul default pe un obiect de clasa CosException
	*/
	CosException() = delete;

	/*
	* Constructor al unui obiect de clasa CosException care primeste un string msg
	* si instantiaza un obiect de clasa CosException care sa aiba ca si camp/atribut privat msg o copie a valorii stringului msg
	*/
	CosException(string msg) : msg{ msg } {

	}

	/*
	* Constructorul de copiere (il setam ca si constructor default = implicit)
	*/
	CosException(const CosException& ot) = default;

	/*
	* Functie operand (de tip rezultat) publica (de tip getter) care returneaza/intoarce prin numele ei atributul privat msg (string) al unui obiect de clasa CosException
	* Date de intrare: -
	* Preconditii: -
	* Date de iesrie: referinta constanta la un string
	* Postconditii: getMessage = referinta constanta la stringul msg (atributul privat al obiectului pe care apelam metoda)
	*/
	const string& getMessage() const noexcept;
};

