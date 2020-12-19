# QOnlineTranslator

The **QOnlineTranslator** class provides translation data.

## Content

- [Public Types](#public-types)
- [Public Functions](#public-functions)
- [Static Public Members](#static-public-member)
- [Member Type Documentation](#member-type-documentation)
- [Member Function Documentation](#member-function-documentation)

## Public Types

| Type | Name                                                                                                              |
| ---: | :---------------------------------------------------------------------------------------------------------------- |
| enum | [**Language**](#language) { NoLanguage, Auto, Afrikaans, Albanian, Amharic, ..., Zulu }                           |
| enum | [**Engine**](#engine) { Google, Yandex, Bing }                                                                    |
| enum | [**TranslationError**](#translation-error) { NoError, ParametersError, NetworkError, ServiceError, ParsingError } |

## Public Functions

|                        Return type | Data member                                                                                                                                                   |
| ---------------------------------: | :------------------------------------------------------------------------------------------------------------------------------------------------------------ |
|                                    | [**QOnlineTranslator**(QWidget \*parent = nullptr)](#constructor)                                                                                             |
|                               void | [**translate**(const QString &text, Engine engine = Google, Language translationLang = Auto, Language sourceLang = Auto, Language uiLang = Auto)](#translate) |
|                               void | [**detectLanguage**(const QString &text, Engine engine = Google)](#detect-language)                                                                           |
|                               void | [**abort**()](#abort)                                                                                                                                         |
|                               bool | [**isRunning**()](#is-running)                                                                                                                                |
|                      QJsonDocument | [**toJson**()](#tojson)                                                                                                                                       |
|                            QString | [**source**()](#source)                                                                                                                                       |
|                            QString | [**sourceTranslit**()](#source-translit)                                                                                                                      |
|                            QString | [**sourceTranscription**()](source-transcription)                                                                                                             |
|                            QString | [**sourceLanguageName**()](#source-language-name)                                                                                                             |
|                           Language | [**sourceLanguage**()](#source-language)                                                                                                                      |
|                            QString | [**translation**()](#translation)                                                                                                                             |
|                            QString | [**translationTranslit**()](translation-translit)                                                                                                             |
|                            QString | [**translationLanguageName**()](#translation-language-name)                                                                                                   |
|                           Language | [**translationLanguage**()](#translation-language)                                                                                                            |
|  QMap\<QString, QVector\<QOption>> | [**translationOptions**()](#translation-options)                                                                                                              |
| QMap\<QString, QVector\<QExample>> | [**examples**()](#examples)                                                                                                                                   |
|                   TranslationError | [**error**()](#error)                                                                                                                                         |
|                            QString | [**errorString**()](#error-string)                                                                                                                            |
|                               bool | [**isSourceTranslitEnabled**()](#is-source-translit-enabled)                                                                                                  |
|                               void | [**setSourceTranslitEnabled**(bool enable)](#set-source-translit-enabled)                                                                                     |
|                               bool | [**isTranslationTranslitEnabled**()](#is-translation-translit-enabled)                                                                                        |
|                               void | [**setTranslationTranslitEnabled**(bool enable)](#set-translation-translit-enabled)                                                                           |
|                               bool | [**isSourceTranscriptionEnabled**()](#is-source-transcription-enabled)                                                                                        |
|                               void | [**setSourceTranscriptionEnabled**(bool enable)](#set-source-transcription-enabled)                                                                           |
|                               bool | [**isDictionaryEnabled**()](#is-dictionary-enabled)                                                                                                           |
|                               void | [**setDictionaryEnabled**(bool enable)](#set-dictionary-enabled)                                                                                              |
|                               bool | [**isDefinitionsEnabled**()](#is-definitions-enabled)                                                                                                         |
|                               void | [**setDefinitionsEnabled**(bool enable)](#set-definitions-enabled)                                                                                            |

## Signals

| Return type | Data member                                                          |
| ----------: | :------------------------------------------------------------------- |
|        void | [**finished**()](#finished-signal)                                   |

## Static Public Members

| Return type | Data member                                                                       |
| ----------: | :-------------------------------------------------------------------------------- |
|     QString | [**languageName**(Language language)](#language-name)                             |
|     QString | [**languageCode**(Language language)](#language-code)                             |
|    Language | [**language**(const QLocale &locale)](#language-1)                                |
|    Language | [**language**(const QString &languageCode)](#language-2)                          |
|        bool | [**isSupportTranslation**(Engine engine, Language lang)](#is-support-translation) |

## Member Type Documentation

### <a id='language'/> enum QOnlineTranslator::Language

This enum has the following values:

|                              Constant | Value | Engine               | Language code |
| ------------------------------------: | :---: | :------------------- | :------------ |
|         QOnlineTranslator::NoLanguage |  -1   |                      |               |
|               QOnlineTranslator::Auto |   0   | Google, Yandex, Bing | auto          |
|          QOnlineTranslator::Afrikaans |   1   | Google, Yandex, Bing | af            |
|           QOnlineTranslator::Albanian |   2   | Google, Yandex       | sq            |
|            QOnlineTranslator::Amharic |   3   | Google, Yandex       | am            |
|             QOnlineTranslator::Arabic |   4   | Google, Yandex, Bing | ar            |
|           QOnlineTranslator::Armenian |   5   | Google, Yandex       | hy            |
|        QOnlineTranslator::Azerbaijani |   6   | Google               | az            |
|             QOnlineTranslator::Basque |   7   | Google, Yandex       | eu            |
|            QOnlineTranslator::Bashkir |   8   | Yandex               | ba            |
|         QOnlineTranslator::Belarusian |   9   | Google, Yandex       | be            |
|            QOnlineTranslator::Bengali |  10   | Google, Yandex, Bing | bn            |
|            QOnlineTranslator::Bosnian |  11   | Google, Yandex, Bing | bs            |
|          QOnlineTranslator::Bulgarian |  12   | Google, Yandex, Bing | bg            |
|            QOnlineTranslator::Catalan |  13   | Google, Yandex, Bing | ca            |
|          QOnlineTranslator::Cantonese |  14   | Bing                 | yue           |
|            QOnlineTranslator::Cebuano |  15   | Google, Yandex       | ceb           |
|  QOnlineTranslator::SimplifiedChinese |  16   | Google, Yandex, Bing | zh-CN         |
| QOnlineTranslator::TraditionalChinese |  17   | Google, Yandex, Bing | zh-TW         |
|           QOnlineTranslator::Corsican |  18   | Google               | co            |
|           QOnlineTranslator::Croatian |  19   | Google, Yandex, Bing | hr            |
|              QOnlineTranslator::Czech |  20   | Google, Yandex, Bing | cs            |
|             QOnlineTranslator::Danish |  21   | Google, Yandex, Bing | da            |
|              QOnlineTranslator::Dutch |  22   | Google, Yandex, Bing | nl            |
|            QOnlineTranslator::English |  23   | Google, Yandex, Bing | en            |
|          QOnlineTranslator::Esperanto |  24   | Google, Yandex       | eo            |
|           QOnlineTranslator::Estonian |  25   | Google, Yandex, Bing | et            |
|             QOnlineTranslator::Fijian |  26   | Bing                 | fj            |
|           QOnlineTranslator::Filipino |  27   | Bing                 | fil           |
|            QOnlineTranslator::Finnish |  28   | Google, Yandex, Bing | fi            |
|             QOnlineTranslator::French |  29   | Google, Yandex, Bing | fr            |
|            QOnlineTranslator::Frisian |  30   | Google               | fy            |
|           QOnlineTranslator::Galician |  31   | Google, Yandex, Bing | gl            |
|           QOnlineTranslator::Georgian |  32   | Yandex               | ka            |
|             QOnlineTranslator::German |  33   | Google, Yandex, Bing | de            |
|              QOnlineTranslator::Greek |  34   | Google, Yandex, Bing | el            |
|           QOnlineTranslator::Gujarati |  35   | Google, Yandex       | gu            |
|      QOnlineTranslator::HaitianCreole |  36   | Google, Yandex, Bing | ht            |
|              QOnlineTranslator::Hausa |  37   | Google               | ha            |
|           QOnlineTranslator::Hawaiian |  38   | Google               | haw           |
|             QOnlineTranslator::Hebrew |  39   | Google, Yandex, Bing | he            |
|           QOnlineTranslator::HillMari |  40   | Yandex               | mrj           |
|              QOnlineTranslator::Hindi |  41   | Google, Yandex, Bing | hi            |
|              QOnlineTranslator::Hmong |  42   | Google, Bing         | hmn           |
|          QOnlineTranslator::Hungarian |  43   | Google, Yandex, Bing | hu            |
|          QOnlineTranslator::Icelandic |  44   | Google, Yandex, Bing | is            |
|               QOnlineTranslator::Igbo |  45   | Google               | ig            |
|         QOnlineTranslator::Indonesian |  46   | Google, Yandex, Bing | id            |
|              QOnlineTranslator::Irish |  47   | Google, Yandex       | ga            |
|            QOnlineTranslator::Italian |  48   | Google, Yandex, Bing | it            |
|           QOnlineTranslator::Japanese |  49   | Google, Yandex, Bing | ja            |
|           QOnlineTranslator::Javanese |  50   | Google, Yandex       | jw            |
|            QOnlineTranslator::Kannada |  51   | Google, Yandex       | kn            |
|             QOnlineTranslator::Kazakh |  52   | Google, Yandex       | kk            |
|              QOnlineTranslator::Khmer |  53   | Google, Yandex       | km            |
|            QOnlineTranslator::Klingon |  54   | Bing                 | tlh           |
|       QOnlineTranslator::KlingonPlqaD |  55   | Bing                 | tlh-Qaak      |
|             QOnlineTranslator::Korean |  56   | Google, Yandex, Bing | ko            |
|            QOnlineTranslator::Kurdish |  57   | Google               | ku            |
|             QOnlineTranslator::Kyrgyz |  58   | Google, Yandex       | ky            |
|                QOnlineTranslator::Lao |  59   | Google, Yandex       | lo            |
|              QOnlineTranslator::Latin |  60   | Google, Yandex       | la            |
|            QOnlineTranslator::Latvian |  61   | Google, Yandex, Bing | lv            |
|    QOnlineTranslator::LevantineArabic |  62   | Bing                 | apc           |
|         QOnlineTranslator::Lithuanian |  63   | Google, Yandex, Bing | lt            |
|      QOnlineTranslator::Luxembourgish |  64   | Google, Yandex       | lb            |
|         QOnlineTranslator::Macedonian |  65   | Google, Yandex       | mk            |
|           QOnlineTranslator::Malagasy |  66   | Google, Yandex, Bing | mg            |
|              QOnlineTranslator::Malay |  67   | Google, Yandex, Bing | ms            |
|          QOnlineTranslator::Malayalam |  68   | Google, Yandex       | ml            |
|            QOnlineTranslator::Maltese |  69   | Google, Yandex, Bing | mt            |
|              QOnlineTranslator::Maori |  70   | Google, Yandex       | mi            |
|            QOnlineTranslator::Marathi |  71   | Google, Yandex       | mr            |
|               QOnlineTranslator::Mari |  72   | Yandex               | mhr           |
|          QOnlineTranslator::Mongolian |  73   | Google, Yandex       | mn            |
|            QOnlineTranslator::Myanmar |  74   | Google, Yandex       | my            |
|             QOnlineTranslator::Nepali |  75   | Google, Yandex       | ne            |
|          QOnlineTranslator::Norwegian |  76   | Google, Yandex, Bing | no            |
|           QOnlineTranslator::Chichewa |  77   | Google               | ny            |
|         QOnlineTranslator::Papiamento |  78   | Yandex               | pap           |
|             QOnlineTranslator::Pashto |  79   | Google               | ps            |
|            QOnlineTranslator::Persian |  80   | Google, Yandex, Bing | fa            |
|             QOnlineTranslator::Polish |  81   | Google, Yandex, Bing | pl            |
|         QOnlineTranslator::Portuguese |  82   | Google, Yandex, Bing | pt            |
|            QOnlineTranslator::Punjabi |  83   | Google, Yandex       | pa            |
|     QOnlineTranslator::QueretaroOtomi |  84   | Bing                 | otq           |
|           QOnlineTranslator::Romanian |  85   | Google, Yandex, Bing | ro            |
|            QOnlineTranslator::Russian |  86   | Google, Yandex, Bing | ru            |
|             QOnlineTranslator::Samoan |  87   | Google, Bing         | sm            |
|        QOnlineTranslator::ScotsGaelic |  88   | Google, Yandex       | gd            |
|    QOnlineTranslator::SerbianCyrillic |  89   | Google, Yandex, Bing | sr-Cyrl       |
|       QOnlineTranslator::SerbianLatin |  90   | Bing                 | sr-Latin      |
|            QOnlineTranslator::Sesotho |  91   | Google               | st            |
|              QOnlineTranslator::Shona |  92   | Google               | sn            |
|             QOnlineTranslator::Sindhi |  93   | Google               | sd            |
|            QOnlineTranslator::Sinhala |  94   | Google, Yandex       | si            |
|             QOnlineTranslator::Slovak |  95   | Google, Yandex, Bing | sk            |
|          QOnlineTranslator::Slovenian |  96   | Google, Yandex, Bing | sl            |
|             QOnlineTranslator::Somali |  97   | Google               | so            |
|            QOnlineTranslator::Spanish |  98   | Google, Yandex, Bing | es            |
|          QOnlineTranslator::Sundanese |  99   | Google, Yandex       | su            |
|            QOnlineTranslator::Swahili |  100  | Google, Yandex, Bing | sw            |
|            QOnlineTranslator::Swedish |  101  | Google, Yandex, Bing | sv            |
|            QOnlineTranslator::Tagalog |  102  | Google, Yandex       | tl            |
|           QOnlineTranslator::Tahitian |  103  | Bing                 | ty            |
|              QOnlineTranslator::Tajik |  104  | Google, Yandex       | tg            |
|              QOnlineTranslator::Tamil |  105  | Google, Yandex, Bing | ta            |
|              QOnlineTranslator::Tatar |  106  | Yandex               | tt            |
|             QOnlineTranslator::Telugu |  107  | Google, Yandex, Bing | te            |
|               QOnlineTranslator::Thai |  108  | Google, Yandex, Bing | th            |
|             QOnlineTranslator::Tongan |  109  | Bing                 | to            |
|            QOnlineTranslator::Turkish |  110  | Google, Yandex, Bing | tr            |
|             QOnlineTranslator::Udmurt |  111  | Yandex               | udm           |
|          QOnlineTranslator::Ukrainian |  112  | Google, Yandex, Bing | uk            |
|               QOnlineTranslator::Urdu |  113  | Google, Yandex, Bing | ur            |
|              QOnlineTranslator::Uzbek |  114  | Google, Yandex       | uz            |
|         QOnlineTranslator::Vietnamese |  115  | Google, Yandex, Bing | vi            |
|              QOnlineTranslator::Welsh |  116  | Google, Yandex, Bing | cy            |
|              QOnlineTranslator::Xhosa |  117  | Google, Yandex       | xh            |
|            QOnlineTranslator::Yiddish |  118  | Google, Yandex       | yi            |
|             QOnlineTranslator::Yoruba |  119  | Google               | yo            |
|        QOnlineTranslator::YucatecMaya |  120  | Bing                 | yua           |
|               QOnlineTranslator::Zulu |  121  | Google               | zu            |

### <a id='engine'/> enum QOnlineTranslator::Engine

This enum has the following values:

|                  Constant | Value | Description                                                         |
| ------------------------: | :---: | :------------------------------------------------------------------ |
| QOnlineTranslator::Google |   0   | [Google Translate](https://translate.google.com) engine             |
| QOnlineTranslator::Yandex |   1   | [Yandex.Translate](https://translate.yandex.com) engine             |
|   QOnlineTranslator::Bing |   2   | [Bing Microsoft Translator](https://www.bing.com/translator) engine |

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

Constructs an object with empty data and with _parent_. You can use [translate()](#translate) to send text to object. The destructor of a parent object destroys all child objects. Setting parent to 0 constructs an object with no parent. The parent of an object may be viewed as the object's owner.

---

### <a id='translate'/> void QOnlineTranslator::translate(_const QString &text, Engine engine = Google, Language translationLang = Auto, Language sourceLang = Auto, Language uiLang = Auto_)

Parse _text_ and translate with _engine_ into _translationLang_ from _sourceLang_ with hints on _uiLang_.

---

### <a id='detect-language'/> void QOnlineTranslator::detectLanguage(_const QString &text, Engine engine = Google_)

Detect language of the _text_ using specified _engine_.

---

### <a id='abort'/> void QOnlineTranslator::abort()

Cancel translation operation (if any).

---

### <a id='is-running'/> bool QOnlineTranslator::isRunning()

Returns `true` when the translation is still processing and has not finished or was aborted yet.

---

### <a id='tojson'/> [QJsonDocument](https://doc.qt.io/qt-5/qjsonobject.html "Qt Documentation") QOnlineTranslator::toJson()

Returns a [QJsonDocument](https://doc.qt.io/qt-5/qjsondocument.html "Qt Documentation") representation from data.

---

### <a id='source'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::source()

Returns the source text.

---

### <a id='source-transliteration'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceTranslit()

Returns the transliteration of the source text.

---

### <a id='finished-signal'/> void QOnlineTranslator::finished()

This signal is emitted when the translation has finished processing. After this signal is emitted, there will be no more updates to the translations's data.

---

### <a id='source-language-name'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceLanguageName()

Returns the name of the source language.

---

### <a id='source-language'/> Language QOnlineTranslator::sourceLanguage()

Returns the source language.

---

### <a id='translation'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translation()

Returns the translated text.

---

### <a id='translation-translit'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translationTranslit()

Returns the transliteration of the translated text.

---

### <a id='source-transcription'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::sourceTranscription()

Returns the transcription of the source text. Supports only for Yandex.

---

### <a id='translation-language-name'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::translationLanguageName()

Returns the name of the translation language.

---

### <a id='translation-language'/> Language QOnlineTranslator::translationLanguage()

Returns the translation language.

---

### <a id='translation-options'/> [QMap](https://doc.qt.io/qt-5/qmap.html "Qt Documentation")\<[QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation"), [QVector](https://doc.qt.io/qt-5/qvector.html "Qt Documentation")\<[QOption](QOption.md "Class documentation")>> QOnlineTranslator::translationOptions()

Returns a [QMap](https://doc.qt.io/qt-5/qmap.html "Qt Documentation") whose key represents the type of speech, and the value is a [QVector](https://doc.qt.io/qt-5/qvector.html "Qt Documentation") of translation options. Read the [QOption](QOption.md "Class documentation") for details.

---

### <a id='examples'/> [QMap](https://doc.qt.io/qt-5/qmap.html "Qt Documentation")\<[QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation"), [QVector](https://doc.qt.io/qt-5/qvector.html "Qt Documentation")\<[QExample](QExample.md "Class documentation")>> QOnlineTranslator::examples()

Returns a [QMap](https://doc.qt.io/qt-5/qmap.html "Qt Documentation") whose key represents the type of speech, and the value is a [QVector](https://doc.qt.io/qt-5/qvector.html "Qt Documentation") of translation examples. Read the [QExample](QExample.md "Class documentation") for details.

---

### <a id='error'/> TranslationError QOnlineTranslator::error()

Returns the error that was found during the processing of the last translation. If no error was found, returns `NoError`. The text of the error can be obtained by [**errorString**()](#error-string).

---

### <a id='error-string'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::errorString()

Returns a human-readable description of the last translation error that occurred.

---

### <a id='is-source-translit-enabled'/> bool QOnlineTranslator::isSourceTranslitEnabled()

Return true if source transliteration is enabled.

---

### <a id='set-source-translit-enabled'/> void QOnlineTranslator::setSourceTranslitEnabled(_bool enable_)

Allows to enable or disable source transliteration.

---

### <a id='is-translation-translit-enabled'/> bool QOnlineTranslator::isTranslationTranslitEnabled()

Return true if translation transliteration is enabled.

---

### <a id='set-translation-translit-enabled'/> void QOnlineTranslator::setTranslationTranslitEnabled(_bool enable_)

Allows to enable or disable translation transliteration.

---

### <a id='is-source-transcription-enabled'/> bool QOnlineTranslator::isSourceTranscriptionEnabled()

Return true if source transcription is enabled.

---

### <a id='set-source-transcription-enabled'/> void QOnlineTranslator::setSourceTranscriptionEnabled(_bool enable_)

Allows to enable or disable source transcriptiond.

---

### <a id='is-dictionary-enabled'/> bool QOnlineTranslator::isDictionaryEnabled()

Return true if dictionary (translation options) is enabled.

---

### <a id='set-dictionary-enabled'/> void QOnlineTranslator::setDictionaryEnabled(_bool enable_)

Allows to enable or disable dictionary (translation options).

---

### <a id='is-definitions-enabled'/> bool QOnlineTranslator::isDefinitionsEnabled()

Return true if definitions is enabled.

---

### <a id='set-definitions-enabled'/> void QOnlineTranslator::setDefinitionsEnabled(_bool enable_)

Allows to enable or disable definitions.

---

### <a id='language-name'/> static [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::languageName(_Language language_)

Returns the _language_ name.

---

### <a id='language-code'/> static [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOnlineTranslator::languageCode(_Language language_)

Returns the code of the _language_. See table [below](#language).

**Note**: These are not the codes for sending API requests.

---

### <a id='language-1'/> static Language QOnlineTranslator::language(_const QLocale &locale_)

Returns the [language](#language) from _locale_ object.

---

### <a id='language-2'/> static Language QOnlineTranslator::language(_const QString &languageCode_)

Returns the [language](#language) from ISO _languageCode_. Useful for CLI interface.

---

### <a id='is-support-translation'/> static bool QOnlineTranslator::isSupportTranslation(_Engine engine, Language lang_)

Returns true if the _lang_ is supported by the _engine_ for translation.
