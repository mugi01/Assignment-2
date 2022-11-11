
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <set>
using namespace std;

/* Constants */
const int ALPHABETIC_LENGTH = 26;

/* Our functions */
void getWords(string &w1, string &w2);
void printWordLadder(string w1, string w2);

/* Main function */
int main() {
    
  string w1, w2;
  getWords(w1, w2); 
  printWordLadder(w1, w2);
    
  return 0;
}


void getWords(string &w1, string &w2) {
  while (true) {
    cout << " Enter the word: ";
    cin>>w1;
    
    cout << "Enter another word of the same length: ";
    cin>>w2;
    
    if (w1.length() == w2.length()) {
      break;
    }
    cout << "Please enter two words with the same length." << endl;
  }
}


/* Function: printWordLadder
 */

void printWordLadder(string w1, string w2){
    
    // creates an empty queue of stacks
    queue<stack<string> > myQueue;
    
    //Create a stack which will contain a final word ladder
    stack<string> wordladder;
    
    stack<string> myStack;
    myStack.push(w1);
    myQueue.push(myStack);

    string token;
    ifstream dictionary("dictionary.txt");
    set<string> myDictionary;
    set<string> testedWords;
    
    if(dictionary.is_open()) {
      
	      while (dictionary >> token) {
	    	myDictionary.insert(token);
	      }

	      while (!(myQueue.empty())) {

			stack<string> ladder = myQueue.front();
			myQueue.pop();
			string word = ladder.top();
		
			if (word == w2) {
			
			  // This is the output of the stack
			  cout << "The WordLadder from " << w1 << " to " << w2 << " is \n";
		
			  while(!ladder.empty()){
			  	wordladder.push(ladder.top());
			  	ladder.pop();
			  }
			  while(!wordladder.empty()){
			  	cout<<wordladder.top()<<" > ";
			  	wordladder.pop();
			  }
		} 
		else {
			  // We add a valid English word:
			  string test;
			  for (int i = 0; i < word.size(); i++) {
			    for (char j = 'a'; j <= 'z'; j++) {
			    test = word.substr(0, i) + j + word.substr(i + 1);
		            
			    // if that word is an english word then:
			    if (myDictionary.count(test)) {
			      
			    
			      if (!testedWords.count(test)) {
						stack<string> copy = ladder;
				                
						// put the neighbor word on top of the copy stack.
						copy.push(test);
				        
						myQueue.push(copy);
			      }
			    }
			    testedWords.insert(test);
			}
		}
	      }
	    }
    } else {
      cerr << "Couldn't open the dictionary" << endl;
    }
    
    
}
