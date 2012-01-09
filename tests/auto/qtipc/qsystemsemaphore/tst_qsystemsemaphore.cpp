/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "../../lackey/lackeytest.h"

#include <QtTest/QtTest>
#include <QtCore/QSystemSemaphore>
#include <QtCore/QVector>
#include <QtCore/QTemporaryDir>

#define EXISTING_SHARE "existing"
#define LACKYWAITTIME 10000

class tst_QSystemSemaphore : public QObject, LackeyTest
{
    Q_OBJECT

public:
    tst_QSystemSemaphore();

public Q_SLOTS:
    void initTestCase();
    void init();
    void cleanup();

private slots:
    void key_data();
    void key();

    void basicacquire();
    void complexacquire();

    void basicProcesses();

    void processes_data();
    void processes();

#ifndef Q_OS_WIN
    void undo();
#endif
    void initialValue();

private:
    QSystemSemaphore *existingLock;

    QTemporaryDir m_temporaryDir;

    QString m_acquireJs;
    QString m_releaseJs;
    QString m_acquirereleaseJs;
};

static inline QString tempDirPattern()
{
    QString result = QDir::tempPath();
    if (!result.endsWith(QLatin1Char('/')))
        result += QLatin1Char('/');
    result += QStringLiteral("tst_qsystemsemaphoreXXXXXX");
    return result;
}

tst_QSystemSemaphore::tst_QSystemSemaphore() : m_temporaryDir(tempDirPattern())
{
    m_temporaryDir.setAutoRemove(true);
}

static bool createFile(const QString &resource,
                       const QString &target,
                       QByteArray *errorMessage)
{
    QFile memory(resource);
    if (!memory.open(QIODevice::ReadOnly | QIODevice::Text)) {
        *errorMessage = "Error reading resource '"
                + resource.toLocal8Bit() + "': "
                + memory.errorString().toLocal8Bit();
        return false;
    }
    QFile file(target);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        *errorMessage = "Error writing '"
                + target.toLocal8Bit() +  "': "
                + file.errorString().toLocal8Bit();
        return false;
    }
    file.write(memory.readAll());
    file.close();
    return true;
}

void tst_QSystemSemaphore::initTestCase()
{
    QByteArray errorMessage;
    QVERIFY2(isValid(&errorMessage), errorMessage.constData());
    QVERIFY(m_temporaryDir.isValid());
    // Write out files from resources to temporary folder
    const QString acquireJs = QStringLiteral("systemsemaphore_acquire.js");
    m_acquireJs = m_temporaryDir.path() + QLatin1Char('/') + acquireJs;
    QVERIFY2(createFile(QStringLiteral(":/") + acquireJs, m_acquireJs, &errorMessage),
             errorMessage.constData());

    const QString releaseJs = QStringLiteral("systemsemaphore_release.js");
    m_releaseJs = m_temporaryDir.path() + QLatin1Char('/') + releaseJs;
    QVERIFY2(createFile(QStringLiteral(":/") + releaseJs, m_releaseJs, &errorMessage),
             errorMessage.constData());

    const QString acquireReleaseJs = QStringLiteral("systemsemaphore_acquirerelease.js");
    m_acquirereleaseJs = m_temporaryDir.path() + QLatin1Char('/') + acquireReleaseJs;
    QVERIFY2(createFile(QStringLiteral(":/") + acquireReleaseJs, m_acquirereleaseJs, &errorMessage),
             errorMessage.constData());
}

void tst_QSystemSemaphore::init()
{
    existingLock = new QSystemSemaphore(EXISTING_SHARE, 1, QSystemSemaphore::Create);
}

void tst_QSystemSemaphore::cleanup()
{
    delete existingLock;
}

void tst_QSystemSemaphore::key_data()
{
    QTest::addColumn<QString>("constructorKey");
    QTest::addColumn<QString>("setKey");

    QTest::newRow("null, null") << QString() << QString();
    QTest::newRow("null, one") << QString() << QString("one");
    QTest::newRow("one, two") << QString("one") << QString("two");
}

/*!
    Basic key testing
 */
void tst_QSystemSemaphore::key()
{
    QFETCH(QString, constructorKey);
    QFETCH(QString, setKey);

    QSystemSemaphore sem(constructorKey);
    QCOMPARE(sem.key(), constructorKey);
    QCOMPARE(sem.error(), QSystemSemaphore::NoError);
    QCOMPARE(sem.errorString(), QString());

    sem.setKey(setKey);
    QCOMPARE(sem.key(), setKey);
    QCOMPARE(sem.error(), QSystemSemaphore::NoError);
    QCOMPARE(sem.errorString(), QString());
}

void tst_QSystemSemaphore::basicacquire()
{
    QSystemSemaphore sem("QSystemSemaphore_basicacquire", 1, QSystemSemaphore::Create);
    QVERIFY(sem.acquire());
    QCOMPARE(sem.error(), QSystemSemaphore::NoError);
    QVERIFY(sem.release());
    QCOMPARE(sem.error(), QSystemSemaphore::NoError);
    QCOMPARE(sem.errorString(), QString());
}

void tst_QSystemSemaphore::complexacquire()
{
    QSystemSemaphore sem("QSystemSemaphore_complexacquire", 2, QSystemSemaphore::Create);
    QVERIFY(sem.acquire());
    QVERIFY(sem.release());
    QVERIFY(sem.acquire());
    QVERIFY(sem.release());
    QVERIFY(sem.acquire());
    QVERIFY(sem.acquire());
    QVERIFY(sem.release());
    QVERIFY(sem.release());
    QCOMPARE(sem.error(), QSystemSemaphore::NoError);
    QCOMPARE(sem.errorString(), QString());
}

void tst_QSystemSemaphore::basicProcesses()
{
    QSystemSemaphore sem("store", 0, QSystemSemaphore::Create);

    QStringList acquireArguments = QStringList(m_acquireJs);
    QStringList releaseArguments = QStringList(m_releaseJs);
    QProcess acquire;
    acquire.setProcessChannelMode(QProcess::ForwardedChannels);

    QProcess release;
    release.setProcessChannelMode(QProcess::ForwardedChannels);

    acquire.start(lackeyBinary(), acquireArguments);
    QVERIFY2(acquire.waitForStarted(), msgCannotStartLackey(acquire.errorString()).constData());
    acquire.waitForFinished(LACKYWAITTIME);
    QVERIFY(acquire.state() == QProcess::Running);
    acquire.kill();
    release.start(lackeyBinary(), releaseArguments);
    QVERIFY2(release.waitForStarted(), msgCannotStartLackey(release.errorString()).constData());
    acquire.waitForFinished(LACKYWAITTIME);
    release.waitForFinished(LACKYWAITTIME);
    QVERIFY(acquire.state() == QProcess::NotRunning);
}

void tst_QSystemSemaphore::processes_data()
{
    QTest::addColumn<int>("processes");
    for (int i = 0; i < 5; ++i) {
        QTest::newRow("1 process") << 1;
        QTest::newRow("3 process") << 3;
        QTest::newRow("10 process") << 10;
    }
}

void tst_QSystemSemaphore::processes()
{
    QSystemSemaphore sem("store", 1, QSystemSemaphore::Create);

    QFETCH(int, processes);
    QVector<QString> scripts(processes, m_acquirereleaseJs);

    QList<QProcess*> consumers;
    for (int i = 0; i < scripts.count(); ++i) {
        QProcess *p = new QProcess;
        p->setProcessChannelMode(QProcess::ForwardedChannels);
        consumers.append(p);
        p->start(lackeyBinary(), QStringList(scripts.at(i)));
    }

    while (!consumers.isEmpty()) {
        consumers.first()->waitForFinished();
        QCOMPARE(consumers.first()->exitStatus(), QProcess::NormalExit);
        QCOMPARE(consumers.first()->exitCode(), 0);
        delete consumers.takeFirst();
    }
}

// This test only checks a unix behavior.
#ifndef Q_OS_WIN
void tst_QSystemSemaphore::undo()
{
    QSystemSemaphore sem("store", 1, QSystemSemaphore::Create);

    QStringList acquireArguments = QStringList(m_acquireJs);
    QProcess acquire;
    acquire.setProcessChannelMode(QProcess::ForwardedChannels);
    acquire.start(lackeyBinary(), acquireArguments);
    QVERIFY2(acquire.waitForStarted(), msgCannotStartLackey(acquire.errorString()).constData());
    acquire.waitForFinished(LACKYWAITTIME);
    QVERIFY(acquire.state()== QProcess::NotRunning);

    // At process exit the kernel should auto undo

    acquire.start(lackeyBinary(), acquireArguments);
    QVERIFY2(acquire.waitForStarted(), msgCannotStartLackey(acquire.errorString()).constData());
    acquire.waitForFinished(LACKYWAITTIME);
    QVERIFY(acquire.state()== QProcess::NotRunning);
}
#endif

void tst_QSystemSemaphore::initialValue()
{
    QSystemSemaphore sem("store", 1, QSystemSemaphore::Create);

    QStringList acquireArguments = QStringList(m_acquireJs);
    QStringList releaseArguments = QStringList(m_releaseJs);
    QProcess acquire;
    acquire.setProcessChannelMode(QProcess::ForwardedChannels);

    QProcess release;
    release.setProcessChannelMode(QProcess::ForwardedChannels);

    acquire.start(lackeyBinary(), acquireArguments);
    QVERIFY2(acquire.waitForStarted(), msgCannotStartLackey(acquire.errorString()).constData());
    acquire.waitForFinished(LACKYWAITTIME);
    QVERIFY(acquire.state()== QProcess::NotRunning);

    acquire.start(lackeyBinary(), acquireArguments << QLatin1String("2"));
    QVERIFY2(acquire.waitForStarted(), msgCannotStartLackey(acquire.errorString()).constData());
    acquire.waitForFinished(LACKYWAITTIME);
    QVERIFY(acquire.state()== QProcess::Running);
    acquire.kill();

    release.start(lackeyBinary(), releaseArguments);
    QVERIFY2(release.waitForStarted(), msgCannotStartLackey(release.errorString()).constData());
    acquire.waitForFinished(LACKYWAITTIME);
    release.waitForFinished(LACKYWAITTIME);
    QVERIFY(acquire.state()== QProcess::NotRunning);
}
QTEST_MAIN(tst_QSystemSemaphore)
#include "tst_qsystemsemaphore.moc"

