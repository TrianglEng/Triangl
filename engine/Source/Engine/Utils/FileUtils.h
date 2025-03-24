#pragma once

#include "Core/Base.h"

namespace Triangl
{
	class NativeFileUtils
	{
	public:
		virtual ~NativeFileUtils() = default;

		virtual bool Exists(std::string_view path) const = 0;
		virtual bool IsFile(std::string_view path) const = 0;
		virtual bool IsDir(std::string_view path) const = 0;
		virtual ssize_t GetFileSize(std::string_view path) const = 0;

		virtual std::string Rel(std::string_view path, std::string pathRelativeTo) const = 0;
		virtual std::string Abs(std::string_view path) const = 0;

		virtual std::string GetWorkingDir() const = 0;
		virtual bool SetWorkingDir(std::string_view path) const = 0;

		virtual bool CreateNewFile(std::string_view path) = 0;
		virtual bool CreateNewDir(std::string_view path) = 0;
		virtual bool RemoveFile(std::string_view path) = 0;
		virtual bool RemoveDir(std::string_view path) = 0;

		virtual bool ReadFromFile(std::string_view path, std::string& outData) = 0;
		virtual bool WriteToFile(std::string_view path, const void* data, size_t size, bool append = false) = 0;
	};

	class FileUtils
	{
	public:
		static bool Exists(std::string_view path)
		{
			return s_Instance->Exists(path);
		}

		static bool IsFile(std::string_view path)
		{
			return s_Instance->IsFile(path);
		}

		static bool IsDir(std::string_view path)
		{
			return s_Instance->IsDir(path);
		}

		static ssize_t GetFileSize(std::string_view path)
		{
			return s_Instance->GetFileSize(path);
		}

		static std::string Rel(std::string_view path, std::string pathRelativeTo)
		{
			return s_Instance->Rel(path, pathRelativeTo);
		}
		static std::string Rel(std::string_view path)
		{
			return Rel(path, GetWorkingDir());
		}

		static std::string Abs(std::string_view path)
		{
			return s_Instance->Abs(path);
		}

		static std::string GetWorkingDir()
		{
			return s_Instance->GetWorkingDir();
		}

		static bool SetWorkingDir(std::string_view path)
		{
			return s_Instance->SetWorkingDir(path);
		}

		static bool CreateNewFile(std::string_view path)
		{
			return s_Instance->CreateNewFile(path);
		}

		static bool CreateNewDir(std::string_view path)
		{
			return s_Instance->CreateNewDir(path);
		}

		/* Recursively created directories contrary to CreateNewDir, which can only create with a depth of one */
		static bool CreateNewDirs(std::string_view path)
		{

		}

		static bool Remove(std::string_view path)
		{
			if (IsFile(path))
			{
				return RemoveFile(path);
			}
			else if (IsDir(path))
			{
				return RemoveDir(path);
			}
			return false;
		}

		static bool RemoveFile(std::string_view path)
		{
			return s_Instance->RemoveFile(path);
		}

		static bool RemoveDir(std::string_view path)
		{
			return s_Instance->RemoveDir(path);
		}

		static bool ReadFromFile(std::string_view path, std::string& outData)
		{
			return s_Instance->ReadFromFile(path, outData);
		}

		static bool WriteToFile(std::string_view path, std::string_view data)
		{
			return s_Instance->WriteToFile(path, data.data(), data.size(), false);
		}

		static bool AppendToFile(std::string_view path, std::string_view data)
		{
			return s_Instance->WriteToFile(path, data.data(), data.size(), true);
		}

		static NativeFileUtils* Native() { return s_Instance.get(); }
	private:
		static Scope<NativeFileUtils> s_Instance;
	};
}
