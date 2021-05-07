#include <QtWidgets/QApplication>
#include <qdebug.h>

#include "GUI.h"
#include "TestingApp.h"
#include "AbstractRepo.h"
#include "FileRepository.h"
#include "ProductValidator.h"
#include "Service.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const TestingApp testing_app;
    testing_app.runTestsApp();

    qDebug() << "--------------------All tests passed--------------------";

    FileRepoProducts repo{ "produse" };
    ProductValidator valid;
    Service srv{ repo, valid };
    const auto gui{ new GUI{ srv } };
    gui->show();

    return a.exec();
}
