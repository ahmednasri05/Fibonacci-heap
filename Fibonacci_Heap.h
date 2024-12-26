#pragma once
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <cmath>
#include <functional>
#include "HashMap.h"
using namespace std;

// Conventions: NIL = nullptr
//              Node* left and right pointers are used to form a circular doubly linked list
//              Node* child pointer is used to point to the leftmost child

template <typename ValueType>
class FibonacciHeap
{
private:
    struct Node
    {
        ValueType value;
        int degree;
        bool marked;
        Node *parent;
        Node *child;
        Node *left;
        Node *right;

        Node(ValueType v)
            : value(v), degree(0), marked(false), parent(nullptr), child(nullptr), left(this), right(this) {}
    };
    typedef Node *NodePointer;
    Node *minNode;
    int nodeCount;
    HashMap<int, Node *> nodeMap;

    // Used by decrease key to clean up the heap to be in the fib sequence
    void consolidate();
    // Used by the consolidate function to make a node in the root list become a child
    void link(Node *y, Node *x);
    // Used by decrease key to remove a child and append it to the root list
    void cut(Node *x, Node *y);
    // Used by decrease key to propagate the cut upwards through the tree, recursively until a non-marked node is found or the root is reached.
    void cascadingCut(Node *y);
    void deleteAll(Node *node);
    void swap(Node *&x, Node *&y);
    string escapeString(const string &str);

public:
    FibonacciHeap();
    ~FibonacciHeap();

    void insert(const ValueType &value);
    void merge(FibonacciHeap &other);
    bool isEmpty() const;
    ValueType extractMin();
    void decreaseKey(const ValueType &oldValue,const ValueType &newValue);
    typename FibonacciHeap<ValueType>::NodePointer findNode(const ValueType &value);
    void deleteNode(const ValueType &value); // has to take ValueType not Node*
    ValueType getMin() const;
    void print();
};

template <typename ValueType>
FibonacciHeap<ValueType>::FibonacciHeap()
{
    minNode = nullptr;
    nodeCount = 0;
}

template <typename ValueType>
FibonacciHeap<ValueType>::~FibonacciHeap()
{
    deleteAll(minNode);
}

template <typename ValueType>
void FibonacciHeap<ValueType>::insert(const ValueType &value)
{
    Node *x = new Node(value);
    // x->value.setPriority(value.getPriority());
    //  add the new node to the hashmap
    if (minNode == nullptr)
    {
        x->right = x;
        x->left = x;
        minNode = x;
    }
    else
    {
        x->right = minNode;
        x->left = minNode->left;
        minNode->left->right = x;
        minNode->left = x;
        if (x->value < minNode->value)
        {
            minNode = x;
        }
    }
    nodeMap.insertDouble(value.getId(), x);
    nodeCount++;
}

template <typename ValueType>
ValueType FibonacciHeap<ValueType>::extractMin()
{
    Node *z = minNode;
    if (!isEmpty())
    {
        // Remove from the map
        nodeMap.removeDouble(z->value.getId());
        while (z->child != nullptr)
        {
            // Add x to the root list of H
            cut(z->child, z); // x.p = nullptr, z.degree--, x.marked = false, insertNode(z->child), nodeCount++
        }
        // Remove z from the root list
        z->left->right = z->right;
        z->right->left = z->left;
        if (z == z->right)
        {
            minNode = nullptr;
        }
        else
        {
            minNode = z->right;
            consolidate();
        }
        nodeCount--;
        ValueType minValue = z->value;
        delete z;
        return minValue;
    }
    cerr << "The heap is empty" << endl;
    return ValueType(); // Return default value if heap is empty
}
template <typename ValueType>
ValueType FibonacciHeap<ValueType>::getMin() const
{
    if (minNode == nullptr)
    {
        cerr << "Heap is empty when calling getMin." << endl;
    }
    else
    {
        cout << "Returning minNode Patient ID: " << minNode->value.getId() << ", Priority: " << minNode->value.getPriority() << endl;
    }
    return minNode->value;
}

template <typename ValueType>
void FibonacciHeap<ValueType>::merge(FibonacciHeap &other)
{
    // If other heap is empty simply do nothing
    if (!other.isEmpty())
    {
        if (isEmpty())
        {
            // if my heap is empty
            minNode = other.minNode;
            nodeCount = other.nodeCount;
        }
        else
        {
            // merge the root lists
            minNode->left->right = other.minNode->right;
            other.minNode->right->left = minNode->left;
            other.minNode->right = minNode;
            minNode->left = other.minNode;
            nodeCount += other.nodeCount;
            // Update the minNode to the smaller of the two
            if (other.minNode->value < minNode->value)
            {
                minNode = other.minNode;
            }
        }
        // Clear the other heap
        other.minNode = nullptr;
        other.nodeCount = 0;
    }
}
template <typename ValueType>
bool FibonacciHeap<ValueType>::isEmpty() const
{
    return minNode == nullptr;
}

template <typename ValueType>
void FibonacciHeap<ValueType>::decreaseKey(const ValueType &oldValue,const ValueType &newValue)
{
    if (newValue > oldValue)
    {
        cout << "New Value is greater than current" << endl;
        exit(0);
    }
    Node *node = findNode(oldValue);
    nodeMap.removeDouble(node->value.getId());
    node->value = newValue;
    nodeMap.insertDouble(newValue.getId(), node);
    // Get Parent
    Node *parent = node->parent;
    // If new value is smaller than parent cut and mark parent
    if (parent != nullptr && parent->value > node->value)
    {
        cut(node, parent);
        cascadingCut(parent);
    }
    // Update min
    if (node->value < minNode->value)
    {
        minNode = node;
    }
}

template <typename ValueType>
void FibonacciHeap<ValueType>::cut(Node *x, Node *y)
{
    // If x is the only child, set y's child to nullptr.
    if (x->right == x)
    {
        y->child = nullptr;
    }
    else
    {
        // Remove x from its sibilings
        x->right->left = x->left;
        x->left->right = x->right;
        // Connect y child to any of the siblings
        if (y->child == x)
        {
            y->child = x->right;
        }
    }
    y->degree--;
    // Add the node in the root list
    x->right = minNode;
    x->left = minNode->left;
    minNode->left->right = x;
    minNode->left = x;
    // Remove its parent and unmark it
    x->parent = nullptr;
    x->marked = false;
}
template <typename ValueType>
void FibonacciHeap<ValueType>::cascadingCut(Node *y)
{
    Node *z = y->parent;
    // Only enters if y has parent because if y doesn't have a parent it is already in the root list
    if (z != nullptr)
    {
        // Mark true if unmarked because this function is always called after cutting
        if (!y->marked)
        {
            y->marked = true;
        }
        else
        {
            // If marked cut and recurse using the parent until a non-marked node is found or the root is reached
            cut(y, z);
            cascadingCut(z);
        }
    }
}

template <typename ValueType>
typename FibonacciHeap<ValueType>::NodePointer FibonacciHeap<ValueType>::findNode(const ValueType &value)
{
    return nodeMap.searchDouble(value.getId());
}

template <typename ValueType>
void FibonacciHeap<ValueType>::deleteNode(const ValueType &value)
{
    Node *node = findNode(value);
    ValueType newValue = value;
    newValue.setPriority(-11);
    if (node != nullptr)
    {
        decreaseKey(node->value, newValue);
        extractMin();
    }
    nodeCount--;
}

template <typename ValueType>
void FibonacciHeap<ValueType>::consolidate()
{
    // array size is log(n) base 1.618, which is the golden ratio aka fibonacci ratio
    int arraySize = static_cast<int>(log(nodeCount) / log(1.618)) + 1;
    Node **degreeTable = new Node *[arraySize];
    for (int i = 0; i < arraySize; ++i)
    {
        degreeTable[i] = nullptr;
    }
    vector<Node *> rootNodes;
    Node *current = minNode;
    if (current != nullptr)
    {
        do
        {
            rootNodes.push_back(current);
            current = current->right;
        } while (current != minNode);
    }

    for (Node *w : rootNodes)
    {
        Node *x = w;
        int d = x->degree;
        while (degreeTable[d] != nullptr)
        {
            Node *y = degreeTable[d];
            if (x->value > y->value)
            {
                swap(x, y);
            }
            link(y, x);
            degreeTable[d] = nullptr;
            d++;
        }
        degreeTable[d] = x;
    }

    minNode = nullptr;
    for (int i = 0; i < arraySize; i++)
    {
        if (degreeTable[i] != nullptr)
        {
            if (minNode == nullptr)
            {
                minNode = degreeTable[i];
                minNode->left = minNode;
                minNode->right = minNode;
            }
            else
            {
                degreeTable[i]->left = minNode;
                degreeTable[i]->right = minNode->right;
                minNode->right->left = degreeTable[i];
                minNode->right = degreeTable[i];
                if (degreeTable[i]->value < minNode->value)
                {
                    minNode = degreeTable[i];
                }
            }
        }
    }
    delete[] degreeTable;
}

template <typename ValueType>
void FibonacciHeap<ValueType>::swap(Node *&x, Node *&y)
{
    Node *temp = x;
    x = y;
    y = temp;
}

template <typename ValueType>
void FibonacciHeap<ValueType>::link(Node *y, Node *x)
{
    // Remove y from the root list
    y->left->right = y->right;
    y->right->left = y->left;

    // Make y a child of x
    y->parent = x;
    if (x->child == nullptr)
    {
        x->child = y;
        y->right = y;
        y->left = y;
    }
    else
    {
        y->right = x->child;
        y->left = x->child->left;
        x->child->left->right = y;
        x->child->left = y;
    }

    // Increase the degree of x
    x->degree++;

    // Mark y as false
    y->marked = false;
}
template <typename ValueType>
void FibonacciHeap<ValueType>::deleteAll(Node *node)
{
    // Empty implementation
}
template <typename ValueType>
void FibonacciHeap<ValueType>::print()
{
    if (!minNode)
    {
        cout << "The Fibonacci Heap is empty." << endl;
        return;
    }

    ofstream dotFile("fibonacci_heap.dot");
    dotFile << "digraph FibonacciHeap {\n";
    dotFile << "    graph [rankdir=TB];\n";     // Top-to-bottom layout for hierarchy
    dotFile << "    node [shape=plaintext];\n"; // Use plaintext for HTML-like labels

    // To group nodes by levels
    vector<vector<Node *>> levels;

    // Recursive lambda to group nodes by levels
    function<void(Node *, int)> groupByLevels = [&](Node *node, int level)
    {
        if (!node)
            return;
        Node *start = node;
        do
        {
            // Ensure levels vector can accommodate this level
            if (levels.size() <= level)
                levels.push_back({});
            levels[level].push_back(node);

            // Recurse into children
            if (node->child)
                groupByLevels(node->child, level + 1);

            node = node->right;
        } while (node != start);
    };

    // Group nodes starting from the root list
    groupByLevels(minNode, 0);

    // Recursive lambda to generate DOT representation
    function<void(Node *, ofstream &)> generateDot = [&](Node *node, ofstream &out)
    {
        if (!node)
            return;

        Node *start = node;
        do
        {
            ostringstream nodeLabel;
            nodeLabel << "Node" << node;

            // HTML-like label for the node
            out << "    " << nodeLabel.str() << " [label=<\n";
            out << "        <table border=\"1\" cellborder=\"0\" cellspacing=\"0\">\n";
            out << "            <tr><td colspan=\"2\"><b>Node</b></td></tr>\n";
            out << "            <tr><td><b>Name:</b></td><td>" << escapeString(node->value.getName()) << "</td></tr>\n";
            out << "            <tr><td><b>ID:</b></td><td>" << node->value.getId() << "</td></tr>\n";
            out << "            <tr><td><b>Priority:</b></td><td>" << node->value.getPriority() << "</td></tr>\n";
            out << "            <tr><td><b>Description:</b></td><td>" << escapeString(node->value.getDescription()) << "</td></tr>\n";
            out << "        </table>\n";
            out << "    >];\n";

            // Highlight the minNode
            if (node == minNode)
            {
                out << "    MinPointer -> " << nodeLabel.str() << " [color=red, penwidth=2];\n";
            }

            // Render child connection
            if (node->child)
            {
                out << "    " << nodeLabel.str() << " -> Node" << node->child
                    << " [label=\"child\", color=blue];\n";
                generateDot(node->child, out);
            }

            // Render sibling connections
            if (node->right != node)
            {
                out << "    " << nodeLabel.str() << " -> Node" << node->right
                    << " [label=\"right\", color=green, constraint=false];\n";
                out << "    " << nodeLabel.str() << " -> Node" << node->left
                    << " [label=\"left\", color=orange, constraint=false];\n";
            }

            node = node->right;
        } while (node != start);
    };

    // Add a visual pointer to the minNode
    dotFile << "    MinPointer [shape=plaintext, label=\"<Minimum Node>\", fontcolor=red];\n";

    // Generate DOT for all nodes starting from the root list
    generateDot(minNode, dotFile);

    // Enforce rank constraints for levels
    for (size_t i = 0; i < levels.size(); ++i)
    {
        dotFile << "    { rank=same; ";
        for (Node *node : levels[i])
        {
            dotFile << "Node" << node << "; ";
        }
        dotFile << "}\n";
    }

    dotFile << "}\n";
    dotFile.close();

    // Call Graphviz to generate a PNG
    system("dot -Tpng fibonacci_heap.dot -o fibonacci_heap.png");

    cout << "Fibonacci Heap visualization generated: fibonacci_heap.png" << endl;
}

template <typename ValueType>
string FibonacciHeap<ValueType>::escapeString(const string &str)
{
    string escaped;
    for (char c : str)
    {
        if (c == '"')
            escaped += "\\\"";
        else
            escaped += c;
    }
    return escaped;
}
