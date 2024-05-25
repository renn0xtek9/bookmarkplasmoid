#ifndef ENVIRONEMENT_THEME_FACADE_H
#define ENVIRONEMENT_THEME_FACADE_H
#include <libbookmarksmodule/data_types.h>
class AbstractEnvironmentThemeFacade {
 public:
  virtual ~AbstractEnvironmentThemeFacade() = default;
  virtual QString getStandardIcon(const bool is_folder, const BookmarkSource bookmark_source) const noexcept = 0;
  virtual QString getCustomOrThemeIconPath(const bool is_folder,
                                           const BookmarkSource bookmark_source,
                                           QString iconpathfromxml) const = 0;
};

#endif  // ENVIRONEMENT_THEME_FACADE_H
