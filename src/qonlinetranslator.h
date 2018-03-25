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

class QOnlineTranslator
{

public:
    inline QOnlineTranslator() {}
    inline QOnlineTranslator(const QString &text)
    { translate(text); }
    inline QOnlineTranslator(const QString &text, const QString &translationLanguage)
    { translate(text, translationLanguage); }
    inline QOnlineTranslator(const QString &text, const QString &translationLanguage, const QString &sourceLanguage)
    { translate(text, translationLanguage, sourceLanguage); }
    inline QOnlineTranslator(const QString &text, const QString &translationLanguage, const QString &sourceLanguage, const QString &translatorLanguage)
    { translate(text, translationLanguage, sourceLanguage, translatorLanguage); }
    inline QOnlineTranslator(const QString &text, const QString &translationLanguage, const QString &sourceLanguage, const QString &translatorLanguage, const bool &autoCorrect)
    { translate(text, translationLanguage, sourceLanguage, translatorLanguage, autoCorrect); }

    void translate(const QString &text, const QString &translationLanguage = "auto", const QString &sourceLanguage = "auto", const QString &translatorLanguage = "auto", const bool &autoCorrect = false);
    void say();

    inline QString sourceLanguage()
    { return m_sourceLanguage; }
    inline QString sourceTranscription()
    { return m_sourceTranscription; }
    inline QString text()
    { return m_text; }
    inline QList<QPair<QString, QStringList> > options()
    { return m_options; }
    inline QString translationTranscription()
    { return m_translationTranscription; }
    inline QString translationLanguage()
    { return m_translationLanguage; }

    static void say(const QString &text, QString language = "auto");
    static QString translateText(const QString &text, QString translationLanguage = "auto", QString sourceLanguage = "auto");

    static const QStringList LANGUAGE_NAMES;
    static const QStringList LANGUAGE_LONG_CODES;
    static const QStringList LANGUAGE_SHORT_CODES;

private:
    static QByteArray receiveReply(const QUrl &url);

    QString m_text;
    QString m_sourceTranscription;
    QString m_translationTranscription;
    QString m_translationLanguage;
    QString m_sourceLanguage;
    QList<QPair<QString, QStringList> > m_options;

    static const QString TTS_URL;
    static const QString TRANSLATION_URL;
    static const QString TRANSLATION_SHORT_URL;
};

#endif // QONLINETRANSLATOR_H
