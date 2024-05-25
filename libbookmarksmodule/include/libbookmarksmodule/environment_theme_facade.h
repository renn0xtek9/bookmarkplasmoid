#ifndef ENVIRONEMENT_THEME_FACADE_H
#define ENVIRONEMENT_THEME_FACADE_H

#include <libbookmarksmodule/abstract_environment_theme_facade.h>

class EnvironmentThemeFacade : public AbstractEnvironmentThemeFacade {
 public:
  EnvironmentThemeFacade() = default;
  virtual ~EnvironmentThemeFacade() = default;
  virtual QString getStandardIcon(const bool is_folder, const BookmarkSource bookmark_source) const noexcept final;
  virtual QString getCustomOrThemeIconPath(const bool is_folder,
                                           const BookmarkSource bookmark_source,
                                           QString iconpathfromxml) const final;
};

#endif  // ENVIRONEMENT_THEME_FACADE_H
