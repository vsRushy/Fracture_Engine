#ifndef __QUAD_TREE_H__
#define __QUAD_TREE_H__

#define QUAD_TREE_MAX_ITEMS 1

#include <vector>

#include "MathGeoLib.h"

class GameObject;

class QuadTreeNode
{
public:
	QuadTreeNode(const AABB& box, QuadTreeNode* parent = nullptr);
	~QuadTreeNode();

	void Insert(GameObject* go);
	void Remove(GameObject* go);
	template<typename TYPE>
	void Intersect(std::vector<GameObject*>& objects, const TYPE& primitive);

	void CreateChilds();
	void ReorganizeObjects();

	bool IsLeaf();

	void DebugDraw();

private:
	std::vector<GameObject*> game_objects;
	
	QuadTreeNode* parent = nullptr;
	QuadTreeNode* childs[4];
	
	AABB box;
};

class Quadtree
{
public:
	Quadtree();
	~Quadtree();

	void Create(const AABB& box);
	void Clear();
	void Insert(GameObject* go);
	void Remove(GameObject* go);
	template<typename TYPE>
	void Intersect(std::vector<GameObject*>& game_objects, const TYPE& primitive);

	void Draw();

private:
	QuadTreeNode* root = nullptr;
};

#endif /* __QUAD_TREE_H__ */
