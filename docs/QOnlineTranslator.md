# QOnlineTranslator

The **QOnlineTranslator** class provides translation data.

## Content

* [Public Functions](#public-functions)
* [Static Public Functions](#static-public-functions)
* [Member Function Documentation](#member-function-documentation)

## Public Functions

| Return type                  | Data member                                                                                                                                        |
|-----------------------------:|:---------------------------------------------------------------------------------------------------------------------------------------------------|
|                              | [**QOnlineTranslator**(QWidget *parent = nullptr)](#c1)                                                                                            |
|                              | [**QOnlineTranslator**(const QString &text, QString &translationLanguageCode = "auto", QString &sourceLanguageCode = "auto", QString &translatorLanguageCode = "auto", bool &autoCorrect = false, QObject *parent = nullptr)](#c2) |
| void                         | [**translate**(const QString &text, QString &translationLanguageCode = "auto", QString &sourceLanguageCode = "auto", QString &translatorLanguageCode = "auto", bool &autoCorrect = false)](#translate) |
| QList\<QMediaContent\>       | [**sourceMedia**()](#source-media)                                                                                                                 |
| QList\<QMediaContent\>       | [**translationMedia**()](#translation-media)                                                                                                       |
| QString                      | [**source**()](#source)                                                                                                                            |
| QString                      | [**sourceLanguageCode**()](#source-language-code)                                                                                                  |
| QString                      | [**sourceTranscription**()](#source-transcription)                                                                                                 |
| QString                      | [**translation**()](#translation)                                                                                                                  |
| QString                      | [**translationLanguageCode**()](#translation-language-code)                                                                                        |
| QString                      | [**translationTranscription**()](translation-transcription)                                                                                        |
| QList\<QTranslationOptions\> | [**translationOptionsList**()](#translation-options-list)                                                                                          |
| QList\<QDefinition\>         | [**definitionsList**()](#definitions-list)                                                                                                         |
| bool                         | [**error**()](#error)                                                                                                                              |
| QStringList                  | [**languages**(int index)](#languages-static)                                                                                                      |
| QStringList                  | [**codes**(int index)](#codes-static)                                                                                                              |
| QString                      | [**codeToLanguage**(const QString &code)](#code-to-language)                                                                                       |
| QString                      | [**languageToCode**(const QString &language)](#language-to-code)                                                                                   |

## Static Public Functions

| Return type          | Function                                                                                                                                        |
|---------------------:|:------------------------------------------------------------------------------------------------------------------------------------------------|
| QString              | [**defaultLocaleToCode**()](#default-locale-to-code-static)                                                                                     |
| QString              | [**translateText**(const QString &text, QString translationLanguageCode = "auto", QString sourceLanguageCode = "auto")](#translate-text-static) |
| QList<QMediaContent> | [**media**(const QString &text, QString language = "auto")](#media)                                                                             |

## Member Function Documentation

### <a id='c1'/> QOnlineTranslator::QOnlineTranslator(*QObject \*parent = nullptr*)
Constructs an object with empty data and with parent object *parent*. You can use [translate()](#translate) to send text to object. The destructor of a parent object destroys all child objects. Setting parent to 0 constructs an object with no parent. The parent of an object may be viewed as the object's owner.
___

### <a id='c2'/> QOnlineTranslator::QOnlineTranslator(*const QString &text, QString &translationLanguageCode = "auto", QString &sourceLanguageCode = "auto", QString &translatorLanguageCode = "auto", bool &autoCorrect = false, QObject \*parent = nullptr*)
Constructs an object initialized with the *text* translated into language of *translationLanguageCode* from language of *sourceLanguageCode* with hints on language of *translatorLanguageCode* with parent object *parent*. Also Google try automatically correct grammatical errors and typos of *text* if *autoCorrect* is set to *true*. For languages see the column **Language code** in the table [above](#languages-table). The destructor of a parent object destroys all child objects. Setting parent to 0 constructs an object with no parent. The parent of an object may be viewed as the object's owner.
___

### <a id='translate'/> void QOnlineTranslator::translate(*const QString &text, QString &translationLanguageCode = "auto", QString &sourceLanguageCode = "auto", QString &translatorLanguageCode = "auto", bool &autoCorrect = false*)
Parse *text* and translate into language of *translationLanguageCode* from language of *sourceLanguageCode* with hints on language of *translatorLanguageCode* and send data into object fields. Also Google try automatically correct grammatical errors and typos of *text* if *autoCorrect* is set to **true**. For languages see the column **Language code** in the table [above](#languages-table).
___

### <a id='source-media'/> [QList](https://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QMediaContent](https://doc.qt.io/qt-5/qmediacontent.html "Qt Documentation")> QOnlineTranslator::sourceMedia()
Splits the source text into parts (if required) and returns list with the generated API URLs to play this text. Google has a limit of up to 5000 characters per request. If the query is larger, then it will be splitted into several.

Example:
```cpp
QOnlineTranslator translator("Hello world!");

QMediaPlayer *player = new QMediaPlayer(this);
QMediaPlaylist *playlist = new QMediaPlaylist(player);

playlist->addMedia(translator.sourceMedia());
player->setPlaylist(playlist);


player->play(); // Plays "Hello World!"

```
___

### <a id='translation-media'/> [QList](https://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QMediaContent](https://doc.qt.io/qt-5/qmediacontent.html "Qt Documentation")> QOnlineTranslator::translationMedia()
Splits the translation into parts (if required) and returns list with the generated API URLs to play this text.
Google has a limit of up to 5000 characters per request. If the query is larger, then it will be splitted into several.
___

### <a id='source'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::source()
Returns source text.
___

### <a id='source-language-code'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceLanguageCode()
Returns source language code of translated text.
___

### <a id='source-language'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceLanguage()
Returns a language that matches code of source language.
___

### <a id='source-transcription'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceTranscription()
Returns transcription of source text. Google sends source transcription only if source text is one word, otherwise function returns empty string.
___

### <a id='translation'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translation()
Returns translated text or text with network error.
___

### <a id='translation-language-code'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translationLanguageCode()
Returns language to which text is translated.
___

### <a id='translation-language'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translationLanguage()
Returns a language that matches code of translation language.
___

### <a id='translation-transcription'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translationTranscription()
Returns transcription of translated text.
___

### <a id='translation-options-list'/> [QList](http://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QTranslationOptions](QTranslationOptions.md "Class documentation")>  QOnlineTranslator::translationOptionsList()
Returns a list of [QTranslationOptions](QTranslationOptions.md "Class documentation"). Read the class documentation for details.
___

### <a id='definitions-list'/> [QList](http://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QDefinition](QDefinition.md "Class documentation")>  QOnlineTranslator::definitionsList()
Returns a list of [QDefinition](QDefinition.md "Class documentation"). Read the class documentation for details.
___

### <a id='error'/> bool QOnlineTranslator::error()
Returns `true` if could not get translation or `true` if translation received. The text of the error can be obtained by [**text**()](#text).
___

### <a id='languages-static'/> static [QStringList](http://doc.qt.io/qt-5/qstringlist.html "Qt Documentation") QOnlineTranslator::languages()
Returns the list of languages names. See the column **Language name** in the table [below](#languages-table).
___

### <a id='codes-static'/> static [QStringList](http://doc.qt.io/qt-5/qstringlist.html "Qt Documentation") QOnlineTranslator::codes()
Returns the list of language code. See the column **Language code** in the table [below](#languages-table).
___

### <a id='languages-table'/> Languages

| Index | Language name        | Language code        | 
|:-----:|:--------------------:|:--------------------:|
| 0     | Automatically detect | auto                 |
| 1 | Afrikaans | af |
| 2 | Albanian | sq |
| 3 | Amharic | am |
| 4 | Arabic | ar |
| 5 | Armenian | hy |
| 6 | Azeerbaijani | az |
| 7 | Basque | eu |
| 8 | Belarusian | be |
| 9 | Bengali | bn |
| 10 | Bosnian | bs |
| 11 | Bulgarian | bg |
| 12 | Catalan | ca |
| 13 | Cebuano | ceb |
| 14 | Chinese(Simplified) | zh-CN |
| 15 | Chinese(Traditional) | zh-TW |
| 16 | Corsican | co |
| 17 | Croatian | hr |
| 18 | Czech | cs |
| 19 | Danish | da |
| 20 | Dutch | nl |
| 21 | English | en |
| 22 | Esperanto | eo |
| 23 | Estonian | et |
| 24 | Finnish | fi |
| 25 | French | fr |
| 26 | Frisian | fy |
| 27 | Galician | gl |
| 28 | Georgian | ka |
| 29 | German | de |
| 30 | Greek | el |
| 31 | Gujarati | gu |
| 32 | HaitianCreole | ht |
| 33 | Hausa | ha |
| 34 | Hawaiian | haw |
| 35 | Hebrew | iw |
| 36 | Hindi | hi |
| 37 | Hmong | hmn |
| 38 | Hungarian | hu |
| 39 | Icelandic | is |
| 40 | Igbo | ig |
| 41 | Indonesian | id |
| 42 | Irish | ga |
| 43 | Italian | it |
| 44 | Japanese | ja |
| 45 | Javanese | jw |
| 46 | Kannada | kn |
| 47 | Kazakh | kk |
| 48 | Khmer | km |
| 49 | Korean | ko |
| 50 | Kurdish | ku |
| 51 | Kyrgyz | ky |
| 52 | Lao | lo |
| 53 | Latin | la |
| 54 | Latvian | lv |
| 55 | Lithuanian | lt |
| 56 | Luxembourgish | lb |
| 57 | Macedonian | mk |
| 58 | Malagasy | mg |
| 59 | Malay | ms |
| 60 | Malayalam | ml |
| 61 | Maltese | mt |
| 62 | Maori | mi |
| 63 | Marathi | mr |
| 64 | Mongolian | mn |
| 65 | Myanmar | my |
| 66 | Nepali | ne |
| 67 | Norwegian | no |
| 68 | Chichewa | ny |
| 69 | Pashto | ps |
| 70 | Persian | fa |
| 71 | Polish | pl |
| 72 | Portuguese | pt |
| 73 | Punjabi | pa |
| 74 | Romanian | ro |
| 75 | Russian | ru |
| 76 | Samoan | sm |
| 77 | ScotsGaelic | gd |
| 78 | Serbian | sr |
| 79 | Sesotho | st |
| 80 | Shona | sn |
| 81 | Sindhi | sd |
| 82 | Sinhala | si |
| 83 | Slovak | sk |
| 84 | Slovenian | sl |
| 85 | Somali | so |
| 86 | Spanish | es |
| 87 | Sundanese | su |
| 88 | Swahili | sw |
| 89 | Swedish | sv |
| 90 | Tagalog | tl |
| 91 | Tajik | tg |
| 92 | Tamil | ta |
| 93 | Telugu | te |
| 94 | Thai | th |
| 95 | Turkish | tr |
| 96 | Ukrainian | uk |
| 97 | Urdu | ur |
| 98 | Uzbek | uz |
| 99 | Vietnamese | vi |
| 100 | Welsh | cy |
| 101 | Xhosa | xh |
| 102 | Yiddish | yi |
| 103 | Yoruba | yo |
| 104 | Zulu | zu |
---

### <a id='code-to-language'/> static [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::codeToLanguage(*const QString &code*)
Returns a [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") containing the language of *code*.
---

### <a id='language-to-code'/> static [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::codeToLanguage(*const QString &language*)
Returns a [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") containing the code of *language*.
---

### <a id='default-locale-to-code-static'/> static [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::defaultLocaleToCode()
Returns a [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") containing the code of the default [QLocale](https://doc.qt.io/qt-5/qlocale.html "Qt Documentation") language.
___

### <a id='translate-text-static'/> static [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translateText(*const QString &text, QString translationLanguageCode = "auto", QString sourceLanguageCode = "auto"*)
Returns the translated text from language of *sourceLanguageCode* to language of *translationLanguageCode* from the source *text*. For languages see the column **Language code** in the table [above](#languages-table).
___

### <a id='media-static'/> [QList](https://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QMediaContent](https://doc.qt.io/qt-5/qmediacontent.html "Qt Documentation")> QOnlineTranslator::media(*const QString &text, QString languageCode = "auto"*)
Splits the *text* into parts (if required) and returns list with the generated API URLs with the language of *languageCode* to play this text.
Google has a limit of up to 5000 characters per request. If the query is larger, then it will be splitted into several.

Example:
```cpp
QMediaPlayer *player = new QMediaPlayer(this);
QMediaPlaylist *playlist = new QMediaPlaylist(player);

playlist->addMedia(QOnlineTranslator::media("Hello World!"));
player->setPlaylist(playlist);


player->play(); // Plays "Hello World!"

```
