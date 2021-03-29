#include "TestingValidation.h"
#include "Product.h"
#include "ProductException.h"
#include "ProductValidator.h"

#include <cassert> // #include <assert.h>

void TestingValidation::runTestsProductValidator() const
{
	ProductValidator valid;
	
	try {
		valid.validateProduct(Product{ "a", "b", 0.1, "c" });
		assert(true);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		valid.validateProduct(Product{ "a", "b", 0.1, "" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Producator invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "a", "b", 0, "c" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Pret invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "a", "b", -0.001, "" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Pret invalid!\nProducator invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "a", "", 0.01, "c" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Tip invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "a", "", 0.001, "" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Tip invalid!\nProducator invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "a", "", -0.525, "c" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Tip invalid!\nPret invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "a", "", -3.25, "" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Tip invalid!\nPret invalid!\nProducator invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "", "b", 13.870, "c" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Nume invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "", "b", 13.870, "" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Nume invalid!\nProducator invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "", "b", -8.69, "c" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Nume invalid!\nPret invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "", "b", -3, "" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Nume invalid!\nPret invalid!\nProducator invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "", "", 10, "c" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Nume invalid!\nTip invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "", "", 7.098313, "" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Nume invalid!\nTip invalid!\nProducator invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "", "", -289.13, "c" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Nume invalid!\nTip invalid!\nPret invalid!\n");
	}

	try {
		valid.validateProduct(Product{ "", "", -32.9, "" });
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Nume invalid!\nTip invalid!\nPret invalid!\nProducator invalid!\n");
	}
}