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

#include "qexample.h"

QExample::QExample(const QString &typeOfSpeech) :
    m_typeOfSpeech(typeOfSpeech)
{
}

QString QExample::typeOfSpeech() const
{
    return m_typeOfSpeech;
}

void QExample::setTypeOfSpeech(const QString &typeOfSpeech)
{
    m_typeOfSpeech = typeOfSpeech;
}

QString QExample::description(int index) const
{
    return m_descriptions.at(index);
}

QString QExample::example(int index) const
{
    return m_examples.at(index);
}

void QExample::addExample(const QString &description, const QString &example)
{
    m_descriptions.append(description);
    m_examples.append(example);
}

int QExample::count() const
{
    return m_descriptions.size();
}
