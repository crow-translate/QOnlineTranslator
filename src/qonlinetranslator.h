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

class QOnlineTranslator
{

public:
    static const QStringList LANGUAGE_NAMES;
    static const QStringList LANGUAGE_LONG_CODES;
    static const QStringList LANGUAGE_SHORT_CODES;

    static QString translate(const QString &text);
    static QString translate(const QString &text, const QString &outputLanguageCode);
    static QString translate(const QString &text, const short &outputLanguageIndex);
    static QString translate(const QString &text, const QString &inputLanguageCode, const QString &outputLanguageCode);
    static QString translate(const QString &text, const short &inputLanguageIndex, const short &outputLanguageIndex);
    static void say(const QString &text, const short &languageIndex);

private:
    static const QString TRANSLATION_URL;

    static QString receiveTranslation(const QString &preparedUrl);
    static void parseText(QString &response);
    static void parseLanguage(QString &response);
};

#endif // QONLINETRANSLATOR_H
