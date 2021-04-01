#include "TestingService.h"
#include "Service.h"
#include "ServiceException.h"
#include "Repository.h"
#include "RepoException.h"
#include "ProductValidator.h"
#include "ProductException.h"

#include <cmath>   // #include <math.h>
#include <cassert> // #include <assert.h>

void TestingService::runTestsServiceCmpStrings() const
{
	RepoProducts repo;
	ProductValidator valid;
	const Service srv{repo, valid};

	assert(srv.cmpStrings(" ", "") == false);
	assert(srv.cmpStrings("afs", "32jio") == false);
	assert(srv.cmpStrings("9823sf", "fdg") == false);
	assert(srv.cmpStrings("1874", "1875") == false);
	assert(srv.cmpStrings("abcdefgh", "abcdhfgh") == false);
	assert(srv.cmpStrings("1fas43o./afs", "2fas43o./afs") == false);

	assert(srv.cmpStrings("", "") == true);
	assert(srv.cmpStrings("-a./b123c34", "-a./b123c34") == true);
	assert(srv.cmpStrings("A5b-.343c", "a5B-.343c") == true);
	assert(srv.cmpStrings(".a.?2351B--C", ".A.?2351b--c") == true);
	assert(srv.cmpStrings("aBc329de12F3", "aBC329dE12f3") == true);
	assert(srv.cmpStrings("459ab4398C0d./23f", "459aB4398c0d./23F") == true);
}

void TestingService::runTestsServiceVerifyIfDouble() const
{
	RepoProducts repo;
	ProductValidator valid;
	const Service srv{ repo, valid };

	try {
		srv.verifyIfDouble("32.341.");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Pretul introdus nu este un numar real!\n");
	}

	try {
		srv.verifyIfDouble(".541");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Pretul introdus nu este un numar real!\n");
	}

	try {
		srv.verifyIfDouble("65.");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Pretul introdus nu este un numar real!\n");
	}

	try {
		srv.verifyIfDouble("0.234");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("23");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("0");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("+443");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("+65.135");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("+0.34");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("-5");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("-435.123");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("-0.3");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}
}

void TestingService::runTestsServiceAdd() const
{
	RepoProducts repo;
	ProductValidator valid;
	Service srv{ repo, valid };

	try {
		srv.add("a", "b", 4.725, "c");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.add("a", "deg", 13.05, "c");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "Produs deja existent!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.add("", "x", 0, "y");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "Nume invalid!\nPret invalid!\n");
	}
}

void TestingService::runTestsServiceDel() const
{
	RepoProducts repo;
	ProductValidator valid;
	Service srv{ repo, valid };

	try {
		srv.del("a", "b");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "Nu exista produse in magazin!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("", "b");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(true);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("a", "");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(true);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("", "");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(true);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	srv.add("a", "b", 0.1, "c");

	try {
		srv.del("a", "b");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "Produs inexistent!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("a", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Producator invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("", "c");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Nume invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Nume invalid!\nProducator invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("a", "c");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}
}

void TestingService::runTestsServiceModify() const
{
	RepoProducts repo;
	ProductValidator valid;
	Service srv{ repo, valid };

	try {
		srv.modify("a", "b", 3.573, "c");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "Nu exista produse in magazin!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}

	srv.add("a", "b", 6.1, "c");

	try {
		srv.modify("a", "x", 9, "d");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "Produs inexistent!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.modify("", "", -5.21, "d");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException& ex) {
		assert(ex.getMessage() == "Nume invalid!\nTip invalid!\nPret invalid!\n");
	}

	try {
		srv.modify("a", "x", 21.4501, "c");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}
}

void TestingService::runTestsServiceSearch() const
{
	RepoProducts repo;
	ProductValidator valid;
	Service srv{ repo, valid };

	try {
		srv.search("", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Nume invalid!\nProducator invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.search("a", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Producator invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.search("", "c");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Nume invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.search("a", "c");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "Nu exista produse in magazin!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}
	
	srv.add("a", "b", 0.56, "c");

	try {
		srv.search("", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Nume invalid!\nProducator invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.search("a", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Producator invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.search("", "c");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Nume invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		const auto& p =  srv.search("a", "c");

		assert(p.getName() == "a");
		assert(p.getType() == "b");
		assert(fabs(p.getPrice() - 0.56) < 1e-12);
		assert(p.getProducer() == "c");
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.search("a", "b");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "Produs inexistent!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}
}

void TestingService::runTestsServiceGetAll() const
{
	RepoProducts repo;
	ProductValidator valid;
	Service srv{ repo, valid };

	try {
		srv.getAll();
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "Nu exista produse in magazin!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}

	srv.add("a", "b", 3.74, "c");

	try {
		const auto& produse = srv.getAll();

		assert(produse.at(0).getName() == "a");
		assert(produse.at(0).getType() == "b");
		assert(fabs(produse.at(0).getPrice() - 3.74) < 1e-12);
		assert(produse.at(0).getProducer() == "c");
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	srv.add("x", "y", 15.1, "z");

	try {
		const auto& produse = srv.getAll();

		assert(produse.at(0).getName() == "a");
		assert(produse.at(0).getType() == "b");
		assert(fabs(produse.at(0).getPrice() - 3.74) < 1e-12);
		assert(produse.at(0).getProducer() == "c");

		assert(produse.at(1).getName() == "x");
		assert(produse.at(1).getType() == "y");
		assert(fabs(produse.at(1).getPrice() - 15.1) < 1e-12);
		assert(produse.at(1).getProducer() == "z");
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	srv.add("abc", "xyzklm", 15.1, "1pr23qst456u7v");

	try {
		const auto& produse = srv.getAll();

		assert(produse.at(0).getName() == "a");
		assert(produse.at(0).getType() == "b");
		assert(fabs(produse.at(0).getPrice() - 3.74) < 1e-12);
		assert(produse.at(0).getProducer() == "c");

		assert(produse.at(1).getName() == "x");
		assert(produse.at(1).getType() == "y");
		assert(fabs(produse.at(1).getPrice() - 15.1) < 1e-12);
		assert(produse.at(1).getProducer() == "z");

		assert(produse.at(2).getName() == "abc");
		assert(produse.at(2).getType() == "xyzklm");
		assert(fabs(produse.at(2).getPrice() - 15.1) < 1e-12);
		assert(produse.at(2).getProducer() == "1pr23qst456u7v");
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}
}

void TestingService::testFunction(const Product& p, const string& name, const string& type, const double& price, const string& producer) const noexcept
{
	assert(p.getName() == name);
	assert(p.getType() == type);
	assert(fabs(p.getPrice() - price) < 1e-12);
	assert(p.getProducer() == producer);
}

void TestingService::runTestsServiceFilterProducts() const
{
	RepoProducts repo;
	ProductValidator valid;
	Service srv{ repo, valid };
	
	vector<Product> products;

	try {
		products = srv.filterProducts("1", "4.25", "<");
		assert(false);
	}
	catch (const RepoException& ex) {
		assert(ex.getMessage() == "Nu exista produse in magazin!\n");
	}

	srv.add("iaurt", "produse lactate", 4.63, "Danone");
	srv.add("chipsuri", "snacksuri", 9.6, "Lays");
	srv.add("boia", "condimente", 0.999, "Delikat");
	srv.add("sare", "condimente", 11, "Maggi");
	srv.add("parmezan", "condimente", 8.301, "Delikat");
	srv.add("chipsuri", "snacks", 9.1, "Pringles");

	products = srv.filterProducts("1", "8.5", "<");
	assert(products.size() == 3);
	testFunction(products.at(0), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(1), "boia", "condimente", 0.999, "Delikat");
	testFunction(products.at(2), "parmezan", "condimente", 8.301, "Delikat");

	products = srv.filterProducts("1", "8.301", "=");
	assert(products.size() == 1);
	testFunction(products.at(0), "parmezan", "condimente", 8.301, "Delikat");

	products = srv.filterProducts("1", "9.4", ">");
	assert(products.size() == 2);
	testFunction(products.at(0), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(1), "sare", "condimente", 11, "Maggi");

	try {
		products = srv.filterProducts("1", "2.57", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Simbol de inegalitate invalid!\n");
	}

	try {
		products = srv.filterProducts("1", "12.013", ".");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Simbol de inegalitate invalid!\n");
	}

	try {
		products = srv.filterProducts("4", "69", "-");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Criteriu de filtrare invalid!\n");
	}

	try {
		products = srv.filterProducts("0", "abc", "-");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Criteriu de filtrare invalid!\n");
	}

	try {
		products = srv.filterProducts("abc", "...", "-");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Criteriu de filtrare invalid!\n");
	}

	try {
		products = srv.filterProducts("", "2.55", "-");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Criteriu de filtrare invalid!\n");
	}

	products = srv.filterProducts("1", "0.1", "<");
	assert(products.size() == 0);

	products = srv.filterProducts("1", "9.69", "=");
	assert(products.size() == 0);

	products = srv.filterProducts("1", "23", ">");
	assert(products.size() == 0);
	
	products = srv.filterProducts("2", "chipsuri", "");
	assert(products.size() == 2);
	testFunction(products.at(0), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(1), "chipsuri", "snacks", 9.1, "Pringles");

	products = srv.filterProducts("2", "sare", "/abc1234XYZ()");
	assert(products.size() == 1);
	testFunction(products.at(0), "sare", "condimente", 11, "Maggi");

	products = srv.filterProducts("2", "iaurt", ".");
	assert(products.size() == 1);
	testFunction(products.at(0), "iaurt", "produse lactate", 4.63, "Danone");

	products = srv.filterProducts("2", "branza", "*");
	assert(products.size() == 0);
	
	products = srv.filterProducts("3", "Delikat", "-");
	assert(products.size() == 2);
	testFunction(products.at(0), "boia", "condimente", 0.999, "Delikat");
	testFunction(products.at(1), "parmezan", "condimente", 8.301, "Delikat");

	products = srv.filterProducts("3", "Pringles", "dsgf/af?OI,.FHfsoijPJfafsF42asf");
	assert(products.size() == 1);
	testFunction(products.at(0), "chipsuri", "snacks", 9.1, "Pringles");

	products = srv.filterProducts("3", "Danone", ".--/");
	assert(products.size() == 1);
	testFunction(products.at(0), "iaurt", "produse lactate", 4.63, "Danone");

	products = srv.filterProducts("3", "Chio", "&&132s");
	assert(products.size() == 0);
}

void TestingService::runTestsServiceSortProducts() const
{
	RepoProducts repo;
	ProductValidator valid;
	Service srv{ repo, valid };

	vector<Product> products;

	try {
		products = srv.sortProducts("1", "c");
		assert(false);
	}
	catch (const RepoException& ex) {
		assert(ex.getMessage() == "Nu exista produse in magazin!\n");
	}

	srv.add("iaurt", "produse lactate", 4.63, "Danone");
	srv.add("chipsuri", "snacksuri", 9.6, "Lays");
	srv.add("boia", "condimente", 0.999, "Delikat");
	srv.add("sare", "condimente", 11, "Maggi");
	srv.add("parmezan", "condimente", 8.301, "Delikat");
	srv.add("chipsuri", "snacks", 9.1, "Pringles");

	products = srv.sortProducts("1", "c");
	testFunction(products.at(0), "boia", "condimente", 0.999, "Delikat");
	testFunction(products.at(1), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(2), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(3), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(4), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(5), "sare", "condimente", 11, "Maggi");

	products = srv.sortProducts("1", "d");
	testFunction(products.at(0), "sare", "condimente", 11, "Maggi");
	testFunction(products.at(1), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(2), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(3), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(4), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(5), "boia", "condimente", 0.999, "Delikat");

	products = srv.sortProducts("2", "C");
	testFunction(products.at(0), "boia", "condimente", 0.999, "Delikat");
	testFunction(products.at(1), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(2), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(3), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(4), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(5), "sare", "condimente", 11, "Maggi");

	products = srv.sortProducts("2", "d");
	testFunction(products.at(0), "sare", "condimente", 11, "Maggi");
	testFunction(products.at(1), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(2), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(3), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(4), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(5), "boia", "condimente", 0.999, "Delikat");

	products = srv.sortProducts("3", "c");
	testFunction(products.at(0), "boia", "condimente", 0.999, "Delikat");
	testFunction(products.at(1), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(2), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(3), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(4), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(5), "sare", "condimente", 11, "Maggi");

	products = srv.sortProducts("3", "D");
	testFunction(products.at(0), "sare", "condimente", 11, "Maggi");
	testFunction(products.at(1), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(2), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(3), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(4), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(5), "boia", "condimente", 0.999, "Delikat");

	try {
		products = srv.sortProducts("1", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Ordine de sortare invalida!\n");
	}

	try {
		products = srv.sortProducts("2", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Ordine de sortare invalida!\n");
	}

	try {
		products = srv.sortProducts("3", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Ordine de sortare invalida!\n");
	}

	try {
		products = srv.sortProducts("", "c");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Criteriu de sortare invalid!\n");
	}

	try {
		products = srv.sortProducts("", "d");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Criteriu de sortare invalid!\n");
	}

	try {
		products = srv.sortProducts("", "C");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Criteriu de sortare invalid!\n");
	}

	try {
		products = srv.sortProducts("", "D");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "Criteriu de sortare invalid!\n");
	}
}

void TestingService::runTestsService() const
{
	runTestsServiceCmpStrings();
	runTestsServiceVerifyIfDouble();
	runTestsServiceAdd();
	runTestsServiceDel();
	runTestsServiceModify();
	runTestsServiceSearch();
	runTestsServiceGetAll();
	runTestsServiceFilterProducts();
	runTestsServiceSortProducts();
}