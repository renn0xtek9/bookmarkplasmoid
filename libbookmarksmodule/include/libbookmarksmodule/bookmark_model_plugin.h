#ifndef BOOKMARKSMODULE_BOOKMARK_MODEL_PLUGIN_H
#define BOOKMARKSMODULE_BOOKMARK_MODEL_PLUGIN_H
#include <QtQml/qqml.h>
#include <libbookmarksmodule/bookmarkmodel.h>

class BookmarkmodelPlugin : public QQmlExtensionPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
 public:
  ~BookmarkmodelPlugin() = default;
  void registerTypes(const char* uri) override;
};

#endif  // BOOKMARKSMODULE_BOOKMARK_MODEL_PLUGIN_H
