#ifndef RADIX_TREE_H
#define RADIX_TREE_H

#include <iostream>
#include <vector>

#include "radixnode.h"

/*!
 * \brief The RadixTree class
 */
class RadixTree
{
public:
    /*!
     * \brief RadixTree
     */
    RadixTree();

    ~RadixTree();
    /*!
     * \brief insert
     * \param word
     */
    bool insert(const std::string& word);
    /*!
     * \brief search
     * \param word
     * \return
     */
    RadixNode* search(const std::string& word);
    /*!
     * \brief remove
     * \param word
     * \return
     */
    bool remove(const std::string& word);
    /*!
     * \brief getDotFileModeOne
     * \return
     */
    const std::string getDotFileModeOne();
    /*!
     * \brief startsWith
     * \param biggerString
     * \param part
     * \return
     */
    bool startsWith(const std::string &biggerString, const std::string &part);
    /*!
     * \brief howManyEqual
     * \param biggerStr
     * \param partStr
     * \return
     */
    int howManyEqual(const std::string &biggerStr, const std::string &partStr);
    /*!
     * \brief removeNodeInFather
     * \param childToRemove
     */
    void removeNodeInFather(RadixNode* childToRemove);

    /*!
     * \brief getRootNode
     * \return
     */
    RadixNode* getRootNode();


private:
    struct RadixNode* root = nullptr;

    /*!
     * \brief getDotFileModeOne
     * \param node
     * \param textToFile
     */
    void getDotFileModeOne(RadixNode* node, std::string& textToFile);
    /*!
     * \brief replaceChildInFather
     * \param father
     * \param oldSon
     * \param newSon
     */
    void replaceChildInFather(RadixNode* father, RadixNode* oldSon, RadixNode* newSon);
};

#endif // RADIX_TREE_H
