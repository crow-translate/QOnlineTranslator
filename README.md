# QOnlineTranslator

[![GitHub (pre-)release](https://img.shields.io/github/release/Shatur95/QOnlineTranslator/all.svg)](https://github.com/Shatur95/QOnlineTranslator/releases)

The **QOnlineTranslator** library provides free usage of Google Translate API for **Qt5**.

## Contents

* [Installation](#installation)
* [Static Public Members](#static-public-members)
* [Public Functions](#public-functions)
* [Static Public Functions](#static-public-functions)
* [Detailed Description](#detailed-description)
* [Members Documentation](#members-documentation)
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

## Static Public Members

| Return type     | Data member                                       |
|----------------:|:--------------------------------------------------|
| QStringList     | [**LANGUAGE_NAMES**](#language-names)             |
| QStringList     | [**LANGUAGE_CODES**](#language-codes)             |

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

## Static Public Functions

| Return type | Function                                                                                                                                |
|------------:|:----------------------------------------------------------------------------------------------------------------------------------------|
| QString     | [**translateText**(const QString &text, QString translationLanguage = "auto", QString sourceLanguage = "auto")](#translate-text-static) |
| QString     | [**codeToLanguage**(const QString &code)](#code-to-language-static)                                                                     |
| QString     | [**languageToCode**(const QString &language)](#language-to-code-static)                                                                 |
| QString     | [**defaultLocaleToCode**()](#default-locale-to-code-static)                                                                             |
| QString     | [**media**(const QString &text, QString language = "auto")](#media)                                                                     |

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

## Members Documentation

### <a id='language-names'/> static [QStringList](http://doc.qt.io/qt-5/qstringlist.html "Qt Documentation") QOnlineTranslator::LANGUAGE_NAMES const
Provides language names that can be used for the text of buttons. See table [below](#languages-table).
___

### <a id='language-codes'/> static [QStringList](http://doc.qt.io/qt-5/qstringlist.html "Qt Documentation") QOnlineTranslator::LANGUAGE_CODES const
Provides language short codes that are used for the Google API. See table [below](#languages-table).
___

### <a id='languages-table'/> Members table of LANGUAGE_NAMES and LANGUAGE_CODES

| Index | LANGUAGE_NAMES       | LANGUAGE_CODES       | 
|:-----:|:--------------------:|:--------------------:|
| 1     | Automatically detect | auto                 |
| 2     | Afrikaans            | af                   |
| 3     | Amharic              | am                   |
| 4     | Arabic               | ar                   |
| 5     | Azerbaijani          | az                   |
| 6     | Belarusian           | be                   |
| 7     | Bulgarian            | bg                   |
| 8 | Bengali | bn |
| 9 | Bosnian | bs |
| 10 | Catalan | ca |
| 11 | Cebuano | ceb |
| 12 | Corsican | co |
| 13 | Czech | cs |
| 14 | Welsh | cy |
| 15 | Danish | da |
| 16 | German | de |
| 17 | Greek | el |
| 18 | English | en |
| 19 | Esperanto | eo |
| 20 | Spanish | es |
| 21 | Estonian | et |
| 22 | Basque | eu |
| 23 | Persian | fa |
| 24 | Finnish | fi |
| 25 | Fijian | fj |
| 26 | French | fr |
| 27 | Frisian | fy |
| 28 | Irish | ga |
| 29 | Scots Gaelic | gd |
| 30 | Galician | gl |
| 31 | Gujarati | gu |
| 32 | Hausa | ha |
| 33 | Hawaiian | haw |
| 34 | Hebrew | he |
| 35 | Hindi | hi |
| 36 | Hmong | hmn |
| 37 | Croatian | hr |
| 38 | Haitian Creole | ht |
| 39 | Hungarian | hu |
| 40 | Armenian | hy |
| 41 | Indonesian | id |
| 42 | Igbo | ig |
| 43 | Icelandic | is |
| 44 | Italian | it |
| 45 | Japanese | ja |
| 46 | Javanese | jv |
| 47 | Georgian | ka |
| 48 | Kazakh | kk |
| 49 | Khmer | km |
| 50 | Kannada | kn |
| 51 | Korean | ko |
| 52 | Kurdish | ku |
| 53 | Kyrgyz | ky |
| 54 | Latin | la |
| 55 | Luxembourgish | lb |
| 56 | Lao | lo |
| 57 | Lithuanian | lt |
| 58 | Latvian | lv |
| 59 | Malagasy | mg |
| 60 | Maori | mi |
| 61 | Macedonian | mk |
| 62 | Malayalam | ml |
| 63 | Mongolian | mn |
| 64 | Marathi | mr |
| 65 | Malay | ms |
| 66 | Maltese | mt |
| 67 | Hmong Daw | mww |
| 68 | Myanmar | my |
| 69 | Nepali | ne |
| 70 | Dutch | nl |
| 71 | Norwegian | no |
| 72 | Chichewa | ny |
| 73 | Querétaro Otomi | otq |
| 74 | Punjabi  | pa |
| 75 | Polish  | pl |
| 76 | Pashto | ps |
| 77 | Portuguese  | pt |
| 78 | Romanian  | ro |
| 79 | Russian  | ru |
| 80 | Sindhi | sd |
| 81 | Sinhala  | si |
| 82 | Slovak  | sk |
| 83 | Slovenian  | sl |
| 84 | Samoan | sm |
| 85 | Shona  | sn |
| 86 | Somali  | so |
| 87 | Albanian  | sq |
| 88 | Serbian | sr |
| 89 | Sesotho  | st |
| 90 | Sundanese  | su |
| 91 | Swedish | sv |
| 92 | Swahili  | sw |
| 93 | Tamil  | ta |
| 94 | Telugu  | te |
| 95 | Tajik | tg |
| 96 | Thai  | th |
| 97 | Filipino  | tl |
| 98 | Klingon  | tlh |
| 199 | Klingon (pIqaD) | tlh-qaak |
| 100 | Tongan  | to |
| 101 | Turkish  | tr |
| 102 | Tatar  | tt |
| 103 | Tahitian | ty |
| 104 | Udmurt  | udm |
| 105 | Ukrainian  | uk |
| 106 | Urdu  | ur |
| 107 | Uzbek | uz |
| 108 | Vietnamese  | vi |
| 109 | Xhosa  | xh |
| 110 | Yiddish  | yi |
| 111 | Yoruba | yo |
| 112 | Yucatec Maya  | yua |
| 113 | Cantonese  | yue |
| 114 | Chinese Simplified  | zh-cn |
| 115 | Chinese Traditional | zh-tw |
| 116 | Zulu | zu |

## Member Function Documentation

### <a id='c1'/> QOnlineTranslator::QOnlineTranslator(*QObject \*parent = nullptr*)
Constructs an object with empty data and with parent object *parent*. You can use [translate()](#translate) to send text to object. The destructor of a parent object destroys all child objects. Setting parent to 0 constructs an object with no parent. The parent of an object may be viewed as the object's owner.
___

### <a id='c2'/> QOnlineTranslator::QOnlineTranslator(*const QString &text, QString &translationLanguage = "auto", QString &sourceLanguage = "auto", QString &translatorLanguage = "auto", bool &autoCorrect = false, QObject \*parent = nullptr*)
Constructs an object initialized with the *text* translated into language of *translationLanguage* code from language of *sourceLanguage* code with hints on language of *translatorLanguage* code with parent object *parent*. Also Google try automatically correct grammatical errors and typos of *text* if *autoCorrect* is set to *true*. For languages see the column **LANGUAGE_CODES** in the table [above](#languages-table). The destructor of a parent object destroys all child objects. Setting parent to 0 constructs an object with no parent. The parent of an object may be viewed as the object's owner.
___

### <a id='translate'/> void QOnlineTranslator::translate(*const QString &text, QString &translationLanguage = "auto", QString &sourceLanguage = "auto", QString &translatorLanguage = "auto", bool &autoCorrect = false*)
Parse *text* and translate into language of *translationLanguage* code from language of *sourceLanguage* code with hints on language of *translatorLanguage* code and send data into object fields. Also Google try automatically correct grammatical errors and typos of *text* if *autoCorrect* is set to **true**. For languages see the column **LANGUAGE_CODES** in the table [above](#languages-table).
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
Returns `true` if could not get translation or `true` if translation received. The text of the error can be obtained by [**text**()](#text)
___

### <a id='translate-text-static'/> static [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translateText(*const QString &text, QString translationLanguage = "auto", QString sourceLanguage = "auto"*)
Returns the translated text from language of *sourceLanguage* code to language of *translationLanguage* code from the source *text*. For languages see the column **LANGUAGE_CODES** in the table [above](#languages-table).
___

### <a id='code-to-language-static'/> static [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::codeToLanguage(*const QString &code*)
Returns a [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") containing the language of *code*.
___

### <a id='language-to-code-static'/> static [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::languageToCode(*const QString &language*)
Returns a [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") containing the code of *language*.
___

### <a id='default-locale-to-code-static'/> static [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::defaultLocaleToCode()
Returns a [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") containing the code of the default [QLocale](https://doc.qt.io/qt-5/qlocale.html "Qt Documentation") language.
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
