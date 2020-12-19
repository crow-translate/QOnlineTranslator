# QOption

The **QOption** structure provides storage for translation options data for a single type of speech.

## Content

- [Public Members](#public-members)
- [Detailed Description](#detailed-description)
- [Members Documentation](#members-documentation)

## Public Members

|        Type | Data member                       |
| ----------: | :-------------------------------- |
|     QString | [**word**](#word)                 |
|     QString | [**gender**](#gender)             |
| QStringList | [**translations**](#translations) |

## Public Functions

| Return type | Data member             |
| ----------: | :---------------------- |
| QJsonObject | [**toJson**()](#tojson) |

## Detailed Description

A **QOption** object can be obtained from the [QOnlineTranslator](docs/QOnlineTranslator.md "Class documentation") object, which contains translation options for a single word.

**Example:**

```cpp
QOnlineTranslator translator;
...

QTextStream out(stdout);
for (auto it = translator.translationOptions().cbegin(); it != translator.translationOptions().cend(); ++it) {
    out << it.key() << ":" << endl; // Output the type of speech with a colon
    for (const auto &[word, gender, translations] : it.value()) {
        if (!gender.isEmpty())
            out << " " << gender; // Print the gender of the word
        out << " " << word << ": "; // Print the word
        out << translations; // Print translations
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

---

## Members Documentation

### <a id='word'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOption::word

Returns word, that specified for translation options.

---

### <a id='gender'/> [QString](https://doc.qt.io/qt-5/qstring.html "Qt Documentation") QOption::gender

Returns the gender of the word above.

---

### <a id='translations'/> [QStringList](https://doc.qt.io/qt-5/qstringlist.html "Qt Documentation") QOption::translations

Returns associated translations for the word.

## Member Function Documentation

### <a id='tojson'/> [QJsonObject](https://doc.qt.io/qt-5/qjsonobject.html "Qt Documentation") QOption::toJson()

Returns a [QJsonObject](https://doc.qt.io/qt-5/qjsonobject.html "Qt Documentation") representation from data.
