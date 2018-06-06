#ifndef QTRANSLATIONOPTIONS_H
#define QTRANSLATIONOPTIONS_H

#include <QStringList>

class QTranslationOptions
{
public:
    QTranslationOptions();
    QTranslationOptions(const QString &typeOfSpeech);

    QString typeOfSpeech() const;
    void setTypeOfSpeech(const QString &typeOfSpeech);

    void appendOption(const QString &word);
    void appendOption(const QString &word, const QStringList &translation);
    void appendTranslation(int index, const QString &translation);
    void appendTranslation(const QString &translation);
    QString word(int index) const;
    QStringList translations(int index) const;
    int count() const;

private:
    QString m_typeOfSpeech;
    QStringList m_words;
    QList<QStringList> m_translations;
};

#endif // QTRANSLATIONOPTIONS_H
