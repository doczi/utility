#ifndef DLLIBRARYLOADER_H
#define DLLIBRARYLOADER_H

#include "libraryloader.h"

#include <dlfcn.h>



/**
 * Dynamically loads libraries using libdl.
 */
class DlLibraryLoader: public LibraryLoader
{
public:
    /**
     * Opens a library.
     * @param libraryPath path of the library to open.
     */
    DlLibraryLoader(const std::string& libraryPath) {
        libraryHandle = dlopen(libraryPath.c_str(), RTLD_LAZY);
        if (libraryHandle == nullptr) {
            throw LibraryLoaderException(dlerror());
        }
    }

    /**
     * Closes the library.
     */
    ~DlLibraryLoader() override  {
        dlclose(libraryHandle);
    }
protected:
    /**
     * @see LibraryLoader::bindRawPointer
     */
    void* bindRawPointer(const std::string& functionName) override {
        void* pointer = dlsym(libraryHandle, functionName.c_str());
        if (pointer == nullptr) {
            throw LibraryLoaderException(dlerror());
        }
        return pointer;
    }
private:
    void* libraryHandle;
};



#endif // DLLIBRARYLOADER_H
