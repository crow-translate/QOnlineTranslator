# QExample

The **QExample** class provides storage for example usage examples for a single type of speech.

## Content

-   [Public Functions](#public-functions)
-   [Detailed Description](#detailed-description)
-   [Member Function Documentation](#member-function-documentation)

## Public Functions

| Return type | Data member                                                                      |
| ----------: | :------------------------------------------------------------------------------- |
|             | [**QExample**(const QString &description, const QString &example)](#constructor) |
|     QString | [**example**()](#example)                                               |
|     QString | [**description**()](#description)                                       |

## Detailed Description

A **QExample** object can be obtained from the [QOnlineTranslator](docs/QOnlineTranslator.md "Class documentation") object, which contains translation example.

**Example:**

```cpp
QOnlineTranslator translator;
...


QTextStream out(stdout);
foreach (const QString &typeOfSpeech, translator.examples().keys()) {
    out << typeOfSpeech << ":" << endl; // Output the type of speech with a colon
    for (const QExample &example : translator->examples().value(typeOfSpeech)) {
        out << "   " << example.description() << endl;
        out << "   " << example.example() << endl;
        out << endl;
    }
    out << endl;
}

/* Returns:
noun:
   an opportunity for stating one's opinion or feelings.
   the voters are entitled to have their say on the treaty

verb:
   utter words so as to convey information, an opinion, a feeling or intention, or an instruction.
   “Thank you,” he said

exclamation:
   used to express surprise or to draw attention to a remark or question.
   say, did you notice any blood?
*/
```

* * *

## Member Function Documentation

### <a id='constructor'/> QExample::QExample(_const QString &description, const QString &example_)

Constructs translation example with specified _description_ and _example_ sentense.

* * *

### <a id='example'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QExample::example()

Returns the example sentense.

* * *

### <a id='description'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QExample::description()

Returns the description for the example.
