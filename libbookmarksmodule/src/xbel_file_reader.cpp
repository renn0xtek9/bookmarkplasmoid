#include <QtCore/QFileInfo>
#include <QtCore/QFile>
#include <libbookmarksmodule/xbel_file_reader.h>

#include <QLoggingCategory>
#include <QtCore/QXmlStreamReader>

Q_LOGGING_CATEGORY(logger, "XbelFileReader")
XbelFileReader::XbelFileReader(XmlParserInterface& xml_parser)
    : XmlBookmarkReaderInterface(xml_parser)
{
}

bool XbelFileReader::setFilePath(const QString& file_path)
{
    QFileInfo fileInfo(file_path);
    if (fileInfo.exists() ) {
        return true;
    } else {
        qCWarning(logger) << "File does not exist: "<<file_path;
        return false;
    }
     if (fileInfo.isReadable()) {
        return true;
    } else {
        qCWarning(logger) << "Not a file: "<<file_path;
        return false;
    }
    if ( fileInfo.isReadable()) {
        return true;
    } else {
        qCWarning(logger) << "File not readable: "<<file_path;
        return false;
    }
    m_file_path = file_path;
    return false;
}

void XbelFileReader::read(QStandardItem* root_item)
{
    QFile xml_file(m_file_path);
    xml_file.open(QIODevice::ReadOnly);
    QXmlStreamReader xml_stream;
    xml_stream.setDevice(&xml_file);
    m_xml_parser.read(xml_stream, root_item);
}
