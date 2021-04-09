#include "TestingApp.h"
#include "TestingDomain.h"
#include "TestingRepo.h"
#include "TestingValidation.h"
#include "TestingUtils.h"
#include "TestingService.h"

void TestingApp::runTestsApp() const
{
	// Testarea layerului/stratului Domain (domeniul aplicatiei, unde sunt definite entitatile modelate de aplicatie)
	{
		TestingDomain testing_domain;
		testing_domain.runTestsDomain();
	}

	// Testarea layerului/stratului Infrastructure/Repository (leyerul/stratul de persistenta a datelor, unde sunt stocate inregistrarile din aplicatie)
	{
		TestingRepo testing_repo;
		testing_repo.runTestsRepo();
	}

	// Testarea layerului/stratului Validation (leyerul/stratul de validare a datelor)
	{
		ProductValidator valid;

		const TestingValidation testing_validation{ valid };
		testing_validation.runTestsProductValidator();
	}

	// Testarea layerului/stratului Utils (leyerul/stratul unde sunt declarate si definite functii utilitare/generice)
	{
		Utils utils;

		const TestingUtils testing_utils{ utils };
		testing_utils.runTestsUtils();
	}

	// Testarea layerului/stratului Business/Service (leyerul/stratul unde se valideaza datele introduse de utilizator in UI si se executa comenzi, adica GRASP Controllerul aplicatiei)
	{
		ProductValidator valid;

		const TestingService testing_service{ valid };
		testing_service.runTestsService();
	}
}