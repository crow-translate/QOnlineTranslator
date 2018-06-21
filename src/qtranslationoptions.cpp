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

#include "qtranslationoptions.h"

QTranslationOptions::QTranslationOptions(const QString &typeOfSpeech)
{
    m_typeOfSpeech = typeOfSpeech;
}

QString QTranslationOptions::typeOfSpeech() const
{
    return m_typeOfSpeech;
}

QString QTranslationOptions::word(int index) const
{
    return m_words.at(index);
}

QString QTranslationOptions::gender(int index) const
{
    return m_genders.at(index);
}

QStringList QTranslationOptions::translations(int index) const
{
    return m_translations.at(index);
}

void QTranslationOptions::setTypeOfSpeech(const QString &typeOfSpeech)
{
    m_typeOfSpeech = typeOfSpeech;
}

void QTranslationOptions::appendOption(const QString &word, const QString &gender, const QStringList &translations)
{
    m_words.append(word);
    m_genders.append(gender);
    m_translations.append(translations);
}

void QTranslationOptions::appendTranslation(int index, const QString &translation)
{
    m_translations[index].append(translation);
}

void QTranslationOptions::appendTranslation(const QString &translation)
{
    m_translations.last().append(translation);
}

int QTranslationOptions::count() const
{
    return m_words.size();
}
