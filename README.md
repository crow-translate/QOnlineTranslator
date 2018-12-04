# QOnlineTranslator

[![GitHub (pre-)release](https://img.shields.io/github/release/Shatur95/QOnlineTranslator/all.svg)](https://github.com/Shatur95/QOnlineTranslator/releases)
[![Codacy grade](https://img.shields.io/codacy/grade/b5abd65ae9504966b1965d598c37dfdb.svg)](https://app.codacy.com/project/Shatur95/QOnlineTranslator/dashboard)

**QOnlineTranslator** is a library for **Qt5** that provides free usage of Google and Yandex translate API. [Detailed documentation](docs/QOnlineTranslator.md "Class documentation").

Example:

```cpp
QCoreApplication a(argc, argv); // It is necessary to create a Qt application object.
QTextStream out(stdout);
...
QOnlineTranslator onlineTranslator("hello");
out << onlineTranslator.text; // Returns "hello" translated to the language of your system

onlineTranslator.translate("Hello world!", "de");
out << onlineTranslator.text; // Returns "Hello world!" translated into German
```

For real example of usage you can look into my other project: [Crow Translate](https://github.com/Shatur95/CrowTranslate "A simple and lightweight translator that allows to translate and say the selected text using the Google Translate API").

## Requirements

**Linux**: GCC 6+

**Windows**: MSVC2017

## Installation

To include the library files I would recommend that you add it as a git submodule to your project and include it's contents with a `.pri` file. For example, if you want to clone the library in `src/third-party/` in your project, use this command to clone with **ssh**:

`git submodule add git@github.com:Shatur95/QOnlineTranslator.git src/third-party/qonlinetranslator`

or this to clone with **https**:

`git submodule add https://github.com/Shatur95/QOnlineTranslator.git src/third-party/qonlinetranslator`

or if you don't want to add the library as a submodule, you can download the archive from the [releases](https://github.com/Shatur95/QOnlineTranslator/releases) page and unpack it to the desired folder **manually**.

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
