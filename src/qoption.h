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

#ifndef QOPTION_H
#define QOPTION_H

#include <QStringList>

class QOption
{
public:
    explicit QOption(const QString &typeOfSpeech = "");

    QString typeOfSpeech() const;
    QString word(int index) const;
    QString gender(int index) const;
    QString translations(int index) const;

    void setTypeOfSpeech(const QString &typeOfSpeech);
    void addWord(const QString &word, const QString &gender = "", const QStringList &translations = QStringList());
    int count() const;

private:
    QString m_typeOfSpeech;
    QStringList m_words;
    QStringList m_genders;
    QStringList m_translations;
};

#endif // QOPTION_H
