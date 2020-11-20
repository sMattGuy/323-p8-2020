#include <iostream>
#include <fstream>
using namespace std;

class AstarNode{
	int configuration[9];
	int gStar;
	int hStar;
	int fStar;
	AstarNode* parent;
	
	AstarNode(){
		this->configuration[9] = {0};
		this->gStar = 0;
		this->hStar = 0;
		this->fStar = 0;
		this->parent = NULL;
	}
	
	void printNode(){
		
	}
};

class AStarSearch{
	AstarNode startNode;
	AstarNode goalNode;
	AstarNode* openList;
	AstarNode* closeList;
	AstarNode* childList;
	
	AStarSearch(){
		this->starNode = NULL;
		this->goalNode = NULL;
		this->openList = NULL;
		this->closeList = NULL;
		this->childList = NULL;
	}
	
	int computeGstar(AstarNode node){
		
	}
	int computeHstar(AstarNode node){
		
	}
	
	bool match(int config1[], int config2[]){
		
	}
	bool isGoalNode(AstarNode node){
		
	}
	bool checkAncestors(AstarNode currentNode){
		
	}
	
	AstarNode listRemove(AstarNode* list){
		
	}
	AstarNode* constructChildList(AstarNode currentNode){
		
	}
	
	void listInsert(AstarNode node){
		
	}
	void printList(AstarNode* list, ofstream& outfile1){
		
	}
	void printSolution(AstarNode currentNode, ofstream& outfile2){
		
	}
};

int main(int argc, char* argv[]){
	return 0;
}