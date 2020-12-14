/*
 *  Copyright © 2018-2020 Hennadii Chernyshchyk <genaloner@gmail.com>
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

#include "qexample.h"
#include "qoption.h"

#include <QMap>
#include <QPointer>
#include <QVector>

class QStateMachine;
class QState;
class QNetworkAccessManager;
class QNetworkReply;

class QOnlineTranslator : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QOnlineTranslator)

    friend class QOnlineTts;

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
        Bashkir,
        Basque,
        Belarusian,
        Bengali,
        Bosnian,
        Bulgarian,
        Cantonese,
        Catalan,
        Cebuano,
        Chichewa,
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
        Kinyarwanda,
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
        Oriya,
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
        SimplifiedChinese,
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
        TraditionalChinese,
        Turkish,
        Turkmen,
        Udmurt,
        Uighur,
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

    enum TranslationError {
        NoError,
        ParametersError,
        NetworkError,
        ServiceError,
        ParsingError
    };

    explicit QOnlineTranslator(QObject *parent = nullptr);

    void translate(const QString &text, Engine engine = Google, Language translationLang = Auto, Language sourceLang = Auto, Language uiLang = Auto);
    void detectLanguage(const QString &text, Engine engine = Google);

    void abort();
    bool isRunning() const;

    QString toJson() const;
    QString source() const;
    QString sourceTranslit() const;
    QString sourceTranscription() const;
    QString sourceLanguageName() const;
    Language sourceLanguage() const;

    QString translation() const;
    QString translationTranslit() const;
    QString translationLanguageName() const;
    Language translationLanguage() const;

    QMap<QString, QVector<QOption>> translationOptions() const;
    QMap<QString, QVector<QExample>> examples() const;

    TranslationError error() const;
    QString errorString() const;

    bool isSourceTranslitEnabled() const;
    void setSourceTranslitEnabled(bool enable);

    bool isTranslationTranslitEnabled() const;
    void setTranslationTranslitEnabled(bool enable);

    bool isSourceTranscriptionEnabled() const;
    void setSourceTranscriptionEnabled(bool enable);

    bool isTranslationOptionsEnabled() const;
    void setTranslationOptionsEnabled(bool enable);

    bool isExamplesEnabled() const;
    void setExamplesEnabled(bool enable);

    static QString languageName(Language lang);
    static QString languageCode(Language lang);
    static Language language(const QLocale &locale);
    static Language language(const QString &langCode);
    static bool isSupportTranslation(Engine engine, Language lang);

signals:
    void finished();

private slots:
    void skipGarbageText();

    // Google
    void requestGoogleTranslate();
    void parseGoogleTranslate();

    // Yandex
    void requestYandexKey();
    void parseYandexKey();

    void requestYandexTranslate();
    void parseYandexTranslate();

    void requestYandexSourceTranslit();
    void parseYandexSourceTranslit();

    void requestYandexTranslationTranslit();
    void parseYandexTranslationTranslit();

    void requestYandexDictionary();
    void parseYandexDictionary();

    // Bing
    void requestBingTranslate();
    void parseBingTranslate();

    void requestBingDictionary();
    void parseBingDictionary();

private:
    /*
     * Engines have translation limit, so need to split all text into parts and make request sequentially.
     * Also Yandex and Bing requires several requests to get dictionary, transliteration etc.
     * We use state machine to rely async computation with signals and slots.
     */
    void buildGoogleStateMachine();
    void buildGoogleDetectStateMachine();

    void buildYandexStateMachine();
    void buildYandexDetectStateMachine();

    void buildBingStateMachine();
    void buildBingDetectStateMachine();

    // Helper functions to build nested states
    void buildSplitNetworkRequest(QState *parent, void (QOnlineTranslator::*requestMethod)(), void (QOnlineTranslator::*parseMethod)(), const QString &text, int textLimit);
    void buildNetworkRequestState(QState *parent, void (QOnlineTranslator::*requestMethod)(), void (QOnlineTranslator::*parseMethod)(), const QString &text = {});

    // Helper functions for transliteration
    void requestYandexTranslit(Language language);
    void parseYandexTranslit(QString &text);

    void resetData(TranslationError error = NoError, const QString &errorString = {});

    // Check for service support
    static bool isSupportTranslit(Engine engine, Language lang);
    static bool isSupportDictionary(Engine engine, Language sourceLang, Language translationLang);

    // Other
    static QString languageApiCode(Engine engine, Language lang);
    static Language language(Engine engine, const QString &langCode);
    static int getSplitIndex(const QString &untranslatedText, int limit);
    static bool isContainsSpace(const QString &text);
    static void addSpaceBetweenParts(QString &text);
    static QString parseYandexSid(const QByteArray &webSiteData);

    static const QMap<Language, QString> s_genericLanguageCodes;

    // Engines have some language codes exceptions
    static const QMap<Language, QString> s_googleLanguageCodes;
    static const QMap<Language, QString> s_yandexLanguageCodes;
    static const QMap<Language, QString> s_bingLanguageCodes;

    static inline QString s_yandexKey; // A key that is parsed from the web version to receive the translation using the API

    // This properties used to store unseful information in states
    static constexpr char s_textProperty[] = "Text";

    // Engines have a limit of characters per translation request.
    // If the query is larger, then it should be splited into several with getSplitIndex() helper function
    static constexpr int s_googleTranslateLimit = 5000;
    static constexpr int s_yandexTranslateLimit = 150;
    static constexpr int s_yandexTranslitLimit = 180;
    static constexpr int s_bingTranslateLimit = 5001;

    QStateMachine *m_stateMachine;
    QNetworkAccessManager *m_networkManager;
    QPointer<QNetworkReply> m_currentReply;

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

    QMap<QString, QVector<QOption>> m_translationOptions;
    QMap<QString, QVector<QExample>> m_examples;

    bool m_sourceTranslitEnabled = true;
    bool m_translationTranslitEnabled = true;
    bool m_sourceTranscriptionEnabled = true;
    bool m_translationOptionsEnabled = true;
    bool m_examplesEnabled = true;

    bool m_onlyDetectLanguage = false;
};

#endif // QONLINETRANSLATOR_H
