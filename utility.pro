TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    libraryloader \
    linalg \
    logger

OTHER_FILES += \
    compilerflags.pri \
    LICENSE \
    .gitignore

