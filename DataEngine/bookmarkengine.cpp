
/*
 * Copyright 2011 Aaron Seigo <aseigo@kde.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 *    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 *    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *    NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *   THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <qt5/QtCore/qfile.h>
#include <qt5/QtGui/QColor>
#include "XbelReader.hpp"

#include <KLocalizedString>
#include "bookmarkengine.h"


/*
 This DataEngine provides a static set of data that is created on
 engine creation. This is a common pattern for DataEngines that relay
 information such as hardware events and shows the most basic form of
 a DataEngine
*/

Bookmarkengine::Bookmarkengine(QObject *parent, const QVariantList &args)
    : Plasma::DataEngine(parent, args)
{
    // we've passed the constructor's args to our parent class
    // we're done for now! Call init()
    init();
}
void Bookmarkengine::init()
{
// 	TODO use QSettings to find the file 
// 	TODO parse files from other origin. e.g Firefox etc. ?
	QString filename="/home/max/.local/share/konqueror/bookmarks.xml";
	QFile konquerorbookmarkfile(filename);
	if (konquerorbookmarkfile.open(QIODevice::OpenModeFlag::ReadOnly)){
		XbelReader reader;
		if(reader.read(&konquerorbookmarkfile)){
			foreach (Bookmark bmkr, reader.getBookrmarks()){
				Plasma::DataEngine::Data data;
				data.insert("Path",bmkr.getPath());
				data.insert("Icon",bmkr.getIconPath());
				data.insert("Origin","Konqueror");
				data.insert("URL",bmkr.getURL());
				if (bmkr.getType()){
					data.insert("IsFolder","True");
				}
				else{
					data.insert("IsFolder","False");
				}
				setData(bmkr.getName(),data);
			}
		}
	}
}

// export the plugin; use the plugin name and the class name
K_EXPORT_PLASMA_DATAENGINE_WITH_JSON(org.kde.plasma.bookmarkengine, Bookmarkengine, "bookmarkengine.json")

// include the moc file so the build system makes it for us
#include "bookmarkengine.moc"

// Contact GitHub API Training Shop Blog About
// © 2017 GitHub, Inc. Terms Privacy Security Status Help
