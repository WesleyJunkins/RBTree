#include <iostream>
#include <string>
#include <queue>
#include <climits>
#include <math.h>
using namespace std;

template <typename keytype, typename valuetype>
class RBTree
{
public:
    struct Node
    {
    public:
        Node *parent;
        Node *left;
        Node *right;
        valuetype value;
        keytype key;
        int nSize;
        bool color;

        // DEFAULT CONSTRUCTOR
        Node()
            : key(), value(), color(1), left(nullptr), right(nullptr), parent(nullptr), nSize(1){};

        // SPECIAL CONSTRUCTOR
        Node(keytype k, valuetype v, bool color)
            : key(k), value(v), color(color), left(nullptr), right(nullptr), parent(nullptr), nSize(1){};
    };

    Node *nilNode;
    Node *root;
    bool completeTree;
    int lowestLevel;

    // DEFAULT CONSTRUCTOR
    RBTree()
    {
        nilNode = new Node;
        nilNode->color = 0;
        nilNode->left = nullptr;
        nilNode->right = nullptr;
        nilNode->parent = nullptr;
        nilNode->nSize = 0;
        root = nilNode;
    };

    // SPECIAL CONSTRUCTOR
    RBTree(keytype K[], valuetype V[], int s)
    {
        nilNode = new Node;
        nilNode->color = 0;
        nilNode->left = nullptr;
        nilNode->right = nullptr;
        nilNode->parent = nullptr;
        nilNode->nSize = 0;
        completeTree = true;
        lowestLevel = 0;
        root = nilNode;

        bool alreadyInOrder = true;
        for (int i = 1; i < s; i++)
        {
            if (K[i - 1] > K[i])
            {
                alreadyInOrder = false;
                break;
            }
        }

        if (alreadyInOrder == true)
        {
            root = constructAscendingTree(K, V, 0, s - 1);
            RB_inOrderTreeSubtreeSpecifier(root);
            RB_levelOrderLevelPrinterTraversalAndCompleteTreeChecker(root);
            this->lowestLevel = RB_LowestLevel(root);
            if (completeTree == false)
            {
                RB_levelOrderLevelPrinterTraversalAndBottomLevelColorer(root);
            }
        }
        else
        {
            for (int i = 0; i < s; i++)
            {
                insert(K[i], V[i]);
            }
        }
    };

    // COPY HELPER FUNCTION
    Node *RB_copyHelper(const Node *current)
    {
        Node *newNode = new Node;
        newNode->key = current->key;
        newNode->value = current->value;
        newNode->color = current->color;
        newNode->nSize = current->nSize;

        if (current->left != nilNode)
        {
            newNode->left = RB_copyHelper(current->left);
            newNode->left->parent = newNode;
        }
        else
        {
            newNode->left = nilNode;
        }

        if (current->right != nilNode)
        {
            newNode->right = RB_copyHelper(current->right);
            newNode->right->parent = newNode;
        }
        else
        {
            newNode->right = nilNode;
        }

        return newNode;
    };

    // COPY CONSTRUCTOR
    RBTree(const RBTree &other)
    {
        nilNode = new Node;
        nilNode->color = 0;
        nilNode->left = nullptr;
        nilNode->right = nullptr;
        nilNode->parent = nilNode;
        nilNode->nSize = 0;
        root = nilNode;

        if (other.root != other.nilNode)
        {
            root = RB_copyHelper(other.root);
            lowestLevel = other.lowestLevel;
            completeTree = other.completeTree;
        }
    };

    // COPY ASSIGNMENT OPERATOR
    RBTree &operator=(const RBTree &other)
    {
        if (this != &other)
        {
            clear(root);
            delete nilNode;

            nilNode = new Node;
            nilNode->color = 0;
            nilNode->left = nullptr;
            nilNode->right = nullptr;
            nilNode->parent = nilNode;
            nilNode->nSize = 0;
            root = nilNode;

            if (other.root != other.nilNode)
            {
                root = RB_copyHelper(other.root);
                lowestLevel = other.lowestLevel;
                completeTree = other.completeTree;
            }
        }
        return *this;
    };

    // DESTRUCTOR
    ~RBTree()
    {
        clear(root);
        delete nilNode;
    };

    // TRADITIONAL SEARCH
    valuetype *search(keytype K)
    {
        Node *current = root;
        while (current != nilNode)
        {
            if (K == current->key)
            {
                return &current->value;
            }
            else if (K < current->key)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return nullptr;
    };

    // NODE SEARCH
    Node *nodeSearch(keytype K)
    {
        Node *current = root;
        while (current != nilNode)
        {
            if (K == current->key)
            {
                return current;
            }
            else if (K < current->key)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return nullptr;
    };

    // INSERT
    void insert(keytype K, valuetype V)
    {
        Node *newNode = new Node;
        newNode->parent = nilNode;
        newNode->left = nilNode;
        newNode->right = nilNode;
        newNode->key = K;
        newNode->value = V;
        RB_Insert(newNode);
    };

    // REMOVE----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    int remove(keytype K)
    {
        Node *nodeToDelete = nodeSearch(K);
        if (nodeToDelete == nullptr)
        {
            return 0;
        }
        else
        {
            RB_delete(nodeToDelete);
        }
        return 1;
    };

    // RANK
    int rank(keytype K)
    {
        Node *current = root;
        while (current != nilNode)
        {
            if (K == current->key)
            {
                return RB_Rank(current);
            }
            else if (K < current->key)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return 0;
    };

    // Select
    keytype select(int pos)
    {
        Node *selectedNode;
        selectedNode = RB_Select(this->root, pos);
        if (selectedNode != nilNode)
        {
            return selectedNode->key;
        }
        return selectedNode->key;
    };

    // K's SUCCESSOR
    keytype *successor(keytype K)
    {
        Node *node = nodeSearch(K);
        Node *newNode;
        if (node->right != nilNode)
        {
            newNode = treeMinimum(node->right);
        }
        else
        {
            newNode = node->parent;
            while ((newNode != nullptr) && (node == newNode->right))
            {
                node = newNode;
                newNode = newNode->parent;
            }
        }
        return &newNode->key;
    };

    // K's PREDECESSOR
    keytype *predecessor(keytype K)
    {
        Node *node = nodeSearch(K);
        Node *newNode;
        if (node->left != nilNode)
        {
            newNode = treeMaximum(node->left);
        }
        else
        {
            newNode = node->parent;
            while ((newNode != nullptr) && (node == newNode->left))
            {
                node = newNode;
                newNode = newNode->parent;
            }
        }
        return &newNode->key;
    };

    // SIZE
    int size()
    {
        if ((root != nilNode) && (root != nullptr))
        {
            return root->nSize;
        }
        else
        {
            return 0;
        }
    };

    // PREORDER TRAVERSAL
    void preorder()
    {
        RB_preorder(root);
        cout << endl;
    };

    // INORDER TRAVERSAL
    void inorder()
    {
        RB_inorder(root);
        cout << endl;
    };

    // POSTORDER TRAVERSAL
    void postorder()
    {
        RB_postorder(root);
        cout << endl;
    };

    // HELPER FUNCTIONS
    // ROTATE LEFT
    void leftRotation(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != nilNode)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;

        y->nSize = x->nSize;
        x->nSize = x->left->nSize + x->right->nSize + 1;
    };

    // ROTATE RIGHT
    void rightRotation(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != nilNode)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;

        y->nSize = x->nSize;
        x->nSize = x->left->nSize + x->right->nSize + 1;
    };

    // INSERT FIXUP HELPER
    void RB_Insert_Fixup(Node *z)
    {
        Node *y;
        while (z->parent->color == 1)
        {
            if (z->parent == z->parent->parent->right)
            {
                y = z->parent->parent->left;
                if (y->color == 1)
                {
                    z->parent->color = 0;
                    y->color = 0;
                    z->parent->parent->color = 1;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotation(z);
                    }
                    z->parent->color = 0;
                    z->parent->parent->color = 1;
                    leftRotation(z->parent->parent);
                }
            }
            else
            {
                y = z->parent->parent->right;
                if (y->color == 1)
                {
                    z->parent->color = 0;
                    y->color = 0;
                    z->parent->parent->color = 1;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotation(z);
                    }
                    z->parent->color = 0;
                    z->parent->parent->color = 1;
                    rightRotation(z->parent->parent);
                }
            }
            if (z == root)
            {
                break;
            }
        }
        root->color = 0;
    };

    // INSERT HELPER
    void RB_Insert(Node *z)
    {
        Node *y;
        Node *x;
        y = nullptr;
        x = this->root;
        while (x != nilNode)
        {
            y = x;
            if (z->key < x->key)
            {
                x->nSize++;
                x = x->left;
            }
            else
            {
                x->nSize++;
                x = x->right;
            }
        }
        z->parent = y;
        if (y == nullptr)
        {
            root = z;
        }
        else if (z->key < y->key)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }
        if (z->parent == nullptr)
        {
            z->color = 0;
            return;
        }
        if (z->parent->parent == nullptr)
        {
            return;
        }
        RB_Insert_Fixup(z);
    };

    // Preorder Traversal
    void RB_preorder(Node *current)
    {
        if (current == nilNode)
        {
            return;
        }
        cout << current->key << " ";
        RB_preorder(current->left);
        RB_preorder(current->right);
    };

    // Inorder Traversal
    void RB_inorder(Node *current)
    {
        if (current == nilNode)
        {
            return;
        }
        RB_inorder(current->left);
        cout << current->key << " ";
        RB_inorder(current->right);
    };

    // Postorder Traversal
    void RB_postorder(Node *current)
    {
        if (current == nilNode)
        {
            return;
        }
        RB_postorder(current->left);
        RB_postorder(current->right);
        cout << current->key << " ";
    };

    // BUILD ASCENDING TREE IN O(size) TIME
    Node *constructAscendingTree(keytype K[], valuetype V[], int start, int end)
    {
        if (start > end)
        {
            return nilNode;
        }

        int middle = (start + end) / 2;
        Node *newNode = new Node;
        newNode->key = K[middle];
        newNode->value = V[middle];
        newNode->color = 0;
        newNode->left = constructAscendingTree(K, V, start, middle - 1);
        newNode->right = constructAscendingTree(K, V, middle + 1, end);
        newNode->left->parent = newNode;
        newNode->right->parent = newNode;

        return newNode;
    };

    // CLEAR FUNCTION
    void clear(Node *z)
    {
        if (z != nilNode)
        {
            clear(z->left);
            clear(z->right);
            delete z;
        }
    };

    // Return the nSize of a node. (Subtree size plus 1)
    int nSizeHelper(Node *node)
    {
        return node->nSize;
    }

    // SELECT HELPER FUNCTION
    Node *RB_Select(Node *x, int i)
    {
        int r = x->left->nSize + 1;
        if (i == r)
        {
            return x;
        }
        else if (i < r)
        {
            return RB_Select(x->left, i);
        }
        else
        {
            return RB_Select(x->right, i - r);
        }
    };

    // RANK HELPER FUNCTION
    int RB_Rank(Node *x)
    {
        int r = x->left->nSize + 1;
        Node *y = x;
        while (y != this->root)
        {
            if (y == y->parent->right)
            {
                r = r + y->parent->left->nSize + 1;
            }
            y = y->parent;
        }
        return r;
    };

    // FUNCTION TO GIVE IN-ORDER CONSTRUCTED TREE THE CORRECT SUBTREE SIZES
    void RB_inOrderTreeSubtreeSpecifier(Node *current)
    {
        if (current == nilNode)
        {
            return;
        }
        RB_inOrderTreeSubtreeSpecifier(current->left);
        RB_inOrderTreeSubtreeSpecifier(current->right);
        current->nSize = current->left->nSize + current->right->nSize + 1;
    };

    // FUNCTION TO FIND THE LOWEST LEVEL OF THE TREE
    int RB_LowestLevel(Node *node)
    {
        if (node == nilNode)
        {
            return 0;
        }
        else
        {
            int leftDepth = RB_LowestLevel(node->left);
            int rightDepth = RB_LowestLevel(node->right);

            if (leftDepth > rightDepth)
            {
                return (leftDepth + 1);
            }
            else
            {
                return (rightDepth + 1);
            }
        }
    };

    // FUNCTION TO CHECK IF A TREE IS COMPLETE (EACH LEVEL HAS 2^LEVEL-1 NODES)
    void RB_levelOrderLevelPrinterTraversalAndCompleteTreeChecker(Node *root)
    {
        if (root == nilNode)
        {
            return;
        }
        queue<Node *> q;
        q.push(root);
        int level = 1;
        while (!q.empty())
        {
            size_t size = q.size();
            if (!(size == pow(2, (level - 1))))
            {
                this->completeTree = false;
            }
            for (int i = 0; i < size; i++)
            {
                Node *current = q.front();
                q.pop();
                if (current->left != nilNode)
                {
                    q.push(current->left);
                }
                if (current->right != nilNode)
                {
                    q.push(current->right);
                }
            }
            level++;
        }
    };

    // FUNCTION TO COLOR THE BOTTOM LEVEL OF A TREE RED
    void RB_levelOrderLevelPrinterTraversalAndBottomLevelColorer(Node *root)
    {
        if (root == nilNode)
        {
            return;
        }
        queue<Node *> q;
        q.push(root);
        int level = 1;
        while (!q.empty())
        {
            size_t size = q.size();
            for (int i = 0; i < size; i++)
            {
                Node *current = q.front();
                q.pop();
                if (this->lowestLevel == level)
                {
                    current->color = 1;
                }
                if (current->left != nilNode)
                {
                    q.push(current->left);
                }
                if (current->right != nilNode)
                {
                    q.push(current->right);
                }
            }
            level++;
        }
    };

    // FUNCTION TO FIND THE MINIMUM OF A TREE (OR SUBTREE OF A PARTICULAR NODE)
    Node *treeMinimum(Node *x)
    {
        while (x->left != nilNode)
        {
            x = x->left;
        }
        return x;
    };

    // FUNCTION TO FIND THE MINIMUM OF A TREE (OR SUBTREE OF A PARTICULAR NODE)
    Node *treeMaximum(Node *x)
    {
        while (x->right != nilNode)
        {
            x = x->right;
        }
        return x;
    }

    // STANDARD TRANSPLANT FUNCTION
    void RB_transplant(Node *u, Node *v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    };

    // FUNCTION TO FIX THE TREE AFTER A DELETE
    void RB_deleteFixup(Node *x)
    {
        Node *w = new Node;
        while ((x != root) && (x->color == 0))
        {
            if (x == x->parent->left)
            {
                w = x->parent->right;
                if (w->color == 1)
                {
                    w->color = 0;
                    x->parent->color = 1;
                    leftRotation(x->parent);
                    w = x->parent->right;
                }
                if ((w->left->color == 0) && (w->right->color == 0))
                {
                    w->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == 0)
                    {
                        w->left->color = 0;
                        w->color = 1;
                        rightRotation(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->right->color = 0;
                    leftRotation(x->parent);
                    x = root;
                }
            }
            else
            {
                w = x->parent->left;
                if (w->color == 1)
                {
                    w->color = 0;
                    x->parent->color = 1;
                    rightRotation(x->parent);
                    w = x->parent->left;
                }
                if ((w->right->color == 0) && (w->left->color == 0))
                {
                    w->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == 0)
                    {
                        w->right->color = 0;
                        w->color = 1;
                        leftRotation(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->left->color = 0;
                    rightRotation(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    };

    // DELETE FUNCTION
    void RB_delete(Node *z)
    {
        bool lastNode = false;
        if ((z == root) && (z->nSize == 1))
        {
            lastNode = true;
        }
        Node *y;
        Node *x;
        Node *current;
        y = z;
        bool yOriginalColor = y->color;
        if (z->right == nilNode)
        {
            x = z->left;
            RB_transplant(z, z->left);
            if (x != root)
            {
                current = x->parent;
            }
            else
            {
                current = x;
            }
        }
        else if (z->left == nilNode)
        {
            x = z->right;
            RB_transplant(z, z->right);
            if (x != root)
            {
                current = x->parent;
            }
            else
            {
                current = x;
            }
        }
        else
        {
            y = treeMaximum(z->left);
            yOriginalColor = y->color;
            x = y->left;
            if (y->parent == z)
            {
                x->parent = y;
                current = y;
            }
            else
            {
                RB_transplant(y, y->left);
                y->left = z->left;
                y->left->parent = y;
                current = y->parent;
            }
            RB_transplant(z, y);
            y->right = z->right;
            y->right->parent = y;
            y->color = z->color;
        }

        if (!lastNode)
        {
            Node *counter = current;
            if (counter != nullptr)
            {
                while (counter != nullptr)
                {
                    counter->nSize = counter->left->nSize + counter->right->nSize + 1;
                    counter = counter->parent;
                }
            }
        }

        // RB_inOrderTreeSubtreeSpecifier(root); //In case this is needed for Later.

        if (yOriginalColor == 0)
        {
            RB_deleteFixup(x);
        }
    };
};