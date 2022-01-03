//
//  file_access_provider.h
//  Renderer
//
//  Created by krzysp on 19/12/2021.
//

#ifndef file_access_provider_h
#define file_access_provider_h

#include <iostream>

namespace engine
{
    /// Most of the file in the game system should be
    /// packed so the FileMemoryBuffer encapsulates
    /// data neede for the buffer stream.
    class FileMemoryBufferStreamI
    {
    public:
        FileMemoryBufferStreamI(std::string filename): filename(filename) { };
        virtual ~FileMemoryBufferStreamI() { }; // memory descrutor moved to derived classes

        std::string &GetFilename() { return filename; };
        void *GetMemory() { return memory; };
        long &GetSize() { return size; };

    protected:
        std::string filename;
        void *memory;
        long size;
    };

    /// Mapped file system onto the FileMemoryBufferStreamI
    /// when no packed data exists.
    class FileMemoryBufferStreamFromFile: public FileMemoryBufferStreamI
    {
    public:
        FileMemoryBufferStreamFromFile(std::string filename);
        virtual ~FileMemoryBufferStreamFromFile();
    };

    /// Memory access for the file chunk in the packed system.
    class FileMemoryBufferStreamFromBundle: public FileMemoryBufferStreamI
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
        virtual FileMemoryBufferStreamI *GetAccess(std::string filename) = 0;

    public:
        /// Get a file path for a specific name. Main bundle will be used.
        virtual std::string getBundledFilepath(const char *value) = 0;

        virtual std::string loadText(std::string filename) = 0;

        /// Load a buffer stream for a specific chunk named `filename`.
        /// If no packed data is presetend the system will try to load the data
        /// from the file system. The ownership is passed onto the caller.
        virtual FileMemoryBufferStreamI *LoadBufferStream(const char *filename) = 0;

    public:
        // tmp
        virtual std::string GetFullPath(std::string filename) = 0;
    };
};

#endif /* file_access_provider_h */
