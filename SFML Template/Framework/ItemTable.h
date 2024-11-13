#pragma once
#include "Item.h"
#include "DataTable.h"

struct DataRecovery
{
	ItemTypes type;
	Item::RecoveryType recoveryType;
	std::string textureId;
	int amount;
};

class ItemTable :
    public DataTable
{
	static DataRecovery Undefined;
protected:
	std::unordered_map<ItemTypes, std::string> table;
	std::unordered_map<ItemTypes, DataRecovery> recoveryTable;
	std::string tablePath = "tables/item_table.csv";
	std::string recoveryTablePath = "tables/item_recovery_table.csv";
public:
	ItemTable() : DataTable(DataTable::Types::Item) { };
	~ItemTable() = default;

	bool Load() override;
	void Release() override;

	const DataRecovery& Get(ItemTypes id);
};


