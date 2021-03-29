#include "Repository.h"
#include "RepoException.h"

void RepoProducts::addProduct(const Product& product)
{
	for (const auto& p : products)
		if (p.cmpProducts(product)) // if (p.getName() == product.getName() && p.getProducer() == product.getProducer())
			throw RepoException("Produs deja existent!\n");
	products.push_back(product);
}

void RepoProducts::deleteProduct(const string& name, const string& producer)
{
	if (!len()) // if (!products.size())
				// if (!this->len())
		throw RepoException("Nu exista produse in magazin!\n");

	/*
	auto found{ false };
	auto pos = 0;
	for (const auto& p : products)
	{
		if (p.getName() == name && p.getProducer() == producer)
		{
			products.erase(products.begin() + pos);
			found = true;
			break;
		}
		++pos;
	}
	if(!found)
		throw RepoException("Produs inexistent!\n");
	*/
	
	auto pos = 0;
	for (const auto& p : products)
	{
		if (p.getName() == name && p.getProducer() == producer)
		{
			products.erase(products.begin() + pos);
			return;
		}
		++pos;
	}
	throw RepoException("Produs inexistent!\n");
}

void RepoProducts::modifyProduct(const Product& product)
{
	if (!len()) // if (!products.size())
				// if (!this->len())
		throw RepoException("Nu exista produse in magazin!\n");

	/*
	auto found{ false };
	for (auto& p : products)
		if(p.cmpProducts(product)) // if (p.getName() == product.getName() && p.getProducer() == product.getProducer())
		{
			p.setType(product.getType());
			p.setPrice(product.getPrice());
			found = true;
			break;
		}
	if (!found)
		throw RepoException("Produs inexistent!\n");
	*/
	
	for (auto& p : products)
		if(p.cmpProducts(product)) // if (p.getName() == product.getName() && p.getProducer() == product.getProducer())
		{
			p.setType(product.getType());
			p.setPrice(product.getPrice());
			return;
		}
	throw RepoException("Produs inexistent!\n");
}

const Product& RepoProducts::searchProduct(const string& name, const string& producer) const
{
	if (!len()) // if (!products.size())
				// if (!this->len())
		throw RepoException("Nu exista produse in magazin!\n");
	for (const auto& p : products)
		if (p.getName() == name && p.getProducer() == producer)
			return p;
	throw RepoException("Produs inexistent!\n");
}

const vector<Product>& RepoProducts::getAll() const
{
	if (!len()) // if (!products.size())
		        // if (!this->len())
		throw RepoException("Nu exista produse in magazin!\n");
	return products; // return this->products;
}

unsigned RepoProducts::len() const
{
	return products.size(); // return this->products.size();
}