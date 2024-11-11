#pragma once

class StringTable : public DataTable
{
public:
	static std::wstring Undefined;
protected:
	// <T1, T2>
	//	T1: ��Ʈ�� ���̵�
	//	T2: �� ��Ʈ�� ([0] �ѱ��� [1] ���� ...)
	std::unordered_map<std::string, std::vector<std::wstring>> table;
	/*std::unordered_map < std::string, std::wstring> table;*/

	std::string filePath = "tables/string_table.csv";
	//std::string filePath = "tables/string_table";



public:
	StringTable() : DataTable(DataTable::Types::String) { };
	~StringTable() = default;

	bool Load() override;
	/*bool Load(Languages lang);*/
	void Release() override;

	const std::wstring& Get(const std::string& id);
	const std::wstring& Get(const std::string& id, Languages lang);

};