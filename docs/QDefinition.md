# QDefinition

The **QDefinition** class provides storage for definitions data.

## Content

-   [Public Functions](#public-functions)
-   [Detailed Description](#detailed-description)
-   [Member Function Documentation](#member-function-documentation)

## Public Functions

| Return type | Data member                                                                                                            |
| ----------: | :--------------------------------------------------------------------------------------------------------------------- |
|             | [**QDefinition**(const QString &typeOfSpeech = "", const QString &description = "", const QString &example = "")](#c1) |
|     QString | [**typeOfSpeech**()](#type-of-speech)                                                                                  |
|     QString | [**description**()](#description)                                                                                      |
|     QString | [**example**()](#example)                                                                                              |
|        void | [**setTypeOfSpeech**(const QString &typeOfSpeech)](#set-type-of-speech)                                                |
|        void | [**setDescription**(const QString &description)](#set-description)                                                     |
|        void | [**setExample**(const QString &example)](#set-example)                                                                 |

## Detailed Description

The **QDefinition** object can be obtained from the [QOnlineTranslator](docs/QOnlineTranslator.md "Class documentation") object, which contains a list of definitions.

**Example:**

```cpp
QOnlineTranslator translator("say", QOnlineTranslator::German, QOnlineTranslator::English, QOnlineTranslator::English); // Translate "say" into German form English with English names of speech types
QTextStream out(stdout);

if (translator.error() != QOnlineTranslator::NoError) {
    out << translator.errorString(); // Print the text of the network error
} else {
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

* * *

## Member Function Documentation

### <a id='c1'/> QDefinition::QDefinition(_const QString &typeOfSpeech = "", const QString &description = "", const QString &example = ""_)

Constructs definition object with _typeOfSpeech_, _description_ and _example_.

* * *

### <a id='type-of-speech'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QDefinition::typeOfSpeech()

Returns type of speech of the definition.

* * *

### <a id='description'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QDefinition::description()

Returns description of the definition.

* * *

### <a id='example'/> \[QString](http&#x3A;//doc.qt.io/qt-5/qstring.html "Qt Documentation") QDefinition::example()

Returns example of the definition.

* * *

### <a id='set-type-of-speech'/> void QDefinition::setTypeOfSpeech(_const QString &typeOfSpeech_)

Sets type of speech of the definition to _typeOfSpeech_.

* * *

### <a id='set-description'/> void QDefinition::setDescription(_const QString &description_)

Sets description of the definition to _description_.

* * *

### <a id='set-example'/> void QDefinition::setExample(_const QString &example_)

Sets example of the definition to _example_.

* * *
