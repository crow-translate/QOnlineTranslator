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

    void appendOption(const QString &word, const QString &gender = "", const QStringList &translations = QStringList());
    void appendTranslation(int index, const QString &translation);
    void appendTranslation(const QString &translation);
    QString word(int index) const;
    QString gender(int index) const;
    QStringList translations(int index) const;
    int count() const;

private:
    QString m_typeOfSpeech;
    QStringList m_words;
    QStringList m_genders;
    QList<QStringList> m_translations;
};

#endif // QTRANSLATIONOPTIONS_H
