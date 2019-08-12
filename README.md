# QOnlineTranslator

[![GitHub (pre-)release](https://img.shields.io/github/release/crow-translate/QOnlineTranslator/all.svg)](https://github.com/crow-translate/QOnlineTranslator/releases)
[![Codacy grade](https://img.shields.io/codacy/grade/b5abd65ae9504966b1965d598c37dfdb.svg)](https://app.codacy.com/project/crow-translate/QOnlineTranslator/dashboard)

**QOnlineTranslator** is a library for **Qt5** that provides free usage of Google, Yandex and Bing translate API. [Detailed documentation](docs/QOnlineTranslator.md "Class documentation").

**Example:**

```cpp
QCoreApplication app(argc, argv);
...
QOnlineTranslator translator;
translator.translate("Hello world", QOnlineTranslator::Google);

QObject::connect(&translator, &QOnlineTranslator::finished, [&] {
    if (translator.error() == QOnlineTranslator::NoError)
        qInfo() << translator.translation();
    else
        qCritical() << translator.errorString();
});
```

For real example of usage you can look into my other project: [Crow Translate](https://github.com/crow-translate/CrowTranslate "A simple and lightweight translator that allows to translate and say the selected text using the Google Translate API").

## Requirements

**Linux**: GCC 6 +

**Windows**: MSVC2017 / MinGW 7 +

## Installation

To include the library files I would recommend that you add it as a git submodule to your project and include it's contents with a `.pri` file. For example, if you want to clone the library in `src/third-party/` in your project, use this command to clone with **ssh**:

`git submodule add git@github.com:crow-translate/QOnlineTranslator.git src/third-party/qonlinetranslator`

or this to clone with **https**:

`git submodule add https://github.com/crow-translate/QOnlineTranslator.git src/third-party/qonlinetranslator`

or if you don't want to add the library as a submodule, you can download the archive from the [releases](https://github.com/crow-translate/QOnlineTranslator/releases) page and unpack it to the desired folder **manually**.

Then include the `qonlinetranslator.pri` file in your `.pro` project file:

`include(src/third-party/qonlinetranslator/qonlinetranslator.pri)`

**Header:**

```cpp
#include "qonlinetranslator.h"
```

**or:**

```cpp
#include <QOnlineTranslator>
```
