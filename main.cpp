#include <QCoreApplication>

#include "solarmaxlogger.hpp"

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

    SolarMaxLogger* smlgr = new SolarMaxLogger();
    smlgr->start();

    return a.exec();
}
