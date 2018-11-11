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
    Q_ENUM(Engine)
    enum Speaker {
        Zahar,
        Ermil,
        Jane,
        Oksana,
        Alyss,
        Omazh
    };
    Q_ENUM(Speaker)
    enum Emotion {
        Neutral,
        Good,
        Evil
    };
    Q_ENUM(Emotion)
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
    Q_ENUM(Language)
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

    static QString languageString(Language language);
    static QString languageCode(Language language);
    static Language language(const QLocale &locale);
    static Language language(const QString &languageCode);

private:
    // Get sync reply
    template<typename... Query>
    QByteArray get(const QString &urlString, const Query&... queryStrings);

    // Get API reply
    QByteArray getGoogleTranslation(const QString &text, const QString &translationCode, const QString &sourceCode = "auto", const QString &uiCode = "en");
    QByteArray getYandexTranslation(const QString &text, const QString &translationCode, const QString &sourceCode = "auto");
    QByteArray getYandexTranslit(const QString &text, const QString &langCode);
    QByteArray getYandexDictionary(const QString &text, const QString &translationCode, const QString &sourceCode, const QString &uiCode);

    // Other
    void resetData();
    static bool isSupportYandexTranslit(Language language);
    static int getSplitIndex(const QString &untranslatedText, int limit);
    static Language language(const QString &languageCode, Engine engine);
    static QString languageCode(Language language, Engine engine);
    static QString speakerCode(Speaker speaker);
    static QString emotionCode(Emotion emotion);

    QNetworkAccessManager m_network;

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
};

#endif // QONLINETRANSLATOR_H
