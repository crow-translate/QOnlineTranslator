# QOnlineTranslator

[![GitHub (pre-)release](https://img.shields.io/github/release/crow-translate/QOnlineTranslator/all.svg)](https://github.com/crow-translate/QOnlineTranslator/releases)

**QOnlineTranslator** is a library for **Qt5** that provides free usage of Google, Yandex, Bing, LibreTranslate and Lingva translate API.

**Example:**

```cpp
QCoreApplication app(argc, argv);

QOnlineTranslator translator;
translator.translate("Hello world", QOnlineTranslator::Google);
QObject::connect(&translator, &QOnlineTranslator::finished, [&] {
    if (translator.error() == QOnlineTranslator::NoError)
        qInfo() << translator.translation();
    else
        qCritical() << translator.errorString();
});

return QCoreApplication::exec();
```

For real example of usage you can look into my other project: [Crow Translate](https://github.com/crow-translate/CrowTranslate "A simple and lightweight translator that allows to translate and say the selected text using the Google Translate API").

## Requirements

**Linux**: GCC 7 +

**Windows**: MSVC2017 / MinGW 7 +

## Installation

To include the library files you could use [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) CMake module. Or you can add it as a git submodule to your project and include it's contents:

**QMake**:

`include(src/third-party/qonlinetranslator/qonlinetranslator.pri)`

**CMake**:

`add_subdirectory(src/third-party/qonlinetranslator)`
