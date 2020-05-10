# QOnlineTts

The **QOnlineTts** class provides TTS URLs generator.

## Content

- [Public Types](#public-types)
- [Public Functions](#public-functions)
- [Static Public Members](#static-public-member)
- [Member Type Documentation](#member-type-documentation)
- [Member Function Documentation](#member-function-documentation)

## Public Types

| Type | Name                                                                                                                |
| ---: | :------------------------------------------------------------------------------------------------------------------ |
| enum | [**Voice**](#voice) { NoVoice, Zahar, Ermil, ..., Omazh }                                                           |
| enum | [**Emotion**](#emotion) { NoEmotion, Good, Evil, Neutral }                                                          |
| enum | [**TtsError**](tts-error) { NoError, UnsupportedEngine, UnsupportedLanguage, UnsupportedVoice, UnsupportedEmotion } |

## Public Functions

|           Return type | Data member                                                                                                                                                                               |
| --------------------: | :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|                       | [**QOnlineTts**(QWidget \*parent = nullptr)](#constructor)                                                                                                                                |
|                  void | [**generateUrls**(const QString &text, QOnlineTranslator::Engine engine, QOnlineTranslator::Language lang, Voice voice = DefaultVoice, Emotion emotion = DefaultEmotion)](#generate-urls) |
| QList\<QMediaContent> | [**media**()](#media)                                                                                                                                                                     |
|              TtsError | [**error**()](#error)                                                                                                                                                                     |
|               QString | [**errorString**()](#error-string)                                                                                                                                                        |

## Static Public Members

| Return type | Data member                                         |
| ----------: | :-------------------------------------------------- |
|     QString | [**voiceCode**(Voice voice)](#voice-code)           |
|     QString | [**emotionCode**(Emotion emotion)](#emotion-code)   |
|     Emotion | [**emotion**(const QString &emotionCode)](#emotion) |
|       Voice | [**voice**(const QString &voiceCode)](#voice)       |

## Member Type Documentation

### <a id='voice'/> enum QOnlineTts::Voice

This enum has the following values:

|            Constant | Value | Engine | Code   |
| ------------------: | :---: | :----- | :----- |
| QOnlineTts::NoVoice |  -1   | Yandex | -      |
|   QOnlineTts::Zahar |   0   | Yandex | zahar  |
|   QOnlineTts::Ermil |   1   | Yandex | ermil  |
|    QOnlineTts::Jane |   2   | Yandex | jane   |
|  QOnlineTts::Oksana |   3   | Yandex | oksana |
|   QOnlineTts::Alyss |   4   | Yandex | alyss  |
|   QOnlineTts::Omazh |   5   | Yandex | omazh  |

### <a id='emotion'/> enum QOnlineTts::Emotion

This enum has the following values:

|              Constant | Value | Engine | Code    |
| --------------------: | :---: | :----- | :------ |
| QOnlineTts::NoEmotion |  -1   | Yandex | -       |
|   QOnlineTts::Neutral |   0   | Yandex | neutral |
|      QOnlineTts::Good |   1   | Yandex | good    |
|      QOnlineTts::Evil |   2   | Yandex | evil    |

### <a id='tts-error'/> enum QOnlineTts::TtsError

Indicates all possible error conditions found during the processing of the URLs generation.

|                        Constant | Value | Description                              |
| ------------------------------: | :---: | :--------------------------------------- |
|             QOnlineTts::NoError |   0   | No error condition                       |
|   QOnlineTts::UnsupportedEngine |   1   | Specified engine does not support TTS    |
| QOnlineTts::UnsupportedLanguage |   2   | Unsupported language by specified engine |
|    QOnlineTts::UnsupportedVoice |   3   | Unsupported voice by specified engine    |
|  QOnlineTts::UnsupportedEmotion |   4   | Unsupported emotion by specified engine  |

## Member Function Documentation

### <a id='constructor'/> QOnlineTts::QOnlineTts(_QObject \*parent = nullptr_)

Constructs an object with empty data and with _parent_. You can use [generateUrls()](#generate-urls) to create URLs for use in QMediaPlayer.

---

### <a id='generate-urls'/> void QOnlineTts::generateUrls(_const QString &text, QOnlineTranslator::Engine engine, QOnlineTranslator::Language lang, Voice voice = DefaultVoice, Emotion emotion = DefaultEmotion_)

Splits _text_ into parts (engines have a limited number of characters per request) and returns list with the generated API URLs to play this text on _language_ with _voice_. _emotion_ argument only affects Yandex engine.

Example:

```cpp
QMediaPlayer *player = new QMediaPlayer(this);
QMediaPlaylist *playlist = new QMediaPlaylist(player);
QOnlineTts tts;

playlist->addMedia(tts.generateUrls("Hello World!", QOnlineTranslator::Google););
player->setPlaylist(playlist);


player->play(); // Plays "Hello World!"
```

---

### <a id='error'/> TranslationError QOnlineTts::error()

Returns the error that was found during the generating tts. If no error was found, returns `NoError`. The text of the error can be obtained by [**errorString**()](#error-string).

---

### <a id='error-string'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTts::errorString()

Returns a human-readable description of the last tts URL generation error that occurred.

---

### <a id='voice-code'/> static [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTts::voiceCode(_Voice voice_)

Returns the code of the _voice_. See table [below](#voice).

---

### <a id='emotion-code'/> static [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTts::emotionCode(_Emotion emotion_)

Returns the code of the _emotion_. See table [below](#emotion).

---

### <a id='emotion'/> static Emotion QOnlineTts::emotion(_const QString &emotionCode_)

Returns the [emotion](#emotion) from the _emotionCode_. Useful for CLI interface.

---

### <a id='voice'/> static Voice QOnlineTts::voice(_const QString &voiceCode_)

Returns the [voice](#voice) from the _voiceCode_. Useful for CLI interface.
