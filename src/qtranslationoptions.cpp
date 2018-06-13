#include "qtranslationoptions.h"

QTranslationOptions::QTranslationOptions(const QString &typeOfSpeech)
{
    m_typeOfSpeech = typeOfSpeech;
}

QString QTranslationOptions::typeOfSpeech() const
{
    return m_typeOfSpeech;
}

QString QTranslationOptions::word(int index) const
{
    return m_words.at(index);
}

QString QTranslationOptions::gender(int index) const
{
    return m_genders.at(index);
}

QStringList QTranslationOptions::translations(int index) const
{
    return m_translations.at(index);
}

void QTranslationOptions::setTypeOfSpeech(const QString &typeOfSpeech)
{
    m_typeOfSpeech = typeOfSpeech;
}

void QTranslationOptions::appendOption(const QString &word, const QString &gender, const QStringList &translations)
{
    m_words.append(word);
    m_genders.append(gender);
    m_translations.append(translations);
}

void QTranslationOptions::appendTranslation(int index, const QString &translation)
{
    m_translations[index].append(translation);
}

void QTranslationOptions::appendTranslation(const QString &translation)
{
    m_translations.last().append(translation);
}

int QTranslationOptions::count() const
{
    return m_words.size();
}
