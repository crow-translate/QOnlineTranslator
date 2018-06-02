# QOnlineTranslator

[![GitHub (pre-)release](https://img.shields.io/github/release/Shatur95/QOnlineTranslator/all.svg)](https://github.com/Shatur95/QOnlineTranslator/releases)

The **QOnlineTranslator** library provides free usage of Google Translate API for **Qt5**.

## Contents

* [Installation](#installation)
* [Public Functions](#public-functions)
* [Static Public Functions](#static-public-functions)
* [Detailed Description](#detailed-description)
* [Member Function Documentation](#member-function-documentation)

## Installation

To include the library files I would recommend that you add it as a git submodule to your project and include it's contents with a `.pri` file. For example, if you want to clone the library in `src/third-party/` in your project, use this command to clone with **ssh**:

`git submodule add git@github.com:Shatur95/QOnlineTranslator.git src/third-party/qonlinetranslator`

or this to clone with **https**:

`git submodule add https://github.com/Shatur95/QOnlineTranslator.git src/third-party/qonlinetranslator`

Then include the `qonlinetranslator.pri` file in your `.pro` project file:

`include(src/third-party/qonlinetranslator/qonlinetranslator.pri)`

**Header:**

```cpp
#include "qonlinetranslator.h"
```

**or:**

```cpp
#include <QOnlineTranslator>
```

## Public Functions

| Return type                         | Data member                                                                                                                                        |
|------------------------------------:|:---------------------------------------------------------------------------------------------------------------------------------------------------|
|                                     | [**QOnlineTranslator**(QWidget *parent = nullptr)](#c1)                                                                                            |
|                                     | [**QOnlineTranslator**(const QString &text, QString &translationLanguage = "auto", QString &sourceLanguage = "auto", QString &translatorLanguage = "auto", bool &autoCorrect = false, QObject *parent = nullptr)](#c2) |
| void                                | [**translate**(const QString &text, QString &translationLanguage = "auto", QString &sourceLanguage = "auto", QString &translatorLanguage = "auto", bool &autoCorrect = false)](#translate) |
| QList<QMediaContent>                | [**sourceMedia**()](#source-media)                                                                                                                 |
| QList<QMediaContent>                | [**translationMedia**()](#translation-media)                                                                                                       |
| QString                             | [**source**()](#source)                                                                                                                            |
| QString                             | [**sourceLanguage**()](#source-language)                                                                                                           |
| QString                             | [**sourceTranscription**()](#source-transcription)                                                                                                 |
| QString                             | [**translation**()](#translation)                                                                                                                  |
| QString                             | [**translationLanguage**()](#translation-language)                                                                                                 |
| QString                             | [**translationTranscription**()](translation-transcription)                                                                                        |
| QList<QPair<QString, QStringList> > | [**options**()](#options)                                                                                                                          |
| bool                                | [**error**()](#error)                                                                                                                              |
| QStringList                         | [**languages**(int index)](#languages-static)                                                                                                      |
| QStringList                         | [**codes**(int index)](#codes-static)                                                                                                              |
| QString                             | [**codeToLanguage**(const QString &code)](#code-to-language)                                                                                       |
| QString                             | [**languageToCode**(const QString &language)](#language-to-code)                                                                                   |

## Static Public Functions

| Return type          | Function                                                                                                                                |
|---------------------:|:----------------------------------------------------------------------------------------------------------------------------------------|
| QString              | [**defaultLocaleToCode**()](#default-locale-to-code-static)                                                                             |
| QString              | [**translateText**(const QString &text, QString translationLanguage = "auto", QString sourceLanguage = "auto")](#translate-text-static) |
| QList<QMediaContent> | [**media**(const QString &text, QString language = "auto")](#media)                                                                     |

## Detailed Description

The **QOnlineTranslator** uses the Google API URL to get the response, and then the parse the reply.

Example:
```cpp
QCoreApplication a(argc, argv); // Always need to create app instance for QEventLoop
...
QOnlineTranslator onlineTranslator("hello");
qInfo() << onlineTranslator.text; // Returns "hello" translated to the language of your system

onlineTranslator.translate("Hello world!", "de");
qInfo() << onlineTranslator.text; // Returns "Hello world!" translated into German
```

For real example of usage you can look into my other project: [Crow Translate](https://github.com/Shatur95/CrowTranslate "A simple and lightweight translator that allows to translate and say the selected text using the Google Translate API").

## Member Function Documentation

### <a id='c1'/> QOnlineTranslator::QOnlineTranslator(*QObject \*parent = nullptr*)
Constructs an object with empty data and with parent object *parent*. You can use [translate()](#translate) to send text to object. The destructor of a parent object destroys all child objects. Setting parent to 0 constructs an object with no parent. The parent of an object may be viewed as the object's owner.
___

### <a id='c2'/> QOnlineTranslator::QOnlineTranslator(*const QString &text, QString &translationLanguage = "auto", QString &sourceLanguage = "auto", QString &translatorLanguage = "auto", bool &autoCorrect = false, QObject \*parent = nullptr*)
Constructs an object initialized with the *text* translated into language of *translationLanguage* code from language of *sourceLanguage* code with hints on language of *translatorLanguage* code with parent object *parent*. Also Google try automatically correct grammatical errors and typos of *text* if *autoCorrect* is set to *true*. For languages see the column **Language code** in the table [above](#languages-table). The destructor of a parent object destroys all child objects. Setting parent to 0 constructs an object with no parent. The parent of an object may be viewed as the object's owner.
___

### <a id='translate'/> void QOnlineTranslator::translate(*const QString &text, QString &translationLanguage = "auto", QString &sourceLanguage = "auto", QString &translatorLanguage = "auto", bool &autoCorrect = false*)
Parse *text* and translate into language of *translationLanguage* code from language of *sourceLanguage* code with hints on language of *translatorLanguage* code and send data into object fields. Also Google try automatically correct grammatical errors and typos of *text* if *autoCorrect* is set to **true**. For languages see the column **Language code** in the table [above](#languages-table).
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
Returns the source text.
___

### <a id='source-language'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceLanguage()
Returns the source language of the translated text.
___

### <a id='source-transcription'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceTranscription()
Returns the transcription of the source text. Google sends source transcription only if the source text is one word, otherwise function returns empty string.
___

### <a id='translation'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translation()
Returns the translated text or text with network error.
___

### <a id='translation-language'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translationLanguage()
Returns the language to which the text is translated.
___

### <a id='translation-transcription'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translationTranscription()
Returns the transcription of the translated text.
___

### <a id='options'/> [QList](http://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QPair](http://doc.qt.io/qt-5/qpair.html "Qt Documentation")<[QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation"), [QStringList](http://doc.qt.io/qt-5/qstringlist.html "Qt Documentation")> >  QOnlineTranslator::options()
Returns a list of pairs whih translation options where the first element is a speech type, and the second is a list of strings with translation options for this type.

Example:

```cpp
QOnlineTranslator translator("say", "de", "en", "en"); // Translate "say" into German form English with English names of speech types
if (translator.error()) // Check for network error
    qDebug() << translator.text();
else {
    foreach (auto typeOfSpeech, translator.options()) {
        qInfo() << typeOfSpeech.first + ":";  // Output type of speech with a colon
        foreach (auto translationOptions, typeOfSpeech.second) {
            qInfo() << translationOptions; // Output translation option of this type (each received line already contains a colon after the first word)
        }
        qInfo() << "\r";
    }
}

/* Returns:
"verb:"
"sagen: say, tell, speak, mean, utter"
"sprechen: speak, talk, say, pronounce, militate, discourse"
"meinen: think, mean, believe, say, opine, fancy"
"heißen: mean, be called, be named, bid, tell, be titled"
"äußern: express, comment, speak, voice, say, utter"
"aussprechen: express, pronounce, say, speak, voice, enunciate"
"vorbringen: make, put forward, raise, say, put, bring forward"
"aufsagen: recite, say, speak"

"noun:"
"Sagen: say"
"Mitspracherecht: say"
*/
```
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
| 100 | Uzbek | uz |
| 101 | Vietnamese | vi |
| 102 | Welsh | cy |
| 103 | Xhosa | xh |
| 104 | Yiddish | yi |
| 105 | Yoruba | yo |
| 106 | Zulu | zu |
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

### <a id='translate-text-static'/> static [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translateText(*const QString &text, QString translationLanguage = "auto", QString sourceLanguage = "auto"*)
Returns the translated text from language of *sourceLanguage* code to language of *translationLanguage* code from the source *text*. For languages see the column **Language code** in the table [above](#languages-table).
___

### <a id='media-static'/> [QList](https://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QMediaContent](https://doc.qt.io/qt-5/qmediacontent.html "Qt Documentation")> QOnlineTranslator::media(*const QString &text, QString language = "auto"*)
Splits the *text* into parts (if required) and returns list with the generated API URLs with the language of *code* to play this text.
Google has a limit of up to 5000 characters per request. If the query is larger, then it will be splitted into several.

Example:
```cpp
QMediaPlayer *player = new QMediaPlayer(this);
QMediaPlaylist *playlist = new QMediaPlaylist(player);

playlist->addMedia(QOnlineTranslator::media("Hello World!"));
player->setPlaylist(playlist);


player->play(); // Plays "Hello World!"

```
