/***************************************************************************
 *   Copyright (C) 2008-2016 by Alexey S. Malakhov <brezerk@gmail.com>     *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 ***************************************************************************/

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "src/version.h"
#include "src/qt/mainwindow.hpp"

#include "lib/db.hpp"

int main(int argc, char **argv) {
    //  Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("brezblock");
    QCoreApplication::setOrganizationDomain("brezblock.org.ua");

    QCoreApplication::setApplicationName("q4wine-qt");
    QCoreApplication::setApplicationVersion(VERSION);

    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOptions({
        {{"b", "binary"},
            QCoreApplication::tr("The Windows <binary> file to open."),
            QCoreApplication::tr("binary")},
        {{"m", "minimize"},
            QCoreApplication::tr("Minimize window on startup.")},
    });

    parser.process(app);

    MainWindow main_w;
    main_w.show();

    q4wine::lib::DBEngine* db =
            q4wine::lib::DBEngine::getInstance();
    db->open(":memory:");

    return app.exec();
}

