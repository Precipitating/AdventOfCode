#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <numeric>
#include <map>
using namespace std;

struct Node
{
	vector<Node*> children;
	vector<int> metadata;
	~Node()
	{
		for (Node* node : children)
		{
			delete node;
			node = nullptr;
		}
	}

};

#pragma region PART1
//int Process(Node* root, stringstream& stream)
//{
//	static int metadataCounter = 0;
//	int children, metadata; 
//
//	stream >> children >> metadata;
//
//	for (size_t i = 0; i < children; ++i)
//	{
//		root->children.push_back(new Node);
//		Process(root->children.back(), stream);
//	}
//
//	for (size_t i = 0; i < metadata; ++i)
//	{
//		int num;
//		stream >> num;
//		metadataCounter += num;
//		root->metadata.push_back(num);
//	}
//
//	return metadataCounter;
//}
#pragma endregion

#pragma region PART2
void Process(Node* root, stringstream& stream)
{
	int children, metadata;

	stream >> children >> metadata;

	for (size_t i = 0; i < children; ++i)
	{
		root->children.push_back(new Node);
		Process(root->children.back(), stream);
	}

	for (size_t i = 0; i < metadata; ++i)
	{
		int num;
		stream >> num;

		root->metadata.push_back(num);
	}
}


int GetResult(Node* root)
{
	static int result = 0;

	if (root->children.size() > 0)
	{
		for (size_t i = 0; i < root->metadata.size(); ++i)
		{
			if (root->metadata[i] <= root->children.size() && root->metadata[i] != 0)
			{
				GetResult(root->children[root->metadata[i] - 1]);
			}
		}
	}
	else
	{
		result += accumulate(root->metadata.begin(), root->metadata.end(), 0);
	}

	return result;

}
#pragma endregion

int main()
{
	fstream file("input.txt");
	string line;
	vector<Node> nodes;
	map<int, Node*> indexMap;

	Node* root = new Node;
	Node* tail = root;
	bool isRootDone = false;

	while (getline(file, line))
	{
		stringstream stream(line);

		Process(root, stream);
		cout << GetResult(root);


	}

	delete root;
	return 0;
}