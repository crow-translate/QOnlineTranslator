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
| enum | [**Language**](#language) { Auto, Afrikaans, Albanian, Amharic, ..., Zulu }                                       |
| enum | [**Engine**](#engine) { Google, Yandex }                                                                          |
| enum | [**Voice**](#voice) { Zahar, Ermil, Jane, Oksana, ..., Female }                                                   |
| enum | [**Emotion**](#emotion) { Good, Evil, Neutral }                                                                   |
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

### <a id='language'/> enum QOnlineTranslator::Language

This enum has the following values:

|                              Constant | Value | Engine               |
| ------------------------------------: | :---: | :------------------- |
|         QOnlineTranslator::NoLanguage |   -1  |                      |
|               QOnlineTranslator::Auto |   0   |                      |
|          QOnlineTranslator::Afrikaans |   1   | Google, Yandex, Bing |
|           QOnlineTranslator::Albanian |   2   | Google, Yandex       |
|            QOnlineTranslator::Amharic |   3   | Google, Yandex       |
|             QOnlineTranslator::Arabic |   4   | Google, Yandex, Bing |
|           QOnlineTranslator::Armenian |   5   | Google, Yandex       |
|        QOnlineTranslator::Azerbaijani |   6   | Google               |
|             QOnlineTranslator::Basque |   7   | Google, Yandex       |
|            QOnlineTranslator::Bashkir |   8   | Yandex               |
|         QOnlineTranslator::Belarusian |   9   | Google, Yandex       |
|            QOnlineTranslator::Bengali |   10  | Google, Yandex, Bing |
|            QOnlineTranslator::Bosnian |   11  | Google, Yandex, Bing |
|          QOnlineTranslator::Bulgarian |   12  | Google, Yandex, Bing |
|            QOnlineTranslator::Catalan |   13  | Google, Yandex, Bing |
|          QOnlineTranslator::Cantonese |   14  | Bing                 |
|            QOnlineTranslator::Cebuano |   15  | Google, Yandex       |
|  QOnlineTranslator::SimplifiedChinese |   16  | Google, Yandex, Bing |
| QOnlineTranslator::TraditionalChinese |   17  | Google, Yandex, Bing |
|           QOnlineTranslator::Corsican |   18  | Google               |
|           QOnlineTranslator::Croatian |   19  | Google, Yandex, Bing |
|              QOnlineTranslator::Czech |   20  | Google, Yandex, Bing |
|             QOnlineTranslator::Danish |   21  | Google, Yandex, Bing |
|              QOnlineTranslator::Dutch |   22  | Google, Yandex, Bing |
|            QOnlineTranslator::English |   23  | Google, Yandex, Bing |
|          QOnlineTranslator::Esperanto |   24  | Google, Yandex       |
|           QOnlineTranslator::Estonian |   25  | Google, Yandex, Bing |
|             QOnlineTranslator::Fijian |   26  | Bing                 |
|           QOnlineTranslator::Filipino |   27  | Bing                 |
|            QOnlineTranslator::Finnish |   28  | Google, Yandex, Bing |
|             QOnlineTranslator::French |   29  | Google, Yandex, Bing |
|            QOnlineTranslator::Frisian |   30  | Google               |
|           QOnlineTranslator::Galician |   31  | Google, Yandex, Bing |
|           QOnlineTranslator::Georgian |   32  | Yandex               |
|             QOnlineTranslator::German |   33  | Google, Yandex, Bing |
|              QOnlineTranslator::Greek |   34  | Google, Yandex, Bing |
|           QOnlineTranslator::Gujarati |   35  | Google, Yandex       |
|      QOnlineTranslator::HaitianCreole |   36  | Google, Yandex, Bing |
|              QOnlineTranslator::Hausa |   37  | Google               |
|           QOnlineTranslator::Hawaiian |   38  | Google               |
|             QOnlineTranslator::Hebrew |   39  | Google, Yandex, Bing |
|           QOnlineTranslator::HillMari |   40  | Yandex               |
|              QOnlineTranslator::Hindi |   41  | Google, Yandex, Bing |
|              QOnlineTranslator::Hmong |   42  | Google, Bing         |
|          QOnlineTranslator::Hungarian |   43  | Google, Yandex, Bing |
|          QOnlineTranslator::Icelandic |   44  | Google, Yandex, Bing |
|               QOnlineTranslator::Igbo |   45  | Google               |
|         QOnlineTranslator::Indonesian |   46  | Google, Yandex, Bing |
|              QOnlineTranslator::Irish |   47  | Google, Yandex       |
|            QOnlineTranslator::Italian |   48  | Google, Yandex, Bing |
|           QOnlineTranslator::Japanese |   49  | Google, Yandex, Bing |
|           QOnlineTranslator::Javanese |   50  | Google, Yandex       |
|            QOnlineTranslator::Kannada |   51  | Google, Yandex       |
|             QOnlineTranslator::Kazakh |   52  | Google, Yandex       |
|              QOnlineTranslator::Khmer |   53  | Google, Yandex       |
|            QOnlineTranslator::Klingon |   54  | Bing                 |
|       QOnlineTranslator::KlingonPlqaD |   55  | Bing                 |
|             QOnlineTranslator::Korean |   56  | Google, Yandex, Bing |
|            QOnlineTranslator::Kurdish |   57  | Google               |
|             QOnlineTranslator::Kyrgyz |   58  | Google, Yandex       |
|                QOnlineTranslator::Lao |   59  | Google, Yandex       |
|              QOnlineTranslator::Latin |   60  | Google, Yandex       |
|            QOnlineTranslator::Latvian |   61  | Google, Yandex, Bing |
|    QOnlineTranslator::LevantineArabic |   62  | Bing                 |
|         QOnlineTranslator::Lithuanian |   63  | Google, Yandex, Bing |
|      QOnlineTranslator::Luxembourgish |   64  | Google, Yandex       |
|         QOnlineTranslator::Macedonian |   65  | Google, Yandex       |
|           QOnlineTranslator::Malagasy |   66  | Google, Yandex, Bing |
|              QOnlineTranslator::Malay |   67  | Google, Yandex, Bing |
|          QOnlineTranslator::Malayalam |   68  | Google, Yandex       |
|            QOnlineTranslator::Maltese |   69  | Google, Yandex, Bing |
|              QOnlineTranslator::Maori |   70  | Google, Yandex       |
|            QOnlineTranslator::Marathi |   71  | Google, Yandex       |
|               QOnlineTranslator::Mari |   72  | Yandex               |
|          QOnlineTranslator::Mongolian |   73  | Google, Yandex       |
|            QOnlineTranslator::Myanmar |   74  | Google, Yandex       |
|             QOnlineTranslator::Nepali |   75  | Google, Yandex       |
|          QOnlineTranslator::Norwegian |   76  | Google, Yandex, Bing |
|           QOnlineTranslator::Chichewa |   77  | Google               |
|         QOnlineTranslator::Papiamento |   78  | Yandex               |
|             QOnlineTranslator::Pashto |   79  | Google               |
|            QOnlineTranslator::Persian |   80  | Google, Yandex, Bing |
|             QOnlineTranslator::Polish |   81  | Google, Yandex, Bing |
|         QOnlineTranslator::Portuguese |   82  | Google, Yandex, Bing |
|            QOnlineTranslator::Punjabi |   83  | Google, Yandex       |
|     QOnlineTranslator::QueretaroOtomi |   84  | Bing                 |
|           QOnlineTranslator::Romanian |   85  | Google, Yandex, Bing |
|            QOnlineTranslator::Russian |   86  | Google, Yandex, Bing |
|             QOnlineTranslator::Samoan |   87  | Google, Bing         |
|        QOnlineTranslator::ScotsGaelic |   88  | Google, Yandex       |
|    QOnlineTranslator::SerbianCyrillic |   89  | Google, Yandex, Bing |
|       QOnlineTranslator::SerbianLatin |   90  | Bing                 |
|            QOnlineTranslator::Sesotho |   91  | Google               |
|              QOnlineTranslator::Shona |   92  | Google               |
|             QOnlineTranslator::Sindhi |   93  | Google               |
|            QOnlineTranslator::Sinhala |   94  | Google, Yandex       |
|             QOnlineTranslator::Slovak |   95  | Google, Yandex, Bing |
|          QOnlineTranslator::Slovenian |   96  | Google, Yandex, Bing |
|             QOnlineTranslator::Somali |   97  | Google               |
|            QOnlineTranslator::Spanish |   98  | Google, Yandex, Bing |
|          QOnlineTranslator::Sundanese |   99  | Google, Yandex       |
|            QOnlineTranslator::Swahili |  100  | Google, Yandex, Bing |
|            QOnlineTranslator::Swedish |  101  | Google, Yandex, Bing |
|            QOnlineTranslator::Tagalog |  102  | Google, Yandex       |
|           QOnlineTranslator::Tahitian |  103  | Bing                 |
|              QOnlineTranslator::Tajik |  104  | Google, Yandex       |
|              QOnlineTranslator::Tamil |  105  | Google, Yandex, Bing |
|              QOnlineTranslator::Tatar |  106  | Yandex               |
|             QOnlineTranslator::Telugu |  107  | Google, Yandex, Bing |
|               QOnlineTranslator::Thai |  108  | Google, Yandex, Bing |
|             QOnlineTranslator::Tongan |  109  | Bing                 |
|            QOnlineTranslator::Turkish |  110  | Google, Yandex, Bing |
|             QOnlineTranslator::Udmurt |  111  | Yandex               |
|          QOnlineTranslator::Ukrainian |  112  | Google, Yandex, Bing |
|               QOnlineTranslator::Urdu |  113  | Google, Yandex, Bing |
|              QOnlineTranslator::Uzbek |  114  | Google, Yandex       |
|         QOnlineTranslator::Vietnamese |  115  | Google, Yandex, Bing |
|              QOnlineTranslator::Welsh |  116  | Google, Yandex, Bing |
|              QOnlineTranslator::Xhosa |  117  | Google, Yandex       |
|            QOnlineTranslator::Yiddish |  118  | Google, Yandex       |
|             QOnlineTranslator::Yoruba |  119  | Google               |
|        QOnlineTranslator::YucatecMaya |  120  | Bing                 |
|               QOnlineTranslator::Zulu |  121  | Google               |

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

### <a id='translation-error'/> enum QOnlineTranslator::TranslationError

Indicates all possible error conditions found during the processing of the translation.

|                           Constant | Value | Description                                                  |
| ---------------------------------: | :---: | :----------------------------------------------------------- |
|         QOnlineTranslator::NoError |   0   | No error condition                                           |
| QOnlineTranslator::ParametersError |   1   | Unsupported combination of parameters                        |
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

Splits the source text of translator into parts (because engines have limit of size per one request) and returns list with the generated API URLs to play this text with _voice_. _emotion_ argument only affects Yandex engine.

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
