#include "radixtree.h"
#include <iostream>
#include <queue>

#include <sstream> //for std::stringstream
#include <string>  //for std::string

using namespace std;

RadixTree::RadixTree()
{
    this->root = new RadixNode("", nullptr);
}

RadixTree::~RadixTree()
{
    cleanTree();
}

void RadixTree::cleanTree()
{
    if (this->root != nullptr)
    {
        this->root->dealockSubTree();
        delete this->root;
        root = nullptr;
    }
}

bool RadixTree::startsWith
(
    const string& biggerString,
    const string& part
)
{
    return part.length() <= biggerString.length()
        && equal(part.begin(), part.end(), biggerString.begin());
}

bool RadixTree::insert(const std::string& word)
{
    if (this->root->vec.size() == 0)
    {
        //Quando não tem nenhum elemento na radix tree, só insere
        RadixNode*  toInsert = new RadixNode(word, root);
        toInsert->isFinal = true;
        root->vec.push_back(toInsert);

        return true;
    }
    else
    {
        RadixNode*  tmp = root;
        std::string currentWord = word;
        bool finished = false;
        bool entered = false;

        while (finished == false)
        {
            entered = false;

            //1: Algum vizinho tem uma parte inicial de word
            //1.1 O vizinho completo é uma parte de word
            RadixNode*  neighbor = nullptr;
            for (int index = 0; index < tmp->vec.size(); ++index)
            {
                neighbor = tmp->vec.at(index);
                if
                (
                    startsWith
                    (
                        currentWord,
                        neighbor->data
                    )
                )
                {
                    int diffSize = currentWord.length() - neighbor->data.length();
                    int st = currentWord.length() - diffSize;
                    std::string rest = currentWord.substr(st);

                    if (rest.compare("") == 0)
                    {
                        //duplicated entry
                        return false;
                    }

                    //tmp continua com o seu dado
                    currentWord = rest;
                    finished = false;//continua
                    tmp = neighbor;

                    entered = true;

                    break;
                }
            }

            if (finished)
                break;
            else if (entered)
                continue;

            //1.2 algum vizinho tem uma subparte que é word completamente
            for (int index = 0; index < tmp->vec.size(); ++index)
            {
                neighbor = tmp->vec.at(index);
                if
                (
                    startsWith
                    (
                        neighbor->data, //maior
                        currentWord     //menor
                    )
                )
                {
                    int diffSize =  neighbor->data.length() - currentWord.length();
                    int st = neighbor->data.length() - diffSize;
                    std::string initial = neighbor->data.substr(0, st);
                    std::string rest = neighbor->data.substr(st);

                    //Quebra o vizinho
                    RadixNode*  fatherToInsert = new RadixNode(initial, nullptr);
                    fatherToInsert->isFinal = true;

                    neighbor->data = rest;
                    //continua com os filhos

                    RadixNode*  backupFather = neighbor->father;

                    neighbor->father = fatherToInsert; //o pai muda
                    fatherToInsert->vec.push_back(neighbor);

                    fatherToInsert->father = backupFather;
                    //replaces em backupFather, o neighbor por fatherToInsert
                    replaceChildInFather
                    (
                        backupFather,
                        neighbor,
                        fatherToInsert
                    );

                    finished = true; //here, it really ends
                    entered = true;
                    break;
                }
            }

            if (finished)
                break;
            else if (entered)
                continue;

            //1.3 apenas uma subparte dele é uma parte de word
            //fazer uma tabela de comparações
            int maxIndex = -1;
            RadixNode*  betterNeighbor = nullptr;
            for (int index = 0; index < tmp->vec.size(); ++index)
            {
                neighbor = tmp->vec.at(index);
                int ret = howManyEqual
                (
                    neighbor->data,
                    currentWord
                );
                if (ret > -1)
                {
                    betterNeighbor = neighbor;
                    maxIndex = ret;
                }
            }

            if (maxIndex != -1) //a parte de algum vizinho é igual a alguma parte de current word
            {
                std::string initial = betterNeighbor->data.substr(0, maxIndex+1); //check maxIndex
                std::string restOfNeighbor = betterNeighbor->data.substr(maxIndex+1);
                std::string restOfCurent = currentWord.substr(maxIndex+1);

                //Quebra o vizinho
                RadixNode*  fatherToInsert = new RadixNode(initial, nullptr);
                fatherToInsert->isFinal = false;

                betterNeighbor->data = restOfNeighbor;
                //continua com os filhos

                RadixNode*  backupFather = betterNeighbor->father;

                betterNeighbor->father = fatherToInsert; //o pai muda
                fatherToInsert->vec.push_back(betterNeighbor);

                fatherToInsert->father = backupFather;
                //replaces em backupFather, o neighbor por fatherToInsert
                replaceChildInFather
                (
                    backupFather,
                    betterNeighbor,
                    fatherToInsert
                );

                //novo vizinho
                RadixNode*  newNeighbor = new RadixNode(restOfCurent, fatherToInsert);
                fatherToInsert->addChild(newNeighbor);
                newNeighbor->isFinal = true;

                finished = true; //here, it really ends
                entered = true;
                break;
            }
            else //2: nenhum vizinho tem alguma parte
            {
                RadixNode*  newNeighbor = new RadixNode(currentWord, tmp);
                tmp->addChild(newNeighbor);
                newNeighbor->isFinal = true;

                finished = true; //here, it really ends
                entered = true;
                break;
            }
        } //end of while loop
    }

    return true;
}

//Return the index of string until where they are equal
int RadixTree::howManyEqual
(
    const std::string& biggerStr,
    const std::string& partStr
)
{
    int sizeOfBigger = biggerStr.length();
    int sizeOfPart = partStr.length();

    int pos = -1;
    for (int index = 0; index < sizeOfPart && index < sizeOfBigger; ++index)
    {
        if (biggerStr.at(index) == partStr.at(index))
            pos = index;
        else
            break;
    }

    return pos;
}

RadixNode*  RadixTree::search(const std::string& word)
{
    std::string currentWord = word;
    RadixNode*  tmp = root;
    RadixNode*  backupTmp = nullptr;
    while (backupTmp != tmp)
    {
        backupTmp = tmp;
        for (int index = 0; index < tmp->vec.size(); ++index)
        {
            RadixNode*  neighbor = tmp->vec.at(index);
            if
            (
                startsWith
                (
                    currentWord,
                    neighbor->data
                )
            )
            {
                //se for igual, acabou
                if (currentWord.compare(neighbor->data) == 0)
                {
                    if (neighbor->isFinal)
                        return neighbor; //É a entrada
                    else
                        return nullptr; //É um prefixo
                }
                else
                {
                    int diffSize = currentWord.length() - neighbor->data.length();
                    int st = currentWord.length() - diffSize;

                    currentWord = currentWord.substr(st); //updated currentRord
                    tmp = neighbor;
                    break;
                }
            }
        }
    }

    return nullptr;
}

bool RadixTree::remove(const std::string& word)
{
    RadixNode*  searched = search(word);
    RadixNode*  fatherOfSearched = searched->father;

    if (searched != nullptr)
    {
        searched->isFinal = false;

        //Se ele tiver filhos, e se essa quantidade de filhos for um,
        //traz o conteúdo do filho e a cor do filho para ele
        if (searched->vec.size() == 1)
        {
            std::string data = searched->data;

            //como sou branco, a cor do filho importa mais

            RadixNode*  fatherOfSearched = searched->father;
            RadixNode*  sonOfSearched = searched->vec.at(0);
            sonOfSearched->data = data + sonOfSearched->data;
            sonOfSearched->father = fatherOfSearched;
            replaceChildInFather
            (
                fatherOfSearched,
                searched,
                sonOfSearched
            );
            delete searched;
            searched = nullptr;
        }

        RadixNode*  tmp = nullptr;
        if (searched != nullptr)
            tmp = searched;
        else
            tmp = fatherOfSearched;

        while (true)
        {
            if (tmp->vec.size() == 0 &&
               (tmp->isFinal == false) &&
               tmp != root)
            {
                RadixNode*  backupNode = tmp;
                removeNodeInFather(tmp);
                tmp = tmp->father;
                delete backupNode;
            }
            else if (tmp->vec.size() == 1 &&
                     (tmp->isFinal == false) &&
                     tmp != root)
            {
                //tmp
                RadixNode* child = tmp->getChild(0);
                tmp->setData(tmp->getData()+child->getData());
                tmp->setIsFinal(child->getIsFinal());

                tmp->removeChild(0);
                std::vector<RadixNode *> childsOfChild = child->getVectorOfChilds();
                for (int index = 0; index < childsOfChild.size(); ++index)
                {
                    RadixNode *n = childsOfChild.at(index);
                    tmp->addChild(n);
                    n->setFather(tmp);
                }

                delete child;
                //foco continua em tmp
            }
            else
            {
                break;
            }
        }

        return true;
    }
    else
        return false;
}

void RadixTree::removeNodeInFather(RadixNode*  childToRemove)
{
    RadixNode*  father = childToRemove->father;
    for (int index = 0; index < father->vec.size(); ++index)
    {
        if (father->vec.at(index) == childToRemove)
        {
            //remove o nó de index: index
            father->vec.erase(father->vec.begin()+index);
            break;
        }
    }
}

RadixNode *RadixTree::getRootNode()
{
    return this->root;
}

void RadixTree::replaceChildInFather
(
    RadixNode*  father,
    RadixNode*  oldSon,
    RadixNode*  newSon
)
{
    for (int index = 0; index < father->vec.size(); ++index)
    {
        if (father->vec.at(index) == oldSon) //está comparando ponteiros
            father->vec[index] = newSon;
    }
}

const std::string RadixTree::getDotFileModeOne()
{
    std::string textToFile = "digraph g{";

    if (root == nullptr)
    {
        textToFile += "NULL;Root [shape=none]; Root -> NULL;";
    }
    else
    {
        textToFile += "Root [shape=none]; rootwithnothing [label=\" \"]; Root -> rootwithnothing;";

        if (root->vec.size() > 0)
            getDotFileModeOne(root, textToFile);
    }

    textToFile += "}";

    return textToFile;
}


std::string getPointerAsString(RadixNode*  node)
{
    const void * address = static_cast<const void*>(node);
    std::stringstream ss;
    ss << address;
    std::string name = ss.str();
    return "\""+name+"\"";
}

std::string getNodeRepresentation(RadixNode*  node)
{
    std::string ret = getPointerAsString(node);
    ret += getPointerAsString(node) +"[ label= \""+node->data+"\" ";

    //Inserir outras propriedades
    if (node->isFinal)
    {
        ret += "color=red fontcolor=white style=filled";
    }

    ret += "];";
    return ret;
}

void RadixTree::getDotFileModeOne(RadixNode*  node, std::string& textToFile)
{
    if (node != root)
        textToFile += getNodeRepresentation(node);

    for (auto n: node->vec)
    {
        if (node != root)
        {
            textToFile += getPointerAsString(node) + " -> " +
                    getPointerAsString(n) + ";";
        }
        else
        {
            textToFile += "rootwithnothing -> " +
                    getPointerAsString(n) + ";";
        }
        getDotFileModeOne(n, textToFile);
    }
}
