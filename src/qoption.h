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

#ifndef QOPTION_H
#define QOPTION_H

#include <QStringList>

class QOption
{
public:
    explicit QOption(const QString &word, const QStringList &translations = {}, const QString &gender = {});

    QString word() const;
    QString gender() const;
    QStringList translations() const;

private:
    QString m_word;
    QStringList m_translations;
    QString m_gender;
};

#endif // QOPTION_H
