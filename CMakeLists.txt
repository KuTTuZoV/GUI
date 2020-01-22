set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Qt/5.14.0/mingw73_32")

find_package(Qt5Core REQUIRED)

find_package(Qt5Gui REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_executable(_GUI main.cpp mainwindow.cpp mainwindow.h ../../pluginGUI/widget.cpp ../../pluginGUI/widget.h)

qt5_use_modules(_GUI Core GUI Xml Widgets)

