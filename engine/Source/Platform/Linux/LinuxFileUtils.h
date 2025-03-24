#pragma once

#include "Utils/FileUtils.h"

namespace Triangl
{
	class LinuxFileUtils : public NativeFileUtils
	{
	public:
		virtual bool Exists(std::string_view path) const override;
		virtual bool IsFile(std::string_view path) const override;
		virtual bool IsDir(std::string_view path) const override;
		virtual ssize_t GetFileSize(std::string_view path) const override;

		virtual std::string Rel(std::string_view path, std::string pathRelativeTo) const override;
		virtual std::string Abs(std::string_view path) const override;

		virtual std::string GetWorkingDir() const override;
		virtual bool SetWorkingDir(std::string_view path) const override;

		virtual bool CreateNewFile(std::string_view path) override;
		virtual bool CreateNewDir(std::string_view path) override;
		virtual bool RemoveFile(std::string_view path) override;
		virtual bool RemoveDir(std::string_view path) override;

		virtual bool ReadFromFile(std::string_view path, std::string& outData) override;
		virtual bool WriteToFile(std::string_view path, const void* data, size_t size, bool append = false) override;
	};
}
