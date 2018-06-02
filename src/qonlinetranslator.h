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
#include <QUrl>
#include <QNetworkReply>
#include <QMediaPlaylist>

class QOnlineTranslator : public QObject
{
    Q_OBJECT

public:
    explicit QOnlineTranslator(QObject *parent = nullptr);
    explicit QOnlineTranslator(const QString &text, const QString &translationLanguage = "auto", const QString &sourceLanguage = "auto", const QString &translatorLanguage = "auto", const bool &autoCorrect = false, QObject *parent = nullptr);

    void translate(const QString &translation, const QString &translationLanguage = "auto", const QString &sourceLanguage = "auto", const QString &translatorLanguage = "auto", const bool &autoCorrect = false);

    QList<QMediaContent> sourceMedia();
    QList<QMediaContent> translationMedia();

    inline QString source()
    { return m_source; }
    inline QString sourceLanguage()
    { return m_sourceLanguage; }
    inline QString sourceTranscription()
    { return m_sourceTranscription; }

    inline QString translation()
    { return m_translation; }
    inline QString translationTranscription()
    { return m_translationTranscription; }
    inline QString translationLanguage()
    { return m_translationLanguage; }
    inline QList<QPair<QString, QStringList> > options()
    { return m_options; }

    inline bool error()
    { return m_error; }

    static QString translateText(const QString &translation, QString translationLanguage = "auto", QString sourceLanguage = "auto");
    static QString codeToLanguage(const QString &code);
    static QString languageToCode(const QString &language);
    static QString defaultLocaleToCode();
    static QList<QMediaContent> media(const QString &text, QString language = "auto");

    static const QStringList LANGUAGE_NAMES;
    static const QStringList LANGUAGE_CODES;

private:
    static int getSplitIndex(const QString &untranslatedText);

    QString m_source;
    QString m_sourceLanguage;
    QString m_sourceTranscription;

    QString m_translation;
    QString m_translationTranscription;
    QString m_translationLanguage;
    QList<QPair<QString, QStringList> > m_options;

    bool m_error = false;
};

#endif // QONLINETRANSLATOR_H
