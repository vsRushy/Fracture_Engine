#include "QuadTree.h"

#include "Globals.h"
#include "GameObject.h"

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

	root = new QuadtreeNode(box);
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

QuadtreeNode::QuadtreeNode(const AABB& box, QuadtreeNode* parent) : box(box), parent(parent)
{
	for (uint i = 0; i < 4; i++)
	{
		childs[i] = nullptr;
	}
}

QuadtreeNode::~QuadtreeNode()
{
	for (uint i = 0; i < 4; i++)
	{
		RELEASE(childs[i]);
	}
}

void QuadtreeNode::Insert(GameObject* go)
{
	if (IsLeaf())
	{
		if (go->bounding_box.Intersects(box))
		{
			if (game_objects.size() < QUAD_TREE_MAX_ITEMS)
			{
				game_objects.push_back(go);
			}
			else
			{
				CreateChilds();
				game_objects.push_back(go);
				ReorganizeObjects();
			}
		}
	}
	else
	{
		for (uint i = 0; i < 4; i++)
		{
			childs[i]->Insert(go);
		}
	}
}

void QuadtreeNode::Remove(GameObject* go)
{
	for (auto item = game_objects.begin(); item != game_objects.end(); item++)
	{
		if (*item == go)
		{
			game_objects.erase(item);
		}
	}

	if (IsLeaf())
	{
		for (uint i = 0; i < 4; i++)
		{
			childs[i]->Remove(go);
		}
	}
}

void QuadtreeNode::CreateChilds()
{
	AABB child_box;
	float3 box_center = box.CenterPoint();
	float3 child_size = float3(box.Size().x / 2.0f, box.Size().y, box.Size().z / 2.0f);

	/* UP - LEFT */
	float3 child_center = float3(box_center.x - box.Size().x / 4.0f, box_center.y, box_center.z + box.Size().z / 4.0f);
	child_box.SetFromCenterAndSize(child_center, child_size);
	childs[0] = new QuadtreeNode(child_box, this); 

	/* UP - RIGHT */
	child_center = float3(box_center.x + box.Size().x / 4.0f, box_center.y, box_center.z + box.Size().z / 4.0f);
	child_box.SetFromCenterAndSize(child_center, child_size);
	childs[1] = new QuadtreeNode(child_box, this);

	/* DOWN - LEFT */
	child_center = float3(box_center.x - box.Size().x / 4.0f, box_center.y, box_center.z - box.Size().z / 4.0f);
	child_box.SetFromCenterAndSize(child_center, child_size);
	childs[2] = new QuadtreeNode(child_box, this);

	/* DOWN - RIGHT */
	child_center = float3(box_center.x + box.Size().x / 4.0f, box_center.y, box_center.z - box.Size().z / 4.0f);
	child_box.SetFromCenterAndSize(child_center, child_size);
	childs[3] = new QuadtreeNode(child_box, this);
}

void QuadtreeNode::ReorganizeObjects()
{
	for (auto item = game_objects.begin(); item != game_objects.end(); item++)
	{
		uint boxes_intersection = 0;
		for (uint i = 0; i < 4; i++)
		{
			if (childs[i]->box.Intersects((*item)->bounding_box))
			{
				boxes_intersection++;
			}
		}

		if (boxes_intersection > 1)
		{
			item++;
		}
		else
		{
			item = game_objects.erase(item);
			for (uint i = 0; i < game_objects.size(); i++)
			{
				for (uint j = 0; j < 4; j++)
				{
					childs[i]->Insert(game_objects[j]);
				}
			}
		}
	}
}

bool QuadtreeNode::IsLeaf()
{
	return (childs[0] == nullptr) ? true : false;
}

void QuadtreeNode::DebugDraw()
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
void QuadtreeNode::Intersect(std::vector<GameObject*>& objects, const TYPE& primitive)
{
	if (primitive.Intersects(box))
	{
		for (auto item = this->game_objects.begin(); item != this->game_objects.end(); item++)
		{
			if (primitive.Intersects((*it)->bounding_box))
			{
				objects.push_back(*item);
			}
		}
		for (uint i = 0; i < 4; i++)
		{
			if (childs[i] != nullptr)
			{
				childs[i]->Intersect(objects, primitive);
			}
		}
	}
}
