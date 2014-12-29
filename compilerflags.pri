QMAKE_CXXFLAGS += \
    -Wall \
    -Wextra \
    -Wdocumentation \
    -Werror \
    -pedantic-errors \
    -std=gnu++11 \
    -frtti \
    -fexceptions \
    -fvisibility=hidden

QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

