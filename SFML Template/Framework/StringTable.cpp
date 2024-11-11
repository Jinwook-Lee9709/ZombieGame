#include "stdafx.h"
#include "StringTable.h"
#include "rapidcsv.h"

std::wstring StringTable::Undefined = L"Undefined Id";

bool StringTable::Load()
{
	Release();
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));
	for (int i = 0; i < doc.GetRowCount(); ++i)
	{
		std::vector<std::string> strings = doc.GetRow<std::string>(i);
		auto it = table.find(strings[0]);
		if (it != table.end())
		{
			std::cout << "��Ʈ�� ���̺� Ű �ߺ�!" << std::endl;
			return false;
		}

		for (int j = 0; j < (int)Languages::Count; ++j)
		{
			auto& vec = table[strings[0]];
			vec.resize((int)Languages::Count);
			vec[j] = converter.from_bytes(strings[j + 1]);
		}
	}

	return true;
}

//bool StringTable::Load(Languages lang = Languages::English)
//{
//	Release();
//	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
//	std::string path;
//	switch (lang) {
//		case Languages::Korean:
//		{
//			path = filePath + "_korean.csv";
//			break;
//		}
//		case Languages::English:
//		{
//			path = filePath + "_english.csv";
//			break;
//		}
//	}
//		
//	rapidcsv::Document doc(path, rapidcsv::LabelParams(0, -1));
//	for (int i = 0; i < doc.GetRowCount(); i++) {
//		std::vector<std::string> key = doc.GetRow<std::string>(i);
//		auto it = table.find(key[0]);
//		if (it != table.end())
//		{
//			std::cout << "��Ʈ�� ���̺� Ű �ߺ�!" << std::endl;
//			return false;
//		}
//
//		for (int j = 0; j < (int)Languages::Count; ++j)
//		{
//			table[key[0]] = converter.from_bytes(key[1]);
//		}
//	}
//}

void StringTable::Release()
{
	table.clear();
}

const std::wstring& StringTable::Get(const std::string& id)
{
	return Get(id, Variables::currentLang);
}

const std::wstring& StringTable::Get(const std::string& id, Languages lang)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}
	//return find->second;
	return (find->second)[(int)lang];
}
