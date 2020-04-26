#include <string>
#include "GameTiles.h"
#include "Utilities.h"
#include "GameAPI.h"

typedef UInt32 (* _TraitNameToID)(const char* traitName);

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0_15
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BE52B0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BE9BE0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BE9FA0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BE9F10;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BEAA90;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BEA9F0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BEA9E0;
#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng
	_TraitNameToID TraitNameToID = (_TraitNameToID)0x00BE7A10;
#else
#error unsupported fallout version
#endif

UInt32 Tile::TraitNameToID(const char* traitName)
{
	return ::TraitNameToID(traitName);
}

Tile::Value* Tile::GetValue(UInt32 typeID)
{
	// values are sorted so could use binary search but these are not paricularly large arrays
	for (UInt32 i = 0; i < values.size; i++)
	{
		Tile::Value* val = values[i];
		if (val && val->id == typeID)
			return val;
	}

	return NULL;
}

Tile::Value* Tile::GetValue(const char* valueName)
{
	UInt32 typeID = TraitNameToID(valueName);
	return GetValue(typeID);
}

Tile* Tile::GetChild(const char* childName)
{
	Tile* child = NULL;
	for (tList<ChildNode>::Iterator iter = childList.Begin(); !iter.End(); ++iter)
	{
		if (*iter && iter->child && !_stricmp(iter->child->name.m_data, childName))
		{
			child = iter->child;
			break;
		}
	}

	return child;
}

Tile::Value * Tile::GetComponentValue(const char* componentPath)
{
	Tokenizer tokens(componentPath, "\\/");
	std::string curToken;
	Tile * parentTile = this;

	while (tokens.NextToken(curToken) != -1 && parentTile)
	{
		DEBUG_PRINT("childName: %s", curToken.c_str());
		Tile* child = parentTile->GetChild(curToken.c_str());
		if (!child)
		{
			// didn't find child; is this last token?
			if (tokens.NextToken(curToken) == -1)
				return parentTile->GetValue(curToken.c_str());
			else	// nope, error
				return NULL;
		}
		else
			parentTile = child;
	}

	// couldn't locate one of the child nodes
	return NULL;
}

std::string Tile::GetQualifiedName()
{
	std::string qualifiedName;
	//if (parent && !parent->GetFloatValue(kTileValue_class, &parentClass))	// i.e., parent is not a menu
	if (parent)
		qualifiedName = parent->GetQualifiedName() + "\\";

	qualifiedName += name.m_data;

	return qualifiedName;
}
