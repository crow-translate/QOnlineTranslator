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

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QMediaPlayer>
#include <QJsonDocument>
#include <QJsonArray>

#if defined(Q_OS_WIN)
#include <QBuffer>
#endif

#include "qonlinetranslator.h"

const QStringList QOnlineTranslator::LANGUAGE_NAMES = { QT_TR_NOOP("Automatically detect"), QT_TR_NOOP("Afrikaans"), QT_TR_NOOP("Amharic"), QT_TR_NOOP("Arabic"),
                                                        QT_TR_NOOP("Azerbaijani"), QT_TR_NOOP("Belarusian"), QT_TR_NOOP("Bulgarian"), QT_TR_NOOP("Bengali"),
                                                        QT_TR_NOOP("Bosnian"), QT_TR_NOOP("Catalan"), QT_TR_NOOP("Cebuano"), QT_TR_NOOP("Corsican"),
                                                        QT_TR_NOOP("Czech"), QT_TR_NOOP("Welsh"), QT_TR_NOOP("Danish"), QT_TR_NOOP("German"),
                                                        QT_TR_NOOP("Greek"), QT_TR_NOOP("English"), QT_TR_NOOP("Esperanto"), QT_TR_NOOP("Spanish"),
                                                        QT_TR_NOOP("Estonian"), QT_TR_NOOP("Basque"), QT_TR_NOOP("Persian"), QT_TR_NOOP("Finnish"),
                                                        QT_TR_NOOP("Fijian"), QT_TR_NOOP("French"), QT_TR_NOOP("Frisian"), QT_TR_NOOP("Irish"),
                                                        QT_TR_NOOP("Scots Gaelic"), QT_TR_NOOP("Galician"), QT_TR_NOOP("Gujarati"), QT_TR_NOOP("Hausa"),
                                                        QT_TR_NOOP("Hawaiian"), QT_TR_NOOP("Hebrew"), QT_TR_NOOP("Hindi"), QT_TR_NOOP("Hmong"),
                                                        QT_TR_NOOP("Croatian"), QT_TR_NOOP("Haitian Creole"), QT_TR_NOOP("Hungarian"), QT_TR_NOOP("Armenian"),
                                                        QT_TR_NOOP("Indonesian"), QT_TR_NOOP("Igbo"), QT_TR_NOOP("Icelandic"), QT_TR_NOOP("Italian"),
                                                        QT_TR_NOOP("Japanese"), QT_TR_NOOP("Javanese"), QT_TR_NOOP("Georgian"), QT_TR_NOOP("Kazakh"),
                                                        QT_TR_NOOP("Khmer"), QT_TR_NOOP("Kannada"), QT_TR_NOOP("Korean"), QT_TR_NOOP("Kurdish"),
                                                        QT_TR_NOOP("Kyrgyz"), QT_TR_NOOP("Latin"), QT_TR_NOOP("Luxembourgish"), QT_TR_NOOP("Lao"),
                                                        QT_TR_NOOP("Lithuanian"), QT_TR_NOOP("Latvian"), QT_TR_NOOP("Malagasy"), QT_TR_NOOP("Maori"),
                                                        QT_TR_NOOP("Macedonian"), QT_TR_NOOP("Malayalam"), QT_TR_NOOP("Mongolian"), QT_TR_NOOP("Marathi"),
                                                        QT_TR_NOOP("Malay"), QT_TR_NOOP("Maltese"), QT_TR_NOOP("Hmong Daw"), QT_TR_NOOP("Myanmar"),
                                                        QT_TR_NOOP("Nepali"), QT_TR_NOOP("Dutch"), QT_TR_NOOP("Norwegian"), QT_TR_NOOP("Chichewa"),
                                                        QT_TR_NOOP("Querétaro Otomi"), QT_TR_NOOP("Punjabi"), QT_TR_NOOP("Polish"), QT_TR_NOOP("Pashto"),
                                                        QT_TR_NOOP("Portuguese"), QT_TR_NOOP("Romanian"), QT_TR_NOOP("Russian"), QT_TR_NOOP("Sindhi"),
                                                        QT_TR_NOOP("Sinhala"), QT_TR_NOOP("Slovak"), QT_TR_NOOP("Slovenian"), QT_TR_NOOP("Samoan"),
                                                        QT_TR_NOOP("Shona"), QT_TR_NOOP("Somali"), QT_TR_NOOP("Albanian"), QT_TR_NOOP("Serbian (Cyrillic)"),
                                                        QT_TR_NOOP("Serbian (Latin)"), QT_TR_NOOP("Sesotho"), QT_TR_NOOP("Sundanese"), QT_TR_NOOP("Swedish"),
                                                        QT_TR_NOOP("Swahili"), QT_TR_NOOP("Tamil"), QT_TR_NOOP("Telugu"), QT_TR_NOOP("Tajik"),
                                                        QT_TR_NOOP("Thai"), QT_TR_NOOP("Filipino"), QT_TR_NOOP("Klingon"), QT_TR_NOOP("Klingon (pIqaD)"),
                                                        QT_TR_NOOP("Tongan"), QT_TR_NOOP("Turkish"), QT_TR_NOOP("Tatar"), QT_TR_NOOP("Tahitian"),
                                                        QT_TR_NOOP("Udmurt"), QT_TR_NOOP("Ukrainian"), QT_TR_NOOP("Urdu"), QT_TR_NOOP("Uzbek"),
                                                        QT_TR_NOOP("Vietnamese"), QT_TR_NOOP("Xhosa"), QT_TR_NOOP("Yiddish"), QT_TR_NOOP("Yoruba"),
                                                        QT_TR_NOOP("Yucatec Maya"), QT_TR_NOOP("Cantonese"), QT_TR_NOOP("Chinese Simplified"), QT_TR_NOOP("Chinese Traditional"),
                                                        QT_TR_NOOP("Zulu") };

const QStringList QOnlineTranslator::LANGUAGE_LONG_CODES = { "automatic", "afrikaans", "amharic", "arabic", "azerbaijani", "belarusian", "bulgarian", "bengali", "bosnian", "catalan",
                                                             "cebuano", "corsican", "czech", "welsh", "danish", "german", "greek", "english", "esperanto", "spanish",
                                                             "estonian", "basque", "persian", "finnish", "fijian", "french", "frisian", "irish", "scots-gaelic", "galician",
                                                             "gujarati", "hausa", "hawaiian", "hebrew", "hindi", "hmong", "croatian", "haitian-creole", "hungarian",
                                                             "armenian", "indonesian", "igbo", "icelandic", "italian", "japanese", "javanese", "georgian", "kazakh",
                                                             "khmer", "kannada", "korean", "kurdish", "kyrgyz", "latin", "luxembourgish", "lao", "lithuanian", "latvian",
                                                             "malagasy", "maori", "macedonian", "malayalam", "mongolian", "marathi", "malay", "maltese", "hmong-daw",
                                                             "myanmar", "nepali", "dutch", "norwegian", "chichewa", "querétaro-otomi", "punjabi", "polish", "pashto",
                                                             "portuguese", "romanian", "russian", "sindhi", "sinhala", "slovak", "slovenian", "samoan", "shona", "somali",
                                                             "albanian", "serbian-cyrillic", "serbian-latin", "sesotho", "sundanese", "swedish", "swahili", "tamil",
                                                             "telugu", "tajik", "thai", "filipino", "klingon", "klingon-piqad", "tongan", "turkish", "tatar", "tahitian",
                                                             "udmurt", "ukrainian", "urdu", "uzbek", "vietnamese", "xhosa", "yiddish", "yoruba", "yucatec-maya",
                                                             "cantonese", "chinese-simplified", "chinese-traditional", "zulu" };

const QStringList QOnlineTranslator::LANGUAGE_SHORT_CODES = { "auto", "af", "am", "ar", "az", "be", "bg", "bn", "bs", "ca", "ceb", "co", "cs", "cy", "da", "de", "el", "en", "eo", "es",
                                                              "et", "eu", "fa", "fi", "fj", "fr", "fy", "ga", "gd", "gl", "gu", "ha", "haw", "he", "hi", "hmn", "hr", "ht", "hu",
                                                              "hy", "id", "ig", "is", "it", "ja", "jv", "ka", "kk", "km", "kn", "ko", "ku", "ky", "la", "lb", "lo", "lt", "lv",
                                                              "mg", "mi", "mk", "ml", "mn", "mr", "ms", "mt", "mww", "my", "ne", "nl", "no", "ny", "otq", "pa", "pl", "ps", "pt",
                                                              "ro", "ru", "sd", "si", "sk", "sl", "sm", "sn", "so", "sq", "sr-cyrl", "sr-latn", "st", "su", "sv", "sw", "ta",
                                                              "te", "tg", "th", "tl", "tlh", "tlh-qaak", "to", "tr", "tt", "ty", "udm", "uk", "ur", "uz", "vi", "xh", "yi", "yo",
                                                              "yua", "yue", "zh-cn", "zh-tw", "zu" };

void QOnlineTranslator::translate(const QString &text, const QString &translationLanguage, const QString &sourceLanguage, const QString &translatorLanguage, const bool &autoCorrect)
{
    m_source = text;

    // Detect system language if translateLanguage not specified
    if (translationLanguage == "auto")
        m_translationLanguage = defaultLocaleToCode();
    else
        m_translationLanguage = translationLanguage;

    // Set auto-correction query option
    QString autocorrection;
    if (autoCorrect == true)
        autocorrection = "qca";
    else
        autocorrection = "qc";

    // Reset old data
    m_translation.clear();
    m_translationTranscription.clear();
    m_sourceTranscription.clear();
    m_sourceLanguage.clear();
    m_options.clear();
    m_error = false;

    // Google has a limit of up to 5000 characters per request. If the query is larger, then it should be splited into several
    QString untranslatedText = text;
    while (!untranslatedText.isEmpty()) {
        int splitIndex = getSplitIndex(untranslatedText); // Split the part by special symbol
        if (splitIndex == -1) {
            // Do not translate the part if it looks like garbage
            m_translation.append(untranslatedText.left(5000));
            untranslatedText = untranslatedText.mid(5000);
            continue;
        }

        // Generate API url
        QUrl apiUrl("https://translate.googleapis.com/translate_a/single");
        apiUrl.setQuery("client=gtx&ie=UTF-8&oe=UTF-8&dt=bd&dt=ex&dt=ld&dt=md&dt=rw&dt=rm&dt=ss&dt=t&dt=at&dt=" + autocorrection +"&sl=" + sourceLanguage + "&tl=" +
                        translationLanguage + "&hl=" + translatorLanguage + "&q=" + QUrl::toPercentEncoding(untranslatedText.left(splitIndex)));

        // Send request
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(QNetworkRequest(apiUrl));

        // Wait for the response
        QEventLoop event;
        QObject::connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
        event.exec();

        // Check for network error
        if (reply->error() != QNetworkReply::NoError) {
            m_error = true;
            m_translation = reply->errorString();
            return;
        }

        // Convert to JsonArray
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonArray jsonData = jsonResponse.array();

        // Parse first sentense. If the answer contains more than one sentence, then at the end of the first one there will be a space
        m_translation.append(jsonData.at(0).toArray().at(0).toArray().at(0).toString());
        for (int i = 1; m_translation.endsWith(" ") || m_translation.endsWith("\n") || m_translation.endsWith("\u00a0"); i++)
            m_translation.append(jsonData.at(0).toArray().at(i).toArray().at(0).toString());

        // Parse transcriptions and source language
        m_translationTranscription.append(jsonData.at(0).toArray().last().toArray().at(2).toString());
        m_sourceTranscription.append(jsonData.at(0).toArray().last().toArray().at(3).toString());
        if (m_sourceLanguage.isEmpty())
            m_sourceLanguage = jsonData.at(2).toString();

        // Remove the parsed part from the next parsing
        untranslatedText = untranslatedText.mid(splitIndex);

        // Add a space between parts
        if (!untranslatedText.isEmpty() && !m_translation.endsWith("\n")) {
            m_translation.append(" ");
            m_translationTranscription.append(" ");
            m_sourceTranscription.append(" ");
        }

        // Translation options
        if (text.size() < 5000) {
            foreach (QJsonValue typeOfSpeach, jsonData.at(1).toArray()) {
                m_options.append(QPair<QString, QStringList>());
                m_options.last().first = typeOfSpeach.toArray().at(0).toString();
                foreach (QJsonValue translationOption, typeOfSpeach.toArray().at(2).toArray()) {
                    m_options.last().second.append(translationOption.toArray().at(0).toString() + ": ");
                    // Add the first word without ",", and then add the remaining words
                    m_options.last().second.last().append(translationOption.toArray().at(1).toArray().at(0).toString());
                    for (int i = 1; i < translationOption.toArray().at(1).toArray().size(); i++)
                        m_options.last().second.last().append(", " + translationOption.toArray().at(1).toArray().at(i).toString());
                }
            }
        }
    }
}

QList<QMediaContent> QOnlineTranslator::sourceMedia()
{
    QList<QMediaContent> mediaList;

    // Google has a limit of up to 5000 characters per request. If the query is larger, then it should be splited into several
    QString unparsedText = m_source;
    while (!unparsedText.isEmpty()) {
        int splitIndex = getSplitIndex(unparsedText); // Split the part by special symbol

        // Generate URL API for add it to the playlist
        QUrl apiUrl("http://translate.googleapis.com/translate_tts");
        apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + m_sourceLanguage +"&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)));
        mediaList.append(apiUrl);

        // Remove the said part from the next saying
        unparsedText = unparsedText.mid(splitIndex);
    }
    return mediaList;
}

QList<QMediaContent> QOnlineTranslator::translationMedia()
{
    QList<QMediaContent> mediaList;

    // Google has a limit of up to 5000 characters per request. If the query is larger, then it should be splited into several
    QString unparsedText = m_translation;
    while (!unparsedText.isEmpty()) {
        int splitIndex = getSplitIndex(unparsedText); // Split the part by special symbol

        // Generate URL API for add it to the playlist
        QUrl apiUrl("http://translate.googleapis.com/translate_tts");
        apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + m_translationLanguage +"&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)));
        mediaList.append(apiUrl);

        // Remove the said part from the next saying
        unparsedText = unparsedText.mid(splitIndex);
    }
    return mediaList;
}

QString QOnlineTranslator::translateText(const QString &text, QString translationLanguage, QString sourceLanguage)
{
    // Detect system language if translationLanguage not specified
    if (translationLanguage == "auto")
        translationLanguage = defaultLocaleToCode();

    QString untranslatedText = text;
    QString translatedText;

    // Google has a limit of up to 5000 characters per request. If the query is larger, then it should be splited into several
    while (!untranslatedText.isEmpty()) {
        int splitIndex = getSplitIndex(untranslatedText); // Split part by special symbols
        if (splitIndex == -1) {
            // Do not translate the part if it looks like garbage
            translatedText.append(untranslatedText.left(5000));
            untranslatedText = untranslatedText.mid(5000);
            continue;
        }

        // Generate short URL API only for translation and and receive a reply
        QUrl apiUrl("https://translate.googleapis.com/translate_a/single");
        apiUrl.setQuery("client=gtx&sl=" + sourceLanguage +"&tl=" + translationLanguage + "&dt=t&q=" + QUrl::toPercentEncoding(untranslatedText.left(splitIndex)));

        // Send request
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(QNetworkRequest(apiUrl));

        // Wait for the response
        QEventLoop event;
        QObject::connect(reply, &QNetworkReply::finished, &event, &QEventLoop::quit);
        event.exec();

        // Check for network error
        if (reply->error() != QNetworkReply::NoError)
            return reply->errorString();

        // Convert to JsonArray
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonArray jsonData = jsonResponse.array();

        // Parse first sentense. If the answer contains more than one sentence, then at the end of the first one there will be a space
        translatedText.append(jsonData.at(0).toArray().at(0).toArray().at(0).toString());
        for (int i = 1; translatedText.endsWith(" ") || translatedText.endsWith("\n") || translatedText.endsWith("\u00a0"); i++)
            translatedText.append(jsonData.at(0).toArray().at(i).toArray().at(0).toString());

        // Remove the parsed part from the next parsing
        untranslatedText = untranslatedText.mid(splitIndex);

        // Add a space between parts
        if (!untranslatedText.isEmpty() && !translatedText.endsWith("\n"))
            translatedText.append(" ");
    }

    return translatedText;
}

QString QOnlineTranslator::codeToLanguage(const QString &code)
{
    int index = LANGUAGE_SHORT_CODES.indexOf(code);
    return LANGUAGE_NAMES.at(index);
}

QString QOnlineTranslator::languageToCode(const QString &language)
{
    int index = LANGUAGE_NAMES.indexOf(language);
    return LANGUAGE_SHORT_CODES.at(index);
}

QString QOnlineTranslator::defaultLocaleToCode()
{
    QLocale locale;
    return locale.name().left(locale.name().indexOf("_"));
}

// Split the first part of the 5000 characters by last special symbol
int QOnlineTranslator::getSplitIndex(const QString &untranslatedText)
{
    if (untranslatedText.size() < 5000)
        return 5000;

    int splitIndex = untranslatedText.lastIndexOf(". ", 4999);
    if (splitIndex != -1)
        return splitIndex + 1;

    splitIndex = untranslatedText.lastIndexOf(" ", 4999);
    if (splitIndex != -1)
        return splitIndex + 1;

    splitIndex = untranslatedText.lastIndexOf("\n", 4999);
    if (splitIndex != -1)
        return splitIndex + 1;

    // Non-breaking gap
    splitIndex = untranslatedText.lastIndexOf("\u00a0", 4999);
    if (splitIndex != -1)
        return splitIndex + 1;
    else
        return 5000;
}
