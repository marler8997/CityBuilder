#pragma once

#include <vector>
#include <map>

#include "Texture.h"

class Grid;
struct TilePosition;
struct Unit;

enum class InventoryReason
{
	Full, MoreThanHalf, MoreThanOne
};

class UnitManager
{
public:
	explicit UnitManager(Grid& grid);

private:
	Grid& _grid;
	std::vector<Unit> _units;

	// Unit tick functions
	void OnTickUnitSawMill(Unit& unit);

	void OnTickUnitBuilderHut(Unit& unit);
	void onTickUnitLogistician(Unit& unit);

	Characters GetCharacter(int jobTileIndex);
	bool IsTileTakenCareBy(TilePosition position, Characters character);
	bool IsTileJobFull(int jobTileIndex);
	int GetMaxUnitOnJob(int jobTileIndex);
	int CountHowManyUnitAreWorkingOn(int jobTileIndex);

	// Utility
	std::vector<TilePosition> GetAllHarvestableTrees(TilePosition position, int radius);
	bool NeedToDropItemsAtJob(Unit& unit, Items item, InventoryReason reason);
	// Get all tiles that are around the position and have enough storage for the item
	std::vector<TilePosition> GetStorageAroundFor(TilePosition position, int radius, Items item);
	std::vector<TilePosition> GetAllBuildableOrDestroyableTiles();
	// Get all tiles that need items to be built but has enough total items to be built
	std::vector<TilePosition> GetTilesThatNeedItemsToBeBuilt();
	std::vector<TilePosition> GetStorageThatHave(Items item);
	std::vector<int> GetAvailableJobs();

	// Inventory
	int GetMaxItemsFor(Unit& unit, Items item);
	static bool IsInventoryEmpty(Unit& unit);
	std::map<Items, int> GetAllUsableItems();

public:
	void UpdateUnits();
	void DrawUnits();

	void AddUnit(const Unit& unit);
};