#ifndef QDEFINITION_H
#define QDEFINITION_H

#include <QString>

class QDefinition
{
public:
    QDefinition(const QString &typeOfSpeech = "", const QString &description = "", const QString &example = "");

    QString typeOfSpeech() const;
    QString description() const;
    QString example() const;

    void setTypeOfSpeech(const QString &typeOfSpeech);
    void setDescription(const QString &description);
    void setExample(const QString &example);

private:
    QString m_typeOfSpeech;
    QString m_description;
    QString m_example;
};

#endif // QDEFINITION_H
