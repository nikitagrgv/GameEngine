#include "Node.h"

#include "../utils/VectorUtils.h"

#include <iostream>
#include <utility>

std::unordered_set<NodePtr, NodePtr::Hash> Node::all_nodes_{};

Node::Node(std::string name, Node* parent)
    : name_(std::move(name))
    , parent_(parent)
{
    all_nodes_.insert(NodePtr(this));
    setParent(parent_);
}

Node::~Node()
{
    assert(!parent_);
    assert(children_.empty());
    std::cout << "deleted " << name_ << std::endl;
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
    assert(!parent || !parent->has_parent(node));

    auto node_ptr = NodePtr(node);

    if (node->parent_)
        Vector::removeElement(node->parent_->children_, node_ptr);

    node->parent_ = parent;
    if (parent)
        parent->children_.push_back(std::move(node_ptr));

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

Node* Node::create(std::string name, Node* parent)
{
    return new Node(std::move(name), parent);
}

void Node::deleteForce()
{
    setParent(nullptr);

    while (!children_.empty())
        children_[children_.size() - 1]->deleteForce();

    all_nodes_.erase(NodePtr(this));
}

std::vector<Node*> Node::getAllNodes()
{
    std::vector<Node*> nodes;
    for (const auto& node : all_nodes_)
    {
        nodes.push_back(node.get());
    }
    return nodes;
}
