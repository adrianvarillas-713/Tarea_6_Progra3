#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

/*PREGUNTA 1
struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;
    explicit BSTNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

class IterativeBST {
private:
    BSTNode* root;

public:
    IterativeBST() : root(nullptr) {}

    ~IterativeBST() {
        if (!root) return;
        stack<BSTNode*> st;
        st.push(root);
        while (!st.empty()) {
            BSTNode* curr = st.top();
            st.pop();
            if (curr->left) st.push(curr->left);
            if (curr->right) st.push(curr->right);
            delete curr;
        }
    }

    // 1. Inserción iterativa
    void insert(int key) {
        BSTNode* newNode = new BSTNode(key);
        if (!root) {
            root = newNode;
            return;
        }
        BSTNode* curr = root;
        BSTNode* parent = nullptr;

        while (curr != nullptr) {
            parent = curr;
            if (key < curr->key) {
                curr = curr->left;
            } else if (key > curr->key) {
                curr = curr->right;
            } else {
                delete newNode;
                return;
            }
        }

        if (key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }


    void remove(int key) {
        BSTNode* curr = root;
        BSTNode* parent = nullptr;


        while (curr != nullptr && curr->key != key) {
            parent = curr;
            curr = (key < curr->key) ? curr->left : curr->right;
        }
        if (curr == nullptr) return;


        if (curr->left != nullptr && curr->right != nullptr) {
            BSTNode* succParent = curr;
            BSTNode* succ = curr->right;
            while (succ->left != nullptr) {
                succParent = succ;
                succ = succ->left;
            }
            curr->key = succ->key;
            curr = succ;
            parent = succParent;
        }


        BSTNode* child = (curr->left != nullptr) ? curr->left : curr->right;
        if (parent == nullptr) {
            root = child;
        } else if (parent->left == curr) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete curr;
    }


    vector<int> inOrder() const {
        vector<int> result;
        stack<BSTNode*> st;
        BSTNode* curr = root;

        while (curr != nullptr || !st.empty()) {

            while (curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }

            curr = st.top();
            st.pop();
            result.push_back(curr->key);
            curr = curr->right;
        }
        return result;
    }


    int height() const {
        if (!root) return -1;
        std::queue<BSTNode*> q;
        q.push(root);
        int h = -1;

        while (!q.empty()) {
            int levelSize = static_cast<int>(q.size());
            h++;
            for (int i = 0; i < levelSize; ++i) {
                BSTNode* curr = q.front();
                q.pop();
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }
        return h;
    }
};

int main() {
    IterativeBST bst;
    for (int i = 1; i <= 20; ++i) bst.insert(i);

    cout << "Altura con 20 elementos ordenados: " << bst.height() << "\n"; // 19
    bst.remove(10);
    bst.remove(20);

    cout << "In-Order tras eliminar 10 y 20: ";
    for (int x : bst.inOrder()) cout << x << " ";
    cout << "\nAltura tras eliminar 2 elementos: " << bst.height() << "\n"; // 17
    return 0;
}*/

/*PREGUNTA 2
enum Color { RED, BLACK };

struct RBNode {
    int key;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(int k, Color c, RBNode* nilNode)
        : key(k), color(c), left(nilNode), right(nilNode), parent(nilNode) {}
};

class RedBlackTree {
private:
    RBNode* NIL;
    RBNode* root;

    void leftRotate(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;

        y->parent = x->parent;
        if (x->parent == NIL) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(RBNode* y) {
        RBNode* x = y->left;
        y->left = x->right;
        if (x->right != NIL) x->right->parent = y;

        x->parent = y->parent;
        if (y->parent == NIL) {
            root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }
        x->right = y;
        y->parent = x;
    }

    void fixInsert(RBNode* z) {

        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBNode* uncle = z->parent->parent->right;
                if (uncle->color == RED) {

                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {

                        z = z->parent;
                        leftRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {

                RBNode* uncle = z->parent->parent->left;
                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }


    int validateBlackHeight(RBNode* node) const {
        if (node == NIL) {
            return (NIL->color == BLACK) ? 1 : -1;
        }
        if (node->color != RED && node->color != BLACK) {
            return -1;
        }
        if (node->color == RED) {
            if (node->left->color == RED || node->right->color == RED) {
                return -1;
            }
        }
        int leftBH = validateBlackHeight(node->left);
        int rightBH = validateBlackHeight(node->right);

        if (leftBH == -1 || rightBH == -1 || leftBH != rightBH) {
            return -1;
        }
        return leftBH + (node->color == BLACK ? 1 : 0);
    }

    void preOrderHelper(RBNode* node) const {
        if (node == NIL) return;
        cout << node->key << "(" << (node->color == RED ? "R" : "B") << ") ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }

    void destroySubtree(RBNode* node) {
        if (node == NIL) return;
        destroySubtree(node->left);
        destroySubtree(node->right);
        delete node;
    }

public:
    RedBlackTree() {
        NIL = new RBNode(0, BLACK, nullptr);
        NIL->left = NIL->right = NIL->parent = NIL;
        root = NIL;
    }

    ~RedBlackTree() {
        destroySubtree(root);
        delete NIL;
    }

    void insert(int key) {
        RBNode* z = new RBNode(key, RED, NIL);
        RBNode* y = NIL;
        RBNode* x = root;

        while (x != NIL) {
            y = x;
            if (z->key < x->key) x = x->left;
            else if (z->key > x->key) x = x->right;
            else { delete z; return; }
        }
        z->parent = y;
        if (y == NIL) root = z;
        else if (z->key < y->key) y->left = z;
        else y->right = z;

        fixInsert(z);
    }

    bool verifyProperties() const {
        if (NIL->color != BLACK) return false;
        if (root != NIL && root->color != BLACK) return false;
        return validateBlackHeight(root) != -1;
    }

    int height() const {
        if (root == NIL) return -1;
        queue<RBNode*> q;
        q.push(root);
        int h = -1;
        while (!q.empty()) {
            int sz = static_cast<int>(q.size());
            h++;
            for (int i = 0; i < sz; ++i) {
                RBNode* curr = q.front();
                q.pop();
                if (curr->left != NIL) q.push(curr->left);
                if (curr->right != NIL) q.push(curr->right);
            }
        }
        return h;
    }

    void printPreOrder() const {
        preOrderHelper(root);
        cout << "\n";
    }
};

int main() {
    RedBlackTree rbt;
    for (int i = 1; i <= 20; ++i) rbt.insert(i);

    cout << "Propiedades validas: " << (rbt.verifyProperties() ? "SI" : "NO") << "\n";
    cout << "Altura RBT (20 ordenados): " << rbt.height() << "\n"; // 5 (vs 19 del BST)
    cout << "Pre-Orden: ";
    rbt.printPreOrder();
    return 0;
}
*/

/*PREGUNTA 3
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

struct DFSState {
    TreeNode* node;
    int currentSum;
    std::vector<int> path;
};

std::vector<int> findRootToLeafPathWithSum(TreeNode* root, int K) {
    if (!root) return {};

    std::stack<DFSState> st;
    st.push({root, root->key, {root->key}});

    while (!st.empty()) {
        DFSState curr = st.top();
        st.pop();

        TreeNode* u = curr.node;


        if (u->left == nullptr && u->right == nullptr && curr.currentSum == K) {
            return curr.path;
        }


        if (u->right != nullptr) {
            std::vector<int> nextPath = curr.path;
            nextPath.push_back(u->right->key);
            st.push({u->right, curr.currentSum + u->right->key, nextPath});
        }
        if (u->left != nullptr) {
            std::vector<int> nextPath = curr.path;
            nextPath.push_back(u->left->key);
            st.push({u->left, curr.currentSum + u->left->key, nextPath});
        }
    }

    return {};
}

int main() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(7);

    int K = 22; // 10 + 5 + 7 = 22
    std::vector<int> path = findRootToLeafPathWithSum(root, K);

    std::cout << "Camino encontrado: ";
    for (int val : path) std::cout << val << " ";
    std::cout << "\n";
    return 0;
}
*/

/*PREGUNTA 4
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

struct BFSMetrics {
    bool isComplete;
    int maxWidth;
    int minDepth;
};

BFSMetrics analyzeTreeBFS(TreeNode* root) {
    if (!root) return {true, 0, -1};

    std::queue<TreeNode*> q;
    q.push(root);

    bool isComplete = true;
    bool seenNull = false;
    int maxWidth = 0;
    int minDepth = -1;
    int currentDepth = 0;

    while (!q.empty()) {
        int levelSize = static_cast<int>(q.size());
        int validNodesInLevel = 0;

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* curr = q.front();
            q.pop();

            if (curr == nullptr) {

                seenNull = true;
            } else {

                if (seenNull) {
                    isComplete = false;
                }
                validNodesInLevel++;


                if (curr->left == nullptr && curr->right == nullptr && minDepth == -1) {
                    minDepth = currentDepth;
                }


                q.push(curr->left);
                q.push(curr->right);
            }
        }

        if (validNodesInLevel > 0) {
            maxWidth = std::max(maxWidth, validNodesInLevel);
            currentDepth++;
        }
    }

    return {isComplete, maxWidth, minDepth};
}

int main() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(12);

    BFSMetrics res = analyzeTreeBFS(root);
    cout << "Es completo: " << (res.isComplete ? "SI" : "NO") << "\n";
    cout << "Ancho maximo: " << res.maxWidth << "\n";
    cout << "Profundidad minima: " << res.minDepth << "\n";
    return 0;
}
*/