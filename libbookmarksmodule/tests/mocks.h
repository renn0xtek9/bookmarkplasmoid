#ifndef MOCKS_H
#define MOCKS_H
#include <libbookmarksmodule/environment_theme_facade.h>

class MockEnvironmentThemeFacade : public AbstractEnvironmentThemeFacade {
 public:
  ~MockEnvironmentThemeFacade() = default;
  virtual QString getStandardIcon(const bool is_folder, const BookmarkSource bookmark_source) const noexcept final {
    return "mocked_getStandardIcon";
  }
  virtual QString getCustomOrThemeIconPath(const bool is_folder,
                                           const BookmarkSource bookmark_source,
                                           QString iconpathfromxml) const final {
    return "mocked_getCustomOrThemeIconPath";
  }
};

#endif  // MOCKS_H
