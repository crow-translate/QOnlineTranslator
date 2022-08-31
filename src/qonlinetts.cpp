/*
 *  Copyright © 2018-2022 Hennadii Chernyshchyk <genaloner@gmail.com>
 *
 *  This file is part of QOnlineTranslator.
 *
 *  QOnlineTranslator is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  QOnlineTranslator is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with QOnlineTranslator. If not, see <https://www.gnu.org/licenses/>.
 */

#include "qonlinetts.h"

#include <QMetaEnum>
#include <QUrl>

const QMap<QOnlineTts::Emotion, QString> QOnlineTts::s_emotionCodes = {
    {Neutral, QStringLiteral("neutral")},
    {Good, QStringLiteral("good")},
    {Evil, QStringLiteral("evil")}};

const QMap<QOnlineTts::Voice, QString> QOnlineTts::s_voiceCodes = {
    {Zahar, QStringLiteral("zahar")},
    {Ermil, QStringLiteral("ermil")},
    {Jane, QStringLiteral("jane")},
    {Oksana, QStringLiteral("oksana")},
    {Alyss, QStringLiteral("alyss")},
    {Omazh, QStringLiteral("omazh")}};

const QMap<QPair<QOnlineTranslator::Language, QLocale::Country>, QString> QOnlineTts::s_regionCodes = {
    {{QOnlineTranslator::Bengali, QLocale::Bangladesh}, QStringLiteral("bn-BD")},
    {{QOnlineTranslator::Bengali, QLocale::India}, QStringLiteral("bn-IN")},
    {{QOnlineTranslator::SimplifiedChinese, QLocale::China}, QStringLiteral("cmn-Hans-CN")},
    {{QOnlineTranslator::English, QLocale::Australia}, QStringLiteral("en-AU")},
    {{QOnlineTranslator::English, QLocale::India}, QStringLiteral("en-IN")},
    {{QOnlineTranslator::English, QLocale::UnitedKingdom}, QStringLiteral("en-GB")},
    {{QOnlineTranslator::English, QLocale::UnitedStates}, QStringLiteral("en-US")},
    {{QOnlineTranslator::French, QLocale::Canada}, QStringLiteral("fr-CA")},
    {{QOnlineTranslator::French, QLocale::France}, QStringLiteral("fr-FR")},
    {{QOnlineTranslator::German, QLocale::Germany}, QStringLiteral("de-DE")},
    {{QOnlineTranslator::Portuguese, QLocale::Brazil}, QStringLiteral("pt-BR")},
    {{QOnlineTranslator::Spanish, QLocale::Spain}, QStringLiteral("es-ES")},
    {{QOnlineTranslator::Spanish, QLocale::UnitedStates}, QStringLiteral("es-US")},
    {{QOnlineTranslator::Tamil, QLocale::India}, QStringLiteral("ta-IN")}};

QOnlineTts::QOnlineTts(QObject *parent)
    : QObject(parent)
{
}

void QOnlineTts::generateUrls(const QString &text, QOnlineTranslator::Engine engine, QOnlineTranslator::Language lang, Voice voice, Emotion emotion)
{
    // Get speech
    QString unparsedText = text;
    switch (engine) {
    case QOnlineTranslator::Google: {
        if (voice != NoVoice) {
            setError(UnsupportedVoice, tr("Selected engine %1 does not support voice settings").arg(QMetaEnum::fromType<QOnlineTranslator::Engine>().valueToKey(engine)));
            return;
        }

        if (emotion != NoEmotion) {
            setError(UnsupportedEmotion, tr("Selected engine %1 does not support emotion settings").arg(QMetaEnum::fromType<QOnlineTranslator::Engine>().valueToKey(engine)));
            return;
        }

        const QString langString = languageApiCode(engine, lang);
        if (langString.isNull())
            return;

        // Google has a limit of characters per tts request. If the query is larger, then it should be splited into several
        while (!unparsedText.isEmpty()) {
            const int splitIndex = QOnlineTranslator::getSplitIndex(unparsedText, s_googleTtsLimit); // Split the part by special symbol

            // Generate URL API for add it to the playlist
            QUrl apiUrl(QStringLiteral("https://translate.googleapis.com/translate_tts"));
            const QString query = QStringLiteral("ie=UTF-8&client=gtx&tl=%1&q=%2").arg(langString, QString(QUrl::toPercentEncoding(unparsedText.left(splitIndex))));
#if defined(Q_OS_LINUX)
            apiUrl.setQuery(query);
#elif defined(Q_OS_WIN)
            apiUrl.setQuery(query, QUrl::DecodedMode);
#endif
            m_media.append(apiUrl);

            // Remove the said part from the next saying
            unparsedText = unparsedText.mid(splitIndex);
        }
        break;
    }
    case QOnlineTranslator::Yandex: {
        const QString langString = languageApiCode(engine, lang);
        if (langString.isNull())
            return;

        const QString voiceString = voiceApiCode(engine, voice);
        if (voiceString.isNull())
            return;

        const QString emotionString = emotionApiCode(engine, emotion);
        if (emotionString.isNull())
            return;

        // Yandex has a limit of characters per tts request. If the query is larger, then it should be splited into several
        while (!unparsedText.isEmpty()) {
            const int splitIndex = QOnlineTranslator::getSplitIndex(unparsedText, s_yandexTtsLimit); // Split the part by special symbol

            // Generate URL API for add it to the playlist
            QUrl apiUrl(QStringLiteral("https://tts.voicetech.yandex.net/tts"));
            const QString query = QStringLiteral("text=%1&lang=%2&speaker=%3&emotion=%4&format=mp3")
                                      .arg(QUrl::toPercentEncoding(unparsedText.left(splitIndex)), langString, voiceString, emotionString);
#if defined(Q_OS_LINUX)
            apiUrl.setQuery(query);
#elif defined(Q_OS_WIN)
            apiUrl.setQuery(query, QUrl::DecodedMode);
#endif
            m_media.append(apiUrl);

            // Remove the said part from the next saying
            unparsedText = unparsedText.mid(splitIndex);
        }
        break;
    }
    case QOnlineTranslator::Bing:
    case QOnlineTranslator::LibreTranslate:
    case QOnlineTranslator::Lingva:
        // NOTE:
        // Lingva returns audio in strange format, use placeholder, until we'll figure it out
        //
        // Example: https://lingva.ml/api/v1/audio/en/Hello%20World!
        // Will return json with uint bytes array, according to documentation
        // See: https://github.com/TheDavidDelta/lingva-translate#public-apis
        setError(UnsupportedEngine, tr("%1 engine does not support TTS").arg(QMetaEnum::fromType<QOnlineTranslator::Engine>().valueToKey(engine)));
        break;
    }
}

QList<QMediaContent> QOnlineTts::media() const
{
    return m_media;
}

QString QOnlineTts::errorString() const
{
    return m_errorString;
}

QOnlineTts::TtsError QOnlineTts::error() const
{
    return m_error;
}

QString QOnlineTts::voiceCode(Voice voice)
{
    return s_voiceCodes.value(voice);
}

QString QOnlineTts::regionCode(QOnlineTranslator::Language language, QLocale::Country region)
{
    return s_regionCodes.value({language, region}, QOnlineTranslator::languageApiCode(QOnlineTranslator::Google, language));
}

QString QOnlineTts::emotionCode(Emotion emotion)
{
    return s_emotionCodes.value(emotion);
}

QOnlineTts::Emotion QOnlineTts::emotion(const QString &emotionCode)
{
    return s_emotionCodes.key(emotionCode, NoEmotion);
}

QOnlineTts::Voice QOnlineTts::voice(const QString &voiceCode)
{
    return s_voiceCodes.key(voiceCode, NoVoice);
}

QPair<QOnlineTranslator::Language, QLocale::Country> QOnlineTts::region(const QString &regionCode)
{
    return s_regionCodes.key(regionCode, {QOnlineTranslator::NoLanguage, QLocale::AnyCountry});
}

QString QOnlineTts::regionName(QOnlineTranslator::Language language, QLocale::Country region)
{
    switch (language) {
    case QOnlineTranslator::Bengali:
        switch (region) {
        case QLocale::Bangladesh:
            return tr("Bangla (Bangladesh)");
        case QLocale::India:
            return tr("Bangla (India)");
        default:
            break;
        }
        break;
    case QOnlineTranslator::SimplifiedChinese:
        switch (region) {
        case QLocale::China:
            return tr("Chinese, Mandarin (China)");
        default:
            break;
        }
        break;
    case QOnlineTranslator::English:
        switch (region) {
        case QLocale::Australia:
            return tr("English (Australia)");
        case QLocale::India:
            return tr("English (India)");
        case QLocale::UnitedKingdom:
            return tr("English (United Kingdom)");
        case QLocale::UnitedStates:
            return tr("English (United States)");
        default:
            break;
        }
        break;
    case QOnlineTranslator::French:
        switch (region) {
        case QLocale::Canada:
            return tr("French (Canada)");
        case QLocale::France:
            return tr("French (France)");
        default:
            break;
        }
        break;
    case QOnlineTranslator::German:
        switch (region) {
        case QLocale::Germany:
            return tr("German (Germany)");
        default:
            break;
        }
        break;
    case QOnlineTranslator::Portuguese:
        switch (region) {
        case QLocale::Brazil:
            return tr("Portuguese (Brazil)");
        default:
            break;
        }
        break;
    case QOnlineTranslator::Spanish:
        switch (region) {
        case QLocale::Spain:
            return tr("Spanish (Spain)");
        case QLocale::UnitedStates:
            return tr("Spanish (United States)");
        default:
            break;
        }
        break;
    case QOnlineTranslator::Tamil:
        switch (region) {
        case QLocale::India:
            return tr("Tamil (India)");
        default:
            break;
        }
        break;
    default:
        break;
    }
    return tr("Default region");
}

QList<QLocale::Country> QOnlineTts::validRegions(QOnlineTranslator::Language language)
{
    switch (language) {
    case QOnlineTranslator::Bengali:
        return {QLocale::Bangladesh, QLocale::India};
    case QOnlineTranslator::SimplifiedChinese:
        return {QLocale::China};
    case QOnlineTranslator::English:
        return {QLocale::Australia, QLocale::India, QLocale::UnitedKingdom, QLocale::UnitedStates};
    case QOnlineTranslator::French:
        return {QLocale::Canada, QLocale::France};
    case QOnlineTranslator::German:
        return {QLocale::Germany};
    case QOnlineTranslator::Portuguese:
        return {QLocale::Brazil};
    case QOnlineTranslator::Spanish:
        return {QLocale::Spain, QLocale::UnitedStates};
    case QOnlineTranslator::Tamil:
        return {QLocale::India};
    default:
        return {};
    }
}

void QOnlineTts::setError(TtsError error, const QString &errorString)
{
    m_error = error;
    m_errorString = errorString;
}

// Returns engine-specific language code for tts
QString QOnlineTts::languageApiCode(QOnlineTranslator::Engine engine, QOnlineTranslator::Language lang)
{
    switch (engine) {
    case QOnlineTranslator::Google:
    case QOnlineTranslator::Lingva: // Lingva is a frontend to Google Translate
        if (lang != QOnlineTranslator::Auto)
            return regionCode(lang, m_regionPreferences.value(lang)); // Google use the same codes for tts (except 'auto')
        break;
    case QOnlineTranslator::Yandex:
        switch (lang) {
        case QOnlineTranslator::Russian:
            return QStringLiteral("ru_RU");
        case QOnlineTranslator::Tatar:
            return QStringLiteral("tr_TR");
        case QOnlineTranslator::English:
            return QStringLiteral("en_GB");
        default:
            break;
        }
        break;
    default:
        break;
    }

    setError(UnsupportedLanguage, tr("Selected language %1 is not supported for %2").arg(QMetaEnum::fromType<QOnlineTranslator::Language>().valueToKey(lang), QMetaEnum::fromType<QOnlineTranslator::Engine>().valueToKey(engine)));
    return {};
}

QString QOnlineTts::voiceApiCode(QOnlineTranslator::Engine engine, Voice voice)
{
    if (engine == QOnlineTranslator::Yandex) {
        if (voice == NoVoice)
            return voiceCode(Zahar);
        return voiceCode(voice);
    }

    setError(UnsupportedVoice, tr("Selected voice %1 is not supported for %2").arg(QMetaEnum::fromType<Voice>().valueToKey(voice), QMetaEnum::fromType<QOnlineTranslator::Engine>().valueToKey(engine)));
    return {};
}

QString QOnlineTts::emotionApiCode(QOnlineTranslator::Engine engine, Emotion emotion)
{
    if (engine == QOnlineTranslator::Yandex) {
        if (emotion == NoEmotion)
            return emotionCode(Neutral);
        return emotionCode(emotion);
    }

    setError(UnsupportedEmotion, tr("Selected emotion %1 is not supported by %2").arg(QMetaEnum::fromType<Emotion>().valueToKey(emotion), QMetaEnum::fromType<QOnlineTranslator::Engine>().valueToKey(engine)));
    return {};
}

const QMap<QOnlineTranslator::Language, QLocale::Country> &QOnlineTts::regions() const
{
    return m_regionPreferences;
}

void QOnlineTts::setRegions(const QMap<QOnlineTranslator::Language, QLocale::Country> &newRegionPreferences)
{
    m_regionPreferences = newRegionPreferences;
}
