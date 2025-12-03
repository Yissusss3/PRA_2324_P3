#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"
using namespace std;

template <typename T> 
class BSTree {
    private:
        //miembros privados
        int nelem;
        BSNode<T> *root;
        BSNode<T>* search (BSNode<T> *node, T e) const {
            if (node == nullptr) {
                throw runtime_error("Elemento no encontrado");
            }
            if (e == node->elem) {
                return node;
            } else if (e < node->elem) {
                return search(node->left, e);
            } else {
                return search(node->right, e);
            }
        }   
        void delete_cascade(BSNode<T> *node) {
            if (node != nullptr) {
                delete_cascade(node->left);
                delete_cascade(node->right);
                delete node;
            }
        }
        BSNode<T>* remove(BSNode<T> *node, T e) {
            if (node == nullptr) {
                throw runtime_error("Elemento no encontrado");
            }
            if (e < node->elem) {
                node->left = remove(node->left, e);
            } else if (e > node->elem) {
                node->right = remove(node->right, e);
            } else {
                // nodo encontrado
                if (node->left == nullptr) {
                    BSNode<T>* rightChild = node->right;
                    delete node;
                    return rightChild;
                } else if (node->right == nullptr) {
                    BSNode<T>* leftChild = node->left;
                    delete node;
                    return leftChild;
                } else {
                    // nodo con dos hijos
                    T succElem = max(node->left);
                    node->elem = succElem;
                    node->left = removeMax(node->left); 
                }
            }
            nelem--;
            return node;
        }
        void print_inorder(BSNode<T>* node, ostream &out) const {
            if (node != nullptr) {
                print_inorder(node->left, out);
                out << node->elem << " ";
                print_inorder(node->right, out);
            }
        }
        T max(BSNode<T>* n) const {
            if (n == nullptr) {
                throw runtime_error("Árbol vacío");
            }
            while (n->right != nullptr) {
                n = n->right;
            }
            return n->elem;
        }
        BSNode<T>* removeMax(BSNode<T>* n) {
            if (n == nullptr) {
                throw runtime_error("Árbol vacío");
            }
            if (n->right == nullptr) {
                BSNode<T>* leftChild = n->left;
                delete n;
                return leftChild;
            }
            n->right = removeMax(n->right);
            return n;
        }
        BSNode<T>* insert (BSNode<T>* n, T e) {
            if (n == nullptr) {
                nelem++;
                return new BSNode<T>(e);
            }
            if (e < n->elem) {
                n->left = insert(n->left, e);
            } else if (e > n->elem) {
                n->right = insert(n->right, e);
            } else {
                throw runtime_error("Elemento ya existe en el árbol");
            }
            return n;
        }
        public:
        // miembros públicos
        BSTree() : nelem(0), root(nullptr) {}
        int size() const {
            return nelem;
        }
        T search (T e) const {
            return search(root, e)->elem;
        }
        void remove (T e) {
            root = remove(root, e);
        }
        ~BSTree() {
            delete_cascade(root);
        }
        friend ostream& operator<<(ostream &out, const BSTree<T> &tree) {

            tree.print_inorder(tree.root, out);
            return out;
        }
        void insert (T e) {
            root = insert(root, e);
        }
        T operator[](T e) const {
            return search(e);
        }
};

#endif
