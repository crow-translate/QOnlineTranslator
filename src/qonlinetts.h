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

#ifndef QONLINETTS_H
#define QONLINETTS_H

#include "qonlinetranslator.h"

#include <QMediaContent>

/**
 * @brief Provides TTS URL generation
 *
 * Example:
 * @code
 * QMediaPlayer *player = new QMediaPlayer(this);
 * QMediaPlaylist *playlist = new QMediaPlaylist(player);
 * QOnlineTts tts;
 *
 * playlist->addMedia(tts.generateUrls("Hello World!", QOnlineTranslator::Google););
 * player->setPlaylist(playlist);
 *
 * player->play(); // Plays "Hello World!"
 * @endcode
 */
class QOnlineTts : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QOnlineTts)

public:
    /**
     * @brief Defines voice to use
     *
     * Used only by Yandex.
     */
    enum Voice {
        // All
        NoVoice = -1,

        // Yandex
        Zahar,
        Ermil,
        Jane,
        Oksana,
        Alyss,
        Omazh
    };
    Q_ENUM(Voice)

    /**
     * @brief Defines emotion to use
     *
     * Used only by Yandex.
     */
    enum Emotion {
        // All
        NoEmotion = -1,

        // Yandex
        Neutral,
        Good,
        Evil
    };
    Q_ENUM(Emotion)

    /**
     * @brief Defines regional accents to use
     *
     * Used only by Google.
     */
    enum Region {
        DefaultRegion,
        BengaliBangladesh,
        BengaliIndia,
        ChineseMandarinChina,
        EnglishAustralia,
        EnglishIndia,
        EnglishUk,
        EnglishUs,
        FrenchCanada,
        FrenchFrance,
        GermanGermany,
        PortugueseBrazil,
        SpanishSpain,
        SpanishUs,
        TamilIndia,
    };
    Q_ENUM(Region)

    /**
     * @brief Indicates all possible error conditions found during the processing of the URLs generation
     */
    enum TtsError {
        /** No error condition */
        NoError,
        /** Specified engine does not support TTS */
        UnsupportedEngine,
        /** Unsupported language by specified engine */
        UnsupportedLanguage,
        /** Unsupported voice by specified engine */
        UnsupportedVoice,
        /** Unsupported emotion by specified engine */
        UnsupportedEmotion,
        /** Unsupported region by specified engine */
        UnsupportedRegion
    };

    /**
     * @brief Create object
     *
     * Constructs an object with empty data and with parent.
     * You can use generateUrls() to create URLs for use in QMediaPlayer.
     *
     * @param parent parent object
     */
    explicit QOnlineTts(QObject *parent = nullptr);

    /**
     * @brief Create TTS urls
     *
     * Splits text into parts (engines have a limited number of characters per request) and returns list with the generated API URLs to play.
     *
     * @param text text to speak
     * @param engine online translation engine
     * @param lang text language
     * @param voice voice to use (used only by Yandex)
     * @param emotion emotion to use (used only by Yandex)
     */
    void generateUrls(const QString &text, QOnlineTranslator::Engine engine, QOnlineTranslator::Language lang, Voice voice = NoVoice, Emotion emotion = NoEmotion);

    /**
     * @brief Generated media
     *
     * @return List of generated URLs
     */
    QList<QMediaContent> media() const;

    /**
     * @brief Last error
     *
     * Error that was found during the generating tts.
     * If no error was found, returns TtsError::NoError.
     * The text of the error can be obtained by errorString().
     *
     * @return last error
     */
    TtsError error() const;

    /**
     * @brief Last error string
     *
     * A human-readable description of the last tts URL generation error that occurred.
     *
     * @return last error string
     */
    QString errorString() const;

    /**
     * @brief Code of the voice
     *
     * @param voice voice
     * @return code for voice
     */
    static QString voiceCode(Voice voice);

    /**
     * @brief Code of the regional voice
     *
     * Used only by Google
     *
     * @param region region
     * @return code for regional language
     */
    static QString regionCode(Region region);

    /**
     * @brief Code of the emotion
     *
     * Used only by Yandex.
     *
     * @param emotion emotion
     * @return code for emotion
     */
    static QString emotionCode(Emotion emotion);

    /**
     * @brief Emotion from code
     *
     * Used only by Yandex.
     *
     * @param emotionCode emotion code
     * @return corresponding emotion
     */
    static Emotion emotion(const QString &emotionCode);

    /**
     * @brief Voice from code
     *
     * Used only by Yandex.
     *
     * @param voiceCode voice code
     * @return corresponding voice
     */
    static Voice voice(const QString &voiceCode);

    /**
     * @brief Voice region from code
     *
     * Used only by Google
     *
     * @param regionCode region code
     * @return corresponding region code
     */
    static Region region(const QString &regionCode);

    /**
     * @brief Voice region preferences
     * @return voice region preferences
     */
    const QMap<QOnlineTranslator::Language, Region> &regionPreferences() const;

    /**
     * @brief Set voice region preferences
     * @param region preferences
     */
    void setRegionPreferences(const QMap<QOnlineTranslator::Language, Region> &regionPreferences);

private:
    void setError(TtsError error, const QString &errorString);

    QString languageApiCode(QOnlineTranslator::Engine engine, QOnlineTranslator::Language lang);
    QString voiceApiCode(QOnlineTranslator::Engine engine, Voice voice);
    QString emotionApiCode(QOnlineTranslator::Engine engine, Emotion emotion);
    QString regionApiCode(QOnlineTranslator::Engine engine, Region region);

    static const QMap<Emotion, QString> s_emotionCodes;
    static const QMap<Voice, QString> s_voiceCodes;
    static const QMap<Region, QString> s_voiceRegionCodes;

    QMap<QOnlineTranslator::Language, Region> m_regionPreferences;

    static constexpr int s_googleTtsLimit = 200;
    static constexpr int s_yandexTtsLimit = 1400;

    QList<QMediaContent> m_media;
    QString m_errorString;
    TtsError m_error = NoError;
};

#endif // QONLINETTS_H
