#include "ProductValidator.h"
#include "ProductException.h"

#include <string>

using std::string;

bool ProductValidator::invalidName(const Product& bad_product) const
{
	if (bad_product.getName() == "")
		return true;
	return false;
	
	// return !bad_product.getName().size();
}

bool ProductValidator::invalidType(const Product& bad_product) const
{
	if (bad_product.getType() == "")
		return true;
	return false;

	// return !bad_product.getType().size();
}

bool ProductValidator::invalidPrice(const Product& bad_product) const
{
	if (bad_product.getPrice() < 1e-12)
		return true;
	return false;

	// return bad_product.getPrice() < 1e-12;
}

bool ProductValidator::invalidProducer(const Product& bad_product) const
{
	if (bad_product.getProducer() == "")
		return true;
	return false;
	
	// return !bad_product.getProduct().size();
}

void ProductValidator::validateProduct(const Product& bad_product) const
{
	string err{ "" }; // lista de erori
	if (invalidName(bad_product)) // validam campul name
		err += "Nume invalid!\n";
	if (invalidType(bad_product)) // validam campul type
		err += "Tip invalid!\n";
	if (invalidPrice(bad_product)) // validam campul price
		err += "Pret invalid!\n";
	if (invalidProducer(bad_product)) // validam campul producer
		err += "Producator invalid!\n";
	if (err.size()) // if (err.size() != 0)
		throw ProductException(err); // aruncam/ridicam exceptie de tipul ProductException cu mesajul err
}