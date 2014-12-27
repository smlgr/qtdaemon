#ifndef UPDATEMOBILE_HPP
#define UPDATEMOBILE_HPP

#include <QObject>

class UpdateMobile : public QObject
{
        Q_OBJECT
    public:
        explicit UpdateMobile(QObject *parent = 0);
        ~UpdateMobile();

    public slots:
        void update();
};

#endif // UPDATEMOBILE_HPP
