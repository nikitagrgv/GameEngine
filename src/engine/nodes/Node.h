#pragma once

#include "glm/glm.hpp"
#include <functional>
#include <memory>
#include <vector>
#include <string>

#include "../core/Object.h"
#include "../core/SharedPtr.h"

class Node;
using NodePtr = SharedPtr<Node>;

class Node : public Object
{
public:
    static NodePtr create(const std::string& name = "noname", Node* parent = nullptr);

    Node(const Node& other) = delete;
    Node& operator=(const Node& other) = delete;

    const glm::mat4& getTransform() const { return transform_; }
    void setTransform(const glm::mat4& transform)
    {
        transform_ = transform;
        update_global_transform();
    }

    const glm::mat4& getGlobalTransform() const { return global_transform_; }
    // TODO implement setGlobalTransform

    void deleteForce();

    const std::string& getName() const { return name_; }
    void setName(const std::string& name) { name_ = name; }
    Node* getParent() const { return parent_; }
    void setParent(Node* parent);

    void addChild(Node* child);
    int getNumChildren() const { return (int)children_.size(); }
    // TODO return weak pointer?
    Node* getChild(int i) { return children_[i]; }
    const Node* getChild(int i) const { return children_[i]; }
    void removeChildren();
    void removeChild(int i);

protected:
    explicit Node(const std::string& name, Node* parent);
    ~Node() override;

private:
    static void set_parent(Node* node, Node* parent);

    bool has_parent(const Node* node) const;

    void update_global_transform();

private:
    std::string name_{"noname"};
    std::vector<NodePtr> children_;
    Node* parent_{nullptr};

    glm::mat4 transform_{1};
    glm::mat4 global_transform_{1};
};
