#include <libbookmarksmodule/data_types.h>
#include <libbookmarksmodule/utils.h>

#include <KF5/KIconThemes/KIconTheme>
#include <QtCore/QFileInfo>
#include <QtCore/QString>

QString getStandardIcon(const bool is_folder, const BookmarkSource bookmark_source) noexcept {
  if (is_folder) {
    switch (bookmark_source) {
      case (BookmarkSource::Konqueror): {
        return QString("folder-bookmark");
      }
      case (BookmarkSource::Okular): {
        return QString("okular");
      }
      case (BookmarkSource::Firefox): {
        return QString("firefox");
      }
      case (BookmarkSource::Chrome): {
        return QString("folder-bookmark");
      }
    }
  } else {
    switch (bookmark_source) {
      case (BookmarkSource::Konqueror): {
        return QString("text-html");
      }
      case (BookmarkSource::Okular): {
        return QString("application-pdf");
      }
      case (BookmarkSource::Firefox): {
        return QString("text-html");
      }
      case (BookmarkSource::Chrome): {
        return QString("google-chrome");
      }
    }
  }
  return QString("text-html");
}

QString getCustomOrThemeIconPath(const bool is_folder, const BookmarkSource bookmark_source, QString iconpathfromxml) {
  QFileInfo finfo(iconpathfromxml);
  QString path, standard, iconsource;
  QStringList themelist("hicolor");
  iconsource = iconpathfromxml;
  if (!finfo.isFile()) {
    iconsource = "";
    themelist.append(KIconTheme::current());
    foreach (QString str, themelist) {
      KIconTheme theme(str);
      path = theme.iconPathByName(iconpathfromxml, 24, KIconLoader::MatchBest);
      if (!path.isEmpty()) {
        iconsource = path;
        break;
      }
    }
    if (iconsource.isEmpty()) {
      themelist.append(KIconTheme::current());
      standard = getStandardIcon(is_folder, bookmark_source);
      foreach (QString str, themelist) {
        KIconTheme theme(str);
        path = theme.iconPathByName(standard, 24, KIconLoader::MatchBest);
        if (!path.isEmpty()) {
          iconsource = path;
          break;
        }
      }
    }
  }
  return iconsource;
}
