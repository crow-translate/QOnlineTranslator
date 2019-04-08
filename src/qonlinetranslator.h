/*
 *  Copyright © 2018-2019 Hennadii Chernyshchyk <genaloner@gmail.com>
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

#include "qoption.h"
#include "qexample.h"

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

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

    QString source() const;
    QString sourceTranslit() const;
    QString sourceTranscription() const;
    QString sourceLanguageString() const;
    Language sourceLanguage() const;

    QString translation() const;
    QString translationTranslit() const;
    QString translationLanguageString() const;
    Language translationLanguage() const;

    QList<QOption> translationOptions() const;
    QList<QExample> examples() const;

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

    static QString languageString(Language lang);
    static QString languageCode(Language lang);
    static Language language(const QLocale &locale);
    static Language language(const QString &langCode);
    static bool isSupportTranslation(Engine engine, Language lang);

private:
    friend class QOnlineTts;

    // Generate Codes for API
    static QString translationLanguageCode(Engine engine, Language lang);

    // Get API reply as JSON
    QByteArray getGoogleTranslation(const QString &text, const QString &translationCode, const QString &sourceCode = "auto", const QString &uiCode = "en");
    QByteArray getYandexTranslation(const QString &text, const QString &translationCode, const QString &sourceCode = "auto");
    QByteArray getYandexTranslit(const QString &text, const QString &langCode);
    QByteArray getYandexDictionary(const QString &text, const QString &translationCode, const QString &sourceCode, const QString &uiCode);
    QByteArray getBingTextLanguage(const QString &text);
    QByteArray getBingTranslation(const QString &text, const QString &translationCode, const QString &sourceCode = "auto");
    QByteArray getBingTranslit(const QString &text, const QString &langCode);
    QByteArray getBingDictionary(const QString &text, const QString &translationCode, const QString &sourceCode);

    // Network requests
    QNetworkReply *getReply(const QUrl &url);
    QNetworkReply *postReply(const QUrl &url, const QByteArray &postData);

    // Check for service support
    static bool isSupportTranslit(Engine engine, Language lang);
    static bool isSupportDictionary(Engine engine, Language sourceLang, Language translationLang);

    // Other
    static Language language(Engine engine, const QString &langCode);
    static int getSplitIndex(const QString &untranslatedText, int limit);
    void resetData(TranslationError error = NoError, const QString &errorString = QString());

    QNetworkAccessManager *m_networkManager;
    QNetworkReply *m_currentReply = nullptr;

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

    QList<QOption> m_translationOptions;
    QList<QExample> m_examples;

    bool m_sourceTranslitEnabled = true;
    bool m_translationTranslitEnabled = true;
    bool m_sourceTranscriptionEnabled = true;
    bool m_translationOptionsEnabled = true;
    bool m_examplesEnabled = true;

    static const QStringList m_languageCodes;
    static QString m_yandexKey;
    static bool m_secondYandexKeyRequest;
};

#endif // QONLINETRANSLATOR_H
