#include "Console.h"
#include "ServiceException.h"
#include "RepoException.h"
#include "ProductException.h"

#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

void UI::showMenu() const
{
	cout << "Meniul aplicatiei:\n";
	cout << "adaugare   - adauga un produs in magazin\n";
	cout << "stergere   - sterge un produs din magazin care are un nume si un producator dati\n";
	cout << "modificare - modifica un produs din magazin\n";
	cout << "cautare    - cauta un produs in magazin dupa un nume si un producator introdusi\n";
	cout << "afisare    - tipareste in consola toate produsele disponibile in magazin\n";
	cout << "filtrare   - filtrare produse dupa: pret, nume, producator\n";
	cout << "sortare    - sortare produse dupa: nume, pret, nume + tip\n";
	cout << "clear      - curata ecranul (se sterge continutul terminalului)\n";
	cout << "exit       - inchide aplicatia\n";
}

void UI::addUI() const
{
	string name, type, price_str, producer;
	
	cout << "Nume: ";
	getline(cin, name);
	
	cout << "Tip: ";
	getline(cin, type);
	
	cout << "Pret: ";
	getline(cin, price_str);
	
	try {
		srv.verifyIfDouble(price_str);
	}
	catch (const ServiceException& se) {
		cerr << endl << se.getMessage() << endl;
		return;
	}
	
	const auto& price = stod(price_str, nullptr);
	
	cout << "Producator: ";
	getline(cin, producer);
	
	cout << endl;
	
	try {
		srv.add(name, type, price, producer);
		cout << "Adaugarea s-a realizat cu succes!\n\n";
	}
	catch (const ProductException& pe) {
		cerr << pe.getMessage() << endl;
	}
	catch (const RepoException& re) {
		cerr << re.getMessage() << endl;
	}
}

void UI::delUI() const
{
	string name, producer;
	
	cout << "Nume: ";
	getline(cin, name);
	
	cout << "Producator: ";
	getline(cin, producer);
	
	cout << endl;
	
	try {
		srv.del(name, producer);
		cout << "Stergerea s-a realizat cu succes!\n\n";
	}
	catch (const ServiceException& se) {
		cerr << se.getMessage() << endl;
	}
	catch (const RepoException& re) {
		cerr << re.getMessage() << endl;
	}
}

void UI::modifyUI() const
{
	string name, type, price_str, producer;
	
	cout << "Nume: ";
	getline(cin, name);
	
	cout << "Tip: ";
	getline(cin, type);
	
	cout << "Pret: ";
	getline(cin, price_str);
	
	try {
		srv.verifyIfDouble(price_str);
	}
	catch (const ServiceException& se) {
		cerr << endl << se.getMessage() << endl;
		return;
	}
	
	const auto& price = stod(price_str, nullptr);
	
	cout << "Producator: ";
	getline(cin, producer);
	
	cout << endl;
	
	try {
		srv.modify(name, type, price, producer);
		cout << "Modificarea s-a realizat cu succes!\n\n";
	}
	catch (const ProductException& pe) {
		cerr << pe.getMessage() << endl;
	}
	catch (const RepoException& re) {
		cerr << re.getMessage() << endl;
	}
}

void UI::searchUI() const
{
	string name, producer;
	
	cout << "Nume: ";
	getline(cin, name);
	
	cout << "Producator: ";
	getline(cin, producer);
	
	cout << '\n';
	
	try {
		const auto& p = srv.search(name, producer);
		cout << "Produsul cu numele " << name << " si producatorul " << producer << " este:\n" << p.strProduct() << endl;
	}
	catch (const ServiceException& se) {
		cerr << se.getMessage() << endl;
	}
	catch (const RepoException& re) {
		cerr << re.getMessage() << endl;
	}
}

void UI::typeProducts(const vector<Product>& products) const
{
	auto cont{ 0 };

	for (const auto& p : products)
		cout << "\nProdusul #" << ++cont << ":\n" << p.strProduct();
	
	cout << endl;
}

void UI::printAllUI() const
{
	try{
		const auto& products = srv.getAll();
		
		cout << "Produsele din magazin sunt:\n";
		typeProducts(products);
	}
	catch(const RepoException& re){
		cerr << re.getMessage() << endl;
	}
}

void UI::showFilterCriterions() const
{
	cout << "Criterii de filtrare:\n";
	cout << "1 - dupa pret\n";
	cout << "2 - dupa nume\n";
	cout << "3 - dupa producator\n";
}

string UI::readFilterCrt() const
{
	showFilterCriterions();
	
	cout << "\nIntroduceti criteriu de filtrare dorit [1|2|3]: ";
	string crt;
	getline(cin, crt);
	
	while (crt != "1" && crt != "2" && crt != "3")
	{
		cerr << "Criteriu de filtrare invalid!\n";
		
		cout << "\nReintroduceti criteriu dorit [1|2|3]: ";
		getline(cin, crt);
	}
	
	return crt;
}

string UI::readFilter(const string& crt) const
{	
	if (crt == "1")
		cout << "\nAlegeti pretul dupa care sa se faca filtrarea: ";
	else if (crt == "2")
		cout << "\nAlegeti numele dupa care sa se faca filtrarea: ";
	else
		cout << "\nAlegeti producatorul dupa care sa se faca filtrarea: ";
	
	string filter;
	getline(cin, filter);
	
	return filter;
}

string UI::readFilterSign() const
{
	cout << "\nAlegeti cum sa fie pretul produselor filtrate in raport cu pretul introdus [<|=|>]: ";
	string sign;
	getline(cin, sign);
	
	while (sign != "<" && sign != "=" && sign != ">")
	{
		cerr << "Semnul de inegalitate intre preturi este invalid!\n";
		
		cout << "\nReintroduceti semnul de inegalitate dorit [<|=|>]: ";
		getline(cin, sign);
	}
	
	return sign;
}

void UI::filterUI() const
{
	const auto crt = readFilterCrt();
	const auto filter = readFilter(crt);
	
	string sign{ "-" };
	
	if (crt == "1")
		sign = readFilterSign();
	try {
		const auto& products = srv.filterProducts(crt, filter, sign);
		
		if (!products.size())
			cout << "\nNu exista produse in magazin cu ";
		else
			cout << "\nProdusele din magazin cu ";
		
		if (crt == "1")
		{
			cout << "pretul ";
			
			if (sign == "<")
				cout << "mai mic (strict) decat ";
			else if (sign == "=")
				cout << "egal cu ";
			else
				cout << "mai mare (strict) decat ";
		}
		else if (crt == "2")
			cout << "numele ";
		else
			cout << "producatorul ";
		
		cout << filter;
		
		if (products.size())
		{
			cout << " sunt:\n";
			typeProducts(products);
		}
		else
			cout << "\n\n";
	}
	catch (const RepoException& re) {
		cerr << endl << re.getMessage() << endl;
	}
	catch (const ServiceException& se) {
		cerr << endl << se.getMessage() << endl;
	}
}

void UI::showSortingCriterions() const
{
	cout << "Criterii de sortare:\n";
	cout << "1 - dupa nume\n";
	cout << "2 - dupa pret\n";
	cout << "3 - dupa nume + tip\n";
}

string UI::readSortingCrt() const
{
	showSortingCriterions();

	cout << "\nIntroduceti criteriu de sortare dorit [1|2|3]: ";
	string crt;
	getline(cin, crt);
	
	while (crt != "1" && crt != "2" && crt != "3")
	{
		cerr << "Criteriu de sortare invalid!\n";

		cout << "\nReintroduceti criteriu dorit [1|2|3]: ";
		getline(cin, crt);
	}
	
	return crt;
}

void UI::showSortingOrders() const
{
	cout << "\nOrdinea de sortare poate fi:\n";
	cout << "c - crescator\n";
	cout << "d - descrescator\n";
}

string UI::readSortingOrd() const
{
	showSortingOrders();

	cout << "\nIntroduceti ordinea de sortare dorita [c|d]: ";
	string ord;
	getline(cin, ord);
	
	while (ord != "c" && ord != "C" && ord != "d" && ord != "D")
	{
		cerr << "Ordine de sortare invalida!\n";
		
		cout << "\nReintroduceti ordinea dorita [c|d]: ";
		getline(cin, ord);
	}
	
	return ord;
}

void UI::sortUI() const
{
	const auto crt = readSortingCrt(); // criteriul de sortare
	const auto ord = readSortingOrd(); // ordinea de sortare

	try {
		const auto& products = srv.sortProducts(crt, ord);
		
		cout << "\nProdusele din magazin ordonate ";
		
		if(ord == "d" || ord == "D")
			cout << "des";

		cout << "crescator dupa ";
		
		if (crt == "1")
			cout << "nume";
		else if (crt == "2")
			cout << "pret";
		else
			cout << "nume + tip";
		
		cout << " sunt:\n";
		
		typeProducts(products);
	}
	catch (const RepoException& re) {
		cerr << endl << re.getMessage() << endl;
	}
}

void UI::clearUI() const noexcept
{
	system("CLS");
}

void UI::debugUI() const
{
	srv.add("iaurt"         , "produse lactate", 4.63   , "Danone");
	srv.add("chipsuri"      , "snaksuri"       , 9.6    , "Lays");
	srv.add("ton in ulei"   , "conserve"       , 13.9841, "Tonno Rio Mare");
	srv.add("boia"          , "condimente"     , 0.999  , "Delikat");
	srv.add("pasta de dinti", "igiena"         , 7.12   , "Colgate");
	srv.add("iaurt"         , "produse lactate", 5.013  , "Milka UK");
	srv.add("sare"          , "condimente"     , 11     , "Maggi");
	srv.add("parmezan"      , "condimente"     , 8.301  , "Delikat");
	srv.add("chipsuri"      , "snaksuri"       , 1.53   , "Chio");
	srv.add("chipsuri"      , "snaksuri"       , 9.1    , "Pringles");
	
	cout << "Cele 10 produse au fost adaugate cu succes in magazin!\n\n";
}

void UI::runApp() const
{
	auto run{ true };
	const vector<string> commands{ "adaugare", "stergere", "modificare",
								   "cautare", "afisare", "filtrare",
								   "sortare", "clear", "exit",
								   "debug" };
	string cmd;
	
	while (run)
	{
		showMenu();
		
		cout << "\n>>>";
		getline(cin, cmd);
		
		if (srv.cmpStrings(cmd, commands.at(0)))
			addUI();
		else if (srv.cmpStrings(cmd, commands.at(1)))
			delUI();
		else if (srv.cmpStrings(cmd, commands.at(2)))
			modifyUI();
		else if (srv.cmpStrings(cmd, commands.at(3)))
			searchUI();
		else if (srv.cmpStrings(cmd, commands.at(4)))
			printAllUI();
		else if (srv.cmpStrings(cmd, commands.at(5)))
			filterUI();
		else if (srv.cmpStrings(cmd, commands.at(6)))
			sortUI();
		else if (srv.cmpStrings(cmd, commands.at(7)))
			clearUI();
		else if (srv.cmpStrings(cmd, commands.at(8)))
			run = false;
		else if (srv.cmpStrings(cmd, commands.at(9)))
			debugUI();
		else
			cerr << "Comanda invalida!\n\n";
	}
}