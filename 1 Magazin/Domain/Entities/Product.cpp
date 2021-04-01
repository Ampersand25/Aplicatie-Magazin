#include "Product.h"

using std::to_string;

const string& Product::getName() const noexcept
{
	return name; // return this->name;
}

const string& Product::getType() const noexcept
{
	return type; // return this->type;
}

const double& Product::getPrice() const noexcept
{
	return price; // return this->price;
}

const string& Product::getProducer() const noexcept
{
	return producer; // return this->producer;
}

void Product::setType(const string& new_type)
{
	type = new_type; // this->type = new_type;
}

void Product::setPrice(const double& new_price) noexcept
{
	price = new_price; // this->price = new_price;
}

bool Product::cmpProducts(const Product& ot) const noexcept
{
	return name == ot.name && producer == ot.producer; // return name == ot.getName() && producer == ot.getProducer();
}

string Product::strProduct() const
{
	return "Nume: " + name + "\nTip: " + type + "\nPret: " + to_string(price) + "\nProducator: " + producer + '\n';
}