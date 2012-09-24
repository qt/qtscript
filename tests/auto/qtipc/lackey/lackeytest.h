/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef LACKEYTEST_H
#define LACKEYTEST_H

#include <QtCore/QStringList>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>

// Mixin base class for tests that use the lackey executable to run scripts.
// Locates the binary starting from the executable directory and the scripts
// directory starting from #define SRCDIR.

class LackeyTest
{
public:
    LackeyTest(int binaryDepth = 1, int sourceDepth = 1);

    QString lackeyBinary() const { return m_lackeyBinary; }
    QString lackeyScriptsDirectory() const  { return m_lackeyScriptsDirectory; }

    // For use in initTestCase()
    bool isValid(QByteArray *errorMessage) const;

    // Messages for use in QVERIFY2
    static QByteArray msgCannotStartProcess(const QString &binary,
                                            const QString &errorMessage);

    QByteArray msgCannotStartLackey(const QString &errorMessage) const
        { return LackeyTest::msgCannotStartProcess(m_lackeyBinary, errorMessage); }

    QString scriptPath(const char *script) const
        { return m_lackeyScriptsDirectory + QLatin1Char('/') + QLatin1String(script); }

    QStringList scriptArguments(const char *script) const
        { return QStringList(scriptPath(script)); }

private:
    QString m_lackeyBinary;
    QString m_lackeyScriptsDirectory;
};

LackeyTest::LackeyTest(int binaryDepth, int sourceDepth)
{
    // Find executable in (shadow) build hierarchy.
    QDir dir = QDir(QCoreApplication::applicationDirPath());
#ifdef Q_OS_WIN
    // cd up from Windows debug/release folders.
    if (!dir.dirName().compare(QLatin1String("debug"), Qt::CaseInsensitive)
        || !dir.dirName().compare(QLatin1String("release"), Qt::CaseInsensitive))
        dir.cdUp();
#endif
    const QString lackey = QStringLiteral("lackey");
    QString binary = lackey;
#ifdef Q_OS_WIN
    binary += QStringLiteral(".exe");
#endif
    for (int i = 0; i < binaryDepth; ++i)
        if (!dir.cdUp())
            return;
    if (dir.cd(lackey) && dir.exists(binary))
        m_lackeyBinary = dir.absoluteFilePath(binary);
    // Find scripts starting from SRC in source hierarchy.
    dir = QDir(QLatin1String(SRCDIR));
    for (int i = 0; i < sourceDepth; ++i)
        if (!dir.cdUp())
            return;
    if (dir.cd(lackey) && dir.cd(QStringLiteral("scripts")))
        m_lackeyScriptsDirectory = dir.absolutePath();
}

bool LackeyTest::isValid(QByteArray *errorMessage) const
{
    if (m_lackeyBinary.isEmpty()) {
        *errorMessage = "Lackey executable could not be found starting from "
                + QCoreApplication::applicationDirPath().toLocal8Bit();
        return false;
    }
    if (!QFileInfo(m_lackeyBinary).isExecutable()) {
        *errorMessage = "Lackey " + m_lackeyBinary.toLocal8Bit() + " is not  executable.";
        return false;
    }
    if (m_lackeyScriptsDirectory.isEmpty()) {
        *errorMessage = "Lackey scripts directory could not be found starting from "
                + QByteArray(SRCDIR);
        return false;
    }
    return true;
}

QByteArray LackeyTest::msgCannotStartProcess(const QString &binary,
                                             const QString &errorMessage)
{
    QByteArray result = "Cannot start: '";
    result += binary.toLocal8Bit();
    result += "': ";
    result += errorMessage.toLocal8Bit();
    return result;
}

#endif // LACKEYTEST_H
