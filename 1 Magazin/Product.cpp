#include "Product.h"

using std::to_string;

const string& Product::getName() const
{
	return name; // return this->name;
}

const string& Product::getType() const
{
	return type; // return this->type;
}

const double& Product::getPrice() const
{
	return price; // return this->price;
}

const string& Product::getProducer() const
{
	return producer; // return this->producer;
}

void Product::setName(const string& new_name)
{
	name = new_name; // this->name = new_name;
}

void Product::setType(const string& new_type)
{
	type = new_type; // this->type = new_type;
}

void Product::setPrice(const double& new_price)
{
	price = new_price; // this->price = new_price;
}

void Product::setProducer(const string& new_producer)
{
	producer = new_producer; // this->producer = new_producer;
}

bool Product::cmpProducts(const Product& ot) const
{
	return name == ot.name && producer == ot.producer; // return name == ot.getName() && producer == ot.getProducer();
}

string Product::strProduct() const
{
	return "Nume: " + name + "\nTip: " + type + "\nPret: " + to_string(price) + "\nProducator: " + producer + '\n';
}