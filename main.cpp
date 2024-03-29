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
		for(int i=0;i<9;i++)
			this->configuration[i] = 0;
		this->gStar = 0;
		this->hStar = 0;
		this->fStar = 0;
		this->parent = nullptr;
		this->next = nullptr;
	}
	
	void printNode(ofstream& output){
		output<<"< ";
		for(int i=0;i<9;i++){
			output<<this->configuration[i]<<" ";
		}
		output<<"| "<<this->fStar<<" | ";
		if(this->parent == nullptr){
			output<<"NULL >";
		}
		else{
			for(int i=0;i<9;i++){
				output<<this->parent->configuration[i]<<" ";
			}
			output<<">";
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
	int h2array[9][9] = {{0,1,2,1,2,3,2,3,4},
						 	   {1,0,1,2,1,2,3,2,3},
					 		   {2,1,0,3,2,1,4,3,2},
							   {1,2,3,0,1,2,1,2,3},
							   {2,1,2,1,0,1,2,1,2},
							   {3,2,1,2,1,0,3,2,1},
							   {2,3,4,1,2,3,0,1,2},
							   {3,2,3,2,1,2,1,0,1},
							   {4,3,2,3,2,1,2,1,0}};

	AStarSearch(){
		this->openList = new AstarNode();
		this->closeList = new AstarNode();
		this->childList = nullptr;
	}
	//simple methods
	int computeGstar(AstarNode* node){
		int temp;
		temp = node->parent->gStar + 1;
		return temp;
	}
	int computeHstar(AstarNode* node){
		int miss = 0;
		for(int i=0; i<9;i++){
			miss += this->h2array[node->configuration[i]][this->goalNode.configuration[i]];
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
	bool isGoalNode(AstarNode* node){
		return this->match(node->configuration, this->goalNode.configuration);
	}
	//complex methods
	bool checkAncestors(AstarNode* currentNode, AstarNode* parent){
		if(parent == nullptr){
			return false;
		}
		else if(this->match(currentNode->configuration, parent->configuration)){
			return true;
		}
		else{
			return this->checkAncestors(currentNode, parent->parent);
		}
	}
	AstarNode* constructChildList(AstarNode* currentNode, ofstream& output){
		AstarNode* dummy = new AstarNode();
		for(int i=0;i<9;i++){
			if(currentNode->configuration[i] == 0){
				if(i+1 < 9){
					int temp = 0;
					AstarNode* newNode = new AstarNode();
					//configuration copy
					for(int j=0;j<9;j++)
						newNode->configuration[j] = currentNode->configuration[j];
					//swap	
					temp = newNode->configuration[i];
					newNode->configuration[i] = newNode->configuration[i+1];
					newNode->configuration[i+1] = temp;
					//g h f star assignment
					newNode->parent = currentNode;
					newNode->gStar = this->computeGstar(newNode);
					newNode->hStar = this->computeHstar(newNode);
					newNode->fStar = newNode->gStar + newNode->hStar;
					//output<<"new +1 node:\n";
					//newNode->printNode(output);
					if(!this->checkAncestors(newNode,currentNode)){
						this->push(newNode, &dummy);
					}
					else{
						//output<<"failed to insert\n";
						delete newNode;
					}
				}
				if(i+3 < 9){
					int temp = 0;
					AstarNode* newNode = new AstarNode();
					//configuration copy
					for(int j=0;j<9;j++)
						newNode->configuration[j] = currentNode->configuration[j];
					//swap	
					temp = newNode->configuration[i];
					newNode->configuration[i] = newNode->configuration[i+3];
					newNode->configuration[i+3] = temp;
					//g h f star assignment
					newNode->parent = currentNode;
					newNode->gStar = this->computeGstar(newNode);
					newNode->hStar = this->computeHstar(newNode);
					newNode->fStar = newNode->gStar + newNode->hStar;
					//output<<"new +3 node:\n";
					//newNode->printNode(output);
					if(!this->checkAncestors(newNode,currentNode)){
						this->push(newNode, &dummy);
					}
					else{
						//output<<"failed to insert\n";
						delete newNode;
					}
				}
				if(i-1 >= 0){
					int temp = 0;
					AstarNode* newNode = new AstarNode();
					//configuration copy
					for(int j=0;j<9;j++)
						newNode->configuration[j] = currentNode->configuration[j];
					//swap	
					temp = newNode->configuration[i];
					newNode->configuration[i] = newNode->configuration[i-1];
					newNode->configuration[i-1] = temp;
					//g h f star assignment
					newNode->parent = currentNode;
					newNode->gStar = this->computeGstar(newNode);
					newNode->hStar = this->computeHstar(newNode);
					newNode->fStar = newNode->gStar + newNode->hStar;
					//output<<"new -1 node:\n";
					//newNode->printNode(output);
					if(!this->checkAncestors(newNode,currentNode)){
						this->push(newNode, &dummy);
					}
					else{
						//output<<"failed to insert\n";
						delete newNode;
					}
				}
				if(i-3 >= 0){
					int temp = 0;
					AstarNode* newNode = new AstarNode();
					//configuration copy
					for(int j=0;j<9;j++)
						newNode->configuration[j] = currentNode->configuration[j];
					//swap	
					temp = newNode->configuration[i];
					newNode->configuration[i] = newNode->configuration[i-3];
					newNode->configuration[i-3] = temp;
					//g h f star assignment
					newNode->parent = currentNode;
					newNode->gStar = this->computeGstar(newNode);
					newNode->hStar = this->computeHstar(newNode);
					newNode->fStar = newNode->gStar + newNode->hStar;
					//output<<"new -3 node:\n";
					//newNode->printNode(output);
					if(!this->checkAncestors(newNode,currentNode)){
						this->push(newNode, &dummy);
					}
					else{
						//output<<"failed to insert\n";
						delete newNode;
					}
				}
				return dummy;
			}
		}
		return nullptr;
	}
	void listInsert(AstarNode* node, AstarNode** list){
		AstarNode* temp = *list;
		if(temp->next == nullptr){
			temp->next = node;
		}
		else{
			while(temp->next != nullptr){
				if(temp->next->fStar > node->fStar)
					break;
				temp = temp->next;
			}
			if(temp->next == nullptr){
				temp->next = node;
			}
			else{
				node->next = temp->next;
				temp->next = node;
			}
		}
	}
	AstarNode* listRemove(AstarNode** list){
		AstarNode* listhead= *list;
		if(listhead->next == nullptr){
			cout<<"ERROR! TRIED REMOVING FROM EMPTY LIST.\n";
			exit(-1);
		}
		AstarNode* temp = listhead->next;
		listhead->next = listhead->next->next;
		temp->next = nullptr;
		return temp;
	}
	//printing methods
	void printList(AstarNode** list, ofstream& outfile1){
		AstarNode* temp = *list;
		while(temp != nullptr){
			temp->printNode(outfile1);
			temp = temp->next;
		}
		outfile1<<"~~~~~~~~~~~~~\n";
	}
	void printSolution(AstarNode* currentNode, ofstream& outfile2){
		cout<<endl<<"Solution found. Please see results file."<<endl;
		outfile2<<"Solution found.\nGoal\n";
		printSolutionHelp(currentNode, outfile2);
	}
	bool printSolutionHelp(AstarNode* node, ofstream& outfile2){
		if(node == nullptr){
			outfile2<<"Start Node\n";
			return true;
		}
		else{
			for(int i=0;i<9;i++){
				if(i==3 || i==6)
					outfile2<<endl;
					outfile2<<node->configuration[i]<<" ";
			}
			outfile2<<endl<<endl;
		}
		return printSolutionHelp(node->parent, outfile2);
	}
	//helper methods not on specs
	void removeNode(AstarNode* node, AstarNode** list){
		AstarNode* listhead = *list;
		if(listhead->next == nullptr){
			return;
		}
		listhead = listhead->next; 
		while(listhead->next != nullptr){
			if(match(node->configuration, listhead->next->configuration)){
				AstarNode* bye = listhead->next;
				listhead->next = listhead->next->next;
				delete bye;
				return;
			}
			listhead = listhead->next;
		}
		return;
	}
	void push(AstarNode* node, AstarNode** list){
		AstarNode* temp = *list;
		if(temp->next == nullptr){
			temp->next = node;
		}
		else{
			node->next = temp->next;
			temp->next = node;
		}
	}
	bool inList(AstarNode* node, AstarNode** list){
		AstarNode* listhead = *list;
		if(listhead->next == nullptr){
			return false;
		}
		listhead = listhead->next; 
		while(listhead != nullptr){
			if(match(node->configuration, listhead->configuration )&& node->fStar < listhead->fStar){
				return true;
			}
			else if(match(node->configuration, listhead->configuration) && !(node->fStar < listhead->fStar)){
				return false;
			}
			listhead = listhead->next;
		}
		return false;
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
	AStar.startNode.hStar = AStar.computeHstar(&AStar.startNode);
	AStar.startNode.fStar = AStar.startNode.hStar;
	AStar.listInsert(&AStar.startNode, &AStar.openList);
	/**debug code
	debug<<"Printing Goal:\n";
	AStar.goalNode.printNode(debug);
	debug<<"Debugging after inserting startnode:\n";
	AStar.startNode.printNode(debug);
	AStar.printList(&AStar.openList, debug);
	**/
	AstarNode* currentNode;
	int counter = 0;
	//step 10 loop
	do{
		//step 2
		currentNode = AStar.listRemove(&AStar.openList);
		AStar.listInsert(currentNode, &AStar.closeList);
		/**
		debug<<"Loop number:"<<counter<<endl;
		debug<<"Outputting current node:\n";
		currentNode->printNode(debug);
		**/
		//step 3
		if(AStar.isGoalNode(currentNode)){
			AStar.printSolution(currentNode, results);
			return 0;
		}
		//step 4
		AStar.childList = AStar.constructChildList(currentNode, debug);
		//debug<<"Debugging after creating Child List:\n";
		//AStar.printList(&AStar.childList, debug);
		
		//step 8 loop
		while(AStar.childList->next != nullptr){
			//step 5
			AstarNode* child = AStar.listRemove(&AStar.childList);
			//step 6
			child->gStar = AStar.computeGstar(child);
			child->hStar = AStar.computeHstar(child);
			child->fStar = child->gStar + child->hStar;
			
			//debug<<"printing child node:\n";
			//child->printNode(debug);
			
			//step 7
			bool inOpen = AStar.inList(child, &AStar.openList);
			bool inClose = AStar.inList(child, &AStar.closeList);
			if(!inOpen && !inClose){
				//debug<<"not in either list\n";
				AStar.listInsert(child, &AStar.openList);
				child->parent = currentNode;
			}
			else if(inOpen){
				//debug<<"in open and better f\n";
				AStar.removeNode(child, &AStar.openList);
				AStar.listInsert(child,&AStar.openList);
				child->parent = currentNode;
			}
			else if(inClose){
				//debug<<"in closed and better f\n";
				AStar.removeNode(child, &AStar.closeList);
				AStar.listInsert(child, &AStar.openList);
				child->parent = currentNode;
			}
			else{
				//debug<<"no where to put, deleting\n";
				delete child;
			}
		}
		//step 9
		if(counter < 20){
			debug<<"This is Open List:"<<endl;
			AStar.printList(&AStar.openList,debug);
			debug<<"This is Close List:"<<endl;
			AStar.printList(&AStar.closeList, debug);
		}
		cout<<"Current Loops:"<<++counter<<"\r";
	}while(!AStar.match(currentNode->configuration, AStar.goalNode.configuration) || AStar.openList->next == nullptr);
	//step 11
	if(AStar.openList->next == nullptr && !AStar.match(currentNode->configuration, AStar.goalNode.configuration)){
		debug<<"ERROR! OPEN LIST EMPTY WITHOUT GOAL BEING FOUND"<<endl;
		return -1;
	}
	//step 12
	debug.close();
	results.close();
	return 0;
}