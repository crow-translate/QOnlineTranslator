#include "qtranslationoptions.h"

QTranslationOptions::QTranslationOptions()
{}

QTranslationOptions::QTranslationOptions(const QString &typeOfSpeech)
{
    m_typeOfSpeech = typeOfSpeech;
}

QString QTranslationOptions::typeOfSpeech() const
{
    return m_typeOfSpeech;
}

void QTranslationOptions::setTypeOfSpeech(const QString &typeOfSpeech)
{
    m_typeOfSpeech = typeOfSpeech;
}

void QTranslationOptions::appendOption(const QString &word)
{
    m_words.append(word);
    m_translations.append(QStringList());
}

void QTranslationOptions::appendOption(const QString &word, const QStringList &translation)
{
    m_words.append(word);
    m_translations.append(translation);
}

void QTranslationOptions::appendTranslation(int index, const QString &translation)
{
    m_translations[index].append(translation);
}

void QTranslationOptions::appendTranslation(const QString &translation)
{
    m_translations.last().append(translation);
}

QString QTranslationOptions::word(int index) const
{
    return m_words.at(index);
}

QStringList QTranslationOptions::translations(int index) const
{
    return m_translations.at(index);
}

int QTranslationOptions::count() const
{
    return m_words.size();
}
