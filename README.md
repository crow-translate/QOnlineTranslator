# QOnlineTranslator

[![GitHub (pre-)release](https://img.shields.io/github/release/Shatur95/QOnlineTranslator/all.svg)](https://github.com/Shatur95/QOnlineTranslator/releases)

The **QOnlineTranslator** library provides free usage of Google Translate API for **Qt5**. It uses the Google API URL to get the response, and then parse the reply. [Detailed documentation](docs/QOnlineTranslator.md "Class documentation").

Example:
```cpp
QCoreApplication a(argc, argv); // Always need to create app instance for QEventLoop
...
QOnlineTranslator onlineTranslator("hello");
qInfo() << onlineTranslator.translation(); // Returns "hello" translated to the language of your system

onlineTranslator.translate("Hello world!", "de");
qInfo() << onlineTranslator.translation(); // Returns "Hello world!" translated into German
```

For real example of usage you can look into my other project: [Crow Translate](https://github.com/Shatur95/CrowTranslate "A simple and lightweight translator that allows to translate and say the selected text using the Google Translate API").


## Installation

To include the library files I would recommend that you add it as a git submodule to your project and include it's contents with a `.pri` file. For example, if you want to clone the library in `src/third-party/` in your project, use this command to clone with **ssh**:

`git submodule add git@github.com:Shatur95/QOnlineTranslator.git src/third-party/qonlinetranslator`

or this to clone with **https**:

`git submodule add https://github.com/Shatur95/QOnlineTranslator.git src/third-party/qonlinetranslator`

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
