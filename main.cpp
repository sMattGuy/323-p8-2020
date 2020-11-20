#include <iostream>
#include <fstream>
using namespace std;

class AstarNode{
	public:
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
	
	void printNode(ofstream& output){
		
	}
};

class AStarSearch{
	public:
	AstarNode startNode;
	AstarNode goalNode;
	AstarNode* openList;
	AstarNode* closeList;
	AstarNode* childList;
	
	AStarSearch(){
		this->openList = new AstarNode();
		this->closeList = new AstarNode();
		this->childList = NULL;
	}
	/**
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
	**/
};

int main(int argc, char* argv[]){
	//checks that correct args were supplied
	if(argc != 5){
		cout<<"Must have 4 arguments in this command to run correctly.\ninFile1, inFile2, Debug, Results\n";
		return -1;
	}
	//creates input stream and checks that its readable
	ifstream inFile1(argv[1]);
	ifstream inFile2(argv[2]);
	if(!inFile1.good() || !inFile2.good()){
		cout<<"Failed to read input file, was name typed correctly?\n";
		return -1;
	}
	//output streams
	ofstream debug(argv[3]);
	ofstream results(argv[4]);
	//create configurations
	int initConfig[9];
	int goalConfig[9];
	
	AStarSearch AStar;
	for(int i=0;i<9;i++){
		inFile1 >> AStar.startNode.configuration[i];
		inFile2 >> AStar.goalNode.configuration[i];
	}
	inFile1.close();
	inFile2.close();
	
	
	
	return 0;
}