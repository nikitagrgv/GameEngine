#include "Node.h"

#include "../utils/VectorUtils.h"

#include <iostream>

Node::Node(const std::string& name, Node* parent)
    : name_(name)
    , parent_(parent)
{
    setParent(parent_);
}

Node::~Node()
{
    std::cout << "deleted " << name_ << std::endl;
    for (auto& child : children_)
    {
        child->parent_ = nullptr;
    }
    children_.clear();
}

void Node::addChild(Node* child)
{
    set_parent(child, this);
}

void Node::setParent(Node* parent)
{
    set_parent(this, parent);
}

void Node::removeChild(int i)
{
    Vector::removeElementByIndex(children_, i);
}

void Node::removeChildren()
{
    children_.clear();
}

void Node::set_parent(Node* node, Node* parent)
{
    assert(node);

    if (!parent)
    {
        node->parent_ = nullptr;
        return;
    }

    assert(!parent->has_parent(node));

    NodePtr node_ptr(node);
    Vector::removeElement(node->parent_->children_, node_ptr);
    parent->children_.push_back(std::move(node_ptr));
    node->parent_ = parent;
    node->update_global_transform();
}

bool Node::has_parent(const Node* node) const
{
    if (!parent_)
        return false;

    if (parent_ == node)
        return true;

    return parent_->has_parent(node);
}

void Node::update_global_transform()
{
    global_transform_ = (parent_ ? parent_->getGlobalTransform() : glm::mat4(1)) * transform_;
    for (auto& child : children_)
    {
        child->update_global_transform();
    }
}

NodePtr Node::create(const std::string& name, Node* parent)
{
    return NodePtr(new Node(name, parent));
}

void Node::deleteForce()
{
    if (!parent_)
    {
        SharedPtr<Node>(this); // TODO: do something better? or change architecture of node management
        return;
    }

    for (int i = 0; i < parent_->getNumChildren(); ++i)
    {
        if (parent_->getChild(i) == this)
        {
            parent_->removeChild(i);
            return;
        }
    }
}
