#include "ProductValidator.h"
#include "ProductException.h"

#include <string>

using std::string;

bool ProductValidator::invalidName(const Product& bad_product) const noexcept
{
	if (!bad_product.getName().size()) // if (bad_product.getName() == "")
		return true;
	return false;

	// return !bad_product.getName().size();
}

bool ProductValidator::invalidType(const Product& bad_product) const noexcept
{
	if (!bad_product.getType().size()) // if (bad_product.getType() == "")
		return true;
	return false;

	// return !bad_product.getType().size();
}

bool ProductValidator::invalidPrice(const Product& bad_product) const noexcept
{
	if (bad_product.getPrice() < 1e-12)
		return true;
	return false;

	// return bad_product.getPrice() < 1e-12;
}

bool ProductValidator::invalidProducer(const Product& bad_product) const noexcept
{
	if (!bad_product.getProducer().size()) // if (bad_product.getProducer() == "")
		return true;
	return false;

	// return !bad_product.getProducer().size();
}

void ProductValidator::validateProduct(const Product& bad_product) const
{
	string err{ "" }; // lista de erori (un string care contine concatenate toate erorile separate prin metacaracterul '\n')

	if (invalidName(bad_product))     // validam campul name (nume)
		err += "[!]Nume invalid!\n";
	if (invalidType(bad_product))     // validam campul type (tip)
		err += "[!]Tip invalid!\n";
	if (invalidPrice(bad_product))    // validam campul price (pret)
		err += "[!]Pret invalid!\n";
	if (invalidProducer(bad_product)) // validam campul producer (producator)
		err += "[!]Producator invalid!\n";
	
	if (err.size()) // if (err.size() != 0)
		            // if (err != "")
		throw ProductException(err); // aruncam/ridicam exceptie de tipul ProductException cu mesajul err
}