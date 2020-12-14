#ifndef QOPTION_H
#define QOPTION_H

#include <QCoreApplication>

struct QOption
{
    QString word;
    QString gender;
    QStringList translations;
    QJsonObject toJson() const;
};

#endif // QOPTION_H
