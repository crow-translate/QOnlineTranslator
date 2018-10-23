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

#include <QNetworkReply>
#include <QMediaPlaylist>

#include "qdictionary.h"
#include "qdefinition.h"

class QOnlineTranslator : public QObject
{
    Q_OBJECT

public:
    enum Engine {
        Google,
        Yandex
    };
    enum Speaker {
        Zahar,
        Ermil,
        Jane,
        Oksana,
        Alyss,
        Omazh
    };
    enum Emotion {
        Neutral,
        Good,
        Evil
    };
    enum Language {
        NoLanguage = -1,
        Auto,
        Afrikaans,
        Albanian,
        Amharic,
        Arabic,
        Armenian,
        Azeerbaijani,
        Basque,
        Bashkir,
        Belarusian,
        Bengali,
        Bosnian,
        Bulgarian,
        Catalan,
        Cebuano,
        SimplifiedChinese,
        TraditionalChinese,
        Corsican,
        Croatian,
        Czech,
        Danish,
        Dutch,
        English,
        Esperanto,
        Estonian,
        Finnish,
        French,
        Frisian,
        Galician,
        Georgian,
        German,
        Greek,
        Gujarati,
        HaitianCreole,
        Hausa,
        Hawaiian,
        Hebrew,
        HillMari,
        Hindi,
        Hmong,
        Hungarian,
        Icelandic,
        Igbo,
        Indonesian,
        Irish,
        Italian,
        Japanese,
        Javanese,
        Kannada,
        Kazakh,
        Khmer,
        Korean,
        Kurdish,
        Kyrgyz,
        Lao,
        Latin,
        Latvian,
        Lithuanian,
        Luxembourgish,
        Macedonian,
        Malagasy,
        Malay,
        Malayalam,
        Maltese,
        Maori,
        Marathi,
        Mari,
        Mongolian,
        Myanmar,
        Nepali,
        Norwegian,
        Chichewa,
        Papiamento,
        Pashto,
        Persian,
        Polish,
        Portuguese,
        Punjabi,
        Romanian,
        Russian,
        Samoan,
        ScotsGaelic,
        Serbian,
        Sesotho,
        Shona,
        Sindhi,
        Sinhala,
        Slovak,
        Slovenian,
        Somali,
        Spanish,
        Sundanese,
        Swahili,
        Swedish,
        Tagalog,
        Tajik,
        Tamil,
        Tatar,
        Telugu,
        Thai,
        Turkish,
        Udmurt,
        Ukrainian,
        Urdu,
        Uzbek,
        Vietnamese,
        Welsh,
        Xhosa,
        Yiddish,
        Yoruba,
        Zulu
    };
    enum TranslationError {
        NoError,
        ParametersError,
        NetworkError,
        ServiceError,
        ParsingError
    };

    explicit QOnlineTranslator(QObject *parent = nullptr);

    void translate(const QString &text, Engine engine = Google, Language translationLang = Auto, Language sourceLang = Auto, Language uiLang = Auto);
    QList<QMediaContent> media(const QString &text, Engine engine, Language language = Auto, Speaker speaker = Zahar, Emotion emotion = Neutral);

    QList<QMediaContent> sourceMedia(Engine engine, Speaker speaker = Zahar, Emotion emotion = Neutral);
    QList<QMediaContent> translationMedia(Engine engine, Speaker speaker = Zahar, Emotion emotion = Neutral);

    QString source() const;
    QString sourceTranslit() const;
    QString sourceLanguageString() const;
    Language sourceLanguage() const;

    QString translation() const;
    QString translationTranslit() const;
    QString translationLanguageString() const;
    Language translationLanguage() const;

    QList<QDictionary> dictionaryList() const;
    QList<QDefinition> definitionsList() const;

    TranslationError error() const;
    QString errorString() const;

    QString languageString(Language language) const;
    static QString languageCode(Language language);
    static Language language(const QLocale &locale);
    static Language language(const QString &languageCode);

private:
    bool generateYandexSid(QNetworkAccessManager &network);

    // Helper functions
    template<typename... Query>
    static QNetworkReply *sendRequest(QNetworkAccessManager &network, const QString &urlString, const Query&... queryStrings);

    static int getSplitIndex(const QString &untranslatedText, int limit);
    static Language language(const QString &languageCode, Engine engine);
    static QString languageCode(Language language, Engine engine);
    static QString speakerCode(Speaker speaker);
    static QString emotionCode(Emotion emotion);

    Language m_sourceLang;
    Language m_translationLang;
    Language m_uiLang;
    TranslationError m_error = NoError;

    QString m_source;
    QString m_sourceTranslit;
    QString m_translation;
    QString m_translationTranslit;
    QString m_errorString;

    QList<QDictionary> m_dictionaryList;
    QList<QDefinition> m_definitionsList;

    static QString m_yandexSid;
    static bool m_secondSidRequest;
    static const QStringList m_languageCodes;

    const QStringList m_languageNames = { tr("Automatically detect"), tr("Afrikaans"), tr("Albanian"), tr("Amharic"), tr("Arabic"), tr("Armenian"),
                                        tr("Azeerbaijani"), tr("Basque"), tr("Bashkir"), tr("Belarusian"), tr("Bengali"), tr("Bosnian"), tr("Bulgarian"), tr("Catalan"),
                                        tr("Cebuano"), tr("Chinese (Simplified)"), tr("Chinese (Traditional)"), tr("Corsican"), tr("Croatian"), tr("Czech"),
                                        tr("Danish"), tr("Dutch"), tr("English"), tr("Esperanto"), tr("Estonian"), tr("Finnish"), tr("French"), tr("Frisian"),
                                        tr("Galician"), tr("Georgian"), tr("German"), tr("Greek"), tr("Gujarati"), tr("Haitian Creole"), tr("Hausa"),
                                        tr("Hawaiian"), tr("Hebrew"), tr("Hill Mari"), tr("Hindi"), tr("Hmong"), tr("Hungarian"), tr("Icelandic"), tr("Igbo"), tr("Indonesian"),
                                        tr("Irish"), tr("Italian"), tr("Japanese"), tr("Javanese"), tr("Kannada"), tr("Kazakh"), tr("Khmer"), tr("Korean"),
                                        tr("Kurdish"), tr("Kyrgyz"), tr("Lao"), tr("Latin"), tr("Latvian"), tr("Lithuanian"), tr("Luxembourgish"),
                                        tr("Macedonian"), tr("Malagasy"), tr("Malay"), tr("Malayalam"), tr("Maltese"), tr("Maori"), tr("Marathi"), tr("Mari"), tr("Mongolian"),
                                        tr("Myanmar"), tr("Nepali"), tr("Norwegian"), tr("Chichewa"), tr("Papiamento"), tr("Pashto"), tr("Persian"), tr("Polish"), tr("Portuguese"),
                                        tr("Punjabi"), tr("Romanian"), tr("Russian"), tr("Samoan"), tr("Scots Gaelic"), tr("Serbian"), tr("Sesotho"), tr("Shona"),
                                        tr("Sindhi"), tr("Sinhala"), tr("Slovak"), tr("Slovenian"), tr("Somali"), tr("Spanish"), tr("Sundanese"), tr("Swahili"),
                                        tr("Swedish"), tr("Tagalog"), tr("Tajik"), tr("Tamil"), tr("Tatar"), tr("Telugu"), tr("Thai"), tr("Turkish"), tr("Udmurt"), tr("Ukrainian"),
                                        tr("Urdu"), tr("Uzbek"), tr("Vietnamese"), tr("Welsh"), tr("Xhosa"), tr("Yiddish"), tr("Yoruba"), tr("Zulu") };
};

#endif // QONLINETRANSLATOR_H
