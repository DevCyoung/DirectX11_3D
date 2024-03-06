#include "pch.h"
#include "FileHelper.h"

void SaveWString(const std::wstring& str, FILE* file)
{
	UINT len = static_cast<UINT>(str.length());
	fwrite(&len, sizeof(UINT), 1, file);
	fwrite(str.c_str(), sizeof(wchar_t), str.length(), file);
}

void LoadWString(std::wstring* const str, FILE* _File)
{
	wchar_t szBuffer[512] = {};

	UINT iLen = 0;
	fread(&iLen, sizeof(UINT), 1, _File);
	Assert(iLen < 512, ASSERT_MSG_INVALID);
	fread(szBuffer, sizeof(wchar_t), iLen, _File);
	*str = szBuffer;
}
