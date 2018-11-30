# QDictionary

The **QDictionary** class provides storage for translation options data for a single type of speech.

## Content

-   [Public Functions](#public-functions)
-   [Detailed Description](#detailed-description)
-   [Member Function Documentation](#member-function-documentation)

## Public Functions

| Return type | Data member                                                                                                                      |
| ----------: | :------------------------------------------------------------------------------------------------------------------------------- |
|             | [**QDictionary**(const QString &typeOfSpeech = "")](#c1)                                                                         |
|     QString | [**typeOfSpeech**()](#type-of-speech)                                                                                            |
|     QString | [**word**(int index)](#word)                                                                                                     |
|     QString | [**gender**(int index)](#gender)                                                                                                 |
| QStringList | [**translations**(int index)](#translations)                                                                                     |
|        void | [**setTypeOfSpeech**(const QString &typeOfSpeech)](#set-type-of-speech)                                                          |
|        void | [**appendWord**(const QString &word, const QString &gender = "", const QStringList &translations = QStringList())](#append-word) |
|         int | [**count**()](#count)                                                                                                            |

## Detailed Description

The **QDictionary** object can be obtained from the [QOnlineTranslator](docs/QOnlineTranslator.md "Class documentation") object, which contains a list of translation options for a single type of speech.

Example:

```cpp
QOnlineTranslator translator("say", "de", "en", "en"); // Translate "say" into German form English with English names of speech types
QTextStream out(stdout);

if (translator.error()) // Check for network error
    out << translator.translation(); // Print the text of the network error
else {
    foreach (auto optionType, translator.dictionaryList()) {
        out << optionType.typeOfSpeech() << ":" << endl; // Output type of speech with a colon
        for (auto i = 0; i <  optionType.count(); i++) {
            if (!optionType.gender(i).isEmpty())
                out << " " << optionType.gender(i); // Prints word gender
            out << " " << optionType.word(i) << ": "; // Prints word
            out << optionType.translations(i); // Prints translations
            out << endl;
        }
        out << endl;
    }
}

/* Returns:
verb:
 sagen: say, tell, speak, mean, utter
 sprechen: speak, talk, say, pronounce, militate, discourse
 meinen: think, mean, believe, say, opine, fancy
 heißen: mean, be called, be named, bid, tell, be titled
 äußern: express, comment, speak, voice, say, utter
 aussprechen: express, pronounce, say, speak, voice, enunciate
 vorbringen: make, put forward, raise, say, put, bring forward
 aufsagen: recite, say, speak

noun:
 Sagen: say
 Mitspracherecht: say
*/
```

* * *

## Member Function Documentation

### <a id='c1'/> QDictionary::QDictionary(_const QString &typeOfSpeech = ""_)

Constructs an empty object with the type of speech text _typeOfSpeech_.

* * *

### <a id='type-of-speech'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QDictionary::typeOfSpeech()

Returns type of speech of the text.

* * *

### <a id='word'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QDictionary::word(_int index_)

Returns the word of the _index_.

* * *

### <a id='gender'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QDictionary::gender(_int index_)

Returns the gender of the word with _index_. Used for some languages, such as German. Can be empty.

* * *

### <a id='translations'/> \[QStringList](http&#x3A;//doc.qt.io/qt-5/qstringlist.html "Qt Documentation") QDictionary::translations(_int index_)

Returns the translations for the word with the _index_.

* * *

### <a id='set-type-of-speech'/> void QDictionary::setTypeOfSpeech(_const QString &typeOfSpeech_)

Sets type of speech of the text to _typeOfSpeech_.

* * *

### <a id='append-word'/> void QDictionary::appendWord(_const QString &word, const QString &gender = "", const QStringList &translations = QStringList()_)

Appends the translation option _word_ with _gender_ and _translations_ onto the end of translation options.

* * *

### <a id='count'/> void QDictionary::count()

Returns the number of words.

* * *
