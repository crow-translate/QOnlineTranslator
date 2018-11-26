# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [1.0.1] - 2018-11-26
### Changed
- Google: Fix parsing for text with non-breaking space.

## [1.0.0] - 2018-11-17
### Added
- Yandex support
- Transcription

### Changed
- Add explicit keyword
- Small changes in the interface to support other backends.
- Rework interface and logic

## [0.9.1] - 2018-08-05
### Changed
- Prevent crashes when converting for non-existent languages or codes.

## [0.9.0] - 2018-07-01
### Added
- Class for translation options.
- Word gender support for translation options.
- Definition support.

### Changed
- Fix incorrect limit for tts.
- Rename some functions.

## [0.8.0] - 2018-06-04
### Added
- Qt internationalization support.
- Function to get the source text.
- Static `defaultLocaleToCode()`, `codeToLanguage()` and `languageToCode()` functions.
- The `error()` method to check for translation errors.
- Inherite from `QObject`.

### Changed
- Rewrite list of languages in accordance with the official Google documentation.
- Splite queries to parts if they exceed the limit.
- Rename some functions.
- Improve network error output.
- Fix Cyrillic playback on Windows.
- Fix the incorrect parsing of sentences with the line break and non-breaking space.
- Fix wrong interpretation of some special characters.
- Fix empty translation language.

### Removed
- Unused `LANGUAGE_LONG_CODES`.
- Text-to-speech functions (now instead of playing, `translationMedia()` and `sourceMedia()` will return a playlist that can be used in [QMediaPlayer](https://doc.qt.io/qt-5/qmediaplayer.html "Qt Documentation")).
- Extra constructors.
- Static variables with languages and their codes (now they accessible from `codes()` and `languages()`).

## [0.7.0] - 2018-03-20
### Added
- Ability to create an object.
- Ability to get source and translation language.
- Ability to get transcription.
- Ability to get translation options.
- Ability to automatically correct grammatical errors and typos of source text.

### Changed
- Fix translation of several sentences.
- Fix the output of network errors.

## [0.3.0] - 2018-03-14
*Initial release*
