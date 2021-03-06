#include "inverterdata.hpp"

InverterData::InverterData()
{

}

InverterData::InverterData(InverterData& other)
{
    datetime = other.datetime;
    raw = other.raw;
    udc = other.udc;
    idc = other.idc;
    ul1 = other.ul1;
    il1 = other.il1;
    pac = other.pac;
    prl = other.prl;
    tkk = other.tkk;
    tnf = other.tnf;
    kdy = other.kdy;
    kld = other.kld;
}

InverterData::~InverterData()
{

}

QDateTime InverterData::getDatetime() const
{
    return datetime;
}

void InverterData::setDatetime(const QDateTime& value)
{
    datetime = value;
}

QString InverterData::getRaw() const
{
    return raw;
}

void InverterData::setRaw(const QString& value)
{
    raw = value;
}

float InverterData::getUdc() const
{
    return udc;
}

void InverterData::setUdc(float value)
{
    udc = value;
}

float InverterData::getIdc() const
{
    return idc;
}

void InverterData::setIdc(float value)
{
    idc = value;
}

float InverterData::getUl1() const
{
    return ul1;
}

void InverterData::setUl1(float value)
{
    ul1 = value;
}

float InverterData::getIl1() const
{
    return il1;
}

void InverterData::setIl1(float value)
{
    il1 = value;
}

float InverterData::getPac() const
{
    return pac;
}

void InverterData::setPac(float value)
{
    pac = value;
}

int InverterData::getPrl() const
{
    return prl;
}

void InverterData::setPrl(int value)
{
    prl = value;
}

int InverterData::getTkk() const
{
    return tkk;
}

void InverterData::setTkk(int value)
{
    tkk = value;
}

float InverterData::getTnf() const
{
    return tnf;
}

void InverterData::setTnf(float value)
{
    tnf = value;
}

float InverterData::getKdy() const
{
    return kdy;
}

void InverterData::setKdy(float value)
{
    kdy = value;
}

float InverterData::getKld() const
{
    return kld;
}

void InverterData::setKld(float value)
{
    kld = value;
}
