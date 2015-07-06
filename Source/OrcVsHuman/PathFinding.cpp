// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "PathFinding.h"
#include "GameInfo.h"

PathFinding PathFinding::instance;

#pragma optimize("", off)

///-------------------------------------------------------------------------------------------------
/// <summary>	Information about the tile. </summary>
///
/// <remarks>	William Barry, 15/01/2014. </remarks>
///-------------------------------------------------------------------------------------------------
class ANodeInfo
{
public:
	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the hash. </summary>
	///
	/// <remarks>	William Barry, 05/02/2013. </remarks>
	///
	/// <returns>	. </returns>
	///-------------------------------------------------------------------------------------------------
	long			Hash()
	{
		return (((int)mIndex.X << 16) | (int)mIndex.Y);
	}

	/// <summary>	The World space location. </summary>
	FVector2D		mLocation;

	/// <summary>	The index, x is Column, y is Row. </summary>
	FVector2D		mIndex;
};

///-------------------------------------------------------------------------------------------------
/// <summary>	Star node. </summary>
///
/// <remarks>	William Barry, 08/02/2013. </remarks>
///-------------------------------------------------------------------------------------------------
class AStarNode
{
public:
	///-------------------------------------------------------------------------------------------------
	/// <summary>	Constructor. </summary>
	///
	/// <remarks>	William Barry, 08/02/2013. </remarks>
	///
	/// <param name="_parent">  	[in,out] If non-null, the parent. </param>
	/// <param name="_tileInfo">	Information describing the tile. </param>
	/// <param name="g">			The float to process. </param>
	/// <param name="h">			The height. </param>
	///-------------------------------------------------------------------------------------------------
	AStarNode(AStarNode* _parent, ANodeInfo _tileInfo, float g, float h)
	{
		mParent = _parent;
		mTileInfo = _tileInfo;
		G = g;
		H = h;
	}

	AStarNode*		mParent;
	ANodeInfo		mTileInfo;
	float			G;
	float			H;
	float			F()		{ return G + H; }
};

bool ANodeDistance::operator() (AStarNode* lhs, AStarNode* rhs) const
{
	return (lhs->F() < rhs->F());
}

class __InternalPathInfo
{
public:
	/// <summary>	Target for the. </summary>
	FVector2D											mTarget;
	/// <summary>	List of opens. </summary>
	std::multiset<AStarNode*, ANodeDistance>			mOpenList;
	/// <summary>	List of closeds. </summary>
	std::map<long, AStarNode*>							mClosedList;
	/// <summary>	List of moves. </summary>
	std::vector<FVector2D>								mMoveList;

	friend class PathFinding;
};

float calculateHuristic(FVector2D& _position, FVector2D& _target)
{
	return FVector2D::Distance(_position, _target);
}

FVector2D getTileIndex(const FVector2D& _position)
{
	return FVector2D((int)(_position.X / TILESIZE_WIDTH), (int)(_position.Y / TILESIZE_HEIGHT));
}

void getNodeInfo(const FVector2D& _location, ANodeInfo* _tileInfo)
{
	_tileInfo->mIndex.X = (int)(_location.X / TILESIZE_WIDTH);
	_tileInfo->mIndex.Y = (int)(_location.Y / TILESIZE_HEIGHT);

	_tileInfo->mLocation.X = _tileInfo->mIndex.X * TILESIZE_WIDTH;
	_tileInfo->mLocation.Y = _tileInfo->mIndex.Y * TILESIZE_HEIGHT;
}

void getNodeInfo(const int _column, const int _row, ANodeInfo* _tileInfo)
{
	_tileInfo->mIndex.X = (int)(_column);
	_tileInfo->mIndex.Y = (int)(_row);

	_tileInfo->mLocation.X = _column * TILESIZE_WIDTH;
	_tileInfo->mLocation.Y = _row * TILESIZE_HEIGHT	;
}

PathFinding::PathFinding()
{
	internalInfo = new __InternalPathInfo();

	internalInfo->mMoveList.push_back(FVector2D(0, -1));
	internalInfo->mMoveList.push_back(FVector2D(-1, 0));
	internalInfo->mMoveList.push_back(FVector2D(1, 0));
	internalInfo->mMoveList.push_back(FVector2D(0, 1));
}

PathFinding::~PathFinding()
{
	std::multiset<AStarNode*, ANodeDistance>::iterator it;
	for (it = internalInfo->mOpenList.begin(); it != internalInfo->mOpenList.end(); it++)
	{
		delete (*it);
	}
	internalInfo->mOpenList.clear();

	for (std::map<long, AStarNode*>::iterator it = internalInfo->mClosedList.begin(); it != internalInfo->mClosedList.end(); it++) {
		delete it->second;
		it->second = NULL;
	}
	internalInfo->mClosedList.clear();

	delete internalInfo;
}

void PathFinding::generatePath(const FVector2D& _position, const FVector2D& _target, std::vector<FVector2D> &_path)
{
	_path.clear();

	internalInfo->mOpenList.clear();
	internalInfo->mClosedList.clear();

	ANodeInfo _nodeInfo;
	getNodeInfo(_target, &_nodeInfo);
	internalInfo->mTarget = _nodeInfo.mLocation;

	// First insert the initial Node into the Open List
	getNodeInfo(_position, &_nodeInfo);
	AStarNode *currentNode = new AStarNode(NULL, _nodeInfo, 0, calculateHuristic(_nodeInfo.mLocation, internalInfo->mTarget));
	internalInfo->mOpenList.insert(currentNode);

	AStarNode* target = NULL;

	while (internalInfo->mOpenList.size() > 0)
	{
		// Grab the lowest Node from the Open List
		std::multiset<AStarNode*, ANodeDistance>::iterator low = internalInfo->mOpenList.begin();

		// Add the currentnode to closedmap and adjacent nodes around to openlist
		target = addNodes(low, _nodeInfo);
		if (target != NULL)
		{
			break;
		}
	}

	while (target != NULL)
	{
		_path.push_back(target->mTileInfo.mLocation);
		target = target->mParent;
	}

	std::multiset<AStarNode*, ANodeDistance>::iterator it;
	for (it = internalInfo->mOpenList.begin(); it != internalInfo->mOpenList.end(); it++)
	{
		delete (*it);
	}
	internalInfo->mOpenList.clear();

	for (std::map<long, AStarNode*>::iterator it = internalInfo->mClosedList.begin(); it != internalInfo->mClosedList.end(); it++) {
		delete it->second;
		it->second = NULL;
	}
	internalInfo->mClosedList.clear();
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Adds the nodes. </summary>
///
/// <remarks>	William Barry, 15/01/2014. </remarks>
///
/// <param name="_map">			[in,out] If non-null, the map. </param>
/// <param name="itNode">   	[in,out] [in,out] If non-null, the iterator node. </param>
/// <param name="_tileInfo">	[in,out] Information describing the tile. </param>
///
/// <returns>	null if it fails, else. </returns>
///-------------------------------------------------------------------------------------------------
AStarNode* PathFinding::addNodes(std::multiset<AStarNode*, ANodeDistance>::iterator& itNode, ANodeInfo& _tileInfo)
{
	AStarNode* currentNode = (*itNode);
	internalInfo->mOpenList.erase(itNode);

	long address = currentNode->mTileInfo.Hash();
	std::map<long, AStarNode*>::iterator mapCheck = internalInfo->mClosedList.find(currentNode->mTileInfo.Hash());
	if (mapCheck == internalInfo->mClosedList.end())
	{
		internalInfo->mClosedList[currentNode->mTileInfo.Hash()] = currentNode;
		if ((int)(currentNode->mTileInfo.mLocation.X) == (int)(internalInfo->mTarget.X) && 
			(int)(currentNode->mTileInfo.mLocation.Y) == (int)(internalInfo->mTarget.Y))
		{
			return currentNode;
		}
	}

	for (int i = 0; i < internalInfo->mMoveList.size(); i++)
	{
		int column = currentNode->mTileInfo.mIndex.X + internalInfo->mMoveList[i].X;
		int row = currentNode->mTileInfo.mIndex.Y + internalInfo->mMoveList[i].Y;

		// If there is a collision we can ignore it
		if (GameInfo::Instance().getCollisionAt(column, row) == true) 
			continue;

		getNodeInfo(column, row, &_tileInfo);

		// If this tile is already in the closed list we can ignore it.
		mapCheck = internalInfo->mClosedList.find(_tileInfo.Hash());
		if (mapCheck != internalInfo->mClosedList.end()) continue;

		AStarNode* _node = findNodeInOpenList(_tileInfo.mIndex);

		// 1) If the node is not in the OpenList then add it
		// 2) Otherwise check if we need to update the G score
		if (_node == NULL)
		{
			float gScore = FVector2D::Distance(currentNode->mTileInfo.mLocation, _tileInfo.mLocation) + currentNode->G;
			float hScore = calculateHuristic(_tileInfo.mLocation, internalInfo->mTarget);
			AStarNode *newNode = new AStarNode(currentNode, _tileInfo, gScore, hScore);
			internalInfo->mOpenList.insert(newNode);
		}
		else
		{
			float gScore = FVector2D::Distance(currentNode->mTileInfo.mLocation, _tileInfo.mLocation) + currentNode->G;
			if (gScore < _node->G)
			{
				_node->G = gScore;
			}
		}
	}
	return NULL;
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Searches for the first node in open list. </summary>
///
/// <remarks>	William Barry, 15/01/2014. </remarks>
///
/// <param name="_index">	The index. </param>
///
/// <returns>	null if it fails, else the found node in open list. </returns>
///-------------------------------------------------------------------------------------------------
AStarNode* PathFinding::findNodeInOpenList(const FVector2D& _index)
{
	std::multiset<AStarNode*, ANodeDistance>::iterator it;
	for (it = internalInfo->mOpenList.begin(); it != internalInfo->mOpenList.end(); it++)
	{
		if ((*it)->mTileInfo.mIndex.X == _index.X && (*it)->mTileInfo.mIndex.Y == _index.Y)
		{
			return (*it);
		}
	}
	return NULL;
}