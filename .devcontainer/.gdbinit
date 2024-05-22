python
import sys
sys.path.insert(0, '/usr/share/gdb/python/gdb/command/')
sys.path.insert(0, '/usr/share/gdb/python/gdb/printer/')
sys.path.insert(0, '/usr/share/gdb/python/gdb/')

from libstdcxx.v6.printers import register_libstdcxx_printers
register_libstdcxx_printers (None)
end

sys.path.insert(0, '/workspaces/qt-creator/share/qtcreator/debugger/')
from qt5printers import register_qt_printers
register_qt_printers (None)

set print pretty on
set debug pretty 1
set logging on
