#include "TrianglPCH.h"
#include "LinuxFileUtils.h"

namespace Triangl
{
	bool LinuxFileUtils::Exists(std::string_view path) const
	{
		return false;
	}

	bool LinuxFileUtils::IsFile(std::string_view path) const
	{
		return false;
	}

	bool LinuxFileUtils::IsDir(std::string_view path) const
	{
		return false;
	}

	ssize_t LinuxFileUtils::GetFileSize(std::string_view path) const
	{
		return -1;
	}

	std::string LinuxFileUtils::Rel(std::string_view path, std::string pathRelativeTo) const
	{
		return "";
	}

	std::string LinuxFileUtils::Abs(std::string_view path) const
	{
		return "";
	}

	std::string LinuxFileUtils::GetWorkingDir() const
	{
		return "";
	}

	bool LinuxFileUtils::SetWorkingDir(std::string_view path) const
	{
		return false;
	}

	bool LinuxFileUtils::CreateNewFile(std::string_view path)
	{
		return false;
	}

	bool LinuxFileUtils::CreateNewDir(std::string_view path)
	{
		return false;
	}

	bool LinuxFileUtils::RemoveFile(std::string_view path)
	{
		return false;
	}

	bool LinuxFileUtils::RemoveDir(std::string_view path)
	{
		return false;
	}

	bool LinuxFileUtils::ReadFromFile(std::string_view path, std::string& out_data)
	{
		return false;
	}

	bool LinuxFileUtils::WriteToFile(std::string_view path, const void* data, size_t size, bool append)
	{
		return false;
	}
}
