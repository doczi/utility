#ifndef QTLIBRARYLOADER_H
#define QTLIBRARYLOADER_H

#include "libraryloader.h"

#include <QLibrary>



/**
 * Dynamically loads libraries using QLibrary.
 */
class QtLibraryLoader: public LibraryLoader
{
public:
    /**
     * Opens a library.
     * @param libraryPath path of the library to open.
     */
    DlLibraryLoader(const std::string& libraryPath):
        library(QString::fromStdString(libraryPath))
    {
        library.load();
    }
protected:
    /**
     * @see LibraryLoader::bindRawPointer
     */
    void* bindRawPointer(const std::string& functionName) override {
        void* pointer = library.resolve(functionName.c_str());
        if (pointer == nullptr) {
            throw LibraryLoaderException(dlerror());
        }
        return pointer;
    }
private:
    QLibrary library;
};



#endif // QTLIBRARYLOADER_H
