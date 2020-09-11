//---------------------------------------------------------------------------
// File: Huffman.h
// Author: Snehal Jogdand
// Date: 01/29/2020
// Program 1: Huffman Coding
//
// DESCRIPTION:
// Huffman: 
//  The header file for Huffman class
//  Provides the set of variables and functions to process 
//  a HuffmanTree
//---------------------------------------------------------------------------

#ifndef HUFFMAN_
#define HUFFMAN_

//---------------------------------------------------------------------------
// Huffman: 
//  The header file for Huffman class
//  Provides the set of variables and functions to process 
//  a HuffmanTree
//---------------------------------------------------------------------------

#include <string>
#include "Heap.h"
#include <iostream>

using namespace std;

const int NUM_CHAR = 26;

/**
    The Huffman class
 */
class Huffman
{
private:

   // The Huffman Tree Node structure
   struct Node {
      char data;
      int frequency;
      const Node* left;
      const Node* right;

      Node() : data(NULL), frequency(0), left(nullptr), right(nullptr) {}

      //------------------------------------------------------------------------
      // Overload < operator.
      // @pre None.
      // @param o The Node object to compare against
      // @returns True if the Node object is less than the right
      bool operator<(const Node& o) { 
         if (frequency != o.frequency) return frequency < o.frequency;
         if (data != o.data) return data < o.data;

         char oData = '#', thisData = '#';
         const Node* lhs = this;
         while (lhs->left != nullptr && lhs->data == '#') {
            lhs = lhs->left;
            thisData = lhs->data;
         }

         const Node *rhs = &o;
         while (rhs->left != nullptr && rhs->data == '#') {
            rhs = rhs->left;
            oData = rhs->data;
         }

         return thisData < oData;
      };

      //------------------------------------------------------------------------
      // Overload > operator.
      // @pre None.
      // @param o The Node object to compare against
      // @returns True if the Node object is less than the right
      bool operator>(const Node& o) {
         if (frequency != o.frequency) return frequency > o.frequency;
         if (data != o.data) return data > o.data;

         char oData = '#', thisData = '#';
         const Node* lhs = this;
         while (lhs->left != nullptr && lhs->data == '#') {
            lhs = lhs->left;
            thisData = lhs->data;
         }

         const Node* rhs = &o;
         while (rhs->left != nullptr && rhs->data == '#') {
            rhs = rhs->left;
            oData = rhs->data;
         }

         return thisData > oData;
      };
      
      //------------------------------------------------------------------------
      // Overload == operator.
      // @pre None.
      // @param o The Node object to compare against
      // @returns True if the Node object is equal to the right
      bool operator==(const Node& o) {
         return frequency == o.frequency && data == o.data;
      };
   };

   string codebook[NUM_CHAR];
   Node* getNewNode(char data, int frequency, const Node* left, const Node* right);
   void prepareCodebook(const Node* node, string code);

public:
   Huffman();
   Huffman(int counts[NUM_CHAR]);

   string getWord(string in);
   friend ostream& operator<<(ostream& output, Huffman& huffman);

   void clear(const Node* heap);
   ~Huffman();
};
#endif