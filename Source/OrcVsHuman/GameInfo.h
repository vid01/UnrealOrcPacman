// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define	TILESIZE_WIDTH	   32
#define	TILESIZE_HEIGHT	32

#define	COLLISIONMAP_WIDTH	19
#define	COLLISIONMAP_HEIGHT	22

class GameInfo
{
private:
	GameInfo() {};
	static GameInfo instance;

public:
	static GameInfo& Instance() { return instance; }
	
	bool getCollisionAt(int x, int y);

	int getCollisionMapWidth()	{ return COLLISIONMAP_WIDTH; }
	int getCollisionMapHeight()	{ return COLLISIONMAP_HEIGHT; }
   int getTileSize() { return TILESIZE_WIDTH; }

};
