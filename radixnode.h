#ifndef RADIXNODE_H
#define RADIXNODE_H

#include <iostream>
#include <vector>

/*!
 * \brief The RadixNode struct
 */
struct RadixNode
{
    /*!
     * \brief RadixNode
     * \param data
     * \param father
     */
    RadixNode(const std::string& data, RadixNode* father);

    /*!
     * \brief hasChildOfChar
     * \param s
     * \return
     */
    RadixNode* hasChildOfChar(const std::string& s);
    /*!
     * \brief addChild
     * \param node
     */
    void addChild(RadixNode* node);

    std::string data = "";
    std::vector<RadixNode*> vec;
    RadixNode* father = nullptr;
    bool isFinal = false;

public:
    /*!
     * \brief dealockSubTree
     */
    void dealockSubTree();

    /*!
     * \brief getNumberOfChilds
     * \return
     */
    int getNumberOfChilds();

    /*!
     * \brief getVectorOfChilds
     * \return
     */
    std::vector<RadixNode*> getVectorOfChilds();

    /*!
     * \brief getChild
     * \param index
     * \return
     */
    RadixNode* getChild(int index);

    /*!
     * \brief getData
     * \return
     */
    const std::string getData();

    /*!
     * \brief setData
     * \param data
     */
    void setData(const std::string& data);

    /*!
     * \brief getIsFinal
     * \return
     */
    bool getIsFinal();

    /*!
     * \brief setIsFinal
     * \param isFinal
     */
    void setIsFinal(bool isFinal);

    /*!
     * \brief removeChild
     * \param index
     */
    void removeChild(int index);

    /*!
     * \brief setFather
     * \param father
     */
    void setFather(RadixNode* father);
};

#endif // RADIXNODE_H
