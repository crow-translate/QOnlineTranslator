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
| QStringList     | [**LANGUAGE_LONG_CODES**](#language-long-codes)   |
| QStringList     | [**LANGUAGE_SHORT_CODES**](#language-short-codes) |

## Public Functions

| Return type                         | Data member                                                                                                                                        |
|------------------------------------:|:---------------------------------------------------------------------------------------------------------------------------------------------------|
|                                     | [**QOnlineTranslator**()](#c1)                                                                                                                     |
|                                     | [**QOnlineTranslator**(const QString &text)](#c2)                                                                                                  |
|                                     | [**QOnlineTranslator**(const QString &text, const QString &targetLanguage)](#c3)                                                                   |
|                                     | [**QOnlineTranslator**(const QString &text, const QString &targetLanguage, const QString &sourceLanguage)](#c4)                                    |
|                                     | [**QOnlineTranslator**(const QString &text, const QString &targetLanguage, const QString &sourceLanguage, const QString &translatorLanguage)](#c5) |
|                                     | [**QOnlineTranslator**(const QString &text, const QString &targetLanguage, const QString &sourceLanguage, const QString &translatorLanguage, const bool &autoCorrect)](#c6) |
| void                                | [**translate**(const QString &text, QString &targetLanguage = "auto", QString &sourceLanguage = "auto", QString &translatorLanguage = "auto", bool &autoCorrect = false)](#translate) |
| void                                | [**say**()](#say)                                                                                                                                  |
| QString                             | [**text**()](#text)                                                                                                                                |
| QString                             | [**sourceLanguage**()](#source-language)                                                                                                           |
| QString                             | [**sourceTranscription**()](#source-transcription)                                                                                                 |
| QString                             | [**targetLanguage**()](#target-language)                                                                                                           |
| QString                             | [**targetTranscription**()](target-transcription)                                                                                                  |
| QList<QPair<QString, QStringList> > | [**options**()](#options)                                                                                                                          |

## Static Public Functions

| Return type | Function                                                                                                                                |
|------------:|:----------------------------------------------------------------------------------------------------------------------------------------|
| QString     | [**translateText**(const QString &text, QString targetLanguage = "auto", QString sourceLanguage = "auto")](#translate-text-static)      |
| void        | [**say**(const QString &text, QString language = "auto")](#say-static)                                                                  |

## Detailed Description

The **QOnlineTranslator** uses the Google API URL to get the response, and then the parse the reply.

Example:
```cpp
QCoreApplication a(argc, argv); // Always need to create app instance for QEventLoop
...
QOnlineTranslator onlineTranslator("hello");
qInfo() << onlineTranslator.text // Returns "hello" translated to the language of your system

onlineTranslator.translate("Hello world!", "de"); // Returns "Hello world!" translated into German
onlineTranslator.say(); // Speaks "Hello world!" in German

QString testString = "Microsoft must die"
QOnlineTranslator::say(testString) // Autodetects language of testString and speaks this string
```

For real example of usage you can look into my other project: [Crow Translate](https://github.com/Shatur95/CrowTranslate "A simple and lightweight translator that allows to translate and speak the selected text using the Google Translate API").

## Members Documentation

### <a id='language-names'/> static [QStringList](http://doc.qt.io/qt-5/qstringlist.html "Qt Documentation") QOnlineTranslator::LANGUAGE_NAMES const
Provides language names that can be used for the text of buttons. See table [below](#languages-table).
___

### <a id='language-long-codes'/> static [QStringList](http://doc.qt.io/qt-5/qstringlist.html "Qt Documentation") QOnlineTranslator::LANGUAGE_LONG_CODES const
Provides language long codes that can be used as arguments for console applications. See table [below](#languages-table).
___

### <a id='language-short-codes'/> static [QStringList](http://doc.qt.io/qt-5/qstringlist.html "Qt Documentation") QOnlineTranslator::LANGUAGE_SHORT_CODES const
Provides language short codes that are used for the Google API. See table [below](#languages-table).
___

### <a id='languages-table'/> Members table of LANGUAGE_NAMES, LANGUAGE_LONG_CODES and LANGUAGE_SHORT_CODES

| Index | LANGUAGE_NAMES       | LANGUAGE_LONG_CODES | LANGUAGE_SHORT_CODES | 
|:-----:|:--------------------:|:-------------------:|:--------------------:|
| 1     | Automatically detect | automatic           | auto                 |
| 2     | Afrikaans            | afrikaans           | af                   |
| 3     | Amharic              | amharic             | am                   |
| 4     | Arabic               | arabic              | ar                   |
| 5     | Azerbaijani          | azerbaijani         | az                   |
| 6     | Belarusian           | belarusian          | be                   |
| 7     | Bulgarian            | bulgarian           | bg                   |
| 8 | Bengali | bengali | bn |
| 9 | Bosnian | bosnian | bs |
| 10 | Catalan | catalan | ca |
| 11 | Cebuano | cebuano | ceb |
| 12 | Corsican | corsican | co |
| 13 | Czech | czech | cs |
| 14 | Welsh | welsh | cy |
| 15 | Danish | danish | da |
| 16 | German | german | de |
| 17 | Greek | greek | el |
| 18 | English | english | en |
| 19 | Esperanto | esperanto | eo |
| 20 | Spanish | spanish | es |
| 21 | Estonian | estonian | et |
| 22 | Basque | basque | eu |
| 23 | Persian | persian | fa |
| 24 | Finnish | finnish | fi |
| 25 | Fijian | fijian | fj |
| 26 | French | french | fr |
| 27 | Frisian | frisian | fy |
| 28 | Irish | irish | ga |
| 29 | Scots Gaelic  | scots-gaelic | gd |
| 30 | Galician  | galician | gl |
| 31 | Gujarati  | gujarati | gu |
| 32 | Hausa | hausa | ha |
| 33 | Hawaiian  | hawaiian | haw |
| 34 | Hebrew  | hebrew | he |
| 35 | Hindi  | hindi | hi |
| 36 | Hmong | hmong | hmn |
| 37 | Croatian  | croatian | hr |
| 38 | Haitian Creole  | haitian-creole | ht |
| 39 | Hungarian  | hungarian | hu |
| 40 | Armenian | armenian | hy |
| 41 | Indonesian  | indonesian | id |
| 42 | Igbo  | igbo | ig |
| 43 | Icelandic  | icelandic | is |
| 44 | Italian | italian | it |
| 45 | Japanese  | japanese | ja |
| 46 | Javanese  | javanese | jv |
| 47 | Georgian  | georgian | ka |
| 48 | Kazakh | kazakh | kk |
| 49 | Khmer  | khmer | km |
| 50 | Kannada  | kannada | kn |
| 51 | Korean  | korean | ko |
| 52 | Kurdish | kurdish | ku |
| 53 | Kyrgyz  | kyrgyz | ky |
| 54 | Latin  | latin | la |
| 55 | Luxembourgish  | luxembourgish | lb |
| 56 | Lao | lao | lo |
| 57 | Lithuanian  | lithuanian | lt |
| 58 | Latvian  | latvian | lv |
| 59 | Malagasy  | malagasy | mg |
| 60 | Maori | maori | mi |
| 61 | Macedonian  | macedonian | mk |
| 62 | Malayalam  | malayalam | ml |
| 63 | Mongolian  | mongolian | mn |
| 64 | Marathi | marathi | mr |
| 65 | Malay  | malay | ms |
| 66 | Maltese  | maltese | mt |
| 67 | Hmong Daw  | hmong-daw | mww |
| 68 | Myanmar | myanmar | my |
| 69 | Nepali  | nepali | ne |
| 70 | Dutch  | dutch | nl |
| 71 | Norwegian  | norwegian | no |
| 72 | Chichewa   | chichewa | ny |
| 73 | Querétaro Otomi  | querétaro-otomi | otq |
| 74 | Punjabi  | punjabi | pa |
| 75 | Polish  | polish | pl |
| 76 | Pashto | pashto | ps |
| 77 | Portuguese  | portuguese | pt |
| 78 | Romanian  | romanian | ro |
| 79 | Russian  | russian | ru |
| 80 | Sindhi | sindhi | sd |
| 81 | Sinhala  | sinhala | si |
| 82 | Slovak  | slovak | sk |
| 83 | Slovenian  | slovenian | sl |
| 84 | Samoan | samoan | sm |
| 85 | Shona  | shona | sn |
| 86 | Somali  | somali | so |
| 87 | Albanian  | albanian | sq |
| 88 | Serbian (Cyrillic) | serbian-cyrillic | sr-cyrl |
| 89 | Serbian (Latin)  | serbian-latin | sr-latn |
| 90 | Sesotho  | sesotho | st |
| 91 | Sundanese  | sundanese | su |
| 92 | Swedish | swedish | sv |
| 93 | Swahili  | swahili | sw |
| 94 | Tamil  | tamil | ta |
| 95 | Telugu  | telugu | te |
| 96 | Tajik | tajik | tg |
| 97 | Thai  | thai | th |
| 98 | Filipino  | filipino | tl |
| 99 | Klingon  | klingon | tlh |
| 100 | Klingon (pIqaD) | klingon-piqad | tlh-qaak |
| 101 | Tongan  | tongan | to |
| 102 | Turkish  | turkish | tr |
| 103 | Tatar  | tatar | tt |
| 104 | Tahitian | tahitian | ty |
| 105 | Udmurt  | udmurt | udm |
| 106 | Ukrainian  | ukrainian | uk |
| 107 | Urdu  | urdu | ur |
| 108 | Uzbek | uzbek | uz |
| 109 | Vietnamese  | vietnamese | vi |
| 110 | Xhosa  | xhosa | xh |
| 111 | Yiddish  | yiddish | yi |
| 112 | Yoruba | yoruba | yo |
| 113 | Yucatec Maya  | yucatec-maya | yua |
| 114 | Cantonese  | cantonese | yue |
| 115 | Chinese Simplified  | chinese-simplified | zh-cn |
| 116 | Chinese Traditional | chinese-traditional | zh-tw |
| 117 | Zulu | zulu | zu |

## Member Function Documentation

### <a id='c1'/> QOnlineTranslator::QOnlineTranslator()
Constructs an object with empty data. You can use [translate](#translate) to send text to object.
___

### <a id='c2'/> QOnlineTranslator::QOnlineTranslator(*const QString &text*)
Constructs an object initialized with the *text* translated into system languge from autodetected languge by Google with hints on system language. For languages see the column **LANGUAGE_SHORT_CODES** in the table [above](#languages-table).
___

### <a id='c3'/> QOnlineTranslator::QOnlineTranslator(*const QString &text, const QString &targetLanguage*)
Constructs an object initialized with the *text* translated into language of *targetLanguage* code from autodetected languge by Google with hints on system language. For languages see the column **LANGUAGE_SHORT_CODES** in the table [above](#languages-table).
___

### <a id='c4'/> QOnlineTranslator::QOnlineTranslator(*const QString &text, const QString &targetLanguage, const QString &sourceLanguage*)
Constructs an object initialized with the *text* translated into language of *targetLanguage* code from language of *sourceLanguage* code with hints on system language. For languages see the column **LANGUAGE_SHORT_CODES** in the table [above](#languages-table).
___

### <a id='c5'/> QOnlineTranslator::QOnlineTranslator(*const QString &text, const QString &targetLanguage, const QString &sourceLanguage, const QString &translatorLanguage*)
Constructs an object initialized with the *text* translated into language of *targetLanguage* code from language of *sourceLanguage* code with hints on language of *translatorLanguage* code. For languages see the column **LANGUAGE_SHORT_CODES** in the table [above](#languages-table).
___

### <a id='c6'/> QOnlineTranslator::QOnlineTranslator(*const QString &text, const QString &targetLanguage, const QString &sourceLanguage, const QString &translatorLanguage, const bool &autoCorrect*)
Constructs an object initialized with the *text* translated into language of *targetLanguage* code from language of *sourceLanguage* code with hints on language of *translatorLanguage* code. Also Google try automatically correct grammatical errors and typos of *text* if *autoCorrect* is set to **true**. For languages see the column **LANGUAGE_SHORT_CODES** in the table [above](#languages-table).
___

### <a id='translate'/> void QOnlineTranslator::translate(*const QString &text, QString &targetLanguage = "auto", QString &sourceLanguage = "auto", QString &translatorLanguage = "auto", bool &autoCorrect = false*)
Parse *text* and translate into language of *targetLanguage* code from language of *sourceLanguage* code with hints on language of *translatorLanguage* code and send data into object fields. Also Google try automatically correct grammatical errors and typos of *text* if *autoCorrect* is set to **true**. For languages see the column **LANGUAGE_SHORT_CODES** in the table [above](#languages-table).
___

### <a id='say'/> void QOnlineTranslator::say()
Speaks translated text from the object using [QMediaPlayer](http://doc.qt.io/qt-5/qmediaplayer.html "Qt Documentation").
___

### <a id='text'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::text()
Returns the translated text.
___

### <a id='source-language'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceLanguage()
Returns the source language of the translated text.
___

### <a id='source-transcription'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceTranscription()
Returns the transcription of the source text. Google sends source transcription only if the source text is one word, otherwise function returns empty string.
___

### <a id='target-language'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::targetLanguage()
Returns the language to which the text is translated.
___

### <a id='target-transcription'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::targetTranscription()
Returns the transcription of the translated text.
___

### <a id='options'/> [QList](http://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QPair](http://doc.qt.io/qt-5/qpair.html "Qt Documentation")<[QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation"), [QStringList](http://doc.qt.io/qt-5/qstringlist.html "Qt Documentation")> >  QOnlineTranslator::options()
Returns a list of pairs whih translation options where the first element is a speech type, and the second is a list of strings with translation options for this type.

Example:

```cpp
QOnlineTranslator translator("say", "de", "en", "en"); // Translate "say" into German form English with English names of speech types
foreach (auto typeOfSpeech, translator.options()) {
    qInfo() << typeOfSpeech.first + ":";  // Output type of speech with a colon
    foreach (auto translationOptions, typeOfSpeech.second) {
        qInfo() << translationOptions; // Output translation option of this type (each received line already contains a colon after the first word)
    }
    qInfo() << "\r";
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

### <a id='translate-text-static'/> static void QOnlineTranslator::translateText(*const QString &text, QString targetLanguage = "auto", QString sourceLanguage = "auto"*)
Returns the translated text from language of *sourceLanguage* code to language of *targetLanguage* code from the source *text*. For languages see the column **LANGUAGE_SHORT_CODES** in the table [above](#languages-table).
___

### <a id='say-static'/> static void QOnlineTranslator::say(*const QString &text, QString language = "auto"*)
Speaks *text* in the language of *language* code using [QMediaPlayer](http://doc.qt.io/qt-5/qmediaplayer.html "Qt Documentation"). Works faster if the language of *text* is specified. For languages see the column **LANGUAGE_SHORT_CODES** in the table [above](#languages-table).
