#ifndef QONLINETTS_H
#define QONLINETTS_H

#include "qonlinetranslator.h"

#include <QMediaContent>

class QOnlineTts : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QOnlineTts)

public:
    enum Voice {
        // All
        NoVoice = -1,
        DefaultVoice,

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
        // All
        NoEmotion = -1,
        DefaultEmotion,

        // Yandex
        Neutral,
        Good,
        Evil
    };
    Q_ENUM(Emotion)

    enum TtsError {
        NoError,
        UnsupportedLanguage,
        UnsupportedVoice,
        UnsupportedEmotion,
    };

    QOnlineTts(QObject *parent = nullptr);

    void generateUrls(const QString &text, QOnlineTranslator::Engine engine, QOnlineTranslator::Language lang, Voice voice = DefaultVoice, Emotion emotion = DefaultEmotion);
    QList<QMediaContent> media() const;

    TtsError error() const;
    QString errorString() const;

    static QString voiceCode(Voice voice);
    static QString emotionCode(Emotion emotion);
    static Emotion emotion(const QString &emotionCode);
    static Voice voice(const QString &voiceCode);
    static bool isSupportTts(QOnlineTranslator::Engine engine, QOnlineTranslator::Language lang);

private:
    void setError(TtsError error, const QString &errorString);

    static QString ttsLanguageCode(QOnlineTranslator::Engine engine, QOnlineTranslator::Language lang);
    static QString voiceCode(QOnlineTranslator::Engine engine, Voice voice);
    static QString emotionCode(QOnlineTranslator::Engine engine, Emotion emotion);

    QList<QMediaContent> m_media;
    QString m_errorString;
    TtsError m_error = NoError;

    const static QStringList m_emotionCodes;
    const static QStringList m_voiceCodes;
};

#endif // QONLINETTS_H
