# QOnlineTranslator

The **QOnlineTranslator** class provides translation data.

## Content

-   [Public Types](#public-types)
-   [Public Functions](#public-functions)
-   [Static Public Members](#static-public-member)
-   [Member Type Documentation](#member-type-documentation)
-   [Member Function Documentation](#member-function-documentation)

## Public Types

| Type | Name                                                                                                              |
| ---: | :---------------------------------------------------------------------------------------------------------------- |
| enum | [**Engine**](#engine) { Google, Yandex }                                                                          |
| enum | [**Voice**](#voice) { Zahar, Ermil, Jane, Oksana, ..., Female }                                                   |
| enum | [**Emotion**](#emotion) { Good, Evil, Neutral }                                                                   |
| enum | [**Language**](#language) { Auto, Afrikaans, Albanian, Amharic, ..., Zulu }                                       |
| enum | [**TranslationError**](#translation-error) { NoError, ParametersError, NetworkError, ServiceError, ParsingError } |

## Public Functions

|               Return type | Data member                                                                                                                                                   |
| ------------------------: | :------------------------------------------------------------------------------------------------------------------------------------------------------------ |
|                           | [**QOnlineTranslator**(QWidget \*parent = nullptr)](#constructor)                                                                                             |
|                      void | [**translate**(const QString &text, Engine engine = Google, Language translationLang = Auto, Language sourceLang = Auto, Language uiLang = Auto)](#translate) |
| QList\\&lt;QMediaContent> | [**media**(const QString &text, Engine engine, Language language = Auto, Voice voice = Default, Emotion emotion = Neutral)](#media)                           |
| QList\\&lt;QMediaContent> | [**sourceMedia**(Engine engine, Voice voice = Default, Emotion emotion = Neutral)](#source-media)                                                             |
| QList\\&lt;QMediaContent> | [**translationMedia**(Engine engine, Voice voice = Default, Emotion emotion = Neutral)](#translation-media)                                                   |
|                   QString | [**source**()](#source)                                                                                                                                       |
|                   QString | [**sourceTranslit**()](#source-translit)                                                                                                                      |
|                   QString | [**sourceTranscription**()](source-transcription)                                                                                                             |
|                   QString | [**sourceLanguageString**()](#source-language-string)                                                                                                         |
|                  Language | [**sourceLanguage**()](#source-language)                                                                                                                      |
|                   QString | [**translation**()](#translation)                                                                                                                             |
|                   QString | [**translationTranslit**()](translation-translit)                                                                                                             |
|                   QString | [**translationLanguageString**()](#translation-language-string)                                                                                               |
|                  Language | [**translationLanguage**()](#translation-language)                                                                                                            |
|   QList\\&lt;QDictionary> | [**dictionaryList**()](#dictionary-list)                                                                                                                      |
|   QList\\&lt;QDefinition> | [**definitionsList**()](#definitions-list)                                                                                                                    |
|          TranslationError | [**error**()](#error)                                                                                                                                         |
|                   QString | [**errorString**()](#error-string)                                                                                                                            |

## Static Public Members

| Return type | Data member                                               |
| ----------: | :-------------------------------------------------------- |
|     QString | [**languageString**(Language language)](#language-string) |
|     QString | [**languageCode**(Language language)](#language-code)     |
|    Language | [**language**(const QLocale &locale)](#language-1)        |
|    Language | [**language**(const QString &languageCode)](#language-2)  |

## Member Type Documentation

### <a id='engine'/> enum QOnlineTranslator::Engine

This enum has the following values:

|                  Constant | Value | Description                                                         |
| ------------------------: | :---: | :------------------------------------------------------------------ |
| QOnlineTranslator::Google |   0   | [Google Translate](https://translate.google.com) engine             |
| QOnlineTranslator::Yandex |   1   | [Yandex.Translate](https://translate.yandex.com) engine             |
|   QOnlineTranslator::Bing |   2   | [Bing Microsoft Translator](https://www.bing.com/translator) engine |

### <a id='voice'/> enum QOnlineTranslator::Voice

This enum has the following values:

|                   Constant | Value | Engine               |
| -------------------------: | :---: | :------------------- |
| QOnlineTranslator::Default |   0   | Google, Yandex, Bing |
|   QOnlineTranslator::Zahar |   1   | Yandex               |
|   QOnlineTranslator::Ermil |   2   | Yandex               |
|    QOnlineTranslator::Jane |   3   | Yandex               |
|  QOnlineTranslator::Oksana |   4   | Yandex               |
|   QOnlineTranslator::Alyss |   5   | Yandex               |
|   QOnlineTranslator::Omazh |   6   | Yandex               |
|    QOnlineTranslator::Male |   7   | Bing                 |
|  QOnlineTranslator::Female |   8   | Bing                 |

### <a id='emotion'/> enum QOnlineTranslator::Emotion

This enum has the following values:

|                   Constant | Value | Description              |
| -------------------------: | :---: | :----------------------- |
| QOnlineTranslator::Neutral |   0   | Neutral voice            |
|    QOnlineTranslator::Good |   1   | Cheerful, friendly voice |
|    QOnlineTranslator::Evil |   2   | Irritated voice          |

### <a id='language'/> enum QOnlineTranslator::Language

This enum has the following values:

|                              Constant | Value |
| ------------------------------------: | :---: |
|         QOnlineTranslator::NoLanguage |   -1  |
|               QOnlineTranslator::Auto |   0   |
|          QOnlineTranslator::Afrikaans |   1   |
|           QOnlineTranslator::Albanian |   2   |
|            QOnlineTranslator::Amharic |   3   |
|             QOnlineTranslator::Arabic |   4   |
|           QOnlineTranslator::Armenian |   5   |
|       QOnlineTranslator::Azeerbaijani |   6   |
|             QOnlineTranslator::Basque |   7   |
|            QOnlineTranslator::Bashkir |   8   |
|         QOnlineTranslator::Belarusian |   9   |
|            QOnlineTranslator::Bengali |   10  |
|            QOnlineTranslator::Bosnian |   11  |
|          QOnlineTranslator::Bulgarian |   12  |
|            QOnlineTranslator::Catalan |   13  |
|          QOnlineTranslator::Cantonese |   14  |
|            QOnlineTranslator::Cebuano |   15  |
|  QOnlineTranslator::SimplifiedChinese |   16  |
| QOnlineTranslator::TraditionalChinese |   17  |
|           QOnlineTranslator::Corsican |   18  |
|           QOnlineTranslator::Croatian |   19  |
|              QOnlineTranslator::Czech |   20  |
|             QOnlineTranslator::Danish |   21  |
|              QOnlineTranslator::Dutch |   22  |
|            QOnlineTranslator::English |   23  |
|          QOnlineTranslator::Esperanto |   24  |
|           QOnlineTranslator::Estonian |   25  |
|             QOnlineTranslator::Fijian |   26  |
|           QOnlineTranslator::Filipino |   27  |
|            QOnlineTranslator::Finnish |   28  |
|             QOnlineTranslator::French |   29  |
|            QOnlineTranslator::Frisian |   30  |
|           QOnlineTranslator::Galician |   31  |
|           QOnlineTranslator::Georgian |   32  |
|             QOnlineTranslator::German |   33  |
|              QOnlineTranslator::Greek |   34  |
|           QOnlineTranslator::Gujarati |   35  |
|      QOnlineTranslator::HaitianCreole |   36  |
|              QOnlineTranslator::Hausa |   37  |
|           QOnlineTranslator::Hawaiian |   38  |
|             QOnlineTranslator::Hebrew |   39  |
|           QOnlineTranslator::HillMari |   40  |
|              QOnlineTranslator::Hindi |   41  |
|              QOnlineTranslator::Hmong |   42  |
|          QOnlineTranslator::Hungarian |   43  |
|          QOnlineTranslator::Icelandic |   44  |
|               QOnlineTranslator::Igbo |   45  |
|         QOnlineTranslator::Indonesian |   46  |
|              QOnlineTranslator::Irish |   47  |
|            QOnlineTranslator::Italian |   48  |
|           QOnlineTranslator::Japanese |   49  |
|           QOnlineTranslator::Javanese |   50  |
|            QOnlineTranslator::Kannada |   51  |
|             QOnlineTranslator::Kazakh |   52  |
|              QOnlineTranslator::Khmer |   53  |
|            QOnlineTranslator::Klingon |   54  |
|       QOnlineTranslator::KlingonPlqaD |   55  |
|             QOnlineTranslator::Korean |   56  |
|            QOnlineTranslator::Kurdish |   57  |
|             QOnlineTranslator::Kyrgyz |   58  |
|                QOnlineTranslator::Lao |   59  |
|              QOnlineTranslator::Latin |   60  |
|            QOnlineTranslator::Latvian |   61  |
|    QOnlineTranslator::LevantineArabic |   62  |
|         QOnlineTranslator::Lithuanian |   63  |
|      QOnlineTranslator::Luxembourgish |   64  |
|         QOnlineTranslator::Macedonian |   65  |
|           QOnlineTranslator::Malagasy |   66  |
|              QOnlineTranslator::Malay |   67  |
|          QOnlineTranslator::Malayalam |   68  |
|            QOnlineTranslator::Maltese |   69  |
|              QOnlineTranslator::Maori |   70  |
|            QOnlineTranslator::Marathi |   71  |
|               QOnlineTranslator::Mari |   72  |
|          QOnlineTranslator::Mongolian |   73  |
|            QOnlineTranslator::Myanmar |   74  |
|             QOnlineTranslator::Nepali |   75  |
|          QOnlineTranslator::Norwegian |   76  |
|           QOnlineTranslator::Chichewa |   77  |
|         QOnlineTranslator::Papiamento |   78  |
|             QOnlineTranslator::Pashto |   79  |
|            QOnlineTranslator::Persian |   80  |
|             QOnlineTranslator::Polish |   81  |
|         QOnlineTranslator::Portuguese |   82  |
|            QOnlineTranslator::Punjabi |   83  |
|     QOnlineTranslator::QueretaroOtomi |   84  |
|           QOnlineTranslator::Romanian |   85  |
|            QOnlineTranslator::Russian |   86  |
|             QOnlineTranslator::Samoan |   87  |
|        QOnlineTranslator::ScotsGaelic |   88  |
|    QOnlineTranslator::SerbianCyrillic |   89  |
|       QOnlineTranslator::SerbianLatin |   90  |
|            QOnlineTranslator::Sesotho |   91  |
|              QOnlineTranslator::Shona |   92  |
|             QOnlineTranslator::Sindhi |   93  |
|            QOnlineTranslator::Sinhala |   94  |
|             QOnlineTranslator::Slovak |   95  |
|          QOnlineTranslator::Slovenian |   96  |
|             QOnlineTranslator::Somali |   97  |
|            QOnlineTranslator::Spanish |   98  |
|          QOnlineTranslator::Sundanese |   99  |
|            QOnlineTranslator::Swahili |  100  |
|            QOnlineTranslator::Swedish |  101  |
|            QOnlineTranslator::Tagalog |  102  |
|           QOnlineTranslator::Tahitian |  103  |
|              QOnlineTranslator::Tajik |  104  |
|              QOnlineTranslator::Tamil |  105  |
|              QOnlineTranslator::Tatar |  106  |
|             QOnlineTranslator::Telugu |  107  |
|               QOnlineTranslator::Thai |  108  |
|             QOnlineTranslator::Tongan |  109  |
|            QOnlineTranslator::Turkish |  110  |
|             QOnlineTranslator::Udmurt |  111  |
|          QOnlineTranslator::Ukrainian |  112  |
|               QOnlineTranslator::Urdu |  113  |
|              QOnlineTranslator::Uzbek |  114  |
|         QOnlineTranslator::Vietnamese |  115  |
|              QOnlineTranslator::Welsh |  116  |
|              QOnlineTranslator::Xhosa |  117  |
|            QOnlineTranslator::Yiddish |  118  |
|             QOnlineTranslator::Yoruba |  119  |
|        QOnlineTranslator::YucatecMaya |  120  |
|               QOnlineTranslator::Zulu |  121  |

### <a id='translation-error'/> enum QOnlineTranslator::TranslationError

Indicates all possible error conditions found during the processing of the translation.

|                           Constant | Value | Description                                                  |
| ---------------------------------: | :---: | :----------------------------------------------------------- |
|         QOnlineTranslator::NoError |   0   | No error condition                                           |
| QOnlineTranslator::ParametersError |   1   | Unsupported combination of backend and languages             |
|    QOnlineTranslator::NetworkError |   2   | Network error                                                |
|    QOnlineTranslator::ServiceError |   3   | Service unavailable or maximum number of requests            |
|    QOnlineTranslator::ParsingError |   4   | The request could not be parsed, please let me know about it |

## Member Function Documentation

### <a id='constructor'/> QOnlineTranslator::QOnlineTranslator(_QObject \*parent = nullptr_)

Constructs an translator with empty data and with parent object _parent_. You can use \[translate()](#translate) to send text to object. The destructor of a parent object destroys all child objects. Setting parent to 0 constructs an object with no parent. The parent of an object may be viewed as the object's owner.

* * *

### <a id='translate'/> void QOnlineTranslator::translate(_const QString &text, Engine engine = Google, Language translationLang = Auto, Language sourceLang = Auto, Language uiLang = Auto_)

Parse _text_ and translate with _engine_ into _translationLang_ from _sourceLang_ with hints on _uiLang_.

* * *

### <a id='media'/> \[QList](https&#x3A;//doc.qt.io/qt-5/qlist.html "Qt Documentation")&lt;\[QMediaContent](https&#x3A;//doc.qt.io/qt-5/qmediacontent.html "Qt Documentation")> QOnlineTranslator::media(_const QString &text, Engine engine, Language language = Auto, Voice voice = Default, Emotion emotion = Neutral_)

Splits _text_ into parts (Google and Yandex have limits on the size of the request) and returns list with the generated API URLs to play this text on _language_ with _voice_. _emotion_ argument only affects Yandex engine.

Example:

```cpp
QMediaPlayer *player = new QMediaPlayer(this);
QMediaPlaylist *playlist = new QMediaPlaylist(player);

playlist->addMedia(QOnlineTranslator::media("Hello World!", QOnlineTranslator::Google));
player->setPlaylist(playlist);


player->play(); // Plays "Hello World!"
```

* * *

### <a id='source-media'/> \[QList](https&#x3A;//doc.qt.io/qt-5/qlist.html "Qt Documentation")&lt;\[QMediaContent](https&#x3A;//doc.qt.io/qt-5/qmediacontent.html "Qt Documentation")> QOnlineTranslator::sourceMedia(_Engine engine, Voice voice = Default, Emotion emotion = Neutral_)

Splits the source text of translator into parts (because backends have limit of size per one request) and returns list with the generated API URLs to play this text with _voice_. _emotion_ argument only affects Yandex engine.

Example:

```cpp
QOnlineTranslator translator("Hello world!");

QMediaPlayer *player = new QMediaPlayer(this);
QMediaPlaylist *playlist = new QMediaPlaylist(player);

playlist->addMedia(translator.sourceMedia(QOnlineTranslator::Google));
player->setPlaylist(playlist);


player->play(); // Plays "Hello World!"
```

* * *

### <a id='translation-media'/> \[QList](https&#x3A;//doc.qt.io/qt-5/qlist.html "Qt Documentation")&lt;\[QMediaContent](https&#x3A;//doc.qt.io/qt-5/qmediacontent.html "Qt Documentation")> QOnlineTranslator::translationMedia(_Engine engine, Voice voice = Default, Emotion emotion = Neutral_)

Splits the translation of translator into parts (Google and Yandex have limits on the size of the request) and returns list with the generated API URLs to play this text with _voice_. _emotion_ argument only affects Yandex engine.

* * *

### <a id='source'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::source()

Returns source text.

* * *

### <a id='source-transliteration'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceTranslit()

Returns transliteration of source text. Google sends source transliteration only if source text is one word, otherwise function returns empty string.

* * *

### <a id='source-language-string'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceLanguage()

Returns name of source language.

* * *

### <a id='source-language'/> Language QOnlineTranslator::sourceLanguage()

Returns source language.

* * *

### <a id='translation'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translation()

Returns translated text.

* * *

### <a id='translation-translit'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translationTranslit()

Returns transliteration of translated text.

* * *

### <a id='source-transcription'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceTranscription()

Returns transcription of source text. Supports only for Yandex.

* * *

### <a id='translation-language-string'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translationLanguage()

Returns name of translation language.

* * *

### <a id='translation-language'/> Language QOnlineTranslator::translationLanguage()

Returns translation language.

* * *

### <a id='dictionary-list'/> \[QList](http&#x3A;//doc.qt.io/qt-5/qlist.html "Qt Documentation")&lt;\[QDictionary](QDictionary.md "Class documentation")>  QOnlineTranslator::dictionaryList()

Returns a list of \[QDictionary](QDictionary.md "Class documentation"). Read the class documentation for details.

* * *

### <a id='definitions-list'/> \[QList](http&#x3A;//doc.qt.io/qt-5/qlist.html "Qt Documentation")&lt;\[QDefinition](QDefinition.md "Class documentation")>  QOnlineTranslator::definitionsList()

Returns a list of \[QDefinition](QDefinition.md "Class documentation"). Read the class documentation for details.

* * *

### <a id='error'/> TranslationError QOnlineTranslator::error()

Returns the error that was found during the processing of last translation or tts. If no error was found, returns NoError. The text of the error can be obtained by \[**errorString**()](#error-string).

* * *

### <a id='error-string'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::errorString()

Returns a human-readable description of the last translation or tts error that occurred.

* * *

### <a id='language-string'/> static \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::languageString(_Language language_)

Returns the _language_ name.

* * *

### <a id='language-code'/> static \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::languageCode(_Language language_)

Returns code of the _language_.

* * *

### <a id='language-1'/> static Language QOnlineTranslator::language(_const QLocale &locale_)

Returns \[Language](#language) from _locale_ object.

* * *

### <a id='language-2'/> static Language QOnlineTranslator::language(_const QString &languageCode_)

Returns \[Language](#language) from ISO _languageCode_.
