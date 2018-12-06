# Changelog

All notable changes to this project will be documented in this file. This project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased](https://github.com/Shatur95/crow-translate/tree/HEAD)

[Full Changelog](https://github.com/Shatur95/QOnlineTranslator/compare/1.0.1...HEAD)

**Added**

-   Bing support.
-   Parsing options.
-   Ability to check if the language is supported by the engine.
-   Yandex: examples support.

**Changed**

-   Initialize languages with `NoLanguage`.
-   Fix check for engine language support.

## [1.0.1](https://github.com/Shatur95/QOnlineTranslator/tree/1.0.1) (2018-11-26)

[Full Changelog](https://github.com/Shatur95/QOnlineTranslator/compare/1.0.0...1.0.1)

**Changed**

-   Google: Fix parsing for text with non-breaking space.

## [1.0.0](https://github.com/Shatur95/QOnlineTranslator/tree/1.0.0) (2018-11-17)

[Full Changelog](https://github.com/Shatur95/QOnlineTranslator/compare/0.9.1...1.0.0)

**Added**

-   Yandex support
-   Transcription

**Changed**

-   Add explicit keyword
-   Small changes in the interface to support other engines.
-   Rework interface and logic

## [0.9.1](https://github.com/Shatur95/QOnlineTranslator/tree/0.9.1) (2018-08-05)

[Full Changelog](https://github.com/Shatur95/QOnlineTranslator/compare/0.9.0...0.9.1)

**Changed**

-   Prevent crashes when converting for non-existent languages or codes.

## [0.9.0](https://github.com/Shatur95/QOnlineTranslator/tree/0.9.0) (2018-07-01)

[Full Changelog](https://github.com/Shatur95/QOnlineTranslator/compare/0.8.0...0.9.0)

**Added**

-   Class for translation options.
-   Word gender support for translation options.
-   Definition support.

**Changed**

-   Fix incorrect limit for tts.
-   Rename some functions.

## [0.8.0](https://github.com/Shatur95/QOnlineTranslator/tree/0.8.0) (2018-06-04)

[Full Changelog](https://github.com/Shatur95/QOnlineTranslator/compare/0.7.0...0.8.0)

**Added**

-   Qt internationalization support.
-   Function to get the source text.
-   Static `defaultLocaleToCode()`, `codeToLanguage()` and `languageToCode()` functions.
-   The `error()` method to check for translation errors.
-   Inherite from `QObject`.

**Changed**

-   Rewrite list of languages in accordance with the official Google documentation.
-   Splite queries to parts if they exceed the limit.
-   Rename some functions.
-   Improve network error output.
-   Fix Cyrillic playback on Windows.
-   Fix the incorrect parsing of sentences with the line break and non-breaking space.
-   Fix wrong interpretation of some special characters.
-   Fix empty translation language.

**Removed**

-   Unused `LANGUAGE_LONG_CODES`.
-   Text-to-speech functions (now instead of playing, `translationMedia()` and `sourceMedia()` will return a playlist that can be used in [QMediaPlayer](https://doc.qt.io/qt-5/qmediaplayer.html "Qt Documentation")).
-   Extra constructors.
-   Static variables with languages and their codes (now they accessible from `codes()` and `languages()`).

## [0.7.0](https://github.com/Shatur95/QOnlineTranslator/tree/0.7.0) (2018-03-20)

[Full Changelog](https://github.com/Shatur95/QOnlineTranslator/compare/0.3.0...0.7.0)

**Added**

-   Ability to create an object.
-   Ability to get source and translation language.
-   Ability to get transcription.
-   Ability to get translation options.
-   Ability to automatically correct grammatical errors and typos of source text.

**Changed**

-   Fix translation of several sentences.
-   Fix the output of network errors.

## [0.3.0](https://github.com/Shatur95/QOnlineTranslator/tree/0.3.0) (2018-03-01)

_Initial release_
