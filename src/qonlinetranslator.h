/*
 *  Copyright © 2018 Gennady Chernyshchuk <genaloner@gmail.com>
 *
 *  This file is part of QOnlineTranslator.
 *
 *  QOnlineTranslator is free library; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a get of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef QONLINETRANSLATOR_H
#define QONLINETRANSLATOR_H

#include <QPair>
#include <QUrl>
#include <QNetworkReply>
#include <QMediaPlaylist>

#include "qtranslationoptions.h"
#include "qdefinition.h"

class QOnlineTranslator : public QObject
{
    Q_OBJECT

public:
    explicit QOnlineTranslator(QObject *parent = nullptr);
    explicit QOnlineTranslator(const QString &text,
                               const QString &translationLanguageCode = "auto",
                               const QString &sourceLanguageCode = "auto",
                               const QString &translatorLanguageCode = "auto",
                               QObject *parent = nullptr);

    void translate(const QString &text,
                   const QString &translationLanguageCode = "auto",
                   const QString &sourceLanguageCode = "auto",
                   const QString &translatorLanguageCode = "auto");

    QList<QMediaContent> sourceMedia() const;
    QList<QMediaContent> translationMedia() const;

    QString source() const;
    QString sourceTranscription() const;
    QString sourceLanguageCode() const;
    QString sourceLanguage() const;

    QString translation() const;
    QString translationTranscription() const;
    QString translationLanguageCode() const;
    QString translationLanguage() const;
    QList<QTranslationOptions> translationOptionsList() const;
    QList<QDefinition> definitionsList() const;
    bool error() const;

    QStringList languages() const;
    QStringList codes() const;
    QString codeToLanguage(const QString &code) const;
    QString languageToCode(const QString &language) const;

    static QString defaultLocaleToCode();
    static QString translateText(const QString &translation, QString translationLanguageCode = "auto", QString sourceLanguageCode = "auto");
    static QList<QMediaContent> media(const QString &text, QString languageCode = "auto");

private:
    static int getSplitIndex(const QString &untranslatedText, int limit);

    QString m_source;
    QString m_sourceLanguageCode;
    QString m_sourceTranscription;

    QString m_translation;
    QString m_translationTranscription;
    QString m_translationLanguageCode;
    QList<QTranslationOptions> m_translationOptionsList;
    QList<QDefinition> m_definitionsList;
    bool m_error = false;

    QStringList m_languageNames = { tr("Automatically detect"), tr("Afrikaans"), tr("Albanian"), tr("Amharic"), tr("Arabic"), tr("Armenian"),
                                  tr("Azeerbaijani"), tr("Basque"), tr("Belarusian"), tr("Bengali"), tr("Bosnian"), tr("Bulgarian"), tr("Catalan"),
                                  tr("Cebuano"), tr("Chinese (Simplified)"), tr("Chinese (Traditional)"), tr("Corsican"), tr("Croatian"), tr("Czech"),
                                  tr("Danish"), tr("Dutch"), tr("English"), tr("Esperanto"), tr("Estonian"), tr("Finnish"), tr("French"), tr("Frisian"),
                                  tr("Galician"), tr("Georgian"), tr("German"), tr("Greek"), tr("Gujarati"), tr("Haitian Creole"), tr("Hausa"),
                                  tr("Hawaiian"), tr("Hebrew"), tr("Hindi"), tr("Hmong"), tr("Hungarian"), tr("Icelandic"), tr("Igbo"), tr("Indonesian"),
                                  tr("Irish"), tr("Italian"), tr("Japanese"), tr("Javanese"), tr("Kannada"), tr("Kazakh"), tr("Khmer"), tr("Korean"),
                                  tr("Kurdish"), tr("Kyrgyz"), tr("Lao"), tr("Latin"), tr("Latvian"), tr("Lithuanian"), tr("Luxembourgish"),
                                  tr("Macedonian"), tr("Malagasy"), tr("Malay"), tr("Malayalam"), tr("Maltese"), tr("Maori"), tr("Marathi"), tr("Mongolian"),
                                  tr("Myanmar"), tr("Nepali"), tr("Norwegian"), tr("Chichewa"), tr("Pashto"), tr("Persian"), tr("Polish"), tr("Portuguese"),
                                  tr("Punjabi"), tr("Romanian"), tr("Russian"), tr("Samoan"), tr("Scots Gaelic"), tr("Serbian"), tr("Sesotho"), tr("Shona"),
                                  tr("Sindhi"), tr("Sinhala"), tr("Slovak"), tr("Slovenian"), tr("Somali"), tr("Spanish"), tr("Sundanese"), tr("Swahili"),
                                  tr("Swedish"), tr("Tagalog"), tr("Tajik"), tr("Tamil"), tr("Telugu"), tr("Thai"), tr("Turkish"), tr("Ukrainian"),
                                  tr("Urdu"), tr("Uzbek"), tr("Vietnamese"), tr("Welsh"), tr("Xhosa"), tr("Yiddish"), tr("Yoruba"), tr("Zulu") };

    QStringList m_languageCodes = { "auto", "af", "sq", "am", "ar", "hy", "az", "eu", "be", "bn", "bs", "bg", "ca", "ceb", "zh-CN", "zh-TW", "co", "hr", "cs",
                                  "da", "nl", "en", "eo", "et", "fi", "fr", "fy", "gl", "ka", "de", "el", "gu", "ht", "ha", "haw", "iw", "hi", "hmn", "hu",
                                  "is", "ig", "id", "ga", "it", "ja", "jw", "kn", "kk", "km", "ko", "ku", "ky", "lo", "la", "lv", "lt", "lb", "mk", "mg",
                                  "ms", "ml", "mt", "mi", "mr", "mn", "my", "ne", "no", "ny", "ps", "fa", "pl", "pt", "pa", "ro", "ru", "sm", "gd", "sr",
                                  "st", "sn", "sd", "si", "sk", "sl", "so", "es", "su", "sw", "sv", "tl", "tg", "ta", "te", "th", "tr", "uk", "ur", "uz",
                                  "vi", "cy", "xh", "yi", "yo", "zu" };
};

#endif // QONLINETRANSLATOR_H
