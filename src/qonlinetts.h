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

        // Yandex
        Zahar,
        Ermil,
        Jane,
        Oksana,
        Alyss,
        Omazh
    };
    Q_ENUM(Voice)

    enum Emotion {
        // All
        NoEmotion = -1,

        // Yandex
        Neutral,
        Good,
        Evil
    };
    Q_ENUM(Emotion)

    enum TtsError {
        NoError,
        UnsupportedEngine,
        UnsupportedLanguage,
        UnsupportedVoice,
        UnsupportedEmotion,
    };

    explicit QOnlineTts(QObject *parent = nullptr);

    void generateUrls(const QString &text, QOnlineTranslator::Engine engine, QOnlineTranslator::Language lang, Voice voice = NoVoice, Emotion emotion = NoEmotion);
    QList<QMediaContent> media() const;

    TtsError error() const;
    QString errorString() const;

    static QString voiceCode(Voice voice);
    static QString emotionCode(Emotion emotion);
    static Emotion emotion(const QString &emotionCode);
    static Voice voice(const QString &voiceCode);

private:
    void setError(TtsError error, const QString &errorString);

    QString languageApiCode(QOnlineTranslator::Engine engine, QOnlineTranslator::Language lang);
    QString voiceApiCode(QOnlineTranslator::Engine engine, Voice voice);
    QString emotionApiCode(QOnlineTranslator::Engine engine, Emotion emotion);

    QList<QMediaContent> m_media;
    QString m_errorString;
    TtsError m_error = NoError;

    const static QStringList m_emotionCodes;
    const static QStringList m_voiceCodes;
};

#endif // QONLINETTS_H
