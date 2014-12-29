#ifndef LIBRARYLOADER_H
#define LIBRARYLOADER_H

#include <stdexcept>
#include <string>



/**
 * Represents errors in working with dinamically loaded libraries.
 */
class LibraryLoaderException: public std::runtime_error
{
public:
    /**
     * @param message desctiption of the error.
     */
    LibraryLoaderException(const std::string& message):
        std::runtime_error(message)
    {}
};



/**
 * Abstract base class for dinamically loaded libraries.
 */
class LibraryLoader
{
public:
    /**
     * Default virtual destructor.
     */
    virtual ~LibraryLoader() = default;

    /**
     * @param functionName name of the function to bind.
     * @returns a function pointer cast to type T.
     * @throws LibraryLoader exception if the function cannot be bound.
     */
    template<typename T> T bindFunction(const std::string& functionName) {
        void* rawPointer = bindRawPointer(functionName);
        if (rawPointer == nullptr) {
            throw LibraryLoaderException(
                    "Trying to bind null function pointer.");
        }
        // -pedantic complains about direct void* to function pointer cast.
        return reinterpret_cast<T>(reinterpret_cast<size_t>(rawPointer));
    }
protected:
    /**
     * @param functionName name of the function to bind.
     * @returns a function pointer cast to void*.
     * @throws LibraryLoader exception if the function cannot be bound.
     */
    virtual void* bindRawPointer(const std::string& functionName) = 0;
};



#define DECLARE_POINTER(function) decltype(&::function) const function;
#define BIND_POINTER(function) \
        ,function(libraryLoader.bindFunction<decltype(function)>(#function))



#endif // LIBRARYLOADER_H
