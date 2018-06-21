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

#include "qdefinition.h"

QDefinition::QDefinition(const QString &typeOfSpeech, const QString &description, const QString &example)
{
    m_typeOfSpeech = typeOfSpeech;
    m_description = description;
    m_example = example;
}

QString QDefinition::typeOfSpeech() const
{
    return m_typeOfSpeech;
}

QString QDefinition::description() const
{
    return m_description;
}

QString QDefinition::example() const
{
    return m_example;
}

void QDefinition::setTypeOfSpeech(const QString &typeOfSpeech)
{
    m_typeOfSpeech = typeOfSpeech;
}

void QDefinition::setDescription(const QString &description)
{
    m_description = description;
}

void QDefinition::setExample(const QString &example)
{
    m_example = example;
}
