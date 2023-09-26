# Binary Search Tree

This folder contains the C++ code for a binary search tree and a text file to be read into the tree

### Overview
- A binary tree data structure is a "tree-like" structure where each node branches out to at most two children.
- A node consists of three parts: data, pointer to left child, and pointer to right child.
- In the case of a binary search tree, the data in a binary tree will be sorted though it may not be a balance sort if the root node is not a median of the data

### Insertion
- There are three possibilites when data is inserted into a binary tree: no data in tree, the data is "less than" the current node, or the data is "greater than" the current node
  - No data in tree: This will cause the new data to become the root of the tree.
  - Less than: This will have the new data node be pushed to the left of the current node
  - More than: This will have the new data node be pushed to the right of the current node

### Time and Space Complexity
- Searching: O(h) where h is the height of the tree (worst case is O(n)).
- Space: O(n)
