// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <map>
#include <set>
#include <vector>

class ANodeInfo;
class AStarNode;
class __InternalPathInfo;

class ANodeDistance
{
public:
	bool operator() (AStarNode* lhs, AStarNode* rhs) const;
};

/**
 * 
 */
class ORCVSHUMAN_API PathFinding
{
public:
	static PathFinding& Instance()
	{
		return instance;
	}

	void generatePath(const FVector2D& _position, const FVector2D& _target, std::vector<FVector2D> &_path);

private:
	AStarNode* addNodes(std::multiset<AStarNode*, ANodeDistance>::iterator& itNode, ANodeInfo& _tileInfo);
	AStarNode* findNodeInOpenList(const FVector2D& _index);

private:
	/// <summary>	Information describing the internal. </summary>
	__InternalPathInfo* internalInfo;


	/// <summary>	Singleton Setting. </summary>
	static PathFinding instance;
	PathFinding();
	~PathFinding();
	inline explicit PathFinding(PathFinding const&)
	{
	}
	inline PathFinding& operator=(PathFinding const&)
	{
		return *this;
	}
};
