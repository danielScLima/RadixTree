// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "radixtree.h"

TEST_CASE( "Testing the insert call in the tree", "[single-file]" )
{
	RadixTree r;
	
	RadixNode *root = r.getRootNode();

	REQUIRE( root->getNumberOfChilds() == 0 );
	r.insert("daniel");
	REQUIRE (!root->getIsFinal());

	root = r.getRootNode();
	REQUIRE( root->getNumberOfChilds() == 1 );

	RadixNode *danielNode = root->getChild(0);
	REQUIRE (danielNode->getIsFinal());
	
	REQUIRE( danielNode->getNumberOfChilds() == 0 );
	REQUIRE( danielNode->getData().compare("daniel") == 0 );
	
	r.insert("paul");
	
	root = r.getRootNode();
	REQUIRE( root->getNumberOfChilds() == 2 );
	REQUIRE(!root->getIsFinal());
	danielNode = root->getChild(0);
	RadixNode *paulNode = root->getChild(1);
	
	REQUIRE( danielNode->getNumberOfChilds() == 0 );
	REQUIRE( danielNode->getData().compare("daniel") == 0 );
	REQUIRE( danielNode->getIsFinal());
	
	REQUIRE( paulNode->getNumberOfChilds() == 0 );
	REQUIRE( paulNode->getData().compare("paul") == 0 );
	REQUIRE( paulNode->getIsFinal());
	
	r.insert("danilo");
	
	root = r.getRootNode();
	REQUIRE( root->getNumberOfChilds() == 2 );
	RadixNode* daniNode = root->getChild(0);
	paulNode = root->getChild(1);
	REQUIRE( !root->getIsFinal());
	
	REQUIRE( daniNode->getNumberOfChilds() == 2 );
	REQUIRE( daniNode->getData().compare("dani") == 0 );
	REQUIRE( !daniNode->getIsFinal());
	
	REQUIRE( paulNode->getNumberOfChilds() == 0 );
	REQUIRE( paulNode->getData().compare("paul") == 0 );
	REQUIRE( paulNode->getIsFinal());
	
	danielNode = daniNode->getChild(0);
	RadixNode* daniloNode = daniNode->getChild(1);
	
	REQUIRE( danielNode->getNumberOfChilds() == 0 );
	REQUIRE( danielNode->getData().compare("el") == 0 );
	REQUIRE( danielNode->getIsFinal());
	
	REQUIRE( daniloNode->getNumberOfChilds() == 0 );
	REQUIRE( daniloNode->getData().compare("lo") == 0 );
	REQUIRE( daniloNode->getIsFinal());
	
	r.insert("danilos");
	
	root = r.getRootNode();
	REQUIRE (!root->getIsFinal());
	REQUIRE( root->getNumberOfChilds() == 2 );
	daniNode = root->getChild(0);
	paulNode = root->getChild(1);
	
	REQUIRE( daniNode->getNumberOfChilds() == 2 );
	REQUIRE( daniNode->getData().compare("dani") == 0 );
	REQUIRE (!daniNode->getIsFinal());
	
	REQUIRE( paulNode->getNumberOfChilds() == 0 );
	REQUIRE( paulNode->getData().compare("paul") == 0 );
	REQUIRE (paulNode->getIsFinal());
	
	danielNode = daniNode->getChild(0);
	daniloNode = daniNode->getChild(1);
	
	REQUIRE( danielNode->getNumberOfChilds() == 0 );
	REQUIRE( danielNode->getData().compare("el") == 0 );
	REQUIRE (danielNode->getIsFinal());
	
	REQUIRE( daniloNode->getNumberOfChilds() == 1 );
	REQUIRE( daniloNode->getData().compare("lo") == 0 );
	REQUIRE (daniloNode->getIsFinal());
	
	RadixNode* danilosNode = daniloNode->getChild(0);
	REQUIRE( danilosNode->getNumberOfChilds() == 0 );
	REQUIRE( danilosNode->getData().compare("s") == 0 );
	REQUIRE (danilosNode->getIsFinal());
	
	r.insert("danila");
	
	root = r.getRootNode();
	REQUIRE( root->getNumberOfChilds() == 2 );
	daniNode = root->getChild(0);
	paulNode = root->getChild(1);
	
	REQUIRE( paulNode->getNumberOfChilds() == 0 );
	
	
	danielNode = daniNode->getChild(0);
	RadixNode* danilNonNode = daniNode->getChild(1);
	
	daniloNode = danilNonNode->getChild(0);
	
	RadixNode* danilaNode = danilNonNode->getChild(1);
	
	danilosNode = daniloNode->getChild(0);
	
	//checking dani
	REQUIRE( daniNode->getNumberOfChilds() == 2 );
	REQUIRE( daniNode->getData().compare("dani") == 0 );
	REQUIRE (!daniNode->getIsFinal());
	
	//checking paul
	REQUIRE( paulNode->getData().compare("paul") == 0 );
	REQUIRE (paulNode->getIsFinal());
	
	//checking dani el
	REQUIRE( danielNode->getData().compare("el") == 0 );
	REQUIRE (danielNode->getIsFinal());
	
	//checking dani l
	REQUIRE( danilNonNode->getData().compare("l") == 0 );
	REQUIRE (!danilNonNode->getIsFinal());
	
	//checking dani l o
	REQUIRE( daniloNode->getData().compare("o") == 0 );
	REQUIRE (daniloNode->getIsFinal());
	
	//checking dani l a
	REQUIRE( danilaNode->getData().compare("a") == 0 );
	REQUIRE (danilaNode->getIsFinal());
	
	//checking dani l o s
	REQUIRE( danilosNode->getData().compare("s") == 0 );
	REQUIRE (danilosNode->getIsFinal());
}

TEST_CASE( "Testing the remove call in the tree", "[single-file]" )
{
	RadixTree r;
	
	RadixNode *root = r.getRootNode();

	REQUIRE( root->getNumberOfChilds() == 0 );
	r.insert("daniel");
	r.insert("paul");
	r.insert("danilo");
	r.insert("danilos");
	r.insert("danila");
	
	root = r.getRootNode();
	REQUIRE( root->getNumberOfChilds() == 2 );
	RadixNode* daniNode = root->getChild(0);
	RadixNode* paulNode = root->getChild(1);
	
	REQUIRE( paulNode->getNumberOfChilds() == 0 );
	
	
	RadixNode* danielNode = daniNode->getChild(0);
	RadixNode* danilNonNode = daniNode->getChild(1);
	
	RadixNode* daniloNode = danilNonNode->getChild(0);
	
	RadixNode* danilaNode = danilNonNode->getChild(1);
	
	RadixNode* danilosNode = daniloNode->getChild(0);
	
	//checking dani
	REQUIRE( daniNode->getNumberOfChilds() == 2 );
	REQUIRE( daniNode->getData().compare("dani") == 0 );
	REQUIRE (!daniNode->getIsFinal());
	
	//checking paul
	REQUIRE( paulNode->getData().compare("paul") == 0 );
	REQUIRE (paulNode->getIsFinal());
	
	//checking dani el
	REQUIRE( danielNode->getData().compare("el") == 0 );
	REQUIRE (danielNode->getIsFinal());
	
	//checking dani l
	REQUIRE( danilNonNode->getData().compare("l") == 0 );
	REQUIRE (!danilNonNode->getIsFinal());
	
	//checking dani l o
	REQUIRE( daniloNode->getData().compare("o") == 0 );
	REQUIRE (daniloNode->getIsFinal());
	
	//checking dani l a
	REQUIRE( danilaNode->getData().compare("a") == 0 );
	REQUIRE (danilaNode->getIsFinal());
	
	//checking dani l o s
	REQUIRE( danilosNode->getData().compare("s") == 0 );
	REQUIRE (danilosNode->getIsFinal());
	
	REQUIRE(r.remove("paul"));
	
	root = r.getRootNode();
	REQUIRE( root->getNumberOfChilds() == 1 );
	daniNode = root->getChild(0);
	
	danielNode = daniNode->getChild(0);
	danilNonNode = daniNode->getChild(1);
	
	daniloNode = danilNonNode->getChild(0);
	
	danilaNode = danilNonNode->getChild(1);
	
	danilosNode = daniloNode->getChild(0);
	
	//checking dani
	REQUIRE( daniNode->getNumberOfChilds() == 2 );
	REQUIRE( daniNode->getData().compare("dani") == 0 );
	REQUIRE (!daniNode->getIsFinal());
	
	//checking dani el
	REQUIRE( danielNode->getData().compare("el") == 0 );
	REQUIRE (danielNode->getIsFinal());
	
	//checking dani l
	REQUIRE( danilNonNode->getData().compare("l") == 0 );
	REQUIRE (!danilNonNode->getIsFinal());
	
	//checking dani l o
	REQUIRE( daniloNode->getData().compare("o") == 0 );
	REQUIRE (daniloNode->getIsFinal());
	
	//checking dani l a
	REQUIRE( danilaNode->getData().compare("a") == 0 );
	REQUIRE (danilaNode->getIsFinal());
	
	//checking dani l o s
	REQUIRE( danilosNode->getData().compare("s") == 0 );
	REQUIRE (danilosNode->getIsFinal());
	
	REQUIRE(r.remove("danilo"));
	
	root = r.getRootNode();
	REQUIRE( root->getNumberOfChilds() == 1 );
	daniNode = root->getChild(0);
	
	danielNode = daniNode->getChild(0);
	danilNonNode = daniNode->getChild(1);
	
	danilosNode = danilNonNode->getChild(0);
	
	danilaNode = danilNonNode->getChild(1);
	
	//checking dani
	REQUIRE( daniNode->getNumberOfChilds() == 2 );
	REQUIRE( daniNode->getData().compare("dani") == 0 );
	REQUIRE (!daniNode->getIsFinal());
	
	//checking dani el
	REQUIRE( danielNode->getData().compare("el") == 0 );
	REQUIRE (danielNode->getIsFinal());
	
	//checking dani l
	REQUIRE( danilNonNode->getData().compare("l") == 0 );
	REQUIRE (!danilNonNode->getIsFinal());
	
	//checking dani l a
	REQUIRE( danilaNode->getData().compare("a") == 0 );
	REQUIRE (danilaNode->getIsFinal());
	
	//checking dani l o s
	REQUIRE( danilosNode->getData().compare("os") == 0 );
	REQUIRE (danilosNode->getIsFinal());
	
	REQUIRE(r.remove("danilos"));
	
	root = r.getRootNode();
	REQUIRE( root->getNumberOfChilds() == 1 );
	daniNode = root->getChild(0);
	
	danielNode = daniNode->getChild(0);
	danilaNode = daniNode->getChild(1);
	
	//checking dani
	REQUIRE( daniNode->getNumberOfChilds() == 2 );
	REQUIRE( daniNode->getData().compare("dani") == 0 );
	REQUIRE (!daniNode->getIsFinal());
	
	//checking dani el
	REQUIRE( danielNode->getData().compare("el") == 0 );
	REQUIRE (danielNode->getIsFinal());
	
	//checking dani l a
	REQUIRE( danilaNode->getData().compare("la") == 0 );
	REQUIRE (danilaNode->getIsFinal());
	
	REQUIRE(r.remove("danila"));
	
	root = r.getRootNode();
	REQUIRE( root->getNumberOfChilds() == 1 );
	danielNode = root->getChild(0);
	
	//checking daniel
	REQUIRE( danielNode->getData().compare("daniel") == 0 );
	REQUIRE (danielNode->getIsFinal());
	
	REQUIRE(r.remove("daniel"));
	
	root = r.getRootNode();
	REQUIRE( root->getNumberOfChilds() == 0 );
	REQUIRE (!root->getIsFinal());
}

TEST_CASE( "Testing the search call in the tree", "[single-file]" )
{
	RadixTree r;

	r.insert("daniel");
	r.insert("paul");
	r.insert("danilo");
	r.insert("danilos");
	r.insert("danila");
	
	REQUIRE (r.search("daniel") != nullptr);
	REQUIRE (r.search("paul") != nullptr);
	REQUIRE (r.search("danilo") != nullptr);
	REQUIRE (r.search("danilos") != nullptr);
	REQUIRE (r.search("danila") != nullptr);
	
	REQUIRE (r.search("carla") == nullptr);
	REQUIRE (r.search("miguel") == nullptr);
}

TEST_CASE( "Testing the search and remove calls in the tree", "[single-file]" )
{
	RadixTree r;

	r.insert("daniel");
	r.insert("paul");
	r.insert("danilo");
	r.insert("danilos");
	r.insert("danila");
	
	REQUIRE (r.search("daniel") != nullptr);
	REQUIRE (r.search("paul") != nullptr);
	REQUIRE (r.search("danilo") != nullptr);
	REQUIRE (r.search("danilos") != nullptr);
	REQUIRE (r.search("danila") != nullptr);
	
	REQUIRE (r.search("carla") == nullptr);
	REQUIRE (r.search("miguel") == nullptr);
	
	REQUIRE(r.remove("danila"));
	REQUIRE(r.remove("daniel"));
	
	REQUIRE (r.search("daniel") == nullptr);
	REQUIRE (r.search("paul") != nullptr);
	REQUIRE (r.search("danilo") != nullptr);
	REQUIRE (r.search("danilos") != nullptr); //erro
	REQUIRE (r.search("danila") == nullptr);
}

TEST_CASE( "Testing the insertion of duplicated entries in the tree", "[single-file]" )
{
	RadixTree r;
	
	REQUIRE (r.insert("dan"));
	REQUIRE (r.insert("daniel"));
	REQUIRE (r.insert("paul"));
	REQUIRE (r.insert("danilo"));
	REQUIRE (r.insert("danilos"));
	REQUIRE (r.insert("danila"));
	
	REQUIRE (!r.insert("dan"));
	REQUIRE (!r.insert("daniel"));
	REQUIRE (!r.insert("paul"));
	REQUIRE (!r.insert("danilo"));
	REQUIRE (!r.insert("danilos"));
	REQUIRE (!r.insert("danila"));
}
