# QExample

The **QExample** class provides storage for example usage examples for a single type of speech.

## Content

-   [Public Functions](#public-functions)
-   [Detailed Description](#detailed-description)
-   [Member Function Documentation](#member-function-documentation)

## Public Functions

| Return type | Data member                                                                     |
| ----------: | :------------------------------------------------------------------------------ |
|             | [**QExample**(const QString &typeOfSpeech = "")](#constructor)                  |
|     QString | [**typeOfSpeech**()](#type-of-speech)                                           |
|     QString | [**example**(int index)](#example)                                              |
|     QString | [**description**(int index)](#description)                                      |
|        void | [**setTypeOfSpeech**(const QString &typeOfSpeech)](#set-type-of-speech)         |
|        void | [**addWord**(const QString &description, const QString &example)](#add-example) |
|         int | [**count**()](#count)                                                           |

## Detailed Description

A **QExample** object can be obtained from the [QOnlineTranslator](docs/QOnlineTranslator.md "Class documentation") object, which contains examples for a single type of speech.

**Example:**

```cpp
QOnlineTranslator translator;
translator.translate("say", QOnlineTranslator::Google, QOnlineTranslator::German, QOnlineTranslator::English, QOnlineTranslator::English);
    
QTextStream out(stdout);
foreach (const QExample &example, translator.examples()) {
    out << example.typeOfSpeech() << endl;
    for (int i = 0; i < example.count(); ++i) {
        out << "   " << example.description(i) << endl;
        out << "   " << example.example(i) << endl;
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

### <a id='constructor'/> QExample::QExample(_const QString &typeOfSpeech = ""_)

Constructs an empty object with the type of speech _typeOfSpeech_ of examples.

* * *

### <a id='type-of-speech'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QExample::typeOfSpeech()

Returns the type of speech of examples.

* * *

### <a id='set-type-of-speech'/> void QExample::setTypeOfSpeech(_const QString &typeOfSpeech_)

Sets the type of speech of examples to _typeOfSpeech_.

* * *

### <a id='example'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QExample::example(_int index_)

Returns the example of the _index_.

* * *

### <a id='description'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QExample::description(_int index_)

Returns the description for the example with the _index_.

* * *

### <a id='add-example'/> void QExample::addWord(_const QString &description, const QString &example_)

Appends the _example_ with the _description_ onto the end of examples.

* * *

### <a id='count'/> void QExample::count()

Returns the number of examples.
