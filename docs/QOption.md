# QOption

The **QOption** class provides storage for translation options data for a single type of speech.

## Content

-   [Public Functions](#public-functions)
-   [Detailed Description](#detailed-description)
-   [Member Function Documentation](#member-function-documentation)

## Public Functions

| Return type | Data member                                                                                                        |
| ----------: | :----------------------------------------------------------------------------------------------------------------- |
|             | [**QOption**(const QString &word, const QStringList &translations = {}, const QString &gender = {})](#constructor) |
|     QString | [**word**()](#word)                                                                                                |
|     QString | [**gender**()](#gender)                                                                                            |
| QStringList | [**translations**()](#translations)                                                                                |

## Detailed Description

A **QOption** object can be obtained from the [QOnlineTranslator](docs/QOnlineTranslator.md "Class documentation") object, which contains translation options for a single word.

**Example:**

```cpp
QOnlineTranslator translator;
...

QTextStream out(stdout);
foreach (const QString &typeOfSpeech, translator.translationOptions().keys()) {
    out << typeOfSpeech << ":" << endl; // Output the type of speech with a colon
    for (const QOption &option : translator->translationOptions().value(typeOfSpeech)) {
        if (!option.gender().isEmpty())
            out << " " << option.gender(); // Print the gender of the word
        out << " " << option.word() << ": "; // Print the word
        out << option.translations(); // Print translations
        out << endl;
    }
    out << endl;
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

### <a id='constructor'/> QOption::QOption(_const QString &word, const QStringList &translations = {}, const QString &gender = {}_)

Constructs an translation option with specified _word_, it _gender_ and it possible _translations_.

* * *

### <a id='word'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOption::word()

Returns word, that specified for translation options.

* * *

### <a id='gender'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOption::gender()

Returns the gender of the word above.

* * *

### <a id='translations'/> [QStringList](https://doc.qt.io/qt-5/qstringlist.html "Qt Documentation") QOption::translations()

Returns associated translations for the word.
