#pragma once // WARNING!! PRAGMA ONCE IS NOT SUPPORTED BY REPLIT'S DEFAULT COMPILER!!! USE GCC, OR ELSE!!
#include <string>
#include <vector>
#include "iostream"
using namespace std;

/**
 * @brief 
 * WordNode node object, stores a next pointer (as this is for a linked list) and the data string
 */
struct WordNode {
    string word;
    WordNode* next;
    //Default constructor
    WordNode() {
        next = nullptr;
    };
    //copy constructor, copies the values from another WordNode pointer
    WordNode(WordNode* node) {
        next = node->next;
        word = node->word;
    };
    //Another copy constructor, fills data with a provided string
    WordNode(string s) {
        word = s;
    }
};
/**
 * @brief 
 * WordList, a linked list comprosied of WordNodes.
 * Contains two constructors, a push method, and a debug print method that only prints size.
 */
struct WordList {
    WordNode *head;
    WordNode *tail;
    //initialize WordList from a starting WordNode that will become head
    WordList(WordNode *_head) {
        head = tail = _head;
    }
    //initialize an empty WordList
       WordList() {
        head = tail = nullptr;
    }
    //Push a WordNode to the front of the list
    void push(WordNode *word) {
       if (head == nullptr) {
           
            head = new WordNode();
            head->word = word->word;
            head->next = nullptr;
      } else {
        //create new node based on passed in word
        WordNode *node = new WordNode(word);
        //set its next pointer to be head
        node->next = head;
        //head now becomes the new node
        head = node;
      }
    }
    
    void print() {
        WordNode* temp = head;
        int i = 0;
        while(temp->next) {
            i++;
            temp = temp->next;
        }
        cout << i << endl;
    }

    //function to find words, returns a vector of strings
    vector<string> findWords(string searchterm) {
        //the vector to be returned
        vector<string> matches;
        //temp pointer to traverse the list
        WordNode* temp = head;
        int index = -99999;
        //list traversal loop
        while(temp->next) {
           
            index = temp->word.find(searchterm);
            if(index >= 0) { //if its index is 0 or larger, a result was found
            //if so, add result to matches
                matches.push_back(temp->word);
            }
            //advance loop
            temp = temp->next;
        }
        //return vector
        return matches;
    }
};
