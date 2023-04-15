/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 15-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   filesSystems.cpp       *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <platform/filesSystems.hpp>

#include <core/logger.hpp>
#include <core/deMemory.hpp>

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

bl8		FilesystemExists(const char *path)
{
	struct stat buffer;
	return stat(path, &buffer) == 0;
}

bl8		FilesystemOpen(const char *path, fileModes mode, bl8 binary, fileHandle *outHandle)
{
	outHandle->isValid = false;
	outHandle->handle = 0;
	const char *modeStr;

	if ((mode & FILE_MODE_READ) != 0 && (mode & FILE_MODE_WRITE) != 0)
	{
		modeStr = binary ? "w+b" : "w+";
	}
	else if ((mode & FILE_MODE_READ) != 0 && (mode & FILE_MODE_WRITE) == 0)
	{
		modeStr = binary ? "rb" : "r";
	}
	else if ((mode & FILE_MODE_READ) == 0 && (mode & FILE_MODE_WRITE) != 0)
	{
		modeStr = binary ? "wb" : "w";
	}
	else
	{
		DE_ERROR("Invalid mode passed while trying to open file: '%s'", path);
		return false;
	}

	// Attempt to open the file.
	FILE *file = fopen(path, modeStr);
	if (!file)
	{
		DE_ERROR("Error opening file: '%s'", path);
		return false;
	}

	outHandle->handle = file;
	outHandle->isValid = true;

	return true;
}

void	FilesystemClose(fileHandle *handle)
{
	if (handle->handle)
	{
		fclose((FILE *)handle->handle);
		handle->handle = 0;
		handle->isValid = false;
	}
}

bl8		FilesystemReadLine(fileHandle *handle, char **lineBuf)
{
	if (handle->handle)
	{
		// Since we are reading a single line, it should be safe to assume this is enough characters.
		char buffer[32000];
		if (fgets(buffer, 32000, (FILE *)handle->handle) != 0)
		{
			uint64 length = strlen(buffer);
			*lineBuf = (char *)Mallocate((sizeof(char) * length) + 1, DE_MEMORY_TAG_STRING);
			strcpy(*lineBuf, buffer);

			return true;
		}
	}

	return false;
}

bl8		FilesystemWriteLine(fileHandle *handle, const char *text)
{
	if (handle->handle)
	{
		sint32 result = fputs(text, (FILE *)handle->handle);
		if (result != EOF)
		{
			result = fputc('\n', (FILE *)handle->handle);
		}

		// Make sure to flush the stream so it is written to the file immediately.
		// This prevents data loss in the event of a crash.
		fflush((FILE *)handle->handle);
		return result != EOF;
	}
	return false;
}

bl8		FilesystemRead(fileHandle *handle, uint64 dataSize, void *outData, uint64 *outBytesRead)
{
	if (handle->handle && outData)
	{
		*outBytesRead = fread(outData, 1, dataSize, (FILE *)handle->handle);
		if (*outBytesRead != dataSize)
		{
			return false;
		}
		return true;
	}
	return false;
}

bl8		FilesystemReadAllBytes(fileHandle *handle, uint8 **outBytes, uint64 *outBytesRead)
{
	if (handle->handle)
	{
		// File size
		fseek((FILE *)handle->handle, 0, SEEK_END);
		uint64 size = ftell((FILE *)handle->handle);
		rewind((FILE *)handle->handle);

		*outBytes = (uint8 *)Mallocate(sizeof(uint8) * size, DE_MEMORY_TAG_STRING);
		*outBytesRead = fread(*outBytes, 1, size, (FILE *)handle->handle);
		if (*outBytesRead != size)
		{
			return false;
		}

		return true;
	}

	return false;
}

bl8		FilesystemWrite(fileHandle *handle, uint64 dataSize, const void *data, uint64 *outBytesWritten)
{
	if (handle->handle)
	{
		*outBytesWritten = fwrite(data, 1, dataSize, (FILE *)handle->handle);
		if (*outBytesWritten != dataSize)
		{
			return false;
		}
		fflush((FILE *)handle->handle);
		
		return true;
	}

	return false;
}
