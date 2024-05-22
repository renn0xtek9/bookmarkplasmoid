#include <libbookmarksmodule/bookmark_model_plugin.h>

void BookmarkmodelPlugin::registerTypes(const char* uri) {
  Q_ASSERT(uri == QLatin1String("Bookmarkmodelplugin"));
  qmlRegisterType<Bookmarkmodel, 1>(uri, 1, 0, "Bookmarkmodel");
}
