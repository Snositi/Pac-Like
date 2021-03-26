#pragma once
#include "Scene.h"
#include "NodeGraph.h"
#include "Wall.h"
#include "Door.h"
#include "Pac.h"
#include "Ghost.h"
#include <Vector2.h>

/// <summary>
/// A Scene that generates a grid of Walls.
/// </summary>
class Maze : public Scene
{
public:
	/// <summary>
	/// A enumerator of tile types.
	/// MODIFY this list with any new tiles needed.
	/// The keys are not ordered.
	/// </summary>
	enum class TileKey {
		OPEN,
		WALL,
		GHOST,
		DUMBGHOST,
		DOOR,
		SPAWN
	};

	/// <summary>
	/// A single space in a Maze.
	/// </summary>
	struct Tile {
		int x;
		int y;
		float cost = 1.0f;
		Actor* actor = nullptr;
		NodeGraph::Node* node = nullptr;
	};

	static const int WIDTH = 28;
	static const int HEIGHT = 31;
	static const int TILE_SIZE = 32;

public:
	/// <param name="map">A 2D array of TileKeys arranged height by width</param>
	Maze(TileKey map[Maze::HEIGHT][Maze::WIDTH]);
	~Maze();

	virtual void draw() override;

	/// <summary>
	/// Get the size of the maze.
	/// </summary>
	/// <returns>a Vector2 storing the maze's width and height</returns>
	MathLibrary::Vector2 getSize() { return m_size; }

	/// <summary>
	/// Get the tile data at the given position.
	/// </summary>
	/// <param name="position">The position to check</param>
	/// <returns>A Tile with the data at the position</returns>
	Tile getTile(MathLibrary::Vector2 position);

	/// <summary>
	/// Get the position of the given tile.
	/// </summary>
	/// <param name="tile">The tile to check</param>
	/// <returns>A Vector2 with the position of the tile</returns>
	MathLibrary::Vector2 getPosition(Tile tile);

	MathLibrary::Vector2 getPlayerSpawn() { return m_PlayerSpawn; }

protected:
	/// <summary>
	/// Create a tile from a given key. If an actor is created, it is added to the scene.
	/// MODIFY this function to add support for new tiles.
	/// </summary>
	/// <param name="cost">The cost to use</param>
	/// <returns>The actor created</returns>
	Tile createTile(int x, int y, TileKey key);

private:
	/// <summary>
	/// Generate a new grid of Walls.
	/// </summary>
	void generate(TileKey map[Maze::HEIGHT][Maze::WIDTH]);

private:
	MathLibrary::Vector2 m_size = { WIDTH, HEIGHT };
	Tile m_grid[WIDTH][HEIGHT];

	//Defaults the players spawn to be the center of the window
	MathLibrary::Vector2 m_PlayerSpawn = { WIDTH / 2 * TILE_SIZE + (TILE_SIZE / 2),	HEIGHT / 2 * TILE_SIZE + (TILE_SIZE / 2) };

	Pac* m_player;
	//Used to detect collision between the player and send a signal to change scenes
	Door* m_door;
};
