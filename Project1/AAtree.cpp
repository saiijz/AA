#include <iostream>

struct Node {
	int key;
	Node* pLeft;
	Node* pRight;
	int level;

	Node() {
		key = 0;
		pLeft = NULL;
		pRight = NULL;
		level = 1;
	}

	Node(int i) {
		key = i;
		pLeft = NULL;
		pRight = NULL;
		level = 1;
	}

	Node(int i, int lvl) {
		key = i;
		pLeft = NULL;
		pRight = NULL;
		level = lvl;
	}

	Node(int i, Node* pL, Node* pR, int lvl) {
		key = i;
		pLeft = pL;
		pRight = pR;
		level = lvl;
	}

};

class AAtree {
private:

	Node* pRoot;
	int height;

public:

	int CreateTree(int);
	int InsertNode(int);
	int InsertNode(Node*&, int);
	int DeleteNode(int);
	int DeleteLeaf(int);
	int DeleteLeaf(Node*&, int);
	int Skew(Node*&);
	int Split(Node*&);
	int FindSubstituteNode(Node*);
	int ReplaceDeletionNode(Node*, int, int);
	Node* FindDeletionNode(Node*, int);
	bool IsHaveOneRightLink(Node*);
	bool IsLeafNode(Node*, int);
	int CreateNode();
	Node* Get();
	AAtree();

};

int AAtree::CreateNode() {
	pRoot->pRight->pRight = new Node();
	return 1;
}

int AAtree::CreateTree(int i)
{

	pRoot = new Node;

	if (!pRoot) {

		return -1;

	}
	else {

		pRoot->key = i;
		pRoot->pLeft = NULL;
		pRoot->pRight = NULL;
		pRoot->level = 1;

		return 0;
	}

}

int AAtree::Skew(Node*& pNode) {

	if (!pNode->pLeft->pRight) {
		pNode->pLeft->pRight = pNode;
		pNode = pNode->pLeft;
		pNode->pRight->pLeft = NULL;
	}
	else {
		Node* pTemp = new Node(pNode->pLeft->pRight->key, pNode->pLeft->pRight->pLeft, pNode->pLeft->pRight->pRight, pNode->pLeft->pRight->level);
		delete pNode->pLeft->pRight;
		pNode->pLeft->pRight = NULL;
		pNode->pLeft->pRight = pNode;
		pNode = pNode->pLeft;
		pNode->pRight->pLeft = pTemp;
	}
	return 1;
}

bool AAtree::IsHaveOneRightLink(Node* pNode) {

	int count{ 0 };
	
	while (pNode->pRight) {
		if (pNode->level == pNode->pRight->level) {
			++count;
		}
		else {
			break;
		}
		pNode = pNode->pRight;
	}
	
	if (count > 1) {

		return false;

	}
	else {

		return true;

	}

}

bool AAtree::IsLeafNode(Node* pNode, int i) {

	if (pNode->key == i) {
		
		if (pNode->pLeft || pNode->pRight) {
			return false;
		}
		
		else {
			return true;
		}

	}

	if (pNode->key > i) {
		return IsLeafNode(pNode->pLeft, i);
	}

	if (pNode->key < i) {
		return IsLeafNode(pNode->pRight, i);
	}

}

int AAtree::Split(Node*& pNode) {

	if (!pNode->pRight->pLeft) {
		pNode->pRight->pLeft = pNode;
		pNode = pNode->pRight;
		pNode->pLeft->pRight = NULL;
	}
	else {
		Node *pTemp = new Node(pNode->pRight->pLeft->key,pNode->pRight->pLeft->pLeft,pNode->pRight->pLeft->pRight, pNode->pRight->pLeft->level);
		delete pNode->pRight->pLeft;
		pNode->pRight->pLeft = NULL;
		pNode->pRight->pLeft = pNode;
		pNode = pNode->pRight;
		pNode->pLeft->pRight = pTemp;
	}
	++pNode->level;

	return 2;
}

int AAtree::FindSubstituteNode(Node* pNode) {

	Node* pTemp{ pNode->pRight };

	while (pTemp->pLeft) {
		pTemp = pTemp->pLeft;
	}

	return pTemp->key;
}

Node* AAtree::FindDeletionNode(Node* pNode, int i) {

	if (pNode->key == i) {
		return pNode;
	}

	if (pNode->key > i) {
		return FindDeletionNode(pNode->pLeft, i);
	}

	if (pNode->key < i) {
		return FindDeletionNode(pNode->pRight, i);
	}

}

int AAtree::ReplaceDeletionNode(Node* pNode, int d, int r) {

	if (pNode->key == d) {
		pNode->key = r;
		return 1;
	}

	if (pNode->key > d) {
		return ReplaceDeletionNode(pNode->pLeft, d, r);
	}

	if (pNode->key < d) {
		return ReplaceDeletionNode(pNode->pRight, d, r);
	}
}

int AAtree::InsertNode(int i) {
	
	if (!pRoot) {

		pRoot = new Node(i);
		return 0;

	}
	else {

		if (pRoot->key > i){

			int temp{ InsertNode(pRoot->pLeft, i) };

			if (temp == 0) {
				Skew(pRoot);
				temp = 1;
			}

			if (temp == 2 && pRoot->level <= pRoot->pLeft->level) {
				Skew(pRoot);
			}

			if (!IsHaveOneRightLink(pRoot)) {
				temp = Split(pRoot);
			}
		
			return temp;
		}

		if (pRoot->key < i) {
			int temp{ InsertNode(pRoot->pRight, i) };

			if (temp == 0) {
				temp = 1;
			}

			if (temp == 2 && pRoot->level <= pRoot->pLeft->level) {
				Skew(pRoot);
			}

			if (!IsHaveOneRightLink(pRoot)) {
				temp = Split(pRoot);
			}

			return temp;
		}

	}
}

int AAtree::InsertNode(Node*& pNode, int i)
{
	if (!pNode) {
		pNode = new Node(i);
		return 0;
	}

	else {

		if (pNode->key > i) {
			int temp{ InsertNode(pNode->pLeft, i) };

			if (temp == 0) {
				Skew(pNode);
				temp = 1;
			}

			if (temp == 2 && pNode->level <= pNode->pLeft->level) {
				Skew(pNode);
			}

			if (!IsHaveOneRightLink(pNode)){
				temp = Split(pNode);
			}

			return temp;
		}

		if (pNode->key < i) {
			int temp{ InsertNode(pNode->pRight, i) };

			if (temp == 0) {
				temp = 1;
			}

			if (temp == 2 && pNode->level <= pNode->pLeft->level) {
				Skew(pNode);
			}

			if (!IsHaveOneRightLink(pNode)) {
				temp = Split(pNode);
			}


			return temp;
		}
	}
}

int AAtree::DeleteLeaf(int i) {

	if (pRoot->key == i) {
		delete pRoot;
		return 0;
	}

	else {

		if (pRoot->key > i) {

			int temp{ DeleteLeaf(pRoot->pLeft,i) };

			if (temp == -1) {

				if (pRoot->pRight->level == pRoot->level) {
					--pRoot->pRight->level;
				}

				--pRoot->level;
				temp = 1;

			}

			if (temp == 0) {

				pRoot->pLeft = NULL;

				if (pRoot->pRight->level == pRoot->level) {
					--pRoot->pRight->level;
				}

				--pRoot->level;
				temp = -1;

			}

			if (pRoot->pRight->level == pRoot->pRight->pLeft->level) {
				Skew(pRoot->pRight);
			}

			if (!IsHaveOneRightLink(pRoot)) {
				Split(pRoot);
			}



			return temp;
		}

		if (pRoot->key < i) {

			int temp{ DeleteLeaf(pRoot->pRight,i) };

			if (temp == 0) {

				pRoot->pRight = NULL;
				temp = 1;
			}

			return temp;
		}

	}


}

int AAtree::DeleteLeaf(Node*& pNode, int i) {
	if (pNode->key == i) {
		delete pNode;
		return 0;
	}

	else {

		if (pNode->key > i) {

			int temp{ DeleteLeaf(pNode->pLeft,i) };
			
			if (temp == -1) {

				if (pNode->pRight->level == pNode->level) {
					--pNode->pRight->level;
				}

				--pNode->level;
				temp = 1;

			}

			if (temp == 0) {

				pNode->pLeft = NULL;

				if (pNode->pRight->level == pNode->level) {
					--pNode->pRight->level;
				}

				--pNode->level;
				temp = -1;

			}

			if (pNode->pRight->pLeft && pNode->pRight->level == pNode->pRight->pLeft->level) {
				Skew(pNode->pRight);
			}

			if (!IsHaveOneRightLink(pNode)) {
				Split(pNode);
			}

			

			return temp;
		}

		if (pNode->key < i) {
			
			int temp{ DeleteLeaf(pNode->pRight,i) };

			if (temp == 0) {

				pNode->pRight = NULL;
				temp = 1;
			}
			
			return temp;
		}

	}

}

int AAtree::DeleteNode(int i) {

	Node* pNode = this->pRoot;
	
	if (IsLeafNode(pNode, i)) {
		DeleteLeaf(i);
	}

	else {
		Node* pTemp{ this->pRoot };
		pTemp = FindDeletionNode(pTemp, i);

		int kTemp = FindSubstituteNode(pTemp);

		DeleteLeaf(kTemp);
		ReplaceDeletionNode(pRoot, pTemp->key, kTemp);
	}

	return 1;
}

Node* AAtree::Get() {
	return this->pRoot;
}

AAtree::AAtree()
{
	pRoot = NULL;
	height = 0;
}

int main() {
	AAtree hihi;
	hihi.CreateTree(45);
	hihi.InsertNode(37);
	hihi.InsertNode(12);
	hihi.InsertNode(52);
	hihi.InsertNode(42);
	hihi.InsertNode(8);
	hihi.InsertNode(5);
	hihi.InsertNode(2);
	hihi.InsertNode(1);
	hihi.InsertNode(18);
	hihi.InsertNode(25);
	hihi.DeleteNode(8);
	system("pause");
	return 0;
}
