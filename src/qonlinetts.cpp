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

#include "qonlinetts.h"

#include <QUrl>
#include <QMetaEnum>

constexpr int googleTtsLimit = 200;
constexpr int yandexTtsLimit = 1400;

const QStringList QOnlineTts::m_emotionCodes = { "neutral", "good", "evil" };
const QStringList QOnlineTts::m_voiceCodes = { "zahar", "ermil", "jane", "oksana", "alyss", "omazh" };

QOnlineTts::QOnlineTts(QObject *parent) :
    QObject(parent)
{
}

void QOnlineTts::generateUrls(const QString &text, QOnlineTranslator::Engine engine, QOnlineTranslator::Language lang, Voice voice, Emotion emotion)
{
    // Get speech
    QString unparsedText = text;
    switch (engine) {
    case QOnlineTranslator::Google:
    {
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
            const int splitIndex = QOnlineTranslator::getSplitIndex(unparsedText, googleTtsLimit); // Split the part by special symbol

            // Generate URL API for add it to the playlist
            QUrl apiUrl("http://translate.googleapis.com/translate_tts");
#if defined(Q_OS_LINUX)
            apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + langString
                            + "&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)));
#elif defined(Q_OS_WIN)
            apiUrl.setQuery("ie=UTF-8&client=gtx&tl=" + langString
                            + "&q=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex)), QUrl::DecodedMode);
#endif
            m_media.append(apiUrl);

            // Remove the said part from the next saying
            unparsedText = unparsedText.mid(splitIndex);
        }
        break;
    }
    case QOnlineTranslator::Yandex:
    {
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
            const int splitIndex = QOnlineTranslator::getSplitIndex(unparsedText, yandexTtsLimit); // Split the part by special symbol

            // Generate URL API for add it to the playlist
            QUrl apiUrl("https://tts.voicetech.yandex.net/tts");
#if defined(Q_OS_LINUX)
            apiUrl.setQuery("text=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex))
                            + "&lang=" + langString
                            + "&speaker=" + voiceString
                            + "&emotion=" + emotionString
                            + "&format=mp3");
#elif defined(Q_OS_WIN)
            apiUrl.setQuery("text=" + QUrl::toPercentEncoding(unparsedText.left(splitIndex))
                            + "&lang=" + langString
                            + "&speaker=" + voiceString
                            + "&emotion=" + emotionString
                            + "&format=mp3", QUrl::DecodedMode);
#endif
            m_media.append(apiUrl);

            // Remove the said part from the next saying
            unparsedText = unparsedText.mid(splitIndex);
        }
        break;
    }
    case QOnlineTranslator::Bing:
        setError(UnsupportedEngine, tr("%1 engine does not support TTS").arg(QMetaEnum::fromType<QOnlineTranslator::Engine>().valueToKey(QOnlineTranslator::Bing)));
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
    return m_voiceCodes.value(voice);
}

QString QOnlineTts::emotionCode(Emotion emotion)
{
    return m_emotionCodes.value(emotion);
}

QOnlineTts::Emotion QOnlineTts::emotion(const QString &emotionCode)
{
    return static_cast<Emotion>(m_emotionCodes.indexOf(emotionCode));
}

QOnlineTts::Voice QOnlineTts::voice(const QString &voiceCode)
{
    return static_cast<Voice>(m_emotionCodes.indexOf(voiceCode));
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
        if (lang != QOnlineTranslator::Auto)
            return QOnlineTranslator::languageApiCode(engine, lang); // Google use the same codes for tts (except 'auto')
        break;
    case QOnlineTranslator::Yandex:
        switch (lang) {
        case QOnlineTranslator::Russian:
            return "ru_RU";
        case QOnlineTranslator::Tatar:
            return "tr_TR";
        case QOnlineTranslator::English:
            return "en_GB";
        default:
            break;
        }
        break;
    default:
        break;
    }

    setError(UnsupportedLanguage, tr("Selected language %1 is not supported for %2")
             .arg(QMetaEnum::fromType<QOnlineTranslator::Language>().valueToKey(lang))
             .arg(QMetaEnum::fromType<QOnlineTranslator::Engine>().valueToKey(engine)));
    return QString();
}

QString QOnlineTts::voiceApiCode(QOnlineTranslator::Engine engine, Voice voice)
{
    if (engine == QOnlineTranslator::Yandex) {
        if (voice == NoVoice)
            return voiceCode(Zahar);
        return voiceCode(voice);
    }

    setError(UnsupportedVoice, tr("Selected voice %1 is not supported for %2")
             .arg(QMetaEnum::fromType<Voice>().valueToKey(voice))
             .arg(QMetaEnum::fromType<QOnlineTranslator::Engine>().valueToKey(engine)));
    return QString();
}

QString QOnlineTts::emotionApiCode(QOnlineTranslator::Engine engine, Emotion emotion)
{
    if (engine == QOnlineTranslator::Yandex) {
        if (emotion == NoEmotion)
            return emotionCode(Neutral);
        return emotionCode(emotion);
    }

    setError(UnsupportedEmotion, tr("Selected emotion %1 is not supported for %2")
             .arg(QMetaEnum::fromType<Emotion>().valueToKey(emotion))
             .arg(QMetaEnum::fromType<QOnlineTranslator::Engine>().valueToKey(engine)));
    return QString();
}
