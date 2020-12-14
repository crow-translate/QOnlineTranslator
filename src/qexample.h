#ifndef QEXAMPLE_H
#define QEXAMPLE_H

#include <QCoreApplication>

struct QExample
{
    QString example;
    QString description;
    QJsonObject toJson() const;
};

#endif // QEXAMPLE_H
