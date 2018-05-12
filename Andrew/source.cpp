#include "assert.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

// the size of the testing matrix, change if necessary
const int SIZE = 32;

class Pitcher {
public:
	Pitcher() {
		contents = 0;
		capacity = 0;
	};
	Pitcher(int Contents, int Capacity) {
		contents = Contents;
		capacity = Capacity;
	}
	void printPitcher() { cout << contents; };
	void printCapacity() { cout << capacity; };
	bool hasRoom() { return (contents != capacity); }
	int space() { return (capacity - contents); }
	int getContents() const { return contents; }

	int contents;
	int capacity;
};

class PitcherGroup {
public:
	PitcherGroup() {
		pitcherGroup[0] = Pitcher(0, 16);
		pitcherGroup[1] = Pitcher(0, 9);
		pitcherGroup[2] = Pitcher(0, 7);
	};
	PitcherGroup(int a, int b, int c) {
		pitcherGroup[0] = Pitcher(a, 16);
		pitcherGroup[1] = Pitcher(b, 9);
		pitcherGroup[2] = Pitcher(c, 7);
	};
	void printPitcherGroup() {
		cout << "( ";
		for (auto &x : pitcherGroup) {
			x.printPitcher();
			cout << " ";
		}
		cout << ") ";
	};

	PitcherGroup& operator=(PitcherGroup other)
	{
		std::swap(pitcherGroup[0], other.pitcherGroup[0]);
		std::swap(pitcherGroup[1], other.pitcherGroup[1]);
		std::swap(pitcherGroup[2], other.pitcherGroup[2]);
		return *this;
	};

	bool operator==(const PitcherGroup &rhs) {
		return (((this->pitcherGroup[0].contents == rhs.pitcherGroup[0].contents) && (this->pitcherGroup[1].contents == rhs.pitcherGroup[1].contents) && (this->pitcherGroup[2].contents == rhs.pitcherGroup[2].contents))?true:false);
	}
	Pitcher pitcherGroup[3];
};

int min(int a, int b) {
	if (a != 0 && b != 0)
		return (a < b) ? a : b;
	else {
		if (a == 0 && b == 0)
			return 0;
		else
			return (a != 0) ? a : b;
	}
}

void printMatrix(int matrix[][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << setw(2) << matrix[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

// returns the index for the closed list of possible combinations which relate to positioning within the adjacency matrix
int returnIndex(vector<PitcherGroup> closedList, PitcherGroup combination) {
	for (int i = 0; i < static_cast<int>(closedList.size()); i++) {
		if (closedList[i] == combination)
			return i;
	}
	return -1;
}

struct Node {
	PitcherGroup data;
	Node* previous = nullptr;
	Node* path[6] = { nullptr };
};

Node *newnode(int a, int b, int c) {
	Node *node = new Node;
	node->data = PitcherGroup(a, b, c);
	return (node);
}

// returns the index for the closed list of possible combinations which relate to positioning within the adjacency matrix
int returnIndex(vector<Node*> closedList, PitcherGroup combination) {
	for (int i = 0; i < static_cast<int>(closedList.size()); i++) {
		if (closedList[i]->data == combination)
			return i;
	}
	return -1;
}

void print2DVector(vector<vector<int>> object)
{
	int count = 0;
	for (auto &x : object) {
		for (auto &y : x) {
			cout << setw(2) << y << " ";
			count++;
		}
		cout << "---- " << count << endl << endl;
	}
}

void FloydAlg(vector<vector<int>> &matrix) {
	//cout << "initial Matrix: \n";
	//print2DVector(matrix);
	for (int k = 0; k < SIZE; k++) {
		// looks at the row second
		for (int i = 0; i < SIZE; i++) {
			// looks at the column first
			for (int j = 0; j < SIZE; j++) {
				// do not update shortest path to itself
				if (i != j) {
					// check for additions with 0, not valid as they are infinity
					if (matrix[i][k] != 0 && matrix[k][j] != 0)
						matrix[i][j] = min(matrix[i][j], (matrix[i][k] + matrix[k][j]));
				}
			}
		}
		//cout << "Floyd Round #" << k + 1 << endl;
		//print2DVector(matrix);
	}
	/*cout << "Floyd Alg Outcome:" << endl;
	print2DVector(matrix);*/
}

bool matrixComparision(const vector<vector<int>> a, const vector<vector<int>> b) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (a[i][j] != b[i][j]) {
				cout << a[i][j] << " != " << b[i][j] << endl;
				return false;
			}
		}
	}
	return true;
}


// creates the graph, and hold adjacency matrix
class Tree {
public:
	Node *root;
	vector<PitcherGroup> v;
	vector<vector<int>> adjacencyMatrix;
	int leaves;

	//Constructor
	Tree() {
		root = newnode(16, 0, 0);
		adjacencyMatrix.resize(32, vector<int>(32, 0));
		v.push_back(root->data);
		root->data.printPitcherGroup();
		leaves = 0;
	}

	// Creates the Graph
	Node *createTree(Node *n, int height) {

		// If last round didn't add anything new than quit
		if (n == nullptr || height == 0) {
			return nullptr;
		}
		// check if a path repeats a combination
		if (height > 1)
		{
			Node *upstream = n->previous; bool bRepeated = false;

			while (bRepeated != true && upstream != nullptr)
			{
				if (n->data == upstream->data)
				{
					bRepeated = true;
				}
				upstream = upstream->previous;
			}

			if (bRepeated)
			{
				return nullptr;
			}
		}
		
		// check for unique combination
		if (returnIndex(v, n->data) == -1) {
			v.push_back(n->data);
			//n->data.printPitcherGroup();
		}

		// check all possible pitcher transitions
		for (int i = 0; i < 6; i++)
		{
			int pitcherNumber = (i % 3);
			// Test pitcher if it has content, test if pitch can pour 
			if (n->data.pitcherGroup[pitcherNumber].contents != 0)
			{
				int pitcherToPour = (i > 2)? ((i + 2) % 3) : ((i + 1) % 3);
				// Try pitcher to leftmost pitcher checking if pitcher to pour at is full already
				if (n->data.pitcherGroup[pitcherToPour].contents != n->data.pitcherGroup[pitcherToPour].capacity)
				{
					int pourAmount = n->data.pitcherGroup[pitcherToPour].capacity - n->data.pitcherGroup[pitcherToPour].contents;
					int decreasedPitcher; int increasedPitcher;

					// Normal Pour or Under Pour
					if (n->data.pitcherGroup[pitcherNumber].contents > pourAmount)
					{
						decreasedPitcher = n->data.pitcherGroup[pitcherNumber].contents - pourAmount;
						increasedPitcher = n->data.pitcherGroup[pitcherToPour].contents + pourAmount;
					}
					else
					{
						increasedPitcher = n->data.pitcherGroup[pitcherToPour].contents + n->data.pitcherGroup[i%3].contents;
						decreasedPitcher = 0;
					}

					//create a new node
					int pitcherUnchanged = (i > 2) ? ((pitcherToPour + 2) % 3) : ((pitcherToPour + 1) % 3);
					switch (pitcherUnchanged)
					{
					case(0):
						if(pitcherNumber == 1)
							n->path[i] = newnode(n->data.pitcherGroup[0].contents, decreasedPitcher, increasedPitcher);
						else
							n->path[i] = newnode(n->data.pitcherGroup[0].contents, increasedPitcher, decreasedPitcher);
						break;
					case(1):
						if (pitcherNumber == 2)
							n->path[i] = newnode(increasedPitcher, n->data.pitcherGroup[1].contents, decreasedPitcher);
						else
							n->path[i] = newnode(decreasedPitcher, n->data.pitcherGroup[1].contents, increasedPitcher);
						break;
					case(2):
						if (pitcherNumber == 0)
							n->path[i] = newnode(decreasedPitcher, increasedPitcher, n->data.pitcherGroup[2].contents);
						else
							n->path[i] = newnode(increasedPitcher, decreasedPitcher, n->data.pitcherGroup[2].contents);
						break;
					default:
						break;
					}
					n->path[i]->previous = n;
					createTree(n->path[i], (height + 1));
					leaves += 1;
				}
			}
				
		}
		
		return nullptr;
	}

	void updateAdjacencyMatrix(vector<Node*> closestCombinations)
	{

		for (int i = 1; i < 32; i++)
		{
			adjacencyMatrix[i][returnIndex(closestCombinations, closestCombinations[i]->previous->data)] += 1;
			adjacencyMatrix[returnIndex(closestCombinations, closestCombinations[i]->previous->data)][i] += 1;
		}
	}
};

/* -------------------------------CODE FOR FINDING THE CLOSEST NODES TO THE ORIGIN----------------------------------------------------- */

/* Function prototypes */
void viewAllHeightNodes(Node* root, vector<Node*> &combinations, int level);

/* Returns closest Nodes of all combinations*/
vector<Node*> levelOrder(const Tree &tree)
{
	vector<Node*> combinations;
	combinations.push_back(tree.root);
	int i = 1;
	while(combinations.size() != tree.v.size())
	{
		viewAllHeightNodes(tree.root, combinations, i);
		//cout << "Height: " << i << endl;
		i++;
	}
	return combinations;
}

/* Views nodes at a given level/height */
void viewAllHeightNodes(Node* root, vector<Node*> &combinations, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
	{
		/*if (root->data == PitcherGroup(8, 8, 0))
		{
			cout << "Found ";
			root->data.printPitcherGroup();
			cout << endl;
			Node* Path = root;

			while (Path != nullptr)
			{
				cout << "-> ";
				Path->data.printPitcherGroup();
				Path = Path->previous;
			}
			cout << endl << endl;
		}*/
		if (returnIndex(combinations, root->data) == -1) {
			combinations.push_back(root);
			//n->data.printPitcherGroup();
		}
	}
	else if (level > 1)
	{
		for (int i = 0; i < 6; i++)
		{
			viewAllHeightNodes(root->path[i], combinations, level - 1);
		}
	}
}



// MAIN PROGRAM
int main() {

	cout << "***Shortest Path to Pitcher Combination from (16,0,0) ***\n" << "Enter a valid Pitcher Combination(ex: 0-16 0-9 0-7):\n note: all 3 numbers must sum up to a sum of 16\n";
	
	int input[3];

	// input array
	for (int i = 0; i < 3; i++)
	{
		cin >> input[i];
	}

	// error handling
	while ((input[0] + input[1] + input[2]) != 16)
	{
		cout << "note: all 3 numbers must sum up to a sum of 16\n";
		for (int i = 0; i < 3; i++)
		{
			cin >> input[i];
		}
	}

	PitcherGroup userPitcherCombination(input[0], input[1], input[2]);

	// Creating Tree
	Tree start;
	Node *test = start.createTree(start.root,1);

	vector<Node*> closest = levelOrder(start);
	
	start.updateAdjacencyMatrix(closest);

	FloydAlg(start.adjacencyMatrix);

	//print2DVector(start.adjacencyMatrix);

	cout << "The path from ( 16 0 0 ) to ";
	userPitcherCombination.printPitcherGroup();
	cout << " is ";

	if (returnIndex(start.v, userPitcherCombination) != -1)
		cout << start.adjacencyMatrix[0][returnIndex(closest, userPitcherCombination)] <<  endl;
	else
		cout << "NONE, there is no such path to this combination!!!";

	// end of program
	//system("PAUSE");
	return 0;
}
