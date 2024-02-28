#pragma once
#include <string.h>

class StringHelper
{
private:
	StringHelper();
	virtual ~StringHelper();
	StringHelper(const StringHelper&) = delete;
	StringHelper& operator=(const StringHelper&) = delete;

public:
	static std::vector<std::wstring> VecToWVec(const std::vector<std::string>& vec);
	static std::vector<std::string>  WVecToVec(const std::vector<std::wstring>& wvec);

	static std::wstring StrToWStr(const std::string& str);
	static std::string WStrToStr(const std::wstring& wstr);
	static std::wstring SplitFilePathExtension(const std::wstring& filePath);

	static void SplitDirectoryPathAndFileName(const std::wstring& filePath,
		std::wstring* outDirectoryPath,
		std::wstring* outFileName);

	static void SplitRootNameAndFilePath(const std::wstring& filePath,
		std::wstring* outRootName,
		std::wstring* outFilePath);

	static std::wstring SWPrintf(const wchar_t* const format, ...);

	static std::wstring GetDirectoryNameFromPath(const std::wstring& filePath);
	static std::wstring GetFileNameFromPath(const std::wstring& filePath);
};
