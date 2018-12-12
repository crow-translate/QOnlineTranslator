/*
 *  Copyright © 2018 Hennadii Chernyshchyk <genaloner@gmail.com>
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

#ifndef QEXAMPLE_H
#define QEXAMPLE_H

#include <QStringList>

class QExample
{
public:
    explicit QExample(const QString &typeOfSpeech = "");

    QString typeOfSpeech() const;
    void setTypeOfSpeech(const QString &typeOfSpeech);

    QString description(int index) const;
    QString example(int index) const;

    void addExample(const QString &description, const QString &example);
    int count() const;

private:
    QString m_typeOfSpeech;
    QStringList m_descriptions;
    QStringList m_examples;
};

#endif // QEXAMPLE_H
