#include "Service.h"
#include "ServiceException.h"
#include "Utils.h"

#include <algorithm>

using std::sort;

bool Service::cmpStrings(const string& str_1, const string& str_2) const
{
	const Utils utils;
	return utils.compareStr(str_1, str_2); // comparam case insensitive cele doua stringuri (str_1 si str_2)
}

void Service::verifyIfDouble(const string& str) const
{
	const Utils utils;
	if (!utils.isDouble(str)) // verificam daca str contine reprezentarea unui numar real
		throw ServiceException("Pretul introdus nu este un numar real!\n"); // aruncam/ridicam exceptie de clasa ServiceException
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
	
	if (!name.size()) // if (name == "")
		err += "Nume invalid!\n"; // name invalid
	if (!producer.size()) // if (producer == "")
		err += "Producator invalid!\n"; // producer invalid

	if(err.size()) // lista de erori contine cel putin o eroare (name si/sau producer sunt stringuri vide, deci invalide)
		throw ServiceException(err); // aruncam exceptie de clasa ServiceException cu mesajul de eroare/exceptie err

	repo.deleteProduct(name, producer); // incercam sa stergem produsul cu numele name si producatorul producer din magazin (repo)
}

void Service::modify(const string& name, const string& type, const double& price, const string& producer)
{
	Product product{ name, type, price, producer }; // cream produsul cu numele name, tipul type, pretul price si producatorul producer
	valid.validateProduct(product); // validam obiectul de clasa Product (produsul) creat (instantiat) anterior/precedent
	repo.modifyProduct(product); // incercam sa modificam un produs care are numele name si producatorul producer din repo (daca acesta exista) cu noul produs product
}

const Product& Service::search(const string& name, const string& producer) const
{
	// validam numele name si producatorul producer
	if (!name.size() * !producer.size()) // if (name == "" && producer == "")
		throw ServiceException("Nume invalid!\nProducator invalid!\n");
	if (!name.size()) // if (name == "")
		throw ServiceException("Nume invalid!\n");
	if (!producer.size()) // if (producer == "")
		throw ServiceException("Producator invalid!\n");
	
	return repo.searchProduct(name, producer); // cautam un produs cu numele name si producatorul producer in lista de produse din repository
}

const vector<Product>& Service::getAll() const
{
	return repo.getAll(); // returnam o referinta constanta la lista de obiecte de clasa Product din repo
}

bool Service::validPriceFilter(const Product& p, const string& price, const string& sign) const
{
	verifyIfDouble(price);

	if (sign == "<") // se filtreaza produsele cu pret mai mic
		return p.getPrice() < stod(price, nullptr);
	else if (sign == "=") // se filtreaza produsele cu pret egal
		return fabs(p.getPrice() - stod(price, nullptr)) < 1e-12;
	else if (sign == ">") // se filtreaza produsele cu pret mai mare
		return p.getPrice() > stod(price, nullptr);
	else // simbol/semn de inegalitate invalid
		throw ServiceException("Simbol de inegalitate invalid!\n");
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

vector<Product> Service::filterProducts(const string& crt, const string& filter, const string& sign) const
{
	const auto& products = repo.getAll();
	vector<Product> filtered_list;

#define pb push_back

	for (const auto& p : products)
	{
		auto isValid{ false }; // semafor care sa indice/semnaleze daca produsul p va fi sau nu filtrat (satisface criteriul de filtrare)

		if (crt == "1") // criteriul de filtrare: pret (fieldul price)
			isValid = validPriceFilter(p, filter, sign);
		else if (crt == "2") // criteriu de filtrare: nume (fieldul name)
			isValid = validNameFilter(p, filter);
		else if (crt == "3") // criteriu de filtrare: producator (fieldul producer)
			isValid = validProducerFilter(p, filter);
		else // criteriu de filtrare invalid
			throw ServiceException("Criteriu de filtrare invalid!\n");

		if (isValid) // obiectul p de clasa Product respecta filtrul impus
			filtered_list.pb(p); // filtram produsul p
	}

#undef pb

	return filtered_list;
}

/*
bool crtNameAscending(const Product& p1, const Product& p2)
{
	return p1.getName() < p2.getName();
}

bool crtNameDescending(const Product& p1, const Product& p2)
{
	return p1.getName() > p2.getName();
}

bool crtPriceAscending(const Product& p1, const Product& p2)
{
	return p1.getPrice() < p2.getPrice();
}

bool crtPriceDescending(const Product& p1, const Product& p2)
{
	return p1.getPrice() > p2.getPrice();
}

bool crtNamePlusTypeAscending(const Product& p1, const Product& p2)
{
	if (p1.getName() == p2.getName())
		return p1.getType() < p2.getType();
	return p1.getName() < p2.getName();
}

bool crtNamePlusTypeDescending(const Product& p1, const Product& p2)
{
	if (p1.getName() == p2.getName())
		return p1.getType() > p2.getType();
	return p1.getName() > p2.getName();
}
*/

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
		throw ServiceException("Criteriu de sortare invalid!\n");
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
		throw ServiceException("Criteriu de sortare invalid!\n");
}

vector<Product> Service::sortProducts(const string& crt, const string& ord) const
{
	auto products = repo.getAll();

	if (ord == "c" || ord == "C") // ordinea de sortare: crescator
		sortProductsAscending(products, crt);
	else if (ord == "d" || ord == "D") // ordinea de sortare: descrescator
		sortProductsDescending(products, crt);
	else // ordine de sortare invalida
		throw ServiceException("Ordine de sortare invalida!\n");

	return products;
}