#include "radixnode.h"

RadixNode::RadixNode(const std::string& data, RadixNode* father):
    data(data), father(father)
{}

RadixNode* RadixNode::hasChildOfChar(const std::string& s)
{
    RadixNode* node = nullptr;
    for (int index = 0; index < vec.size(); ++index)
    {
        node = vec.at(index);
        if (node->data == s)
            return node;
    }
    return nullptr;
}
void RadixNode::addChild(RadixNode* node)
{
    vec.push_back(node);
}

void RadixNode::dealockSubTree()
{
    RadixNode* node = nullptr;
    for (int index = 0; index < vec.size(); ++index)
    {
        node = vec.at(index);
        node->dealockSubTree();
        delete node;
    }
}

int RadixNode::getNumberOfChilds()
{
    return vec.size();
}

std::vector<RadixNode *> RadixNode::getVectorOfChilds()
{
    return vec;
}

RadixNode* RadixNode::getChild(int index)
{
    return vec.at(index);
}

const std::string RadixNode::getData()
{
    return this->data;
}

void RadixNode::setData(const std::string& data)
{
    this->data = data;
}

bool RadixNode::getIsFinal()
{
    return this->isFinal;
}

void RadixNode::setIsFinal(bool isFinal)
{
    this->isFinal = isFinal;
}

void RadixNode::removeChild(int index)
{
    if (vec.size() > index)
    {
        vec.erase(vec.begin()+index);
    }
    else
        throw std::invalid_argument("invalid index");
}

void RadixNode::setFather(RadixNode *father)
{
    this->father = father;
}
