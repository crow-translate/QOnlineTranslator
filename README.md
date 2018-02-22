# QOnlineTranslator

The `QOnlineTranslator` library provides free usage of Google Translate API for `Qt5`.

## Installation

To include the library files I would recommend that you add it as a git submodule to your project and include it's contents with a `.pri` file. Go to the directory where you want to clone the library (for example, `src/third-party/`) and use this command:

`git submodule add git@github.com:Shatur95/QOnlineTranslator.git qonlinetranslator`

Then include the `qonlinetranslator.pri` file in your `.pro` project file:

`include(src/third-party/qonlinetranslator/qonlinetranslator.pri)`

## Static Public Types

| Return type     | Data member          |
|:----------------|:---------------------|
| QString         | TRANSLATION_URL      |
| QStringList     | LANGUAGE_NAMES       |
| QStringList     | LANGUAGE_LONG_CODES  |
| QStringList     | LANGUAGE_SHORT_CODES |

## Static Public Members

| Return type  | Function                                                                                            |
|:-------------|:----------------------------------------------------------------------------------------------------|
| QString      | translate(const QString &text)                                                                      |
| QString      | translate(const QString &text, const QString &outputLanguageCode)                                   |
| QString      | translate(const QString &text, const short &outputLanguageIndex)                                    |
| QString      | translate(const QString &text, const QString &inputLanguageCode, const QString &outputLanguageCode) |
| QString      | translate(const QString &text, const short &inputLanguageIndex, const short &outputLanguageIndex)   |
| void         | say(const QString &text, const short &languageIndex)                                                |

## Detailed Description

The `QOnlineTranslator` uses the Google API URL to get the response, and then the parse the reply for translation translation. Normally you do not need to create an object, all functions and members of this class are static.

Example:
```cpp
QCoreApplication a(argc, argv); // Always need to create app instance for QEventLoop
...
QString inputLanguageCode = "en";
QString outputLanguageCode = "ru";
QString text = "Hello Word!";
qDebug() << QOnlineTranslator::translate(text, inputLanguageCode, outputLanguageCode);
QOnlineTranslator::speech(text, inputLanguageCode, outputLanguageCode);
```

## Member Type Documentation

### `QString QOnlineTranslator::TRANSLATION_URL`

Provides translation link with arguments support:

```cpp
https://translate.googleapis.com/translate_a/single?client=gtx&sl=%1&tl=%2&dt=t&q=%3
```

Where:

* `%1` - Input text language
* `%2` - Output text language
* `%3` - Text for translation

### `QStringList QOnlineTranslator::LANGUAGE_NAMES const`
Provides language names that can be used for the text of buttons. See table below.

### `QStringList QOnlineTranslator::LANGUAGE_LONG_CODES const`
Provides language long codes that can be used as arguments for console applications. See table below.

### `QStringList QOnlineTranslator::LANGUAGE_SHORT_CODES const`
Provides language short codes that are used for the Google API. See table below.

### Members of `LANGUAGE_NAMES`, `LANGUAGE_LONG_CODES` and `LANGUAGE_SHORT_CODES`

| Index | LANGUAGE_NAMES       | LANGUAGE_LONG_CODES | LANGUAGE_SHORT_CODES | 
|:-----:|:--------------------:|:-------------------:|:--------------------:|
| 1     | Automatically detect | automatic           | auto                 |
| 2     | Afrikaans            | afrikaans           | af                   |
| 3     | Amharic              | amharic             | am                   |
| 4     | Arabic               | arabic              | ar                   |
| 5     | Azerbaijani          | azerbaijani         | az                   |
| 6     | Belarusian           | belarusian          | be                   |
| 7 | Bulgarian | bulgarian | bg |
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

### `QString QOnlineTranslator::translate(const QString &text)`

Returns a string containing the translation of the `text` from the automatically detected language to your system language.

### `QString QOnlineTranslator::translate(const QString &text, const QString &outputLanguageCode)`

Returns a string containing the translation of the `text` from the automatically detected language to language of `outputLanguageCode`. For language codes see the column `LANGUAGE_SHORT_CODES` in the table above.

### `QString QOnlineTranslator::translate(const QString &text, const short &outputLanguageIndex)`

Returns a string containing the translation of the `text` from the automatically detected language to language of `outputLanguageIndex`. For language indexes see the column `Index` in the table above.

### `QString QOnlineTranslator::translate(const QString &text, const QString &inputLanguageCode, const QString &outputLanguageCode)`

Returns a string containing the translation of the `text` from the language of `inputLanguageCode` to language of `outputLanguageCode`. For language codes see the column `LANGUAGE_SHORT_CODES` in the table above.

### `QString QOnlineTranslator::translate(const QString &text, const short &inputLanguageIndex, const short &outputLanguageIndex)`

Returns a string containing the translation of the `text` from the language of `inputLanguageIndex` to language of `outputLanguageIndex`. For language indexes see the column `Index` in the table above.

### `void QOnlineTranslator::say(const QString &text, const short &languageIndex)`

Speak `text` in the language of `languageIndex`. For language indexes see the column `Index` in the table above.
