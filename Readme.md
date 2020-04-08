# BookmarkWidgets
This is a plasmoid for plasma 5. The original goal was to replace the bookmarkplasmoid of KDE4. 
It can only display bookmark (in *bookmarks.xml* format). If you want to edit it, you will need **keditbookmark**
It can displays the content of what used to be *konqueror* bookmarks, *as well as okular* (pdf) bookmarks. 
Support for any Software that uses *bookmarks.xml* structure to save its bookmarks (Marble, Konsole ... ?) should be pretty straightforward to implement

If you like this plasmoid, up me on [opendesktop](https://www.opendesktop.org/c/1519558653)

## Architecture
It has a qml frontend (for the plasmoid in itself) and a C++ backend to analyze the bookmark repositories


## TODO 

* [ ] Support for Firefox bookmarks
* [ ] Extend unit-tests to cover all implemented use cases
    * [ ] Debug/understand why bookmarksmodule_test::get_correct_number_of_element_for_chrome_bookmarks fails

## Compile instruction 
Under ubuntu you will need

    git clone https://github.com/renn0xtek9/BookMarkWidgets.git
    cd BookMarkWidgets
    sudo apt install extra-cmake-modules plasma-framework-dev qtdeclarative5-dev libkf5iconthemes-dev build-essentials g++
    ./install.sh
    
    
## Known bugs 

* The plasmoid does not catch the focus correctly (i.e. using  keyboard arrows does not mobe index in the list). This bug is believed to be caused by framework. And I have not really clue / time to solve it. (We need to analyze it using gammarays)

## Changelog 
Version 2.0.2 
Version 2.0.1 
Version 2.0.0
- Added search feature
- Add support for Google Chrome bookmarks 









Version number:2.0.2
