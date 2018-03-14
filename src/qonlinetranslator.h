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

class QOnlineTranslator
{

public:
    QOnlineTranslator(const QString &text, const QString &translationLanguage, const QString &sourceLanguage, const QString &translatorLanguage, const bool &autoCorrect);
    QOnlineTranslator(const QString &text, const QString &translationLanguage, const QString &sourceLanguage, const QString &translatorLanguage);
    QOnlineTranslator(const QString &text, const QString &translationLanguage, const QString &sourceLanguage);
    QOnlineTranslator(const QString &text, const QString &translationLanguage);
    QOnlineTranslator(const QString &text);

    void translate(const QString &text, QString translationLanguage = "auto", QString sourceLanguage = "auto", const QString &translatorLanguage = "auto", const bool &autoCorrect = false);
    void say();
    QString sourceLanguage();
    QString sourceTranscription();
    QString text();
    QList<QPair<QString, QStringList> > options();
    QString translationTranscription();
    QString translationLanguage();

    static void say(const QString &text, QString language = "auto");
    static QString translateText(const QString &text, QString translationLanguage = "auto", QString sourceLanguage = "auto");

    static const QStringList LANGUAGE_NAMES;
    static const QStringList LANGUAGE_LONG_CODES;
    static const QStringList LANGUAGE_SHORT_CODES;

private:
    static QString receiveQuery(const QString &preparedUrl);

    QString m_text;
    QString m_sourceTranscription;
    QString m_translationTranscription;
    QString m_translationLanguage;
    QString m_sourceLanguage;
    QList<QPair<QString, QStringList> > m_translationOptions;

    static const QString TTS_URL;
    static const QString TRANSLATION_URL;
    static const QString TRANSLATION_SHORT_URL;
};

#endif // QONLINETRANSLATOR_H
