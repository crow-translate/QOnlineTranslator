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

#ifndef QDEFINITION_H
#define QDEFINITION_H

#include <QString>

class QDefinition
{
public:
    QDefinition(const QString &typeOfSpeech = "", const QString &description = "", const QString &example = "");

    QString typeOfSpeech() const;
    QString description() const;
    QString example() const;

    void setTypeOfSpeech(const QString &typeOfSpeech);
    void setDescription(const QString &description);
    void setExample(const QString &example);

private:
    QString m_typeOfSpeech;
    QString m_description;
    QString m_example;
};

#endif // QDEFINITION_H
