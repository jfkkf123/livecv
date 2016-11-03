#include <QCoreApplication>
#include <QTest>
#include <qqml.h>

#include "qtestrunner.h"

int main(int argc, char *argv[]){

    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    return QTestRunner::runTests(argc, argv);
}