/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 15-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   filesSystems.hpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef FILESSYSTEMS_HPP
# define FILESSYSTEMS_HPP

# include <defines.hpp>

// Holds a handle to a file.
typedef struct	fileHandle
{
	// Opaque handle to internal file handle.
	void	*handle;
	bl8		isValid;
}	fileHandle;

typedef enum	fileModes
{
	FILE_MODE_READ = 0x1,
	FILE_MODE_WRITE = 0x2
}	fileModes;

/**
 * Checks if a file with the given path exists.
 * @param path The path of the file to be checked.
 * @returns True if exists; otherwise false.
 */
DE_API bl8	FilesystemExists(const char *path);

/**
 * Attempt to open file located at path.
 * @param path The path of the file to be opened.
 * @param mode Mode flags for the file when opened (read/write). See file_modes enum in filesystem.h.
 * @param binary Indicates if the file should be opened in binary mode.
 * @param outHandle A pointer to a file_handle structure which holds the handle information.
 * @returns True if opened successfully; otherwise false.
 */
DE_API bl8	FilesystemOpen(const char *path, fileModes mode, bl8 binary, fileHandle *outHandle);

/**
 * Closes the provided handle to a file.
 * @param handle A pointer to a file_handle structure which holds the handle to be closed.
 */
DE_API void	FilesystemClose(fileHandle *handle);

/**
 * Reads up to a newline or EOF. Allocates *line_buf, which must be freed by the caller.
 * @param handle A pointer to a file_handle structure.
 * @param lineBuf A pointer to a character array which will be allocated and populated by this method.
 * @returns True if successful; otherwise false.
 */
DE_API bl8	FilesystemReadLine(fileHandle *handle, char **lineBuf);

/**
 * Writes text to the provided file, appending a '\n' afterward.
 * @param handle A pointer to a file_handle structure.
 * @param text The text to be written.
 * @returns True if successful; otherwise false.
 */
DE_API bl8	FilesystemWriteLine(fileHandle *handle, const char *text);

/**
 * Reads up to data_size bytes of data into out_bytes_read.
 * Allocates *out_data, which must be freed by the caller.
 * @param handle A pointer to a file_handle structure.
 * @param dataSize The number of bytes to read.
 * @param outData A pointer to a block of memory to be populated by this method.
 * @param outBytesRead A pointer to a number which will be populated with the number of bytes actually read from the file.
 * @returns True if successful; otherwise false.
 */
DE_API bl8	FilesystemRead(fileHandle *handle, uint64 dataSize, void *outData, uint64 *outBytesRead);

/**
 * Reads up to data_size bytes of data into out_bytes_read.
 * Allocates *out_bytes, which must be freed by the caller.
 * @param handle A pointer to a file_handle structure.
 * @param outBytes A pointer to a byte array which will be allocated and populated by this method.
 * @param outBytesRead A pointer to a number which will be populated with the number of bytes actually read from the file.
 * @returns True if successful; otherwise false.
 */
DE_API bl8	FilesystemReadAllBytes(fileHandle *handle, uint8 **outBytes, uint64 *outBytesRead);

/**
 * Writes provided data to the file.
 * @param handle A pointer to a file_handle structure.
 * @param dataSize The size of the data in bytes.
 * @param data The data to be written.
 * @param outBytesWritten A pointer to a number which will be populated with the number of bytes actually written to the file.
 * @returns True if successful; otherwise false.
 */
DE_API bl8	FilesystemWrite(fileHandle *handle, uint64 dataSize, const void *data, uint64 *outBytesWritten);

#endif
