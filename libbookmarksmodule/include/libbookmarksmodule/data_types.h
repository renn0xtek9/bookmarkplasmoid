#ifndef BOOKMARKSMODULE_DATA_TYPES_H
#define BOOKMARKSMODULE_DATA_TYPES_H
#include <QtCore/QObject>
enum BookmarkRoles {
  Iconpathrole = Qt::UserRole,
  Displayrole = Qt::DisplayRole,
  Tooltiprole = Qt::ToolTipRole,
  IsFolderRole = Qt::UserRole + 2,
  SourceRole = Qt::UserRole + 3
};

enum class BookmarkSource {
  Okular,    /**< We are currently parsing an okular bookmarks repository */
  Konqueror, /**< We are currently parsing an konqueror bookmarks repository */
  Firefox,   /**< We are currently parsing an firefox bookmarks repository */
  Chrome     /**< We are currently parsing an chrome bookmarks repository */
};
#endif  // BOOKMARKSMODULE_DATA_TYPES_H
