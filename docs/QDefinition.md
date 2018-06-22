# QDefinition

The **QDefinition** class provides storage for definitions data.

## Content

* [Public Functions](#public-functions)
* [Detailed Description](#detailed-description)
* [Member Function Documentation](#member-function-documentation)

## Public Functions

| Return type | Data member                                                                                                            |
|------------:|:-----------------------------------------------------------------------------------------------------------------------|
|             | [**QDefinition**(const QString &typeOfSpeech = "", const QString &description = "", const QString &example = "")](#c1) |
| QString     | [**typeOfSpeech**()](#type-of-speech)                                                                                  |
| QString     | [**description**()](#description)                                                                                      |
| QString     | [**example**()](#example)                                                                                              |
| void        | [**setTypeOfSpeech**(const QString &typeOfSpeech)](#set-type-of-speech)                                                |
| void        | [**setDescription**(const QString &description)](#set-description)                                                     |
| void        | [**setExample**(const QString &example)](#set-example)                                                                 |

## Detailed Description

The **QDefinition** object can be obtained from the [QOnlineTranslator](docs/QOnlineTranslator.md "Class documentation") object, which contains a list of definitions.

Example:

```cpp
QOnlineTranslator translator("say", "de", "en", "en"); // Translate "say" into German form English with English names of speech types
QTextStream out(stdout);

if (translator.error()) // Check for network error
    out << translator.translation(); // Print the text of the network error
else {
    foreach (QDefinition definition, translator.definitionsList()) {
        out << definition.typeOfSpeech() << endl;
        out << "   " << definition.description() << endl;
        out << "   " << definition.example() << endl;
        out << endl;
    }
}

/* Returns:
noun
   an opportunity for stating one's opinion or feelings.
   the voters are entitled to have their say on the treaty

verb
   utter words so as to convey information, an opinion, a feeling or intention, or an instruction.
   “Thank you,” he said

exclamation
   used to express surprise or to draw attention to a remark or question.
   say, did you notice any blood?
*/
```
---

## Member Function Documentation

### <a id='c1'/> QDefinition::QDefinition(*const QString &typeOfSpeech = "", const QString &description = "", const QString &example = ""*)
Constructs definition object with *typeOfSpeech*, *description* and *example*.
___

### <a id='type-of-speech'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QDefinition::typeOfSpeech()
Returns type of speech of the definition.
___

### <a id='description'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QDefinition::description()
Returns description of the definition.
___

### <a id='example'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QDefinition::example()
Returns example of the definition.
___

### <a id='set-type-of-speech'/> void QDefinition::setTypeOfSpeech(*const QString &typeOfSpeech*)
Sets type of speech of the definition to *typeOfSpeech*.
___

### <a id='set-description'/> void QDefinition::setDescription(*const QString &description*)
Sets description of the definition to *description*.
___

### <a id='set-example'/> void QDefinition::setExample(*const QString &example*)
Sets example of the definition to *example*.
___
