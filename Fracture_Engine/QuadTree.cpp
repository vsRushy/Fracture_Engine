#include "QuadTree.h"

#include "Globals.h"

#include "GL/glew.h"

/* Quad Tree ----------------------------------- */

Quadtree::Quadtree()
{

}

Quadtree::~Quadtree()
{
	Clear();
}

void Quadtree::Create(const AABB& box)
{
	Clear();

	root = new QuadTreeNode(box);
}

void Quadtree::Clear()
{
	RELEASE(root);
}

void Quadtree::Insert(GameObject* go)
{
	if (root != nullptr)
	{
		root->Insert(go);
	}
}

void Quadtree::Remove(GameObject* go)
{
	if (root != nullptr)
	{
		root->Remove(go);
	}
}

void Quadtree::Draw()
{
	glBegin(GL_LINES);
	
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

	if (root != nullptr)
	{
		root->DebugDraw();
	}

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
	glEnd();
}

template<typename TYPE>
void Quadtree::Intersect(std::vector<GameObject*>& objects, const TYPE& primitive)
{
	if (root != nullptr)
	{
		root->Intersect(objects, primitive);
	}
}


/* Quad Tree Node ----------------------------------- */

QuadTreeNode::QuadTreeNode(const AABB& box, QuadTreeNode* parent)
{
	for (uint i = 0; i < 4; i++)
	{
		childs[i] = nullptr;
	}
}

QuadTreeNode::~QuadTreeNode()
{
	for (uint i = 0; i < 4; i++)
	{
		RELEASE(childs[i]);
	}
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
	return (childs[0] == nullptr) ? true : false;
}

void QuadTreeNode::DebugDraw()
{
	for (uint i = 0; i < box.NumEdges(); i++)
	{
		glVertex3f(box.Edge(i).a.x, box.Edge(i).a.y, box.Edge(i).a.z);
		glVertex3f(box.Edge(i).b.x, box.Edge(i).b.y, box.Edge(i).b.z);
	}

	if (!IsLeaf())
	{
		/* It has childs */
		for (uint i = 0; i < 4; ++i)
		{
			childs[i]->DebugDraw();
		}
	}
}

template<typename TYPE>
void QuadTreeNode::Intersect(std::vector<GameObject*>& objects, const TYPE& primitive)
{

}
