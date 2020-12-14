#include "qexample.h"

#include <QJsonObject>

QJsonObject QExample::toJson() const
{
    QJsonObject object
    {
        {"example", example},
        {"description", description},
    };

    return object;
}
