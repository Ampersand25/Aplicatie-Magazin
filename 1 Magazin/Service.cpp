#include "Service.h"
#include "ServiceException.h"
#include "Utils.h"

#include <algorithm> // for std::sort, std::copy_if, std::back_inserter
#include <exception> // for std::exception
#include <string>    // for stoi (string to integer build-in function)
#include <iostream>  // for back_inserter

using std::sort;
using std::copy_if;
using std::back_inserter;
using std::exception;

bool Service::cmpStrings(const string& str_1, const string& str_2) const noexcept
{
	const Utils utils;
	return utils.compareStr(str_1, str_2); // comparam case insensitive cele doua stringuri (str_1 si str_2)
}

void Service::verifyIfDouble(const string& str) const
{
	const Utils utils;

	if (!utils.isDouble(str)) // verificam daca str contine reprezentarea unui numar real
		throw ServiceException("[!]Pretul introdus nu este un numar real!\n"); // aruncam/ridicam exceptie de clasa ServiceException
}

void Service::add(const string& name, const string& type, const double& price, const string& producer)
{
	Product product{ name, type, price, producer }; // cream produsul cu numele name, tipul type, pretul price si producatorul producer
	
	valid.validateProduct(product); // validam obiectul de clasa Product (produsul) creat (instantiat) anterior/precedent
	repo.addProduct(product); // incercam sa adaugam in repo produsul product
}

void Service::del(const string& name, const string& producer)
{
	// validam numele name si producatorul producer
	string err{ "" }; // lista de erori (string)
	
	if (!name.size())     // if (name == "")
		err += "[!]Nume invalid!\n";       // name invalid
	if (!producer.size()) // if (producer == "")
		err += "[!]Producator invalid!\n"; // producer invalid

	if(err.size()) // lista de erori contine cel putin o eroare (name si/sau producer sunt stringuri vide, deci invalide)
		throw ServiceException(err); // aruncam exceptie de clasa ServiceException cu mesajul de eroare/exceptie err

	repo.deleteProduct(name, producer); // incercam sa stergem produsul cu numele name si producatorul producer din magazin (repo)
	
	// pe linia asta se ajunge daca exista cel putin un produs (obiect de clasa Product) cu numele name si producatorul producer
	// cu alte cuvinte, metoda publica deleteProduct a obiectului repo nu a aruncat exceptie (deci stergerea s-a realizat cu succes)
	cosCumparaturi.stergeProduseCos(name, producer); // stergem/eliminam toate produsele din cosul de cumparaturi cu numele name si producatorul producer
}

void Service::modify(const string& name, const string& type, const double& price, const string& producer)
{
	Product product{ name, type, price, producer }; // cream produsul cu numele name, tipul type, pretul price si producatorul producer
	
	valid.validateProduct(product); // validam obiectul de clasa Product (produsul) creat (instantiat) anterior/precedent
	repo.modifyProduct(product); // incercam sa modificam un produs care are numele name si producatorul producer din repo (daca acesta exista) cu noul produs product
	
	// pe linia asta se ajunge daca exista cel putin un produs (obiect de clasa Product) product in magazin (repository)
	// cu alte cuvinte, metoda publica modifyProduct a obiectului repo nu a aruncat exceptie (deci modificarea s-a realizat cu succes)
	cosCumparaturi.modificaProduseCos(product); // modificam toate produsele din cosul de cumparaturi care au acelasi nume si producator cu produsul product (adica numele name si producatorul producer)
}

const Product& Service::search(const string& name, const string& producer) const
{
	// validam numele name si producatorul producer
	if (!name.size() * !producer.size()) // if (name == "" && producer == "")
		throw ServiceException("[!]Nume invalid!\n[!]Producator invalid!\n");
	if (!name.size())                    // if (name == "")
		throw ServiceException("[!]Nume invalid!\n");
	if (!producer.size())                // if (producer == "")
		throw ServiceException("[!]Producator invalid!\n");
	
	return repo.searchProduct(name, producer); // cautam un produs cu numele name si producatorul producer in lista de produse din repository
}

const vector<Product>& Service::getAll() const
{
	return repo.getAll(); // returnam o referinta constanta la lista de obiecte de clasa Product din repo
}

dictionary Service::countType() const
{
	dictionary types_map;

	const auto& products{ getAll() };

	for (const auto& prod : products)
		if (types_map.find(prod.getType()) == types_map.end())
			types_map[prod.getType()] = make_pair(prod.getType(), 1); // types_map[prod.getType()] = { prod.getType(), 1 };
		else
			++types_map[prod.getType()].second;

	return types_map;
}

/*
bool Service::validPriceFilter(const Product& p, const string& price, const string& sign) const
{
	verifyIfDouble(price);

	if (sign == "<")      // se filtreaza produsele cu pret mai mic
		return p.getPrice() < stod(price, nullptr);
	else if (sign == "=") // se filtreaza produsele cu pret egal
		return fabs(p.getPrice() - stod(price, nullptr)) < 1e-12;
	else if (sign == ">") // se filtreaza produsele cu pret mai mare
		return p.getPrice() > stod(price, nullptr);
	else                  // simbol/semn de inegalitate invalid
		throw ServiceException("[!]Simbol de inegalitate invalid!\n");
}

bool Service::validNameFilter(const Product& p, const string& name) const
{
	if (cmpStrings(p.getName(), name))
		return true; // p satisface filtrul de nume
	return false; // p nu satisface filtrul de nume
}

bool Service::validProducerFilter(const Product& p, const string& producer) const
{
	if (cmpStrings(p.getProducer(), producer))
		return true; // p satisface filtrul de producator
	return false; // p nu satisface filtrul de producator
}
*/

void Service::filterAfterPrice(const vector<Product>& products, vector<Product>& filtered_list, const string& price, const string& sign) const
{
	verifyIfDouble(price);

	const auto& price_double{ stod(price, nullptr) };

	if (sign != "<" && sign != "=" && sign != ">") // simbol/semn de inegalitate invalid
		throw ServiceException("[!]Simbol de inegalitate invalid!\n");

	copy_if(products.begin(),
		products.end(),
		back_inserter(filtered_list),
		[&price_double, &sign](const Product& p) {
			if (sign == "<")
				return p.getPrice() < price_double;
			else if (sign == ">")
				return p.getPrice() > price_double;
			return fabs(p.getPrice() - price_double) < 1e-12;
		});
}

void Service::filterAfterName(const vector<Product>& products, vector<Product>& filtered_list, const string& name) const
{
	copy_if(products.begin(),
		products.end(),
		back_inserter(filtered_list),
		[&](const Product& p) noexcept {
			return cmpStrings(p.getName(), name);
		});
}

void Service::filterAfterProducer(const vector<Product>& products, vector<Product>& filtered_list, const string& producer) const
{
	copy_if(products.begin(),
		products.end(),
		back_inserter(filtered_list),
		[&](const Product& p) noexcept {
			return cmpStrings(p.getProducer(), producer);
		});
}

vector<Product> Service::filterProducts(const string& crt, const string& filter, const string& sign) const
{
	/*
	const auto& products{ repo.getAll() };
	vector<Product> filtered_list;

#define pb push_back

	for (const auto& p : products)
	{
		auto isValid{ false }; // semafor care sa indice/semnaleze daca produsul p va fi sau nu filtrat (satisface criteriul de filtrare)

		if (crt == "1")      // criteriul de filtrare: pret (fieldul price)
			isValid = validPriceFilter(p, filter, sign);
		else if (crt == "2") // criteriu de filtrare: nume (fieldul name)
			isValid = validNameFilter(p, filter);
		else if (crt == "3") // criteriu de filtrare: producator (fieldul producer)
			isValid = validProducerFilter(p, filter);
		else                 // criteriu de filtrare invalid
			throw ServiceException("[!]Criteriu de filtrare invalid!\n");

		if (isValid) // obiectul p de clasa Product respecta filtrul impus
			filtered_list.pb(p); // filtram produsul p
	}

#undef pb

	return filtered_list;
	*/

	const auto& products{ repo.getAll() };
	vector<Product> filtered_list;

	if (crt == "1")      // criteriul de filtrare: pret (fieldul price)
		filterAfterPrice(products, filtered_list, filter, sign);
	else if (crt == "2") // criteriu de filtrare: nume (fieldul name)
		filterAfterName(products, filtered_list, filter);
	else if (crt == "3") // criteriu de filtrare: producator (fieldul producer)
		filterAfterProducer(products, filtered_list, filter);
	else                 // criteriu de filtrare invalid
		throw ServiceException("[!]Criteriu de filtrare invalid!\n");

	return filtered_list;
}

/*
void Service::sortProductsAscending(vector<Product>& products, const string& crt) const
{
	if (crt == "1") // criteriu sortare: nume
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) noexcept {return p1.getName() < p2.getName(); });
	else if (crt == "2") // criteriu sortare: pret
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) noexcept {return p1.getPrice() < p2.getPrice(); });
	else if (crt == "3") // criteriu sortare: nume + tip
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) noexcept {if (p1.getName() == p2.getName()) { return p1.getType() < p2.getType(); } return p1.getName() < p2.getName(); });
	else // criteriu de sortare invalid
		throw ServiceException("[!]Criteriu de sortare invalid!\n");
}

void Service::sortProductsDescending(vector<Product>& products, const string& crt) const
{
	if (crt == "1") // criteriu sortare: nume
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) noexcept {return p1.getName() > p2.getName(); });
	else if (crt == "2") // criteriu sortare: pret
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) noexcept {return p1.getPrice() > p2.getPrice(); });
	else if (crt == "3") // criteriu sortare: nume + tip
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) noexcept {if (p1.getName() == p2.getName()) { return p1.getType() > p2.getType(); } return p1.getName() > p2.getName(); });
	else // criteriu de sortare invalid
		throw ServiceException("[!]Criteriu de sortare invalid!\n");
}
*/

void Service::sortCrtName(vector<Product>& products, bool reversed) const
{
	sort(products.begin(),
		products.end(),
		[reversed](const Product& p1, const Product& p2) noexcept {
			if (!reversed)
				return p1.getName() < p2.getName();
			return p1.getName() > p2.getName();
		});
}

void Service::sortCrtPrice(vector<Product>& products, bool reversed) const
{
	sort(products.begin(),
		products.end(),
		[reversed](const Product& p1, const Product& p2) noexcept {
			if (!reversed)
				return p1.getPrice() < p2.getPrice();
			return p1.getPrice() > p2.getPrice();
		});
}

void Service::sortCrtNamePlusType(vector<Product>& products, bool reversed) const
{
	sort(products.begin(),
		products.end(),
		[reversed](const Product& p1, const Product& p2) noexcept {
			if (!reversed)
			{
				if (p1.getName() == p2.getName())
					return p1.getType() < p2.getType();
				return p1.getName() < p2.getName();
			}
			else {
				if (p1.getName() == p2.getName())
					return p1.getType() > p2.getType();
				return p1.getName() > p2.getName();
			}
		});
}

vector<Product> Service::sortProducts(const string& crt, const string& ord) const
{
	/*
	auto products = repo.getAll();
	
	if (ord == "c" || ord == "C")      // ordinea de sortare: crescator
		sortProductsAscending(products, crt);
	else if (ord == "d" || ord == "D") // ordinea de sortare: descrescator
		sortProductsDescending(products, crt);
	else                               // ordine de sortare invalida
		throw ServiceException("[!]Ordine de sortare invalida!\n");

	return products;
	*/

	if (ord != "c" && ord != "C" && ord != "d" && ord != "D") // ordine de sortare invalida
		throw ServiceException("[!]Ordine de sortare invalida!\n");

	auto products{ repo.getAll() };

#define ternary(a, b, c) \
	((a) ? (b) : (c))
	const auto reversed{ ternary(ord == "d" || ord == "D", true, false) }; // const auto reversed{ (ord == "c" || ord == "C") ? (false) : (true) };
#undef ternary

	// reversed = 0 => sortare in ordine crescatoare
	//            1 => sortare in ordine descrescatoare

	if (crt == "1")      // criteriu sortare: nume
		sortCrtName(products, reversed);
	else if (crt == "2") // criteriu sortare: pret
		sortCrtPrice(products, reversed);
	else if (crt == "3") // criteriu sortare: nume + tip
		sortCrtNamePlusType(products, reversed);
	else                 // criteriu de sortare invalid
		throw ServiceException("[!]Criteriu de sortare invalid!\n");

	return products;
}

void Service::golireCos()
{
	cosCumparaturi.golesteCos();
}

void Service::adaugareCos(const string& name, const string& producer)
{
	// validam numele name si producatorul producer
	string err{ "" }; // lista de erori (string)

	if (!name.size())     // if (name == "")
		err += "[!]Nume invalid!\n";       // name invalid
	if (!producer.size()) // if (producer == "")
		err += "[!]Producator invalid!\n"; // producer invalid

	if (err.size()) // lista de erori contine cel putin o eroare (name si/sau producer sunt stringuri vide, deci invalide)
		throw ServiceException(err); // aruncam exceptie de clasa ServiceException cu mesajul de eroare/exceptie err

	cosCumparaturi.adaugaInCos(name, producer);
}

void Service::generareCos(const string& num)
{
	try {
		const int number_of_products{ stoi(num) };

		if (number_of_products < 0)
			throw ServiceException("[!]Numarul introdus nu este o valoare pozitiva!\n");

		cosCumparaturi.genereazaCos(number_of_products);
	}
	catch (const exception&) {
		throw ServiceException("[!]Nu ati introdus un numar!\n");
	}
}

void Service::exportCos(const string& filename, const string& filetype)
{
	if (!filename.size()) // if (filename == "")
		throw ServiceException("[!]Numele fisierului nu poate fi vid!\n");

	if (cmpStrings(filetype, "html"))     // exportul cosului de cumparaturi se face intr-un fisier html
		cosCumparaturi.exportCosFisierHTML(filename);
	else if (cmpStrings(filetype, "csv")) // exportul cosului de cumparaturi se face intr-un fisier csv
		cosCumparaturi.exportCosFisierCSV(filename);
	else                                  // tipul fisierului este invalid (nu este html sau csv)
		throw ServiceException("[!]Tip fisier export invalid!\n");
}

const double& Service::totalCos() noexcept
{
	return cosCumparaturi.getTotal();
}

unsigned Service::cantitateCos() noexcept
{
	return cosCumparaturi.nrProduseCos();
}