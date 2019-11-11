#include "QuadTree.h"

/* Quad Tree ----------------------------------- */

Quadtree::Quadtree()
{

}

Quadtree::~Quadtree()
{

}

void Quadtree::Create(const AABB& box)
{
	Clear();

	root = new QuadTreeNode(box);
}

void Quadtree::Clear()
{

}

void Quadtree::Insert(GameObject* go)
{

}

void Quadtree::Remove(GameObject* go)
{

}

template<typename TYPE>
void Quadtree::Intersect(std::vector<GameObject*>& objects, const TYPE& primitive)
{

}


/* Quad Tree Node ----------------------------------- */

QuadTreeNode::QuadTreeNode(const AABB& box, QuadTreeNode* parent)
{

}

QuadTreeNode::~QuadTreeNode()
{

}

void QuadTreeNode::Insert(GameObject* go)
{

}

void QuadTreeNode::Remove(GameObject* go)
{

}

void QuadTreeNode::CreateChilds()
{

}

void QuadTreeNode::ReorganizeObjects()
{

}

bool QuadTreeNode::IsLeaf()
{
	bool ret = false;



	return ret;
}

void QuadTreeNode::DebugDraw()
{

}

template<typename TYPE>
void QuadTreeNode::Intersect(std::vector<GameObject*>& objects, const TYPE& primitive)
{

}
