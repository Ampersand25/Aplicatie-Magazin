// 1 Magazin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "TestingApp.h"
#include "Repository.h"
#include "FileRepository.h"
#include "ProductValidator.h"
#include "Service.h"
#include "Console.h"

// Pentru detectarea de memory leaks (scurgeri de memorie)
#define _CRTDBG_MAP_ALLOC
#include <cstdio> // #include <stdio.h>
#include <crtdbg.h>

#include <iostream> // pentru std::cin si std::cout
#include <string>   // pentru std::string
#include <memory>   // pentru std::unique_ptr si std::make_unique

using std::cin;
using std::cout;
using std::string;
using std::unique_ptr;
using std::make_unique;

/*
* Procedura care ruleaza testele pentru fiecare layer/strat din aplicatie (cu exceptia UI-ului)
*/
void testApplication(void)
{
    const TestingApp testing_app; // instantiem un obiect de clasa TestingApp
    testing_app.runTestsApp(); // rulam toate testele (pentru fiecare layer/strat din aplicatie)
}

/*
* Procedura (functie procedurala) care afiseaza optiunile de persistenta a datelor in cadrul aplicatiei
*/
void meniuSalvareFisiere(void)
{
    cout << "Alegeti cum sa se faca salvarea datelor in cadrul aplicatie:\n";
    cout << "1 - salvare in memorie\n";
    cout << "2 - salvare in fisier text\n";
}

/*
* Functie operand (de tip rezultat) care citeste de la tastatura (intrarea standard) modul in care se vor salva datele in cadrul aplicatiei
* Subprogramul intoarce un string care contine modul de salvare a datelor (stringul "1" pentru salvare in memorie si stringul "2" pentru salvare in fisier text)
*/
string readOptionDataPersistence(void)
{
    string ans; // string in care vom citi raspunsul dat de utilizator (user)
    getline(cin, ans); // citim stringul ans de la tastatura (intrarea standard) cu functia getline (care citeste si spatiile, pana la newline = end of line)

    while (ans != "1" && ans != "2") // stringul ans nu este valid (raspunsul utilizatorului este invalid)
    {
        cout << "Optiune inexistenta!\n";
        cout << "\n>>>";

        getline(cin, ans); // re-citim in stringul ans cum sa se faca salvarea datelor in aplicatie
    }

    // ans este stringul "1" sau "2"

    return ans; // returnam/intoarcem prin numele functiei stringul care reprezinta modul in care se vor salva datele in fisier
                // ans = "1" - salvarea datelor in memorie
                // ans = "2" - salvarea datelor in fisier
}

/*
* Functie operand (de tip rezultat) care citeste de la tastatura (intrarea standard) numele fisierului in care vor fi salvate datele din cadrul aplicatiei
* Subprogramul intoarce un string nevid (<> "") care va fi numele fisierului in care se va face import si export in cadrul aplicatiei
*/
string readFilename(void)
{
    cout << "\nIntroduceti numele fisierului text in care sa se faca salvarea datelor: ";

    string filename; // string in care memoram/retinem numele fisierului in care se vor salva datele
    getline(cin, filename); // citim stringul filename de la tastatura (intrarea standard) cu functia getline (care citeste si spatiile, pana la newline = end of line)

    while (filename.empty()) // while (!filename.size())
                             // while (filename == "")
    {
        // stringul citit de la tastatura (filename) este vid/gol
        // acesta nu poate reprezenta numele unui fisier text

        cout << "Numele fisierului nu poate sa fie vid!\n";
        cout << "\nReintroduceti numele fisierului text in care se va face salvarea datelor: ";

        getline(cin, filename); // re-citim numele fisierului in care se vor salva datele
    }

    // stringul filename contine cel putin un element (caracter) <=> nu este gol

    return filename; // returnam/intoarcem prin numele functiei un string (sir de caractere din STL) care reprezinta numele fisierului text in care se vor salva datele din aplicatie
                     // filename <> "" (stringul filename nu este stringul vid)
}

/*
* Procedura care asambleaza si ruleaza (executa) aplicatia
*/
void runApplication(const unique_ptr<RepoProducts>& repo)
{
    ProductValidator valid; // instantiem un obiect de clasa ProductValidator
    Service srv{ *repo, valid }; // instantiem un obiect de clasa Service caruia ii parsam ca si atribute private obiectele repo (de clasa RepoProducts) si valid (de clasa ProductValidator) instantiate anterior/precedent
    const UI ui{ srv }; // instantiem un obiect de clasa UI caruia ii parsam ca si atribut privat obiectul srv (de clasa Service) instantiat anterior
    ui.runApp(); // pornim aplicatia
}

/*
* Procedura (functie procedurala) care instantiaza repository-ul in care se vor memora datele din aplicatie
* Repo-ul poate sa fie unu simplu (salvare in memorie) sau cu fisiere (salvare in fisier text)
* Subrutina asambleaza repository-ul (obiect de clasa RepoProducts sau derivat din aceasta clasa) si dupa face un apel polimorfic la procedura runApplication care va instantia si celelalte obiecte din aplicatie dupa care o va executa (rula)
*/
void setUpRepository(void)
{
    meniuSalvareFisiere(); // afisam meniul cu optiunile de salvare a datelor

    cout << "\n>>>";

    const string ans{ readOptionDataPersistence() }; // string in care retinem modul de salvare a datelor in aplicatie
                                                     // ans = "1" - salvare in memorie
                                                     // ans = "2" - salvare in fisier text

    unique_ptr<RepoProducts> repo;

    if (ans == "1")
    {
        // salvarea datelor in memorie

        repo = make_unique<RepoProducts>(); // instantiem un obiect de clasa RepoProducts
    }
    else {
        // salvarea datelor in fisier text (cu extensia .txt)

        const string filename{ readFilename() }; // numele fisierului text in care vom salva datele

        repo = make_unique<FileRepoProducts>(filename); // instantiem un obiect de clasa FileRepoProducts caruia ii atribuim ca si camp privat stringul filename (numele fisierului text in care va avea loc persistenta datelor din aplicatie)
    }

    runApplication(repo); // apealam procedura runApplication care va rula aplicatia
}

/*
* Procedura (functie procedurala) care testeaza aplicatia de memory leaks (scurgeri de informatie)
*/
void testMemoryLeaks(void) noexcept
{
    _CrtDumpMemoryLeaks(); // apelam _CrtDumpMemoryLeaks care detecteaza scurgerile de memorie rezultate in urma ne-eliberarii memoriei de pe heap (alocata dinamic) cu free sau delete
}

int main(void)
{
    // Testarea aplicatiei
    testApplication();

    // Asamblarea si rularea aplicatie
    setUpRepository();

    // Testam aplicatia de memory leaks (scurgeri/leak-uri de memorie)
    testMemoryLeaks();

    // Terminarea aplicatiei
    return 0; // codul de return al aplicatiei (exit status) care indica o terminare normala (0 - fara erori)
}