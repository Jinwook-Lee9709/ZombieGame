#include "stdafx.h"
#include "ItemTable.h"
#include "rapidcsv.h"

DataRecovery ItemTable::Undefined;

bool ItemTable::Load()
{
	Release();

	rapidcsv::Document doc1(tablePath, rapidcsv::LabelParams(0, -1));
	for (int i = 0; i < doc1.GetRowCount(); ++i)
	{
		auto row = doc1.GetRow<std::string>(i);
		ItemTypes id = (ItemTypes)std::stoi(row[0]);
		if (table.find(id) != table.end()) {
			std::cout << "중복된 키값 오류" << std::endl;
			return false;
		}
		table[id] = row[1];
	}
	rapidcsv::Document doc2(recoveryTablePath, rapidcsv::LabelParams(0, -1));
	for (int i = 0; i < doc2.GetRowCount(); ++i)
	{
		auto row = doc2.GetRow<std::string>(i);
		ItemTypes id = (ItemTypes)std::stoi(row[0]);
		if (recoveryTable.find(id) != recoveryTable.end()) {
			std::cout << "중복된 키값 오류" << std::endl;
			return false;
		}
		recoveryTable[id].type = id;
		recoveryTable[id].recoveryType = (Item::RecoveryType)std::stoi(row[1]);
		recoveryTable[id].amount = std::stoi(row[2]);
		recoveryTable[id].textureId = row[3];
	}
}

void ItemTable::Release()
{
	table.clear();
	recoveryTable.clear();
}

const DataRecovery& ItemTable::Get(ItemTypes id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}
	if (find->second == "Recovery") {
		auto findR = recoveryTable.find(id);
		if (findR == recoveryTable.end())
		{
			return Undefined;
		}
		return findR->second;
	}
}
