/*
 * Authors: Group6 hw3
 * Date: 2023
 * Filename: tree_indexing_a.cpp 
 * Description: 
 */

/*
 * INSTRUCTIONS:
 * ssume that our block size is 30 bytes. In this question, each node in a B+ tree must fit in a
 * block and its size must be as close as possible to the size of a block. Answer the following parts
 * using B+ trees.
 * (a) Assume that all data values are integers with a fixed size of 8 bytes and each record pointer
 * takes at most 4 bytes. Find a B+ tree whose height changes from 2 to 3 when the value 20 is
 * inserted. Note that the height of a tree is the depth of its deepest node plus one. For example,
 * the height of a tree with a single node is 1. Show your structure before and after the insertion. (1
 * point
*/

//#include <iostream>
#include <stdio.h>


#define BLOCK_SIZE 30
#define INT_SIZE 8
#define RECORD_PTR 4


//Need a stucture for a node here I think.
//Also need to make a double linked list for this stuff.



