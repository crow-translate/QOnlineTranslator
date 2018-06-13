#include "qdefinition.h"

QDefinition::QDefinition(const QString &typeOfSpeech, const QString &description, const QString &example)
{
    m_typeOfSpeech = typeOfSpeech;
    m_description = description;
    m_example = example;
}

QString QDefinition::typeOfSpeech() const
{
    return m_typeOfSpeech;
}

QString QDefinition::description() const
{
    return m_description;
}

QString QDefinition::example() const
{
    return m_example;
}

void QDefinition::setTypeOfSpeech(const QString &typeOfSpeech)
{
    m_typeOfSpeech = typeOfSpeech;
}

void QDefinition::setDescription(const QString &description)
{
    m_description = description;
}

void QDefinition::setExample(const QString &example)
{
    m_example = example;
}
