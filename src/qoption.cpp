/*
 *  Copyright © 2018-2019 Hennadii Chernyshchyk <genaloner@gmail.com>
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

#include "qoption.h"

QOption::QOption(const QString &typeOfSpeech) :
    m_typeOfSpeech(typeOfSpeech)
{
}

QString QOption::typeOfSpeech() const
{
    return m_typeOfSpeech;
}

void QOption::setTypeOfSpeech(const QString &typeOfSpeech)
{
    m_typeOfSpeech = typeOfSpeech;
}

QString QOption::word(int index) const
{
    return m_words.at(index);
}

QString QOption::gender(int index) const
{
    return m_genders.at(index);
}

QString QOption::translations(int index) const
{
    return m_translations.at(index);
}

void QOption::addWord(const QString &word, const QString &gender, const QStringList &translations)
{
    m_words.append(word);
    m_genders.append(gender);
    if (!translations.isEmpty()) {
        m_translations.append(translations.at(0));
        for (int i = 1; i < translations.size(); ++i)
            m_translations.last().append(", " + translations.at(i));
    }
    else
        m_translations.append("");
}

int QOption::count() const
{
    return m_words.size();
}
