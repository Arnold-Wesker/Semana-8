// En mi caso implemente un Árbol Rojo-Negro usando la clase RedBlackTree. Cada nodo del árbol, representado por la estructura 
// Node, tiene un color, un valor, una posición y punteros a su nodo padre y a sus nodos hijos. Al insertar un elemento con insert, se 
// crea un nuevo nodo y se inserta en el árbol. Si la inserción viola las propiedades del Árbol Rojo-Negro, uso las funciones 
// rotateLeft, rotateRight y fixViolation para corregirlo. Para cada consulta, use la función query que a su vez llama a queryHelper 
// para buscar el valor en el árbol. Si se halla el valor, se devuelve su posición. Si no, se devuelve -1. Finalmente, en la función 
// main, se leen los datos de entrada, se insertan los valores en el árbol y se realizan las consultas, imprimiendo el resultado de 
// c/u.
#include <iostream>

enum Color {Rojo, Negro};

struct Node {
    int data;
    int position;
    Node *left, *right, *parent;
    Color color;

    Node(int data, int position) {
        this->data = data;
        this->position = position;
        left = right = parent = nullptr;
        this->color = Rojo;
    }
};

class RedBlackTree {
private:
    Node *root;
    int size;

protected:
    void rotateLeft(Node *&root, Node *&pt) {
        Node *pt_right = pt->right;

        if (pt_right) {
            pt->right = pt_right->left;

            if (pt->right != nullptr)
                pt->right->parent = pt;

            pt_right->parent = pt->parent;
        }

        if (!pt->parent)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;

        if (pt_right)
            pt_right->left = pt;

        pt->parent = pt_right;
    }

    void rotateRight(Node *&root, Node *&pt) {
        Node *pt_left = pt->left;

        if (pt_left) {
            pt->left = pt_left->right;

            if (pt->left != nullptr)
                pt->left->parent = pt;

            pt_left->parent = pt->parent;
        }

        if (!pt->parent)
            root = pt_left;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
        else
            pt->parent->right = pt_left;

        if (pt_left)
            pt_left->right = pt;

        pt->parent = pt_left;
    }

    void fixViolation(Node *&root, Node *&pt) {
        Node *parent_pt = nullptr;
        Node *grand_parent_pt = nullptr;

        while ((pt != root) && pt && pt->color != Negro && pt->parent && pt->parent->color == Rojo) {

            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            if (parent_pt == grand_parent_pt->left) {

                Node *uncle_pt = grand_parent_pt ? grand_parent_pt->right : nullptr;

                if (uncle_pt != nullptr && uncle_pt->color == Rojo) {
                    grand_parent_pt->color = Rojo;
                    parent_pt->color = Negro;
                    uncle_pt->color = Negro;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    if (grand_parent_pt)
                        rotateRight(root, grand_parent_pt);

                    if (parent_pt)
                        std::swap(parent_pt->color, grand_parent_pt->color);

                    pt = parent_pt;
                }
            } else {
                Node *uncle_pt = grand_parent_pt ? grand_parent_pt->left : nullptr;

                if (uncle_pt != nullptr && uncle_pt->color == Rojo) {
                    grand_parent_pt->color = Rojo;
                    parent_pt->color = Negro;
                    uncle_pt->color = Negro;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    if (grand_parent_pt)
                        rotateLeft(root, grand_parent_pt);

                    if (parent_pt)
                        std::swap(parent_pt->color, grand_parent_pt->color);

                    pt = parent_pt;
                }
            }
        }

        if (root)
            root->color = Negro;
    }

public:
    RedBlackTree() { root = nullptr; size = 0; }

    void insert(const int &data) {
        Node *pt = new Node(data, size++);

        root = insert(root, pt);

        fixViolation(root, pt);
    }

    int query(int data) {
        return queryHelper(root, data);
    }

    Node* insert(Node *root, Node *pt) {
        if (root == nullptr)
            return pt;

        if (pt->data < root->data) {
            root->left = insert(root->left, pt);
            if (root->left)
                root->left->parent = root;
        } else if (pt->data > root->data) {
            root->right = insert(root->right, pt);
            if (root->right)
                root->right->parent = root;
        }

        return root;
    }

    int queryHelper(Node *root, int data) {
        while (root != nullptr) {
            if (data < root->data)
                root = root->left;
            else if (data > root->data)
                root = root->right;
            else
                return root->position;
        }

        return -1;
    }
};

int main() {
    RedBlackTree tree;
    int N, Q;
    std::cin >> N >> Q;

    for(int i = 0; i < N; i++) {
        int data;
        std::cin >> data;
        tree.insert(data);
    }

    for(int i = 0; i < Q; i++) {
        int query;
        std::cin >> query;
        int result = tree.query(query);
        if (result != -1) {
            std::cout << result << std::endl;
        } else {
            std::cout << -1 << std::endl;
        }
    }

    return 0;
}