#include "TrianglPCH.h"
#include "WindowsFileUtils.h"

namespace Triangl
{
	bool WindowsFileUtils::Exists(std::string_view path) const
	{
		DWORD dwAttribs = GetFileAttributesA(path.data());
		return dwAttribs != INVALID_FILE_ATTRIBUTES;
	}

	bool WindowsFileUtils::IsFile(std::string_view path) const
	{
		DWORD dwAttribs = GetFileAttributesA(path.data());
		return dwAttribs != INVALID_FILE_ATTRIBUTES && !(dwAttribs & FILE_ATTRIBUTE_DIRECTORY);
	}

	bool WindowsFileUtils::IsDir(std::string_view path) const
	{
		DWORD dwAttribs = GetFileAttributesA(path.data());
		return dwAttribs != INVALID_FILE_ATTRIBUTES && (dwAttribs & FILE_ATTRIBUTE_DIRECTORY);
	}

	ssize_t WindowsFileUtils::GetFileSize(std::string_view path) const
	{
		WIN32_FILE_ATTRIBUTE_DATA w32FileAttribData;

		if (!GetFileAttributesExA(path.data(), GetFileExInfoStandard, &w32FileAttribData))
		{
			return -1;
		}

		LARGE_INTEGER liSize;
		liSize.HighPart = w32FileAttribData.nFileSizeHigh;
		liSize.LowPart = w32FileAttribData.nFileSizeLow;

		return liSize.QuadPart;
	}

	std::string WindowsFileUtils::Rel(std::string_view path, std::string pathRelativeTo) const
	{
		// TODO
		return "";
	}

	std::string WindowsFileUtils::Abs(std::string_view path) const
	{
		char absPath[MAX_PATH];
		DWORD dwWritten = GetFullPathNameA(path.data(), MAX_PATH, absPath, nullptr);

		if (dwWritten == 0)
		{
			TL_CORE_ERROR("WindowsFileUtils::Abs error, failed to retrieve the absolute path of '{}', GetFullPathNameA reported 0 written bytes to the target buffer!", dwWritten);
			return "";
		}

		return absPath;
	}

	std::string WindowsFileUtils::GetWorkingDir() const
	{
		char wdir[MAX_PATH];
		DWORD dwWritten = GetCurrentDirectoryA(MAX_PATH, wdir);

		if (dwWritten == 0)
		{
			TL_CORE_ERROR("WindowsFileUtils::GetWorkingDir error, failed to retrieve the working dir, GetCurrentDirectoryA reported 0 written bytes to the target buffer!", dwWritten);
			return "";
		}

		return wdir;
	}

	bool WindowsFileUtils::SetWorkingDir(std::string_view path) const
	{
		if (!SetCurrentDirectoryA(path.data()))
		{
			TL_CORE_ERROR("WindowsFileUtils::SetWorkingDir error, couldn't change working dir to '{}', SetCurrentDirectoryA returned false!", path);
			return false;
		}
		return true;
	}

	bool WindowsFileUtils::CreateNewFile(std::string_view path)
	{
		HANDLE hFile = CreateFileA
		(
			path.data(),
			0,
			0,
			nullptr,
			CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL,
			nullptr
		);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			TL_CORE_ERROR("WindowsFileUtils::CreateNewFile error, failed to create file '{}'; CreateFileA returned INVALID_HANDLE_VALUE for the requested creation file!", path);
			return false;
		}

		CloseHandle(hFile);
		return true;
	}

	bool WindowsFileUtils::CreateNewDir(std::string_view path)
	{
		return CreateDirectoryA(path.data(), nullptr);
	}

	bool WindowsFileUtils::RemoveFile(std::string_view path)
	{
		return DeleteFileA(path.data());
	}

	bool WindowsFileUtils::RemoveDir(std::string_view path)
	{
		// TODO
		return false;
	}

	bool WindowsFileUtils::ReadFromFile(std::string_view path, std::string& outData)
	{
		HANDLE hFile = CreateFileA
		(
			path.data(),
			GENERIC_READ,
			FILE_SHARE_READ,
			nullptr,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			nullptr
		);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			TL_CORE_ERROR("WindowsFileUtils::ReadFromFile error, couldn't read from file '{}'; CreateFileA returned INVALID_HANDLE_VALUE!", path);
			return false;
		}

		DWORD dwSize = SetFilePointer(hFile, 0, 0, FILE_END);
		outData = std::string(dwSize, '\0');
		SetFilePointer(hFile, 0, 0, FILE_BEGIN);

		DWORD dwRead;
		if (!ReadFile(hFile, outData.data(), dwSize, &dwRead, nullptr))
		{
			TL_CORE_ERROR("WindowsFileUtils::ReadFromFile error, couldn't read from file '{}'; ReadFile returned FALSE!", path);
			CloseHandle(hFile);
			return false;
		}

		if (dwRead != dwSize)
		{
			TL_CORE_ERROR("WindowsFileUtils::ReadFromFile error, couldn't read from file '{}'; expected to read {} bytes but only read {}!", dwSize, dwRead);
			CloseHandle(hFile);
			return false;
		}
		
		CloseHandle(hFile);
		return true;
	}

	bool WindowsFileUtils::WriteToFile(std::string_view path, const void* data, size_t size, bool append)
	{
		return false;
	}
}
