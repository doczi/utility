TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    libraryloader \
    linalg \
    logger \
    test

OTHER_FILES += \
    compilerflags.pri \
    LICENSE \
    .gitignore

