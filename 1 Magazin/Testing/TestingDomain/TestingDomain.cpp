#include "TestingDomain.h"
#include "Product.h"

#include <cassert> // #include <assert.h>
#include <cmath>   // #include <math.h>

void TestingDomain::runTestsDomainGetters() const
{
	Product p{ "Milka cu lapte", "produse lactate", 6.99, "Milka UK" };

	assert(p.getName() == "Milka cu lapte");
	assert(p.getType() == "produse lactate");
	assert(fabs(p.getPrice() - 6.99) < 1e-12);
	assert(p.getProducer() == "Milka UK");
}

void TestingDomain::runTestsDomainSetters() const
{
	Product p{ "Milka cu lapte", "produse lactate", 6.99, "Milka UK" };

	assert(p.getName() == "Milka cu lapte");
	assert(p.getType() == "produse lactate");
	assert(fabs(p.getPrice() - 6.99) < 1e-12);
	assert(p.getProducer() == "Milka UK");

	p.setType("produse curatenie");
	
	assert(p.getName() == "Milka cu lapte");
	assert(p.getType() == "produse curatenie");
	assert(fabs(p.getPrice() - 6.99) < 1e-12);
	assert(p.getProducer() == "Milka UK");

	p.setPrice(25.1375);

	assert(p.getName() == "Milka cu lapte");
	assert(p.getType() == "produse curatenie");
	assert(fabs(p.getPrice() - 25.1375) < 1e-12);
	assert(p.getProducer() == "Milka UK");
}

void TestingDomain::runTestsDomainCmpProducts() const
{
	Product p{ "Milka cu lapte", "produse lactate", 6.99, "Milka UK" };

	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse curatenie", 25.1375, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse curatenie", 25.1375, "Milka UK" }) == 0);
	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse curatenie", 6.99, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse curatenie", 6.99, "Milka UK" }) == 0);

	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse lactate", 25.1375, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse lactate", 25.1375, "Milka UK" }) == 0);
	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse lactate", 6.99, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse lactate", 6.99, "Milka UK" }) == 0);

	assert(p.cmpProducts({ "Milka cu lapte", "produse curatenie", 25.1375, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Milka cu lapte", "produse curatenie", 25.1375, "Milka UK" }) == 1);
	assert(p.cmpProducts({ "Milka cu lapte", "produse curatenie", 6.99, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Milka cu lapte", "produse curatenie", 6.99, "Milka UK" }) == 1);

	assert(p.cmpProducts({ "Milka cu lapte", "produse lactate", 25.1375, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Milka cu lapte", "produse lactate", 25.1375, "Milka UK" }) == 1);
	assert(p.cmpProducts({ "Milka cu lapte", "produse lactate", 6.99, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Milka cu lapte", "produse lactate", 6.99, "Milka UK" }) == 1);
}

void TestingDomain::runTestsDomainStrProduct() const
{
	Product p1{ "Milka cu lapte", "produse lactate", 6.99, "Milka UK" };
	assert(p1.strProduct() == "Nume: Milka cu lapte\nTip: produse lactate\nPret: 6.990000\nProducator: Milka UK\n");

	Product p2{ "Detergent lichid LENOR", "produse curatenie", 25.1375, "LENOR" };
	assert(p2.strProduct() == "Nume: Detergent lichid LENOR\nTip: produse curatenie\nPret: 25.137500\nProducator: LENOR\n");

	Product p3{ "Chipsuri Lays cu branza", "produs alimentar", 3.847193, "Lays" };
	assert(p3.strProduct() == "Nume: Chipsuri Lays cu branza\nTip: produs alimentar\nPret: 3.847193\nProducator: Lays\n");

	Product p4{ "Parmezan", "condimente", 132.03813752742, "Broccoli INC" };
	assert(p4.strProduct() == "Nume: Parmezan\nTip: condimente\nPret: 132.038138\nProducator: Broccoli INC\n");
}

void TestingDomain::runTestsDomain() const
{
	runTestsDomainGetters();
	runTestsDomainSetters();
	runTestsDomainCmpProducts();
	runTestsDomainStrProduct();
}