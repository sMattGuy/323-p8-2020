#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

class AstarNode{
	public:
	int configuration[9];
	int gStar;
	int hStar;
	int fStar;
	AstarNode* parent;
	AstarNode* next;
	
	AstarNode(){
		this->configuration[9] = {0};
		this->gStar = 0;
		this->hStar = 0;
		this->fStar = 0;
		this->parent = NULL;
		this->next = NULL;
	}
	
	void printNode(ofstream& output){
		for(int i=0;i<9;i++){
			output<<this->configuration[i]<<" ";
		}
		output<<this->fStar<<" ";
		for(int i=0;i<9;i++){
			output<<this->parent->configuration[i]<<" ";
		}
		output<<endl;
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
	
	int computeGstar(AstarNode node){
		int temp;
		temp = node.parent->gStar + 1;
		return temp;
	}
	int computeHstar(AstarNode node){
		int miss = 0;
		for(int i=0; i<9;i++){
			if(node.configuration[i] != this->goalNode.configuration[i])
				miss++;
		}
		return miss;
	}
	
	bool match(int config1[], int config2[]){
		for(int i=0;i<9;i++){
			if(config1[i] != config2[i])
				return false;
		}
		return true;
	}
	bool isGoalNode(AstarNode node){
		return this->match(node.configuration, this->goalNode.configuration);
	}
	bool checkAncestors(AstarNode currentNode){
		if(this->match(currentNode.configuration, this->startNode.configuration))
			return false;
		else if(this->match(currentNode.configuration, this->startNode.configuration))
			return true;
		else
			return checkAncestors(*currentNode.parent);
	}
	bool inList(AstarNode node, AstarNode* list){
		if(list->next == NULL){
			return false;
		}
		AstarNode temp = *list->next; 
		while(temp.next != NULL){
			if(match(node.configuration, temp.configuration)){
				return true;
			}
			temp = *temp.next;
		}
		return false;
	}
	bool betterF(AstarNode node, AstarNode* list){
		if(list->next == NULL){
			return false;
		}
		AstarNode temp = *list->next; 
		while(temp.next != NULL){
			if(match(node.configuration, temp.next->configuration)){
				if(node.fStar < temp.next->fStar){
					return true;
				}
				else
					return false;
			}
			temp = *temp.next;
		}
		return false;
	}
	void swapNode(AstarNode node, AstarNode* list){
		if(list->next == NULL){
			return;
		}
		AstarNode temp = *list->next; 
		while(temp.next != NULL){
			if(match(node.configuration, temp.next->configuration)){
				if(node.fStar < temp.next->fStar){
					node.next = temp.next->next;
					temp.next->next == NULL;
					temp.next = &node;
					return;
				}
				else
					return;
			}
			temp = *temp.next;
		}
		return;
	}
	
	AstarNode listRemove(AstarNode* list){
		if(list->next == NULL){
			cout<<"ERROR! TRIED REMOVING FROM EMPTY LIST.\n";
			exit(-1);
		}
		AstarNode temp = *list->next;
		list->next = list->next->next;
		temp.next = NULL;
		return temp;
	}
	/**
	AstarNode* constructChildList(AstarNode currentNode){
		//no idea figure out later
		return &currentNode;
	}
	**/
	void listInsert(AstarNode node){
		if(this->openList->next == NULL){
			this->openList->next = &node;
		}
		else{
			AstarNode temp = *this->openList->next;
			while(temp.next != NULL){
				if(temp.next->fStar > node.fStar)
					break;
				temp = *temp.next;
			}
			if(temp.next == NULL){
				temp.next = &node;
			}
			else{
				node.next = temp.next;
				temp.next = &node;
			}
		}
	}
	void printList(AstarNode* list, ofstream& outfile1){
		
	}
	void printSolution(AstarNode currentNode, ofstream& outfile2){
		
	}
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
	//step 0
	AStarSearch AStar;
	for(int i=0;i<9;i++){
		inFile1 >> AStar.startNode.configuration[i];
		inFile2 >> AStar.goalNode.configuration[i];
	}
	inFile1.close();
	inFile2.close();
	//step 1
	AStar.startNode.gStar = 0;
	AStar.startNode.hStar = AStar.computeHstar(AStar.startNode);
	AStar.startNode.fStar = AStar.startNode.hStar;
	AStar.listInsert(AStar.startNode);
	AstarNode currentNode;
	//step 9 loop
	do{
		//step 2
		currentNode = AStar.listRemove(AStar.openList);
		//step 3
		if(AStar.isGoalNode(currentNode)){
			AStar.printSolution(currentNode, results);
			return 0;
		}
		//step 4
		
		//AStar.childList = AStar.constructChildList(currentNode);
		
		//step 5
		AstarNode child = AStar.listRemove(AStar.childList);
		child.parent = &currentNode;
		//step 6
		child.gStar = AStar.computeGstar(child);
		child.hStar = AStar.computeHstar(child);
		child.fStar = child.gStar + child.hStar;
		//step 7
		if(!AStar.inList(child, AStar.openList) && !AStar.inList(child, AStar.closeList)){
			AStar.listInsert(child);
		}
		else if(AStar.inList(child, AStar.openList)){
			if(AStar.betterF(child, AStar.openList)){
				AStar.swapNode(child, AStar.openList);
			}
		}
		else if(AStar.inList(child, AStar.closeList)){
			if(AStar.betterF(child, AStar.closeList)){
				AStar.listRemove(AStar.closeList);
				AStar.listInsert(child);
			}
		}
		debug<<"This is Open List:"<<endl;
		AStar.printList(AStar.openList,debug);
		debug<<"This is Close List:"<<endl;
		AStar.printList(AStar.closeList, debug);
	}while(!AStar.match(currentNode.configuration, AStar.goalNode.configuration) || AStar.openList->next == NULL);
	if(AStar.openList->next == NULL && !AStar.match(currentNode.configuration, AStar.goalNode.configuration)){
		debug<<"ERROR! OPEN LIST EMPTY WITHOUT GOAL BEING FOUND"<<endl;
		return -1;
	}
	debug.close();
	results.close();
	return 0;
}