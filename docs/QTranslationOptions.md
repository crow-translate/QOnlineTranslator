# QTranslationOptions

The **QTranslationOptions** class provides storage for translation options data for a single type of speech.

## Content

* [Public Functions](#public-functions)
* [Detailed Description](#detailed-description)
* [Member Function Documentation](#member-function-documentation)

## Public Functions

| Return type                         | Data member                                                                                                                                        |
|------------------------------------:|:---------------------------------------------------------------------------------------------------------------------------------------------------|
|                                     | [**QTranslationOptions**()](#c1)                                                                                                                   |
|                                     | [**QTranslationOptions**(const QString &typeOfSpeech)](#c2)                                                                                        |
| QString                             | [**typeOfSpeech**()](#type-of-speech)                                                                                                              |
| void                                | [**setTypeOfSpeech**(const QString &typeOfSpeech)](#set-type-of-speech)                                                                            |
| void                                | [**appendOption**(const QString &word)](#append-option)                                                                                            |
| void                                | [**appendTranslation**(int index, const QString &translation)](#append-translation-1)                                                              |
| void                                | [**appendTranslation**(const QString &translation)](#append-translation-2)                                                                         |
| QString                             | [**word**(int index)](#word)                                                                                                                       |
| QString                             | [**translations**(int index)](#translations)                                                                                                       |
| int                                 | [**count**()](#count)                                                                                                                              |

## Detailed Description

The **QTranslationOptions** class provides storage for translation options data for a single type of speech.

Example:

```cpp
QOnlineTranslator translator("say", "de", "en", "en"); // Translate "say" into German form English with English names of speech types
QTextStream out(stdout);

if (translator.error()) // Check for network error
    out << translator.translation(); // Print the text of the network error
else {
    foreach (auto optionType, translator.translationOptionsList()) {
        out << optionType.typeOfSpeech() << ":" << endl; // Output type of speech with a colon
        for (auto i = 0; i <  optionType.count(); i++) {
            out << optionType.word(i) << ": "; // Print synonym for the source word
            out << optionType.translations(i).at(0); // Output first translation option for the synonym
            for (auto j = 1; j < optionType.translations(i).size(); j++) {
                out << ", " << optionType.translations(i).at(j); // Print the rest of the translation options
            }
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
---

## Member Function Documentation

### <a id='c1'/> QOnlineTranslator::QTranslationOptions()
Constructs an empty object.
___

### <a id='c2'/> QOnlineTranslator::QTranslationOptions(*const QString &typeOfSpeech*)
Constructs an empty object with the type of speech text *typeOfSpeech*.
___

### <a id='type-of-speech'/> void QOnlineTranslator::typeOfSpeech()
Returns the text of type of speech.
___

### <a id='set-type-of-speech'/> void QOnlineTranslator::setTypeOfSpeech(*const QString &typeOfSpeech*)
Sets type of speech text to *typeOfSpeech*.
___

### <a id='append-option'/> void QOnlineTranslator::appendOption(*const QString &word*)
Appends the translation option *word* onto the end of translation options.
___

### <a id='append-translation-1'/> void QOnlineTranslator::appendTranslation(*int index, const QString &translation*)
Appends the translation *translation* onto the end of translations for the word with the *index*.
___

### <a id='append-translation-2'/> void QOnlineTranslator::appendTranslation(*const QString &translation*)
Appends the *translation* onto the end of translations for the last translation option word.
___

### <a id='word'/> void QOnlineTranslator::word(*int index*)
Returns the word of the *index*
___

### <a id='translations'/> void QOnlineTranslator::translations(*int index*)
Returns the translations for the word with the *index*
___

### <a id='count'/> void QOnlineTranslator::count()
Returns the number of words.
___
