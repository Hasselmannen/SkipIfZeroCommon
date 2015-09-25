#include "sfz/util/IO.hpp"
#include "sfz/Assert.hpp"

#include <cstdlib>
#include <cstdio> // fopen, fwrite, BUFSIZ
#include <cstdint>
#include <cstring>

#if defined(_WIN32)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlobj.h>
#include <direct.h>

#elif defined(__APPLE__)
#include <sys/stat.h>

#elif defined(__unix)
#include <sys/stat.h>
#endif

namespace sfz {

using std::size_t;
using std::uint8_t;

const string& myDocumentsPath() noexcept
{
	static const string path = []() {
#ifdef _WIN32
		char tempPath[MAX_PATH];
		HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, tempPath);
		if (result != S_OK) sfz_error("Could not retrieve MyDocuments path.");
		return string{tempPath};
#else
		return std::getenv("HOME");
#endif
	}();
	return path;
}

const string& gameBaseFolderPath() noexcept
{
	static const std::string path = myDocumentsPath() + "/My Games";
	return path;
}

bool fileExists(const char* path) noexcept
{
	std::FILE* file = std::fopen(path, "r");
	if (file == NULL) return false;
	std::fclose(file);
	return true;
}

bool directoryExists(const char* path) noexcept
{
#ifdef _WIN32
	std::FILE* file = std::fopen(path, "r");
	if (file == NULL) {
		DWORD ftyp = GetFileAttributesA(path);
		if (ftyp == INVALID_FILE_ATTRIBUTES) return false;
		if (ftyp & FILE_ATTRIBUTE_DIRECTORY) return true;
		return false;
	}
	std::fclose(file);
	return true;
#else
	std::FILE* file = std::fopen(path, "r");
	if (file == NULL) return false;
	std::fclose(file);
	return true;
#endif
}

bool createFile(const char* path) noexcept
{
	std::FILE* file = std::fopen(path, "w");
	if (file == NULL) return false;
	std::fclose(file);
	return true;
}

bool createDirectory(const char* path) noexcept
{
#ifdef _WIN32
	int res = _mkdir(path);
	return res == 0;
#else
	int res = mkdir(path, 0775);
	return res == 0;
#endif
}

bool deleteFile(const char* path) noexcept
{
	int res = std::remove(path);
	return res == 0;
}

bool deleteDirectory(const char* path) noexcept
{
#ifdef _WIN32
	int res = _rmdir(path);
	return res == 0;
#else
	int res = std::remove(path);
	return res == 0;
#endif
}

bool copyFile(const char* srcPath, const char* dstPath) noexcept
{
	uint8_t buffer[BUFSIZ];

	std::FILE* source = std::fopen(srcPath, "rb");
	std::FILE* destination = std::fopen(dstPath, "wb");
	if (source == NULL) return false;
	if (destination == NULL) return false;

	size_t size;
	while ((size = std::fread(buffer, 1, BUFSIZ, source)) > 0) {
		std::fwrite(buffer, 1, size, destination);
	}

	std::fclose(source);
	std::fclose(destination);

	return true;
}

int64_t sizeofFile(const char* path) noexcept
{
	std::FILE* file = std::fopen(path, "rb");
	if (file == NULL) return -1;
	std::fseek(file, 0, SEEK_END);
	int64_t size = std::ftell(file);
	std::fclose(file);
	return size;
}

vector<uint8_t> readBinaryFile(const char* path) noexcept
{
	// Open file
	std::FILE* file = std::fopen(path, "rb");
	if (file == NULL) return vector<uint8_t>{};

	// Get size of file
	std::fseek(file, 0, SEEK_END);
	int64_t size = std::ftell(file);
	std::rewind(file); // Rewind position to beginning of file
	if (size < 0) {
		std::fclose(file);
		return vector<uint8_t>{};
	}

	// Create vector with enough capacity to fit file
	vector<uint8_t> temp(static_cast<size_t>(size+1));
	uint8_t* tempPtr = temp.data();

	// Read the file into the vector
	uint8_t buffer[BUFSIZ];
	size_t readSize;
	while ((readSize = std::fread(buffer, 1, BUFSIZ, file)) > 0) {
		std::memcpy(tempPtr, buffer, readSize);
		tempPtr += readSize;
	}

	return std::move(temp);
}

} // namespace sfz