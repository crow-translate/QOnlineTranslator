/*
 *  Copyright © 2018 Gennady Chernyshchuk <genaloner@gmail.com>
 *
 *  This file is part of QOnlineTranslator.
 *
 *  QOnlineTranslator is free library; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a get of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef QONLINETRANSLATOR_H
#define QONLINETRANSLATOR_H

#include <QString>
#include <QPair>
#include <QUrl>
#include <QNetworkReply>

class QOnlineTranslator
{

public:
    inline QOnlineTranslator() {}
    inline QOnlineTranslator(const QString &text, const QString &translationLanguage = "auto", const QString &sourceLanguage = "auto", const QString &translatorLanguage = "auto", const bool &autoCorrect = false)
    { translate(text, translationLanguage, sourceLanguage, translatorLanguage, autoCorrect); }

    void translate(const QString &text, const QString &translationLanguage = "auto", const QString &sourceLanguage = "auto", const QString &translatorLanguage = "auto", const bool &autoCorrect = false);
    void say();

    inline QString text()
    { return m_text; }
    inline QString sourceLanguage()
    { return m_sourceLanguage; }
    inline QString sourceTranscription()
    { return m_sourceTranscription; }
    inline QString translationTranscription()
    { return m_translationTranscription; }
    inline QString translationLanguage()
    { return m_translationLanguage; }
    inline QList<QPair<QString, QStringList> > options()
    { return m_options; }
    inline bool error()
    { return m_error; }

    static void say(const QString &text, QString language = "auto");
    static QString translateText(const QString &text, QString translationLanguage = "auto", QString sourceLanguage = "auto");
    static QString codeToLanguage(const QString &code);
    static QString languageToCode(const QString &language);
    static QString defaultLocaleToCode();

    static const QStringList LANGUAGE_NAMES;
    static const QStringList LANGUAGE_LONG_CODES;
    static const QStringList LANGUAGE_SHORT_CODES;

private:
    static int getSplitIndex(const QString &untranslatedText);

    QString m_text;
    QString m_sourceLanguage;
    QString m_sourceTranscription;
    QString m_translationTranscription;
    QString m_translationLanguage;
    QList<QPair<QString, QStringList> > m_options;
    bool m_error = false;
};

#endif // QONLINETRANSLATOR_H
