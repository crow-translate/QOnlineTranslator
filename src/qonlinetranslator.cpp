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

#include <QEventLoop>
#include <QMediaPlayer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "qonlinetranslator.h"

// Engines have a limit of characters per translation request.
// If the query is larger, then it should be splited into several with getSplitIndex() helper function
constexpr int GOOGLE_TRANSLATE_LIMIT = 5000;
constexpr int GOOGLE_TTS_LIMIT = 200;

constexpr int YANDEX_TRANSLATE_LIMIT = 150;
constexpr int YANDEX_TRANSLIT_LIMIT = 180;
constexpr int YANDEX_TTS_LIMIT = 1400;

QString QOnlineTranslator::m_yandexSid;
bool QOnlineTranslator::m_secondSidRequest = false;
const QStringList QOnlineTranslator::m_languageCodes = { "auto", "af", "sq", "am", "ar", "hy", "az", "eu", "ba", "be", "bn", "bs", "bg", "ca", "ceb", "zh-CN", "zh-TW", "co", "hr", "cs",
                                                         "da", "nl", "en", "eo", "et", "fi", "fr", "fy", "gl", "ka", "de", "el", "gu", "ht", "ha", "haw", "he", "mrj", "hi", "hmn", "hu",
                                                         "is", "ig", "id", "ga", "it", "ja", "jw", "kn", "kk", "km", "ko", "ku", "ky", "lo", "la", "lv", "lt", "lb", "mk", "mg",
                                                         "ms", "ml", "mt", "mi", "mr", "mhr", "mn", "my", "ne", "no", "ny", "pap", "ps", "fa", "pl", "pt", "pa", "ro", "ru", "sm", "gd", "sr",
                                                         "st", "sn", "sd", "si", "sk", "sl", "so", "es", "su", "sw", "sv", "tl", "tg", "ta", "tt", "te", "th", "tr", "udm", "uk", "ur", "uz",
                                                         "vi", "cy", "xh", "yi", "yo", "zu" };

QOnlineTranslator::QOnlineTranslator(QObject *parent) :
    QObject(parent)
{
}

void QOnlineTranslator::translate(const QString &text, Engine engine, Language translationLang, Language sourceLang, Language uiLang)
{
    // Set new data
    m_source = text;
    m_sourceLang = sourceLang;

    if (translationLang == Auto)
        m_translationLang = language(QLocale());
    else
        m_translationLang = translationLang;

    if (uiLang == Auto)
        m_uiLang = language(QLocale());
    else
        m_uiLang = uiLang;

    // Reset old data
    resetData();
    m_error = NoError;

    // Generate API codes
    QString sourceCode = translationLanguageCode(m_sourceLang, engine); // May be autodetected
    const QString translationCode = translationLanguageCode(m_translationLang, engine);
    const QString uiCode = translationLanguageCode(m_uiLang, engine);

   // Check for errors
    if (uiCode.isEmpty() || translationCode.isEmpty() || sourceCode.isEmpty()) {
        m_errorString = tr("Error: One of languages is not supported for this backend.");
        m_error = ParametersError;
        return;
    }

    QString unsendedText;
    switch (engine) {
    case Google:
        // Google has a limit of characters per translation request. If the query is larger, then it should be splited into several
        unsendedText = m_source;
        while (!unsendedText.isEmpty()) {
            const int splitIndex = getSplitIndex(unsendedText, GOOGLE_TRANSLATE_LIMIT); // Split the part by special symbol

            // Do not translate the part if it looks like garbage
            if (splitIndex == -1) {
                m_translation.append(unsendedText.left(GOOGLE_TRANSLATE_LIMIT));
                unsendedText = unsendedText.mid(GOOGLE_TRANSLATE_LIMIT);
                continue;
            }

            const QByteArray reply = getGoogleTranslation(unsendedText.left(splitIndex), translationCode, sourceCode, uiCode);
            if (reply.isEmpty()) {
                resetData();
                return;
            }

            // Convert to JsonArray
            const QJsonDocument jsonResponse = QJsonDocument::fromJson(reply);
            const QJsonArray jsonData = jsonResponse.array();

            // Parse first sentense. If the answer contains more than one sentence, then at the end of the first one there will be a space
            m_translation.append(jsonData.at(0).toArray().at(0).toArray().at(0).toString());
            for (int i = 1; m_translation.endsWith(" ") || m_translation.endsWith("\n") || m_translation.endsWith("\u00a0"); ++i)
                m_translation.append(jsonData.at(0).toArray().at(i).toArray().at(0).toString());

            // Parse transliterations and source language
            m_translationTranslit.append(jsonData.at(0).toArray().last().toArray().at(2).toString());
            m_sourceTranslit.append(jsonData.at(0).toArray().last().toArray().at(3).toString());
            if (m_sourceLang == Auto) {
                // Parse language
                m_sourceLang = language(jsonData.at(2).toString(), engine);
                if (m_sourceLang == NoLanguage) {
                    m_errorString = tr("Error: Unable to parse language from response.");
                    m_error = ParsingError;
                    resetData();
                    return;
                }
            }

            // Remove the parsed part from the next parsing
            unsendedText = unsendedText.mid(splitIndex);

            // Add a space between parts
            if (!unsendedText.isEmpty() && !m_translation.endsWith("\n")) {
                m_translation.append(" ");
                m_translationTranslit.append(" ");
                m_sourceTranslit.append(" ");
            }

            if (text.size() < GOOGLE_TRANSLATE_LIMIT) {
                // Translation options
                foreach (QJsonValue translationOption, jsonData.at(1).toArray()) {
                    m_dictionaryList << QDictionary(translationOption.toArray().at(0).toString());
                    foreach (QJsonValue wordData, translationOption.toArray().at(2).toArray()) {
                        QString word = wordData.toArray().at(0).toString();
                        QString gender = wordData.toArray().at(4).toString();
                        QStringList translations;
                        foreach (auto translationForWord, wordData.toArray().at(1).toArray()) {
                            translations.append(translationForWord.toString());
                        }
                        m_dictionaryList.last().appendWord(word, gender, translations);
                    }
                }

                // Definitions
                foreach (QJsonValue definition, jsonData.at(12).toArray()) {
                    m_definitionsList << QDefinition();
                    m_definitionsList.last().setTypeOfSpeech(definition.toArray().at(0).toString());
                    m_definitionsList.last().setDescription(definition.toArray().at(1).toArray().at(0).toArray().at(0).toString());
                    m_definitionsList.last().setExample(definition.toArray().at(1).toArray().at(0).toArray().at(2).toString());
                }
            }
        }
        return;

    case Yandex:
        // Get translation
        // Yandex has a limit of characters per translation request. If the query is larger, then it should be splited into several.
        unsendedText = m_source;
        while (!unsendedText.isEmpty()) {
            const int splitIndex = getSplitIndex(unsendedText, YANDEX_TRANSLATE_LIMIT); // Split the part by special symbol

            // Do not translate the part if it looks like garbage
            if (splitIndex == -1) {
                m_translation.append(unsendedText.left(YANDEX_TRANSLATE_LIMIT));
                unsendedText = unsendedText.mid(YANDEX_TRANSLATE_LIMIT);
                continue;
            }

            // Get API reply
            const QByteArray reply = getYandexTranslation(unsendedText.left(splitIndex), translationCode, sourceCode);
            if (reply.isEmpty()) {
                resetData();
                return;
            }

            // Parse translation data
            const QJsonDocument jsonResponse = QJsonDocument::fromJson(reply);
            const QJsonObject jsonData = jsonResponse.object();
            m_translation += jsonData.value("text").toArray().at(0).toString();
            if (m_sourceLang == Auto) {
                // Parse language
                sourceCode = jsonData.value("lang").toString();
                sourceCode = sourceCode.left(sourceCode.indexOf("-"));
                m_sourceLang = language(sourceCode, engine);
                if (m_sourceLang == NoLanguage) {
                    m_errorString = tr("Error: Unable to parse language from response.");
                    m_error = ParsingError;
                    resetData();
                    return;
                }
            }

            // Remove the parsed part from the next parsing
            unsendedText = unsendedText.mid(splitIndex);
        }

        // Get source transliteration
        if (isSupportYandexTranslit(m_sourceLang)) {
            // Yandex has a limit of characters per transliteration request. If the query is larger, then it should be splited into several.
            unsendedText = m_source;
            while (!unsendedText.isEmpty()) {
                const int splitIndex = getSplitIndex(unsendedText, YANDEX_TRANSLIT_LIMIT); // Split the part by special symbol

                // Do not translate the part if it looks like garbage
                if (splitIndex == -1) {
                    m_sourceTranslit.append(unsendedText.left(YANDEX_TRANSLIT_LIMIT));
                    unsendedText = unsendedText.mid(YANDEX_TRANSLIT_LIMIT);
                    continue;
                }

                // Get API reply
                const QByteArray reply = getYandexTranslit(unsendedText.left(splitIndex), sourceCode);
                if (reply.isEmpty()) {
                    resetData();
                    return;
                }

                m_sourceTranslit += reply.mid(1).chopped(1);

                // Remove the parsed part from the next parsing
                unsendedText = unsendedText.mid(splitIndex);
            }
        }

        // Get translation transliteration
        if (isSupportYandexTranslit(m_translationLang)) {
            // Yandex has a limit of characters per transliteration request. If the query is larger, then it should be splited into several.
            unsendedText = m_translation;
            while (!unsendedText.isEmpty()) {
                const int splitIndex = getSplitIndex(unsendedText, YANDEX_TRANSLIT_LIMIT); // Split the part by special symbol

                // Do not translate the part if it looks like garbage
                if (splitIndex == -1) {
                    m_translationTranslit.append(unsendedText.left(YANDEX_TRANSLIT_LIMIT));
                    unsendedText = unsendedText.mid(YANDEX_TRANSLIT_LIMIT);
                    continue;
                }

                // Get API reply
                const QByteArray reply = getYandexTranslit(unsendedText.left(splitIndex), translationCode);
                if (reply.isEmpty()) {
                    resetData();
                    return;
                }

                m_translationTranslit += reply.mid(1).chopped(1);

                // Remove the parsed part from the next parsing
                unsendedText = unsendedText.mid(splitIndex);
            }
        }

        // Request dictionary data if only one word is translated.
        if (!m_source.contains(" ")) {
            const QByteArray reply = getYandexDictionary(m_source, translationCode, sourceCode, uiCode);
            if (reply.isEmpty()) {
                resetData();
                return;
            }

            const QJsonDocument jsonResponse = QJsonDocument::fromJson(reply);
            const QJsonValue dictionary = jsonResponse.object().value(sourceCode + "-" + translationCode);
            foreach (QJsonValue dictionary, dictionary.toObject().value("regular").toArray()) {
                m_dictionaryList << QDictionary(dictionary.toObject().value("pos").toObject().value("text").toString());
                foreach (QJsonValue wordData, dictionary.toObject().value("tr").toArray()) {
                    QString word = wordData.toObject().value("text").toString();
                    QString gender = wordData.toObject().value("gen").toObject().value("text").toString();
                    QStringList translations;
                    foreach (QJsonValue translationForWord, wordData.toObject().value("mean").toArray()) {
                        translations.append(translationForWord.toObject().value("text").toString());
                    }
                    m_dictionaryList.last().appendWord(word, gender, translations);
                }
            }
        }
        return;
    }
}

QList<QMediaContent> QOnlineTranslator::media(const QString &text, Engine engine, Language lang, Speaker speaker, Emotion emotion)
{
    m_error = NoError;
    QList<QMediaContent> mediaList;
    QString langCode;
    QString unparsedText = text;

    // Detect language if required
    if (lang != Auto) {
        langCode = ttsLanguageCode(lang, engine);
        if (langCode.isEmpty()) {
            m_errorString = tr("Error: Unsupported language for tts.");
            m_error = ParametersError;
            return mediaList;
        }
    } else {
        switch (engine) {
        case Google: {
            // Get API reply
            const QByteArray reply = getGoogleTranslation(text.left(getSplitIndex(text, GOOGLE_TRANSLATE_LIMIT)), "en");
            if (reply.isEmpty())
                return mediaList;

            // Parse language
            langCode = reply.chopped(4);
            langCode = langCode.mid(langCode.lastIndexOf("\"") + 1);
            break;
        }
        case Yandex: {
            // Get API reply
            const QByteArray reply = getYandexTranslation(text.left(getSplitIndex(text, YANDEX_TRANSLATE_LIMIT)), "en");
            if (reply.isEmpty())
                return mediaList;

            // Parse language
            const QJsonDocument jsonResponse = QJsonDocument::fromJson(reply);
            const QJsonObject jsonData = jsonResponse.object();
            langCode = jsonData.value("lang").toString();
            langCode = langCode.left(langCode.indexOf("-"));
            
            // Convert to tts code
            const Language detectedLang = language(langCode, Yandex);
            langCode = ttsLanguageCode(detectedLang, Yandex);
            if (langCode.isEmpty()) {
                m_errorString = tr("Error: Unable to parse language");
                m_error = ParametersError;
                return mediaList;
            }
        }
        }
    }

    // Get speech
    switch (engine) {
    case Google:
        // Google has a limit of characters per tts request. If the query is larger, then it should be splited into several
        while (!unparsedText.isEmpty()) {
            const int splitIndex = getSplitIndex(unparsedText, GOOGLE_TTS_LIMIT); // Split the part by special symbol

            // Generate URL API for add it to the playlist
            QUrl apiUrl("http://translate.googleapis.com/translate_tts");
#if defined(Q_OS_LINUX)
            apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + langCode +"&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)));
#elif defined(Q_OS_WIN)
            apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + languageCode +"&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)), QUrl::DecodedMode);
#endif
            mediaList.append(apiUrl);

            // Remove the said part from the next saying
            unparsedText = unparsedText.mid(splitIndex);
        }
        break;
    case Yandex:
        const QString speakerCode = this->speakerCode(speaker);
        const QString emotionCode = this->emotionCode(emotion);

        // Yandex has a limit of characters per tts request. If the query is larger, then it should be splited into several
        while (!unparsedText.isEmpty()) {
            const int splitIndex = getSplitIndex(unparsedText, YANDEX_TTS_LIMIT); // Split the part by special symbol

            // Generate URL API for add it to the playlist
            QUrl apiUrl("https://tts.voicetech.yandex.net/tts");
#if defined(Q_OS_LINUX)
            apiUrl.setQuery("text=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)) +
                            "&lang=" + langCode +
                            "&speaker=" + speakerCode +
                            "&emotion=" + emotionCode +
                            "&format=mp3");
#elif defined(Q_OS_WIN)
            apiUrl.setQuery("text=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)) +
                            "&lang=" + languageCode +
                            "&speaker=" + speakerCode +
                            "&emotion=" + emotionCode +
                            "&format=mp3", QUrl::DecodedMode);
#endif
            mediaList.append(apiUrl);

            // Remove the said part from the next saying
            unparsedText = unparsedText.mid(splitIndex);
        }
        break;
    }

    return mediaList;
}

QList<QMediaContent> QOnlineTranslator::sourceMedia(Engine engine, Speaker speaker, Emotion emotion)
{
    return media(m_source, engine, m_sourceLang, speaker, emotion);
}

QList<QMediaContent> QOnlineTranslator::translationMedia(Engine engine, Speaker speaker, Emotion emotion)
{
    return media(m_translation, engine, m_translationLang, speaker, emotion);
}

QString QOnlineTranslator::source() const
{
    return m_source;
}

QString QOnlineTranslator::sourceTranslit() const
{
    return m_sourceTranslit;
}

QString QOnlineTranslator::sourceLanguageString() const
{
    return languageString(m_sourceLang);
}

QOnlineTranslator::Language QOnlineTranslator::sourceLanguage() const
{
    return m_sourceLang;
}

QString QOnlineTranslator::translation() const
{
    return m_translation;
}

QString QOnlineTranslator::translationTranslit() const
{
    return m_translationTranslit;
}

QString QOnlineTranslator::translationLanguageString() const
{
    return languageString(m_translationLang);
}

QOnlineTranslator::Language QOnlineTranslator::translationLanguage() const
{
    return m_translationLang;
}

QList<QDictionary> QOnlineTranslator::dictionaryList() const
{
    return m_dictionaryList;
}

QList<QDefinition> QOnlineTranslator::definitionsList() const
{
    return m_definitionsList;
}

QString QOnlineTranslator::errorString() const
{
    return m_errorString;
}

QOnlineTranslator::TranslationError QOnlineTranslator::error() const
{
    return m_error;
}

QString QOnlineTranslator::languageString(QOnlineTranslator::Language lang)
{
    switch (lang) {
    case NoLanguage:
        return "";
    case Auto:
        return tr("Automatically detect");
    case Afrikaans:
        return tr("Afrikaans");
    case Albanian:
        return tr("Albanian");
    case Amharic:
        return tr("Amharic");
    case Arabic:
        return tr("Arabic");
    case Armenian:
        return tr("Armenian");
    case Azeerbaijani:
        return tr("Azeerbaijani");
    case Basque:
        return tr("Basque");
    case Bashkir:
        return tr("Bashkir");
    case Belarusian:
        return tr("Belarusian");
    case Bengali:
        return tr("Bengali");
    case Bosnian:
        return tr("Bosnian");
    case Bulgarian:
        return tr("Bulgarian");
    case Catalan:
        return tr("Catalan");
    case Cebuano:
        return tr("Cebuano");
    case SimplifiedChinese:
        return tr("Chinese (Simplified)");
    case TraditionalChinese:
        return tr("Chinese (Traditional)");
    case Corsican:
        return tr("Corsican");
    case Croatian:
        return tr("Croatian");
    case Czech:
        return tr("Czech");
    case Danish:
        return tr("Danish");
    case Dutch:
        return tr("Dutch");
    case English:
        return tr("English");
    case Esperanto:
        return tr("Esperanto");
    case Estonian:
        return tr("Estonian");
    case Finnish:
        return tr("Finnish");
    case French:
        return tr("French");
    case Frisian:
        return tr("Frisian");
    case Galician:
        return tr("Galician");
    case Georgian:
        return tr("Georgian");
    case German:
        return tr("German");
    case Greek:
        return tr("Greek");
    case Gujarati:
        return tr("Gujarati");
    case HaitianCreole:
        return tr("Haitian Creole");
    case Hausa:
        return tr("Hausa");
    case Hawaiian:
        return tr("Hawaiian");
    case Hebrew:
        return tr("Hebrew");
    case HillMari:
        return tr("Hill Mari");
    case Hindi:
        return tr("Hindi");
    case Hmong:
        return tr("Hmong");
    case Hungarian:
        return tr("Hungarian");
    case Icelandic:
        return tr("Icelandic");
    case Igbo:
        return tr("Igbo");
    case Indonesian:
        return tr("Indonesian");
    case Irish:
        return tr("Irish");
    case Italian:
        return tr("Italian");
    case Japanese:
        return tr("Japanese");
    case Javanese:
        return tr("Javanese");
    case Kannada:
        return tr("Kannada");
    case Kazakh:
        return tr("Kazakh");
    case Khmer:
        return tr("Khmer");
    case Korean:
        return tr("Korean");
    case Kurdish:
        return tr("Kurdish");
    case Kyrgyz:
        return tr("Kyrgyz");
    case Lao:
        return tr("Lao");
    case Latin:
        return tr("Latin");
    case Latvian:
        return tr("Latvian");
    case Lithuanian:
        return tr("Lithuanian");
    case Luxembourgish:
        return tr("Luxembourgish");
    case Macedonian:
        return tr("Macedonian");
    case Malagasy:
        return tr("Malagasy");
    case Malay:
        return tr("Malay");
    case Malayalam:
        return tr("Malayalam");
    case Maltese:
        return tr("Maltese");
    case Maori:
        return tr("Maori");
    case Marathi:
        return tr("Marathi");
    case Mari:
        return tr("Mari");
    case Mongolian:
        return tr("Mongolian");
    case Myanmar:
        return tr("Myanmar");
    case Nepali:
        return tr("Nepali");
    case Norwegian:
        return tr("Norwegian");
    case Chichewa:
        return tr("Chichewa");
    case Papiamento:
        return tr("Papiamento");
    case Pashto:
        return tr("Pashto");
    case Persian:
        return tr("Persian");
    case Polish:
        return tr("Polish");
    case Portuguese:
        return tr("Portuguese");
    case Punjabi:
        return tr("Punjabi");
    case Romanian:
        return tr("Romanian");
    case Russian:
        return tr("Russian");
    case Samoan:
        return tr("Samoan");
    case ScotsGaelic:
        return tr("Scots Gaelic");
    case Serbian:
        return tr("Serbian");
    case Sesotho:
        return tr("Sesotho");
    case Shona:
        return tr("Shona");
    case Sindhi:
        return tr("Sindhi");
    case Sinhala:
        return tr("Sinhala");
    case Slovak:
        return tr("Slovak");
    case Slovenian:
        return tr("Slovenian");
    case Somali:
        return tr("Somali");
    case Spanish:
        return tr("Spanish");
    case Sundanese:
        return tr("Sundanese");
    case Swahili:
        return tr("Swahili");
    case Swedish:
        return tr("Swedish");
    case Tagalog:
        return tr("Tagalog");
    case Tajik:
        return tr("Tajik");
    case Tamil:
        return tr("Tamil");
    case Tatar:
        return tr("Tatar");
    case Telugu:
        return tr("Telugu");
    case Thai:
        return tr("Thai");
    case Turkish:
        return tr("Turkish");
    case Udmurt:
        return tr("Udmurt");
    case Ukrainian:
        return tr("Ukrainian");
    case Urdu:
        return tr("Urdu");
    case Uzbek:
        return tr("Uzbek");
    case Vietnamese:
        return tr("Vietnamese");
    case Welsh:
        return tr("Welsh");
    case Xhosa:
        return tr("Xhosa");
    case Yiddish:
        return tr("Yiddish");
    case Yoruba:
        return tr("Yoruba");
    case Zulu:
        return tr("Zulu");
    }

    return tr("Unknown");
}

QString QOnlineTranslator::languageCode(QOnlineTranslator::Language lang)
{
    if (lang == NoLanguage)
        return "";
    else
        return m_languageCodes.at(lang);
}

QOnlineTranslator::Language QOnlineTranslator::language(const QLocale &locale)
{
    Language language;

    switch (locale.language()) {
    case QLocale::Afrikaans:
        language = Afrikaans;
        break;
    case QLocale::Albanian:
        language = Albanian;
        break;
    case QLocale::Amharic:
        language = Amharic;
        break;
    case QLocale::Arabic:
        language = Arabic;
        break;
    case QLocale::Armenian:
        language = Armenian;
        break;
    case QLocale::Azerbaijani:
        language = Azeerbaijani;
        break;
    case QLocale::Basque:
        language = Basque;
        break;
    case QLocale::Belarusian:
        language = Belarusian;
        break;
    case QLocale::Bengali:
        language = Bengali;
        break;
    case QLocale::Bosnian:
        language = Bosnian;
        break;
    case QLocale::Bulgarian:
        language = Bulgarian;
        break;
    case QLocale::Catalan:
        language = Catalan;
        break;
    case QLocale::Chinese:
        language = SimplifiedChinese;
        break;
    case QLocale::LiteraryChinese:
        language = TraditionalChinese;
        break;
    case QLocale::Corsican:
        language = Corsican;
        break;
    case QLocale::Croatian:
        language = Croatian;
        break;
    case QLocale::Czech:
        language = Czech;
        break;
    case QLocale::Danish:
        language = Danish;
        break;
    case QLocale::Dutch:
        language = Dutch;
        break;
    case QLocale::Esperanto:
        language = Esperanto;
        break;
    case QLocale::Estonian:
        language = Estonian;
        break;
    case QLocale::Finnish:
        language = Finnish;
        break;
    case QLocale::French:
        language = French;
        break;
    case QLocale::Frisian:
        language = Frisian;
        break;
    case QLocale::Galician:
        language = Galician;
        break;
    case QLocale::Georgian:
        language = Georgian;
        break;
    case QLocale::German:
        language = German;
        break;
    case QLocale::Greek:
        language = Greek;
        break;
    case QLocale::Gujarati:
        language = Gujarati;
        break;
    case QLocale::Haitian:
        language = HaitianCreole;
        break;
    case QLocale::Hausa:
        language = Hausa;
        break;
    case QLocale::Hawaiian:
        language = Hawaiian;
        break;
    case QLocale::Hebrew:
        language = Hebrew;
        break;
    case QLocale::Hindi:
        language = Hindi;
        break;
    case QLocale::HmongNjua:
        language = Hmong;
        break;
    case QLocale::Hungarian:
        language = Hungarian;
        break;
    case QLocale::Icelandic:
        language = Icelandic;
        break;
    case QLocale::Igbo:
        language = Igbo;
        break;
    case QLocale::Indonesian:
        language = Indonesian;
        break;
    case QLocale::Irish:
        language = Irish;
        break;
    case QLocale::Italian:
        language = Italian;
        break;
    case QLocale::Japanese:
        language = Japanese;
        break;
    case QLocale::Javanese:
        language = Javanese;
        break;
    case QLocale::Kannada:
        language = Kannada;
        break;
    case QLocale::Kazakh:
        language = Kazakh;
        break;
    case QLocale::Khmer:
        language = Khmer;
        break;
    case QLocale::Korean:
        language = Korean;
        break;
    case QLocale::Kurdish:
        language = Kurdish;
        break;
    case QLocale::Lao:
        language = Lao;
        break;
    case QLocale::Latin:
        language = Latin;
        break;
    case QLocale::Latvian:
        language = Latvian;
        break;
    case QLocale::Lithuanian:
        language = Lithuanian;
        break;
    case QLocale::Luxembourgish:
        language = Luxembourgish;
        break;
    case QLocale::Macedonian:
        language = Macedonian;
        break;
    case QLocale::Malagasy:
        language = Malagasy;
        break;
    case QLocale::Malay:
        language = Malay;
        break;
    case QLocale::Malayalam:
        language = Malayalam;
        break;
    case QLocale::Maltese:
        language = Maltese;
        break;
    case QLocale::Maori:
        language = Maori;
        break;
    case QLocale::Marathi:
        language = Marathi;
        break;
    case QLocale::Mongolian:
        language = Mongolian;
        break;
    case QLocale::Nepali:
        language = Nepali;
        break;
    case QLocale::Norwegian:
        language = Norwegian;
        break;
    case QLocale::Pashto:
        language = Pashto;
        break;
    case QLocale::Persian:
        language = Persian;
        break;
    case QLocale::Polish:
        language = Polish;
        break;
    case QLocale::Portuguese:
        language = Portuguese;
        break;
    case QLocale::Punjabi:
        language = Punjabi;
        break;
    case QLocale::Romanian:
        language = Romanian;
        break;
    case QLocale::Russian:
        language = Russian;
        break;
    case QLocale::Samoan:
        language = Samoan;
        break;
    case QLocale::Gaelic:
        language = ScotsGaelic;
        break;
    case QLocale::Serbian:
        language = Serbian;
        break;
    case QLocale::Shona:
        language = Shona;
        break;
    case QLocale::Sindhi:
        language = Sindhi;
        break;
    case QLocale::Sinhala:
        language = Sinhala;
        break;
    case QLocale::Slovak:
        language = Slovak;
        break;
    case QLocale::Slovenian:
        language = Slovenian;
        break;
    case QLocale::Somali:
        language = Somali;
        break;
    case QLocale::Spanish:
        language = Spanish;
        break;
    case QLocale::Sundanese:
        language = Sundanese;
        break;
    case QLocale::Swahili:
        language = Swahili;
        break;
    case QLocale::Swedish:
        language = Swedish;
        break;
    case QLocale::Filipino:
        language = Tagalog;
        break;
    case QLocale::Tajik:
        language = Tajik;
        break;
    case QLocale::Tamil:
        language = Tamil;
        break;
    case QLocale::Telugu:
        language = Telugu;
        break;
    case QLocale::Thai:
        language = Thai;
        break;
    case QLocale::Turkish:
        language = Turkish;
        break;
    case QLocale::Ukrainian:
        language = Ukrainian;
        break;
    case QLocale::Urdu:
        language = Urdu;
        break;
    case QLocale::Uzbek:
        language = Uzbek;
        break;
    case QLocale::Vietnamese:
        language = Vietnamese;
        break;
    case QLocale::Welsh:
        language = Welsh;
        break;
    case QLocale::Xhosa:
        language = Xhosa;
        break;
    case QLocale::Yiddish:
        language = Yiddish;
        break;
    case QLocale::Yoruba:
        language = Yoruba;
        break;
    case QLocale::Zulu:
        language = Zulu;
        break;
    default:
        language = English;
        break;
    }

    return language;
}

QOnlineTranslator::Language QOnlineTranslator::language(const QString &langCode)
{
    return static_cast<Language>(m_languageCodes.indexOf(langCode));
}

void QOnlineTranslator::resetData()
{
    m_translation.clear();
    m_translationTranslit.clear();
    m_sourceTranslit.clear();
    m_dictionaryList.clear();
    m_definitionsList.clear();
}

bool QOnlineTranslator::isSupportYandexTranslit(QOnlineTranslator::Language language)
{
    if (language == Amharic
            || language == Armenian
            || language == Bengali
            || language == SimplifiedChinese
            || language == Georgian
            || language == Greek
            || language == Gujarati
            || language == Hebrew
            || language == Hindi
            || language == Japanese
            || language == Kannada
            || language == Korean
            || language == Malayalam
            || language == Marathi
            || language == Nepali
            || language == Punjabi
            || language == Russian
            || language == Sinhala
            || language == Tamil
            || language == Telugu
            || language == Thai
            || language == Yiddish) {
        return true;
    } else {
        return false;
    }
}

template<typename... Query>
QByteArray QOnlineTranslator::get(const QString &urlString, const Query&... queryStrings)
{
    // Generate API url
    QUrl url(urlString);
    url.setQuery((queryStrings + ...));

    // Send request and wait for the response
    QNetworkReply *reply = m_network.get(QNetworkRequest(url));
    QEventLoop waitForResponse;
    connect(reply, &QNetworkReply::finished, &waitForResponse, &QEventLoop::quit);
    waitForResponse.exec();

    if (reply->error() == QNetworkReply::NoError) {
        const QByteArray data = reply->readAll();
        delete reply;
        return data;
    } else {
        m_errorString = reply->errorString();
        m_error = NetworkError;
        delete reply;
        return "";
    }
}

QByteArray QOnlineTranslator::getGoogleTranslation(const QString &text, const QString &translationCode, const QString &sourceCode, const QString &uiCode)
{
    const QByteArray reply = get("https://translate.googleapis.com/translate_a/single",
                                 "client=gtx&ie=UTF-8&oe=UTF-8&dt=bd&dt=ex&dt=ld&dt=md&dt=rw&dt=rm&dt=ss&dt=t&dt=at&dt=qc&sl=",
                                 sourceCode,
                                 "&tl=",
                                 translationCode,
                                 "&hl=",
                                 uiCode,
                                 "&q=",
                                 QUrl::toPercentEncoding(text));

    // Check availability of service
    if (reply.startsWith("<")) {
        m_errorString = tr("Error: Backend systems have detected unusual traffic from your computer network. Please try your request again later.");
        m_error = ServiceError;
        return "";
    } else {
        return reply;
    }
}

QByteArray QOnlineTranslator::getYandexTranslation(const QString &text, const QString &translationCode, const QString &sourceCode)
{
    // Generate session ID to access API (Required for Yandex)
    if (m_yandexSid.isEmpty()) {
        // Download web-version
        const QByteArray webSiteData = get("https://translate.yandex.com/", "");
        if (webSiteData.isEmpty())
            return "";

        if (webSiteData.contains("<title>Oops!</title>")) {
            m_errorString = tr("Error: Backend systems have detected unusual traffic from your computer network. Please try your request again later.");
            m_error = ServiceError;
            return "";
        }

        // Parse SID
        const QString sid = webSiteData.mid(webSiteData.indexOf("SID: '") + 6, 26);

        // Yandex show reversed parts of session ID, need to decode
        QStringList sidParts = sid.split(".");
        for (short i = 0; i < sidParts.size(); ++i)
            std::reverse(sidParts[i].begin(), sidParts[i].end());

        m_yandexSid = sidParts.join(".");
        if (m_yandexSid.isEmpty()) {
            m_errorString = tr("Error: Unable to parse Yandex SID.");
            m_error = ParsingError;
            return "";
        }
    }

    // Generate API url
    QUrl url("https://translate.yandex.net/api/v1/tr.json/translate");
    url.setQuery("id="
                 + m_yandexSid
                 + "-0-0&srv=tr-text&text="
                 + QUrl::toPercentEncoding(text)
                 + "&lang="
                 + (sourceCode == "auto" ? translationCode : sourceCode + "-" + translationCode));

    // Send request and wait for the response
    QNetworkReply *reply = m_network.get(QNetworkRequest(url));
    QEventLoop waitForResponse;
    connect(reply, &QNetworkReply::finished, &waitForResponse, &QEventLoop::quit);
    waitForResponse.exec();

    // Check for errors
    if (reply->error() != QNetworkReply::NoError) {
        if (reply->error() < 201) {
            // Network errors
            m_errorString = reply->errorString();
            m_error = NetworkError;
            delete reply;
            return "";
        }
        if (reply->error() == QNetworkReply::ContentAccessDenied && !m_secondSidRequest) {
            // Try to generate a new session ID second time, if the previous is invalid
            m_yandexSid.clear();
            m_secondSidRequest = true; // Do not generate the session ID third time if the second one was generated incorrectly
            delete reply;
            return getYandexTranslation(text, translationCode, sourceCode);
        } else {
            // Parse data to get request error type
            const QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
            m_errorString = jsonResponse.object().value("message").toString();
            m_error = ServiceError;
            delete reply;
            return "";
        }
    } else {
        m_secondSidRequest = false;
    }

    const QByteArray data = reply->readAll();
    delete reply;
    return data;
}

QByteArray QOnlineTranslator::getYandexTranslit(const QString &text, const QString &langCode)
{
    return get("https://translate.yandex.net/translit/translit",
               "text=",
               QUrl::toPercentEncoding(text),
               "&lang=",
               langCode);
}

QByteArray QOnlineTranslator::getYandexDictionary(const QString &text, const QString &translationCode, const QString &sourceCode, const QString &uiCode)
{
    return get("http://dictionary.yandex.net/dicservice.json/lookupMultiple",
               "text=",
               QUrl::toPercentEncoding(text),
               "&ui=",
               uiCode,
               "&dict=",
               sourceCode,
               "-",
               translationCode);
}

// Get split index of the text according to the limit
int QOnlineTranslator::getSplitIndex(const QString &untranslatedText, int limit)
{
    if (untranslatedText.size() < limit)
        return limit;

    int splitIndex = untranslatedText.lastIndexOf(". ", limit - 1);
    if (splitIndex != -1)
        return splitIndex + 1;

    splitIndex = untranslatedText.lastIndexOf(" ", limit - 1);
    if (splitIndex != -1)
        return splitIndex + 1;

    splitIndex = untranslatedText.lastIndexOf("\n", limit - 1);
    if (splitIndex != -1)
        return splitIndex + 1;

    // Non-breaking gap
    splitIndex = untranslatedText.lastIndexOf("\u00a0", limit - 1);
    if (splitIndex != -1)
        return splitIndex + 1;

    // If the text has not passed any check and is most likely garbage
    return limit;
}

QOnlineTranslator::Language QOnlineTranslator::language(const QString &langCode, Engine engine)
{
    // Google execptions
    if (engine == Google) {
        // Unsupported languages
        if (langCode == "ba"
                || langCode == "mrj"
                || langCode == "mhr"
                || langCode == "ny"
                || langCode == "tt"
                || langCode == "udm") {
            return NoLanguage;
        }
    }

    // Yandex execptions
    if (engine == Yandex) {
        // Yandex use another codes for this languages
        if (langCode == "zn")
            return SimplifiedChinese;
        if (langCode == "jv")
            return Javanese;

        if (langCode == "ku")
            return NoLanguage;
    }

    // General case
    return static_cast<Language>(m_languageCodes.indexOf(langCode));
}

QString QOnlineTranslator::translationLanguageCode(QOnlineTranslator::Language language, Engine engine)
{
    QString languageCode;

    if (language == NoLanguage) {
        return "";
    }

    // Engines execptions
    switch (engine) {
    case Google:
        if (language == Bashkir
                || language == HillMari
                || language == Mari
                || language == Papiamento
                || language == Tatar
                || language == Udmurt) {
            return "";
        }
        break;
    case Yandex:
        if (language == SimplifiedChinese)
            return "zn";
        if (language == Javanese)
            return  "jv";
        if (language == Kurdish)
            return "";
        break;
    }

    // General case
    return m_languageCodes.at(language);
}

QString QOnlineTranslator::ttsLanguageCode(QOnlineTranslator::Language language, QOnlineTranslator::Engine engine)
{
    if (engine == Yandex) {
        switch (language) {
        case NoLanguage:
            return "";
        case Russian:
            return "ru_RU";
        case Tatar:
            return "tr_TR";
        case English:
            return "en_GB";
        default:
            return "";
        }
    } else {
        return translationLanguageCode(language, engine); // Google use the same codes for tts
    }
}

QString QOnlineTranslator::speakerCode(QOnlineTranslator::Speaker speaker)
{
    QString speakerString;
    switch (speaker) {
    case Zahar:
        speakerString = "zahar";
        break;
    case Ermil:
        speakerString = "ermil";
        break;
    case Jane:
        speakerString = "jane";
        break;
    case Oksana:
        speakerString = "oksana";
        break;
    case Alyss:
        speakerString = "alyss";
        break;
    case Omazh:
        speakerString = "omazh";
        break;
    }

    return speakerString;
}

QString QOnlineTranslator::emotionCode(QOnlineTranslator::Emotion emotion)
{
    QString emotionString;
    switch (emotion) {
    case Good:
        emotionString = "good";
        break;
    case Evil:
        emotionString = "evil";
        break;
    case Neutral:
        emotionString = "neutral";
        break;
    }

    return emotionString;
}
