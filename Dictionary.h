//
// Created by Fatima Gowher on 2019-11-11.
//

#ifndef ASSIGMENT4B_DICTIONARY_H
#define ASSIGMENT4B_DICTIONARY_H

//
// Created by Fatima Gowher on 2019-10-22.
//


#pragma once

//#ifndef dictionary_h
//#define dictionary_h

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// This will be used to build the prefix tree
struct Node
{
    char character;
    bool isWord;
    Node *nextNodes[26];

    // Initialize the node
    Node(char character, bool isWord)
    {
        this->character = character;
        this->isWord = isWord;

        for (int i = 0; i < 26; i++)
            nextNodes[i] = NULL;
    }
};

// A dictionary is a prefix tree data structure that arranges
// the words through prefixing
class Dictionary
{
public:

    // Create an empty dictionary
    Dictionary()
    {
        // The root node is just a place holder to start with
        root = new Node('\0', false);
        numWords = 0;  //new change
    }

    // Load words from file
    Dictionary(string filename)
    {
        root = new Node('\0', false);  //new change
        numWords = 0;  //new change
        ifstream inFile;
        inFile.open(filename.c_str());  //new change
        string word;

        while (inFile >> word)  //new change
            addWord(word);

        inFile.close();
    }

    // Deallocate all used nodes
    ~Dictionary()
    {
        //deleteNode(root);
    }

    // Find the slots where to put the word
    void addWord(string word)
    {
        if (word.empty())
            return;

        addWord(root, word, 0);
    }

    // Check if the given word forms a word
    bool isWord(string word)
    {
        if (word.empty())
            return false;

        Node *node = findPrefixLastNode(root, word, 0);
        return node != NULL && node->isWord;
    }

    // Check if a word is prefix
    bool isPrefix(string word)
    {
        if (word.empty())
            return false;

        Node *node = findPrefixLastNode(root, word, 0);
        return node != NULL;
    }

    // Print all words that starts with a prefix
    void printWords(string prefix, void visit(string &))
    {
        if (prefix.empty())
        {
            printWords(root, "", visit);
            return;
        }

        Node *node = findPrefixLastNode(root, prefix, 0);
        printWords(node, prefix, visit);
    }

    // Return the number of words
    int wordCount()
    {
        return numWords++;
    }

private:
    Node *root;
    int numWords;

    // Recursively find and add the approriate nodes to store a word
    void addWord(Node *currentNode, string &word, int nextIndex)
    {
        char character = word[nextIndex];

        // Add only the node if it doesn't exist yet
        Node *nextNode = currentNode->nextNodes[character - 'a'];

        if (nextNode == NULL)
        {
            nextNode = new Node(character, false);
            currentNode->nextNodes[character - 'a'] = nextNode;
        }

        // Now dig deeper to find the next characters of the word
        nextIndex++;

        if (nextIndex >= (int) word.size())
        {
            // If we reached the last letter, we formed a word
            if (!nextNode->isWord)
                numWords++;

            nextNode->isWord = true;
            return;
        }

        addWord(nextNode, word, nextIndex);
    }

    // Recursively find the last node that holds the prefix
    Node *findPrefixLastNode(Node *currentNode, string &prefix, int nextIndex)
    {
        char character = prefix[nextIndex];

        // Traverse the next character
        Node *nextNode = currentNode->nextNodes[character - 'a'];

        // Stop if we hit a dead end
        if (nextNode == NULL)
            return NULL;

        // Now dig deeper to find the next characters of the word
        // Stop if we reached a dead end
        nextIndex++;

        if (nextIndex >= (int)prefix.size())
            return nextNode;

        return findPrefixLastNode(nextNode, prefix, nextIndex);
    }

    // Print all words on this branch and sub-branches
    void printWords(Node *currentNode, string prefix, void visit(string &))
    {
        if (currentNode == NULL)
            return;

        if (currentNode->isWord)
            visit(prefix);

        for (int i = 0; i < 26; i++)
        {
            if (currentNode->nextNodes[i] != NULL)
            {
                string newPrefix = prefix;
                newPrefix += (i + 'a');
                printWords(currentNode->nextNodes[i], newPrefix, visit);
            }
        }
    }

    // Recursively delete all words

    void deleteNode(Node *currentNode)
    {
        if (currentNode == NULL)
            return;

        for (int i = 0; i < 26; i++)
            if (currentNode->nextNodes[i] != NULL)
                deleteNode(currentNode->nextNodes[i]);

        delete currentNode;


    }




};












#endif //ASSIGMENT4B_DICTIONARY_H
