#include "qoption.h"

#include <QJsonObject>
#include <QJsonArray>

QJsonObject QOption::toJson() const
{
    QJsonObject object
    {
        {"word", word},
        {"gender", gender},
        {"translations", QJsonArray::fromStringList(translations)}
    };

    return object;
}
