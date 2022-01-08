//
//  file_access_provider.h
//  Renderer
//
//  Created by krzysp on 19/12/2021.
//

#ifndef file_access_provider_h
#define file_access_provider_h

#include <iostream>
#include "common.h"

namespace engine
{
    /**
     Provides an abstraction over file access.
     */
    class FileStreamI
    {
    public:
        FileStreamI(std::string filename): m_filename(filename) { };
        virtual ~FileStreamI() { };
        std::string &GetFilename() { return m_filename; };

    public: // file operations
        /**
         *  Return the size of the file, or -1 if unknown
         */
        int64_t &GetSize() { return m_size; };

        /**
         *  Seek to \c offset relative to \c whence, one of stdio's whence values:
         *  RW_SEEK_SET, RW_SEEK_CUR, RW_SEEK_END
         *
         *  \return the final offset in the data stream, or -1 on error.
         */
        virtual int64_t Seek(int64_t offset, int whence) = 0;

        /**
         *  Read up to \c maxnum objects each of size \c size from the data
         *  stream to the area pointed at by \c ptr.
         *
         *  \return the number of objects read, or 0 at error or end of file.
         */
        virtual size_t Read(void *ptr, size_t size, size_t maxnum) = 0;

    public: // helpers
        /** Helper to read the whole file as string */
        virtual std::string ReadBufferString() = 0;

        /**
         Create a RW ops for SDL. Only one such operation can be performed
         at a given time.
         */
        virtual std::unique_ptr<SDL_RWops> CreateRWOps() = 0;

    protected:
        std::string m_filename;
        int64_t m_size;
    };

    /// Mapped file system onto the FileMemoryBufferStreamI
    /// when no packed data exists.
    class FileMemoryBufferStreamFromFile: public FileStreamI
    {
        FILE *m_fp;
    public:
        FileMemoryBufferStreamFromFile(std::string filename);
        virtual ~FileMemoryBufferStreamFromFile();

        int64_t Seek(int64_t offset, int whence);
        size_t Read(void *ptr, size_t size, size_t maxnum);
        std::string ReadBufferString();
        std::unique_ptr<SDL_RWops> CreateRWOps();
    };

    /// Memory access for the file chunk in the packed system.
    class FileMemoryBufferStreamFromBundle: public FileStreamI
    {

    };

    /// Main accessor for files. Returns FileMemoryBufferI items
    /// so different part of the engine can load the data from a
    /// byte stream.
    class FileAccessI
    {
    public:
        /// Loads a packed file with all assets.
        /// This is incompatible with LoadDirectory.
        /// returns: 0 upon success, otherwise error
        virtual int LoadPackedFile(std::string filename) = 0;

        /// Loads a directory for loading files directly off the file system.
        /// This is incompatible with LoadPackedFile.
        /// returns: 0 upon success, otherwise error
        virtual int LoadDirectory(std::string directory) = 0;

        /// Get the default resources directory. Should be connected
        /// to the main application directory.
        virtual std::string GetResourcesDirectory() = 0;

    public:

        /// Loads up a buffer stream for a specific filename. If the FileAccessI
        /// was setup up with a directory a FileMemoryBufferStreamFromFile
        /// will be returned. In case of a packaed resource file this will
        /// return FileMemoryBufferStreamFromBundle.
        /// Memory ownership is passed to the caller.
        virtual FileStreamI *GetAccess(std::string filename) = 0;

    public:
        /// Get a file path for a specific name. Main bundle will be used.
        virtual std::string getBundledFilepath(const char *value) = 0;

        virtual std::string loadText(std::string filename) = 0;

        /// Load a buffer stream for a specific chunk named `filename`.
        /// If no packed data is presetend the system will try to load the data
        /// from the file system. The ownership is passed onto the caller.
        virtual FileStreamI *LoadBufferStream(const char *filename) = 0;

    public:
        // tmp
        virtual std::string GetFullPath(std::string filename) = 0;
    };
};

#endif /* file_access_provider_h */
