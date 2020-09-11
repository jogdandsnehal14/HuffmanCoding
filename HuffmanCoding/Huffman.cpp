//---------------------------------------------------------------------------
// File: Huffman.h
// Author: Snehal Jogdand
// Date: 01/29/2020
// Program 1: Huffman Coding
//
// DESCRIPTION:
// Huffman: 
//  The class file for Huffman class
//  Provides the set of variables and functions to process 
//  a HuffmanTree
//---------------------------------------------------------------------------

#include "Huffman.h"

//------------------------------------------------------------------------
// Creates a new node with the given comparable item
// @pre None.
// @param data The character data
// @param frequency The frequency of the character
// @param left The left node item
// @param right The right node item
// @returns The newly created Node object
Huffman::Node* Huffman::getNewNode(char data, int frequency, const Node* left, const Node* right)
{
   Node* node = new Node();
   node->data = data;
   node->frequency = frequency;
   node->left = left;
   node->right = right;
   return node;
}

//------------------------------------------------------------------------
// The Huffman default constructor
Huffman::Huffman() {
}

//------------------------------------------------------------------------
// This constructor takes the frequency for each letter from 'a' to 'z'. 
// It constructs the Huffman tree and compute the code for each character
// @pre The array contains the frequency of letters from 'a' to 'z'.
// @param counts The array containing the frequency of each letter
Huffman::Huffman(int counts[NUM_CHAR]) {
   Heap<Node>* heap = new Heap<Node>();
   char ch = 'a';
   for (int i = 0; i < NUM_CHAR; i++) {
      char nextCh = ch + i;
      if (counts[i] > 0) {
         Node* node = getNewNode(nextCh, counts[i], nullptr, nullptr);
         heap->insert(node);
      }
   }

   while (heap->size() > 1) {
      const Node* left = heap->deleteMin();
      const Node* right = heap->deleteMin();
      Node* newNode = getNewNode('#', left->frequency + right->frequency, left, right);
      heap->insert(newNode);
   }

   prepareCodebook(heap->findMin(), "");

   const Node* temp = heap->findMin();
   clear(temp);
   delete heap;
}

//------------------------------------------------------------------------
// This methods takes in a word to encode. All letters in the word are
// converted to the appropriate bit strings.Non - letters may be ignored.
// @pre The codebook is generated
// @param in The string to huffman encode
// @returns The created huffman code for provided string
string Huffman::getWord(string in) {
   string output = "";
   for (char ch : in) {
      // ignore non-letters
      if (ch - 'a' >= 0 || ch - 'a' <= 'z' - 'a') 
         output += codebook[ch - 'a'];
   }

   return output;
}

//------------------------------------------------------------------------
// Recursively generates the codebook from the given heap root node by traversing the heap tree
// @pre items has been allocated space for the pointers.
// @param root The heap root node
// @param code The generated huffman code
void Huffman::prepareCodebook(const Node* root, string code) {
   if (root == nullptr) return;
   if (root->data != '#') codebook[root->data - 'a'] = code;

   prepareCodebook(root->left, code + "0");
   prepareCodebook(root->right, code + "1");
}

//------------------------------------------------------------------------
// Destroys all the nodes in the given BS Tree in a recursive manner
// @pre No
// @param node The heap root node
void Huffman::clear(const Node* node) {
   if (node == nullptr) return;
   const Node* nodeToDeletePtr = node;
  
   if (node->left == nullptr && node->right == nullptr)
   {
      delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr;
      return;
   }

   clear(node->left);
   clear(node->right);
}

//------------------------------------------------------------------------
// The Huffman destructor
Huffman::~Huffman() {
   codebook->clear();
}

//------------------------------------------------------------------------
// Overload output stream '<<' operator.
// @pre None.
// @param output The output stream to print the output
// @param huffman The huffman object to output
ostream& operator<<(ostream& output, Huffman& huffman) {
   for (int i = 0; i < NUM_CHAR; i++) {
      if (huffman.codebook[i].size() > 0)
         output << (char) ('a' + i) << "\t" << huffman.codebook[i] << endl;
   }

   return output;
}