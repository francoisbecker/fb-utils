#!/bin/sh
mv lest.hpp lest.bak.hpp
wget -c https://raw.githubusercontent.com/martinmoene/lest/master/include/lest/lest.hpp
diff lest.bak.hpp lest.hpp
rm lest.bak.hpp

