// 1 Magazin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "TestingApp.h"
#include "Repository.h"
#include "ProductValidator.h"
#include "Service.h"
#include "Console.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdio> // #include <stdio.h>
#include <crtdbg.h>

int main(void)
{
    // Testarea aplicatiei
    const TestingApp testing_app; // instantiem un obiect de clasa TestingApp
    testing_app.runTestsApp(); // rulam toate testele (pentru fiecare layer/strat din aplicatie)

    // Asamblarea si rularea aplicatie
    //RepoProducts repo; // instantiem un obiect de clasa RepoProducts
    //ProductValidator valid; // instantiem un obiect de clasa ProductValidator
    //Service srv{ repo, valid }; // instantiem un obiect de clasa Service caruia ii parsam ca si atribute private obiectele repo (de clasa RepoProducts) si valid (de clasa ProductValidator) instantiate anterior/precedent
    //const UI ui{ srv }; // instantiem un obiect de clasa UI caruia ii parsam ca si atribut privat obiectul srv (de clasa Service) instantiat anterior
    //ui.runApp(); // pornim aplicatia

    // Testam aplicatia de memory leaks (scurgeri/leak-uri de memorie)
    //_CrtDumpMemoryLeaks();

    // Terminarea aplicatiei
    return 0; // codul de return al aplicatiei (exit status) care indica o terminare normala (0 - fara erori)
}