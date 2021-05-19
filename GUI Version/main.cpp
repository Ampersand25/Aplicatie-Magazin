#include <QtWidgets/QApplication>
#include <qdebug.h>

#include "GUI.h"
#include "TestingApp.h"
#include "AbstractRepo.h"
#include "FileRepository.h"
#include "ProductValidator.h"
#include "Service.h"

void testApp()
{
    const TestingApp testing_app;
    testing_app.runTestsApp();

    qDebug() << "\n--------------------All tests passed--------------------\n";
}

int main(int argc, char* argv[])
{
    int exit_code;
    
    QApplication a(argc, argv);

    testApp();

    FileRepoProducts repo{ "produse" };
    ProductValidator valid;
    Service srv{ repo, valid };
    const auto gui{ new GUI{ srv } };
    gui->show();

    exit_code = a.exec();

    return exit_code;
}