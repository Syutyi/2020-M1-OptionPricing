#include "BinomialTree.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Defaut constructor
BinomialTree::BinomialTree() {
	_u = 2.0;
	_d = 0.5;
	_n = 2;
	_stockPrice = 100.0;
	_p = 0.5;
	_initial_node = new Node(_p, 1.0 - _p, _stockPrice);
}

// Constructor with parameters
BinomialTree::BinomialTree(double u, double d, int n, double stockPrice, double p) {
	_u = u;
	_d = d;
	_n = n;
	_stockPrice = stockPrice;
	_p = p;

	// Constructing the first node of the tree
	_initial_node = new Node(0, _p, 1.0 - p);
	_initial_node->setPrice(_stockPrice);
}

BinomialTree::~BinomialTree()
{
	//
}

// Method that builds up the tree
void BinomialTree::buildTree(double r, double deltaT) {
	// Vector that contains the node
	std::vector<Node*> current_i;
	std::vector<Node*> previous_nodes;
	current_i.push_back(_initial_node);

	// FIFO Algorithm
	for (int i = 1; i <= _n; i++)
	{
		// Put every current node in the vector that contains the previous node
		for (int j = 0; j < i; j++)
		{
			previous_nodes.push_back(current_i.at(j));
		}

		// Clearing the vecotr with the current nodes
		current_i.clear();

		// Setting all the previous node as the parents of the current nodes
		for (int j = 0; j <= i; j++)
		{
			// Adding all the nodes to the vector that contains the current nodes and creating the nodes that would be added to the tree
			current_i.push_back(new Node(i, _p, 1.0 - _p));

			// Error handling and adding the current node to the tree partially
			if(j != i)
				current_i.at(j)->setParentUp(previous_nodes.at(j));
			if (j != 0)
				current_i.at(j)->setParentDown(previous_nodes.at(j-1));
		}

		// Setting the price and the child nodes 
		for (int j = 0; j < i; j++)
		{
			// Setting the price of the child by using the price of the parent nodes
			for (int k = 0; k <= j + 1; k++)
			{
				double price_before_up = 0.0;
				double price_before_down = 0.0;
				if (current_i.at(k)->getParentUp() != nullptr)
				{
					// Setting the child as their parents' child 
					if (current_i.at(k)->getParentUp() == previous_nodes.at(j))
					{
						previous_nodes.at(j)->setChildUp(current_i.at(k));
					}
					price_before_up = current_i.at(k)->getParentUp()->getPrice();
				}

				if (current_i.at(k)->getParentDown() != nullptr)
				{
					// Same process for the down child
					if (current_i.at(k)->getParentDown() == previous_nodes.at(j))
					{
						previous_nodes.at(j)->setChildDown(current_i.at(k));
					}
					price_before_down = current_i.at(k)->getParentDown()->getPrice();
				}

				// Setting the price of the nodes 
				if (price_before_up == 0) {
					current_i.at(k)->setPrice(price_before_down *_d);
				}
				else if (price_before_down == 0) {
					current_i.at(k)->setPrice(price_before_up * _u);
				}
				else {
					current_i.at(k)->setPrice(price_before_up * _u);
				}
			}

			// Setting the payoff of the trees
			for (int k = 0; k < previous_nodes.size(); k++) {
				previous_nodes.at(k)->setPayOff(r, deltaT);
			}

		}
		// Clearing the vector that contains all the previous nodes
		previous_nodes.clear();
	}
	_treeBuilt = true;

}

Node* BinomialTree::getFirstNode() {
	return _initial_node;
}

// Function that displays the tree
void BinomialTree::display(Node* tree) {
	if (tree == nullptr)
		return;
	if(tree == _initial_node)
		std::cout << _initial_node->getPrice() << " ";
	else 
		std::cout << tree->getPrice() << " ";
	if (tree->getChildUp() != nullptr)
	{
		// std::cout << "Child Up";
		display(tree->getChildUp());
	}
	if (tree->getChildDown() != nullptr)
	{
		// std::cout << "Child Down";
		display(tree->getChildDown());
	}
	std::cout << std::endl;
}


