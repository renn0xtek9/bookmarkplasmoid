#ifndef MOCKS_H
#define MOCKS_H
#include <libbookmarksmodule/abstract_environment_theme_facade.h>
#include <libbookmarksmodule/xml_parser_interface.h>

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

class MockXbelParserInterface : public XmlParserInterface {
 public:
  explicit MockXbelParserInterface(const BookmarkSource bookmark_source, const AbstractEnvironmentThemeFacade& theme_facade)
      : XmlParserInterface(bookmark_source, theme_facade) {}
  ~MockXbelParserInterface() = default;
  virtual void read(QXmlStreamReader& xml_stream, QStandardItem* parent) final {
    readCallCount++;
    return;
  }
  int readCallCount{};
};


#endif  // MOCKS_H
