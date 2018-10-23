# QOnlineTranslator

The **QOnlineTranslator** class provides translation data.

## Content

* [Public Types](#public-types)
* [Public Functions](#public-functions)
* [Static Public Members](#static-public-member)
* [Member Type Documentation](#member-type-documentation)
* [Member Function Documentation](#member-function-documentation)

## Public Types

| Type | Name                                                                                                              |
|-----:|:------------------------------------------------------------------------------------------------------------------|
| enum | [**Engine**](#engine) { Google, Yandex }                                                                          |
| enum | [**Speaker**](#speaker) { Zahar, Ermil, Jane, Oksana, ..., Omazh }                                                |
| enum | [**Emotion**](#emotion) { Good, Evil, Neutral }                                                                   |
| enum | [**Language**](#language) { Auto, Afrikaans, Albanian, Amharic, ..., Zulu }                                       |
| enum | [**TranslationError**](#translation-error) { NoError, ParametersError, NetworkError, ServiceError, ParsingError } |

## Public Functions

| Return type                  | Data member                                                                                                                                                   |
|-----------------------------:|:--------------------------------------------------------------------------------------------------------------------------------------------------------------|
|                              | [**QOnlineTranslator**(QWidget *parent = nullptr)](#constructor)                                                                                              |
| void                         | [**translate**(const QString &text, Engine engine = Google, Language translationLang = Auto, Language sourceLang = Auto, Language uiLang = Auto)](#translate) |
| QList\<QMediaContent\>       | [**media**(const QString &text, Engine engine, Language language = Auto, Speaker speaker = Zahar, Emotion emotion = Neutral)](#media)                         |
| QList\<QMediaContent\>       | [**sourceMedia**(Engine engine, Speaker speaker = Zahar, Emotion emotion = Neutral)](#source-media)                                                           |
| QList\<QMediaContent\>       | [**translationMedia**(Engine engine, Speaker speaker = Zahar, Emotion emotion = Neutral)](#translation-media)                                                 |
| QString                      | [**source**()](#source)                                                                                                                                       |
| QString                      | [**sourceTranslit**()](#source-translit)                                                                                                                      |
| QString                      | [**sourceLanguageString**()](#source-language-string)                                                                                                         |
| Language                     | [**sourceLanguage**()](#source-language)                                                                                                                      |
| QString                      | [**translation**()](#translation)                                                                                                                             |
| QString                      | [**translationTranslit**()](translation-translit)                                                                                                             |
| QString                      | [**translationLanguageString**()](#translation-language-string)                                                                                               |
| Language                     | [**translationLanguage**()](#translation-language)                                                                                                            |
| QList\<QDictionary\>         | [**dictionaryList**()](#dictionary-list)                                                                                                                      |
| QList\<QDefinition\>         | [**definitionsList**()](#definitions-list)                                                                                                                    |
| TranslationError             | [**error**()](#error)                                                                                                                                         |
| QString                      | [**errorString**()](#error-string)                                                                                                                            |

## Static Public Members

| Return type | Data member                                               |
|------------:|:----------------------------------------------------------|
| QString     | [**languageString**(Language language)](#language-string) |
| QString     | [**languageCode**(Language language)](#language-code)     |
| Language    | [**language**(const QLocale &locale)](#language-1)        |
| Language    | [**language**(const QString &languageCode)](#language-2)  |

## Member Type Documentation

### <a id='engine'/> enum QOnlineTranslator::Engine

This enum has the following values:

| Constant                  | Value | Description                                                  |
|--------------------------:|:-----:|:-------------------------------------------------------------|
| QOnlineTranslator::Google | 0     | [**Google Translate**](https://translate.google.com/) engine |
| QOnlineTranslator::Yandex | 1     | [**Yandex.Translate**](https://translate.yandex.com/) engine |

### <a id='speaker'/> enum QOnlineTranslator::Speaker

This enum has the following values:

| Constant                  | Value | Description |
|--------------------------:|:-----:|:------------|
| QOnlineTranslator::Zahar  | 0     | Man voice   |
| QOnlineTranslator::Ermil  | 1     | Man voice   |
| QOnlineTranslator::Jane   | 2     | Woman voice |
| QOnlineTranslator::Oksana | 3     | Woman voice |
| QOnlineTranslator::Alyss  | 4     | Woman voice |
| QOnlineTranslator::Omazh  | 5     | Woman voice |

### <a id='emotion'/> enum QOnlineTranslator::Emotion

This enum has the following values:

| Constant                     | Value | Description              |
|-----------------------------:|:-----:|:-------------------------|
| QOnlineTranslator::Neutral   | 0     | Neutral voice            |
| QOnlineTranslator::Good      | 1     | Cheerful, friendly voice |
| QOnlineTranslator::Evil      | 2     | Irritated voice          |

### <a id='language'/> enum QOnlineTranslator::Language

This enum has the following values:

| Constant                     | Value |
|-----------------------------:|:-----:|
| QOnlineTranslator::NoLanguage | -1 |
| QOnlineTranslator::Auto | 0 |
| QOnlineTranslator::Afrikaans | 1 |
| QOnlineTranslator::Albanian | 2 |
| QOnlineTranslator::Amharic | 3 |
| QOnlineTranslator::Arabic | 4 |
| QOnlineTranslator::Armenian | 5 |
| QOnlineTranslator::Azeerbaijani | 6 |
| QOnlineTranslator::Basque | 7 |
| QOnlineTranslator::Bashkir | 8 |
| QOnlineTranslator::Belarusian | 9 |
| QOnlineTranslator::Bengali | 10 |
| QOnlineTranslator::Bosnian | 11 |
| QOnlineTranslator::Bulgarian | 12 |
| QOnlineTranslator::Catalan | 13 |
| QOnlineTranslator::Cebuano | 14 |
| QOnlineTranslator::SimplifiedChinese | 15 |
| QOnlineTranslator::TraditionalChinese | 16 |
| QOnlineTranslator::Corsican | 17 |
| QOnlineTranslator::Croatian | 18 |
| QOnlineTranslator::Czech | 19 |
| QOnlineTranslator::Danish | 20 |
| QOnlineTranslator::Dutch | 21 |
| QOnlineTranslator::English | 22 |
| QOnlineTranslator::Esperanto | 23 |
| QOnlineTranslator::Estonian | 24 |
| QOnlineTranslator::Finnish | 25 |
| QOnlineTranslator::French | 26 |
| QOnlineTranslator::Frisian | 27 |
| QOnlineTranslator::Galician | 28 |
| QOnlineTranslator::Georgian | 29 |
| QOnlineTranslator::German | 30 |
| QOnlineTranslator::Greek | 31 |
| QOnlineTranslator::Gujarati | 32 |
| QOnlineTranslator::HaitianCreole | 33 |
| QOnlineTranslator::Hausa | 34 |
| QOnlineTranslator::Hawaiian | 35 |
| QOnlineTranslator::Hebrew | 36 |
| QOnlineTranslator::HillMari | 37 |
| QOnlineTranslator::Hindi | 38 |
| QOnlineTranslator::Hmong | 39 |
| QOnlineTranslator::Hungarian | 40 |
| QOnlineTranslator::Icelandic | 41 |
| QOnlineTranslator::Igbo | 42 |
| QOnlineTranslator::Indonesian | 43 |
| QOnlineTranslator::Irish | 44 |
| QOnlineTranslator::Italian | 45 |
| QOnlineTranslator::Japanese | 46 |
| QOnlineTranslator::Javanese | 47 |
| QOnlineTranslator::Kannada | 48 |
| QOnlineTranslator::Kazakh | 49 |
| QOnlineTranslator::Khmer | 50 |
| QOnlineTranslator::Korean | 51 |
| QOnlineTranslator::Kurdish | 52 |
| QOnlineTranslator::Kyrgyz | 53 |
| QOnlineTranslator::Lao | 54 |
| QOnlineTranslator::Latin | 55 |
| QOnlineTranslator::Latvian | 56 |
| QOnlineTranslator::Lithuanian | 57 |
| QOnlineTranslator::Luxembourgish | 58 |
| QOnlineTranslator::Macedonian | 59 |
| QOnlineTranslator::Malagasy | 60 |
| QOnlineTranslator::Malay | 61 |
| QOnlineTranslator::Malayalam | 62 |
| QOnlineTranslator::Maltese | 63 |
| QOnlineTranslator::Maori | 64 |
| QOnlineTranslator::Marathi | 65 |
| QOnlineTranslator::Mari | 66 |
| QOnlineTranslator::Mongolian | 67 |
| QOnlineTranslator::Myanmar | 68 |
| QOnlineTranslator::Nepali | 69 |
| QOnlineTranslator::Norwegian | 70 |
| QOnlineTranslator::Chichewa | 71 |
| QOnlineTranslator::Papiamento | 72 |
| QOnlineTranslator::Pashto | 73 |
| QOnlineTranslator::Persian | 74 |
| QOnlineTranslator::Polish | 75 |
| QOnlineTranslator::Portuguese | 76 |
| QOnlineTranslator::Punjabi | 77 |
| QOnlineTranslator::Romanian | 78 |
| QOnlineTranslator::Russian | 79 |
| QOnlineTranslator::Samoan | 80 |
| QOnlineTranslator::ScotsGaelic | 81 |
| QOnlineTranslator::Serbian | 82 |
| QOnlineTranslator::Sesotho | 83 |
| QOnlineTranslator::Shona | 84 |
| QOnlineTranslator::Sindhi | 85 |
| QOnlineTranslator::Sinhala | 86 |
| QOnlineTranslator::Slovak | 87 |
| QOnlineTranslator::Slovenian | 88 |
| QOnlineTranslator::Somali | 89 |
| QOnlineTranslator::Spanish | 90 |
| QOnlineTranslator::Sundanese | 91 |
| QOnlineTranslator::Swahili | 92 |
| QOnlineTranslator::Swedish | 93 |
| QOnlineTranslator::Tagalog | 94 |
| QOnlineTranslator::Tajik | 95 |
| QOnlineTranslator::Tamil | 96 |
| QOnlineTranslator::Tatar | 97 |
| QOnlineTranslator::Telugu | 98 |
| QOnlineTranslator::Thai | 99 |
| QOnlineTranslator::Turkish | 100 |
| QOnlineTranslator::Udmurt | 101 |
| QOnlineTranslator::Ukrainian | 102  |
| QOnlineTranslator::Urdu | 103 |
| QOnlineTranslator::Uzbek | 104 |
| QOnlineTranslator::Vietnamese | 105 |
| QOnlineTranslator::Welsh | 106 |
| QOnlineTranslator::Xhosa | 107 |
| QOnlineTranslator::Yiddish | 108 |
| QOnlineTranslator::Yoruba | 109 |
| QOnlineTranslator::Zulu | 110 |

### <a id='translation-error'/> enum QOnlineTranslator::TranslationError

Indicates all possible error conditions found during the processing of the translation.

| Constant                             | Value | Description                                                  |
|-------------------------------------:|:-----:|:-------------------------------------------------------------|
| QOnlineTranslator::NoError           | 0     | No error condition	                                          |
| QOnlineTranslator::ParametersError   | 1     | Unsupported combination of backend and languages             |
| QOnlineTranslator::NetworkError      | 2     | Network error                                                |
| QOnlineTranslator::ServiceError      | 3     | Service unavailable or maximum number of requests            |
| QOnlineTranslator::ParsingError      | 4     | The request could not be parsed, please let me know about it |

## Member Function Documentation

### <a id='constructor'/> QOnlineTranslator::QOnlineTranslator(*QObject \*parent = nullptr*)
Constructs an translator with empty data and with parent object *parent*. You can use [translate()](#translate) to send text to object. The destructor of a parent object destroys all child objects. Setting parent to 0 constructs an object with no parent. The parent of an object may be viewed as the object's owner.
___

### <a id='translate'/> void QOnlineTranslator::translate(*const QString &text, Engine engine = Google, Language translationLang = Auto, Language sourceLang = Auto, Language uiLang = Auto*)
Parse *text* and translate with *engine* into *translationLang* from *sourceLang* with hints on *uiLang*.
___

### <a id='media'/> [QList](https://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QMediaContent](https://doc.qt.io/qt-5/qmediacontent.html "Qt Documentation")> QOnlineTranslator::media(*const QString &text, Engine engine, Language language = Auto, Speaker speaker = Zahar, Emotion emotion = Neutral*)
Splits *text* into parts (Google and Yandex have limits on the size of the request) and returns list with the generated API URLs to play this text on *language*. *speaker* and *emotion* arguments only affects the voice characteristics for Yandex engine.

Example:
```cpp
QMediaPlayer *player = new QMediaPlayer(this);
QMediaPlaylist *playlist = new QMediaPlaylist(player);

playlist->addMedia(QOnlineTranslator::media("Hello World!", QOnlineTranslator::Google));
player->setPlaylist(playlist);


player->play(); // Plays "Hello World!"

```
___

### <a id='source-media'/> [QList](https://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QMediaContent](https://doc.qt.io/qt-5/qmediacontent.html "Qt Documentation")> QOnlineTranslator::sourceMedia(*Engine engine, Speaker speaker = Zahar, Emotion emotion = Neutral*)
Splits the source text of translator into parts (Google and Yandex have limits on the size of the request) and returns list with the generated API URLs to play this text. *speaker* and *emotion* arguments only affects the voice characteristics for Yandex engine.

Example:
```cpp
QOnlineTranslator translator("Hello world!");

QMediaPlayer *player = new QMediaPlayer(this);
QMediaPlaylist *playlist = new QMediaPlaylist(player);

playlist->addMedia(translator.sourceMedia(QOnlineTranslator::Google));
player->setPlaylist(playlist);


player->play(); // Plays "Hello World!"

```
___

### <a id='translation-media'/> [QList](https://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QMediaContent](https://doc.qt.io/qt-5/qmediacontent.html "Qt Documentation")> QOnlineTranslator::translationMedia(*Engine engine, Speaker speaker = Zahar, Emotion emotion = Neutral*)
Splits the translation of translator into parts (Google and Yandex have limits on the size of the request) and returns list with the generated API URLs to play this text. *speaker* and *emotion* arguments only affects the voice characteristics for Yandex engine.
___

### <a id='source'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::source()
Returns source text.
___

### <a id='source-transliteration'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceTranslit()
Returns transliteration of source text. Google sends source transliteration only if source text is one word, otherwise function returns empty string.
___

### <a id='source-language-string'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceLanguage()
Returns name of source language.
___

### <a id='source-language'/> Language QOnlineTranslator::sourceLanguage()
Returns source language.
___

### <a id='translation'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translation()
Returns translated text.
___

### <a id='translation-translit'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translationTranslit()
Returns transliteration of translated text.
___

### <a id='translation-language-string'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translationLanguage()
Returns name of translation language.
___

### <a id='translation-language'/> Language QOnlineTranslator::translationLanguage()
Returns translation language.
___

### <a id='dictionary-list'/> [QList](http://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QDictionary](QDictionary.md "Class documentation")>  QOnlineTranslator::dictionaryList()
Returns a list of [QDictionary](QDictionary.md "Class documentation"). Read the class documentation for details.
___

### <a id='definitions-list'/> [QList](http://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QDefinition](QDefinition.md "Class documentation")>  QOnlineTranslator::definitionsList()
Returns a list of [QDefinition](QDefinition.md "Class documentation"). Read the class documentation for details.
___

### <a id='error'/> TranslationError QOnlineTranslator::error()
Returns the error that was found during the processing of last translation or tts. If no error was found, returns NoError. The text of the error can be obtained by [**errorString**()](#error-string).
___

### <a id='error-string'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::errorString()
Returns a human-readable description of the last translation or tts error that occurred.
___

### <a id='language-string'/> static [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::languageString(*Language language*)
Returns the *language* name.
___

### <a id='language-code'/> static [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::languageString(*Language language*)
Returns code of the *language*.
___

### <a id='language-1'/> static Language QOnlineTranslator::language(*const QLocale &locale*)
Returns [Language](#language) from *locale* object.
___

### <a id='language-2'/> static Language QOnlineTranslator::language(*const QString &languageCode*)
Returns [Language](#language) from ISO *languageCode*.
