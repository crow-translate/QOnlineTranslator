# QOption

The **QOption** class provides storage for translation options data for a single type of speech.

## Content

-   [Public Functions](#public-functions)
-   [Detailed Description](#detailed-description)
-   [Member Function Documentation](#member-function-documentation)

## Public Functions

| Return type | Data member                                                                                                                |
| ----------: | :------------------------------------------------------------------------------------------------------------------------- |
|             | [**QOption**(const QString &typeOfSpeech = "")](#constructor)                                                              |
|     QString | [**typeOfSpeech**()](#type-of-speech)                                                                                      |
|     QString | [**word**(int index)](#word)                                                                                               |
|     QString | [**gender**(int index)](#gender)                                                                                           |
| QStringList | [**translations**(int index)](#translations)                                                                               |
|        void | [**setTypeOfSpeech**(const QString &typeOfSpeech)](#set-type-of-speech)                                                    |
|        void | [**addWord**(const QString &word, const QString &gender = "", const QStringList &translations = QStringList())](#add-word) |
|         int | [**count**()](#count)                                                                                                      |

## Detailed Description

A **QOption** object can be obtained from the [QOnlineTranslator](docs/QOnlineTranslator.md "Class documentation") object, which contains translation options for a single type of speech.

**Example:**

```cpp
QOnlineTranslator translator;
translator.translate("say", QOnlineTranslator::Google, QOnlineTranslator::German, QOnlineTranslator::English, QOnlineTranslator::English);

QTextStream out(stdout);
if (translator.error() != QOnlineTranslator::NoError) {
    out << translator.errorString() << endl; // Print the text of the network error
} else {
    foreach (const QOption &option, translator.translationOptions()) {
        out << option.typeOfSpeech() << ":" << endl; // Output the type of speech with a colon
        for (auto i = 0; i <  option.count(); i++) {
            if (!option.gender(i).isEmpty())
                out << " " << option.gender(i); // Print the gender of the word
            out << " " << option.word(i) << ": "; // Print the word
            out << option.translations(i); // Print translations
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

### <a id='constructor'/> QOption::QOption(_const QString &typeOfSpeech = ""_)

Constructs an empty object with the type of speech _typeOfSpeech_ for translation options.

* * *

### <a id='type-of-speech'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOption::typeOfSpeech()

Returns the type of speech of translation options.

* * *

### <a id='set-type-of-speech'/> void QOption::setTypeOfSpeech(_const QString &typeOfSpeech_)

Sets the type of speech of translation options to _typeOfSpeech_.

* * *

### <a id='word'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOption::word(_int index_)

Returns the word of the _index_.

* * *

### <a id='gender'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOption::gender(_int index_)

Returns the gender of the word with _index_.

* * *

### <a id='translations'/> [QStringList](https://doc.qt.io/qt-5/qstringlist.html "Qt Documentation") QOption::translations(_int index_)

Returns translations for the word with the _index_.

* * *

### <a id='add-word'/> void QOption::addWord(_const QString &word, const QString &gender = "", const QStringList &translations = QStringList()_)

Appends the translation option _word_ with _gender_ and _translations_ onto the end of translation options.

* * *

### <a id='count'/> void QOption::count()

Returns the number of words.
