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

#include "qdictionary.h"
#include "qdefinition.h"

#include <QNetworkReply>
#include <QMediaPlaylist>

class QOnlineTranslator : public QObject
{
    Q_OBJECT

public:
    enum Language {
        NoLanguage = -1,
        Auto,
        Afrikaans,
        Albanian,
        Amharic,
        Arabic,
        Armenian,
        Azerbaijani,
        Basque,
        Bashkir,
        Belarusian,
        Bengali,
        Bosnian,
        Bulgarian,
        Catalan,
        Cantonese,
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
        Fijian,
        Filipino,
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
        Klingon,
        KlingonPlqaD,
        Korean,
        Kurdish,
        Kyrgyz,
        Lao,
        Latin,
        Latvian,
        LevantineArabic,
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
        QueretaroOtomi,
        Romanian,
        Russian,
        Samoan,
        ScotsGaelic,
        SerbianCyrillic,
        SerbianLatin,
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
        Tahitian,
        Tajik,
        Tamil,
        Tatar,
        Telugu,
        Thai,
        Tongan,
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
        YucatecMaya,
        Zulu
    };
    Q_ENUM(Language)

    enum Engine {
        Google,
        Yandex,
        Bing
    };
    Q_ENUM(Engine)

    enum Voice {
        // All
        Default,

        // Yandex
        Zahar,
        Ermil,
        Jane,
        Oksana,
        Alyss,
        Omazh,

        // Bing
        Female,
        Male
    };
    Q_ENUM(Voice)

    enum Emotion {
        Neutral,
        Good,
        Evil
    };
    Q_ENUM(Emotion)

    enum TranslationError {
        NoError,
        ParametersError,
        NetworkError,
        ServiceError,
        ParsingError
    };

    explicit QOnlineTranslator(QObject *parent = nullptr);

    void translate(const QString &text, Engine engine = Google, Language translationLang = Auto, Language sourceLang = Auto, Language uiLang = Auto);
    QList<QMediaContent> media(const QString &text, Engine engine, Language lang = Auto, Voice voice = Default, Emotion emotion = Neutral);

    QList<QMediaContent> sourceMedia(Engine engine, Voice voice = Default, Emotion emotion = Neutral);
    QList<QMediaContent> translationMedia(Engine engine, Voice voice = Default, Emotion emotion = Neutral);

    QString source() const;
    QString sourceTranslit() const;
    QString sourceTranscription() const;
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

    bool isSourceTranslitEnabled() const;
    void setSourceTranslitEnabled(bool enable);

    bool isTranslationTranslitEnabled() const;
    void setTranslationTranslitEnabled(bool enable);

    bool isSourceTranscriptionEnabled() const;
    void setSourceTranscriptionEnabled(bool enable);

    bool isDictionaryEnabled() const;
    void setDictionaryEnabled(bool enable);

    bool isDefinitionsEnabled() const;
    void setDefinitionsEnabled(bool enable);

    static QString languageString(Language lang);
    static QString languageCode(Language lang);
    static Language language(const QLocale &locale);
    static Language language(const QString &langCode);

private:
    // Get API reply as JSON
    QByteArray getGoogleTranslation(const QString &text, const QString &translationCode, const QString &sourceCode = "auto", const QString &uiCode = "en");
    QByteArray getYandexTranslation(const QString &text, const QString &translationCode, const QString &sourceCode = "auto");
    QByteArray getYandexTranslit(const QString &text, const QString &langCode);
    QByteArray getYandexDictionary(const QString &text, const QString &translationCode, const QString &sourceCode, const QString &uiCode);
    QByteArray getBingTextLanguage(const QString &text);
    QByteArray getBingTranslation(const QString &text, const QString &translationCode, const QString &sourceCode = "auto");
    QByteArray getBingTranslit(const QString &text, const QString &langCode);
    QByteArray getBingDictionary(const QString &text, const QString &translationCode, const QString &sourceCode);

    // Generate Codes for API
    QString translationLanguageCode(Language lang, Engine engine);
    QString ttsLanguageCode(Language lang, Engine engine);
    QString voiceCode(Voice voice, Engine engine);
    static QString emotionCode(Emotion emotion);

    // Check for service support
    static bool isSupportGoogle(Language lang);
    static bool isSupportYandexTranslation(Language lang);
    static bool isSupportYandexTranslit(Language lang);
    static bool isSupportYandexDictionary(Language sourceLang, Language translationLang);
    static bool isSupportBingTranslation(Language lang);
    static bool isSupportBingTranslit(Language lang);
    static bool isSupportBingDictionary(Language sourceLang, Language translationLang);

    // Other
    static Language language(const QString &langCode, Engine engine);
    static int getSplitIndex(const QString &untranslatedText, int limit);
    void resetData();

    QNetworkAccessManager m_network{this};

    Language m_sourceLang = NoLanguage;
    Language m_translationLang = NoLanguage;
    Language m_uiLang = NoLanguage;
    TranslationError m_error = NoError;

    QString m_source;
    QString m_sourceTranslit;
    QString m_sourceTranscription;
    QString m_translation;
    QString m_translationTranslit;
    QString m_errorString;

    QList<QDictionary> m_dictionaryList;
    QList<QDefinition> m_definitionsList;

    bool m_sourceTranslitEnabled = true;
    bool m_translationTranslitEnabled = true;
    bool m_sourceTranscriptionEnabled = true;
    bool m_dictionaryEnabled = true;
    bool m_definitionsEnabled = true;
    char m_padding[3];

    static QString m_yandexKey;
    static const QStringList m_languageCodes;
    static bool m_secondYandexKeyRequest;
};

#endif // QONLINETRANSLATOR_H
