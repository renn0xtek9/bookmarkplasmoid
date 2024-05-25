#ifndef LIBBOOKMARKSMODULE_UTILS_H
#define LIBBOOKMARKSMODULE_UTILS_H

#include <libbookmarksmodule/data_types.h>

#include <QtCore/QString>

QString getStandardIcon(const bool is_folder, const BookmarkSource bookmark_source) noexcept;
QString getCustomOrThemeIconPath(const bool is_folder, const BookmarkSource bookmark_source, QString iconpathfromxml);

#endif  // LIBBOOKMARKSMODULE_UTILS_H
