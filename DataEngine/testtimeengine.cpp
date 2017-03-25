
// the following header is required by the LGPL because
// we are using the actual time engine code
/*
 *   Copyright 2007 Aaron Seigo <aseigo@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "testtimeengine.h"

#include <QDate>
#include <QTime>

#include <KF5/KDELibs4Support/ksystemtimezone.h>
// #include <KDateTime>

#include <KF5/KDELibs4Support/kdatetime.h>

#include <Plasma/DataContainer>


#include <qt5/QtCore/QHash>

// see libkf5bookmarks5

TestTimeEngine::TestTimeEngine(QObject* parent, const QVariantList& args)
    : Plasma::DataEngine(parent, args)
{
    // We ignore any arguments - data engines do not have much use for them
    Q_UNUSED(args)

    // This prevents applets from setting an unnecessarily high
    // update interval and using too much CPU.
    // In the case of a clock that only has second precision,
    // a third of a second should be more than enough.
    setMinimumPollingInterval(333);
}

bool TestTimeEngine::sourceRequestEvent(const QString &name)
{
    // We do not have any special code to execute the
    // first time a source is requested, so we just call
    // updateSourceEvent().
    return updateSourceEvent(name);
}

bool TestTimeEngine::updateSourceEvent(const QString &name)
{
    QString timezone;

    if (name == "Local") {
        // Local is a special case - we just get the current time and date
        setData(name, "Time", QTime::currentTime());
        setData(name, "Date", QDate::currentDate());
    } else {
        // First check the timezone is valid
        KTimeZone newTz = KSystemTimeZones::zone(name);
        if (!newTz.isValid()) {
            return false;
        }

        // Get the date and time
        KDateTime dt = KDateTime::currentDateTime(newTz);
        setData(name, "Time", dt.time());
        setData(name, "Date", dt.date());
    }
    return true;
}

// This does the magic that allows Plasma to load
// this plugin.  The first argument must match
// the X-Plasma-EngineName in the .desktop file.
// The second argument is the name of the class in
// your plugin that derives from Plasma::DataEngine
K_EXPORT_PLASMA_DATAENGINE(testtime, TestTimeEngine)

// this is needed since TestTimeEngine is a QObject
#include "testtimeengine.moc"
