# QExample

The **QExample** structure provides storage for example usage examples for a single type of speech.

## Content

- [Public Members](#public-members)
- [Detailed Description](#detailed-description)
- [Members Documentation](#members-documentation)

## Public Members

|    Type | Data member                     |
| ------: | :------------------------------ |
| QString | [**example**](#example)         |
| QString | [**description**](#description) |

## Public Functions

| Return type | Data member             |
| ----------: | :---------------------- |
| QJsonObject | [**toJson**()](#tojson) |

## Detailed Description

A **QExample** object can be obtained from the [QOnlineTranslator](docs/QOnlineTranslator.md "Class documentation") object, which contains translation example.

**Example:**

```cpp
QOnlineTranslator translator;
...


QTextStream out(stdout);
for (auto it = translator.examples().cbegin(); it != translator.examples().cend(); ++it) {
    out << it.key() << ":" << endl; // Output the type of speech with a colon
    for (const auto &[example, description] : it.value()) {
        out << "   " << description << endl;
        out << "   " << example << endl;
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

---

## Members Documentation

### <a id='example'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QExample::example

Returns the example sentense.

---

### <a id='description'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QExample::description

Returns the description for the example.

## Member Function Documentation

### <a id='tojson'/> [QJsonObject](https://doc.qt.io/qt-5/qjsonobject.html "Qt Documentation") QExample::toJson()

Returns a [QJsonObject](https://doc.qt.io/qt-5/qjsonobject.html "Qt Documentation") representation from data.
