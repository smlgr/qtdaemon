#ifndef INVERTERDATA_HPP
#define INVERTERDATA_HPP

#include <QString>
#include <QDateTime>

class InverterData
{
    public:
        InverterData();
        ~InverterData();

        QDateTime getDatetime() const;
        void setDatetime(const QDateTime& value);

        QString getRaw() const;
        void setRaw(const QString& value);

        float getUdc() const;
        void setUdc(float value);

        float getIdc() const;
        void setIdc(float value);

        float getUl1() const;
        void setUl1(float value);

        float getIl1() const;
        void setIl1(float value);

        float getPac() const;
        void setPac(float value);

        int getPrl() const;
        void setPrl(int value);

        int getTkk() const;
        void setTkk(int value);

        float getTnf() const;
        void setTnf(float value);

        float getKdy() const;
        void setKdy(float value);

        float getKld() const;
        void setKld(float value);

    private:
        QDateTime datetime;
        QString raw;
        float udc;
        float idc;
        float ul1;
        float il1;
        float pac;
        int prl;
        int tkk;
        float tnf;
        float kdy;
        float kld;
};

#endif // INVERTERDATA_HPP
