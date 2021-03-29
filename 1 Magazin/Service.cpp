#include "Service.h"
#include "Utils.h"

#include <exception>
#include <algorithm>

using std::exception;
using std::sort;

bool Service::cmpStrings(const string& str_1, const string& str_2) const
{
	Utils utils;
	return utils.compareStr(str_1, str_2);
}

void Service::verifyIfDouble(const string& str) const
{
	Utils utils;
	if (!utils.isDouble(str))
		throw exception("Pretul introdus nu este un numar real!\n");
}

void Service::add(const string& name, const string& type, const double& price, const string& producer)
{
	Product product{ name, type, price, producer };
	valid.validateProduct(product);
	repo.addProduct(product);
}

void Service::del(const string& name, const string& producer)
{
	if (name == "" && producer == "")
		throw exception("Nume invalid!\nProducator invalid!\n");
	if(name == "")
		throw exception("Nume invalid!\n");
	if (producer == "")
		throw exception("Producator invalid!\n");
	repo.deleteProduct(name, producer);
}

void Service::modify(const string& name, const string& type, const double& price, const string& producer)
{
	Product product{ name, type, price, producer };
	valid.validateProduct(product);
	repo.modifyProduct(product);
}

const Product& Service::search(const string& name, const string& producer) const
{
	if (name == "" && producer == "")
		throw exception("Nume invalid!\nProducator invalid!\n");
	if (name == "")
		throw exception("Nume invalid!\n");
	if (producer == "")
		throw exception("Producator invalid!\n");
	return repo.searchProduct(name, producer);
}

const vector<Product>& Service::getAll() const
{
	return repo.getAll();
}

vector<Product> Service::filterProducts(const string& crt, const string& filter, const string& sign) const
{
	const auto& products = repo.getAll();
	vector<Product> filtered_list;
#define pb push_back
	for (const auto& p : products)
	{
		auto isValid{ false };
		if (crt == "1")
		{
			verifyIfDouble(filter);
			if (sign == "<")
			{
				if (p.getPrice() < stod(filter, nullptr))
					isValid = true;
			}
			else if (sign == "=")
			{
				if (fabs(p.getPrice() - stod(filter, nullptr)) < 1e-12)
					isValid = true;
			}
			else if (sign == ">")
			{
				if (p.getPrice() > stod(filter, nullptr))
					isValid = true;
			}
			else
				throw exception("Simbol de inegalitate invalid!\n");
		}
		else if (crt == "2")
		{
			if (cmpStrings(p.getName(), filter))
				isValid = true;
		}
		else if (crt == "3")
		{
			if (cmpStrings(p.getProducer(), filter))
				isValid = true;
		}
		else throw exception("Criteriu invalid!\n");
		if (isValid)
			filtered_list.pb(p);
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
	if (crt == "1")
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) {return p1.getName() < p2.getName(); });
	else if (crt == "2")
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) {return p1.getPrice() < p2.getPrice(); });
	else if (crt == "3")
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) {if (p1.getName() == p2.getName()) return p1.getType() < p2.getType(); return p1.getName() < p2.getName(); });
	else throw exception("Criteriu invalid!\n");
}

void Service::sortProductsDescending(vector<Product>& products, const string& crt) const
{
	if (crt == "1")
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) {return p1.getName() > p2.getName(); });
	else if (crt == "2")
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) {return p1.getPrice() > p2.getPrice(); });
	else if (crt == "3")
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) {if (p1.getName() == p2.getName()) return p1.getType() > p2.getType(); return p1.getName() > p2.getName(); });
	else throw exception("Criteriu invalid!\n");
}

vector<Product> Service::sortProducts(const string& crt, const string& ord) const
{
	auto products = repo.getAll();
	if (ord == "c" || ord == "C")
		sortProductsAscending(products, crt);
	else if (ord == "d" || ord == "D")
		sortProductsDescending(products, crt);
	else throw exception("Ordine invalida!\n");
	return products;
}