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
                throw out_of_range("Elemento no encontrado");
            }
            if (e < node->elem) {
                return search(node->left, e);
            } else if (e > node->elem) {
                return search(node->right, e);
            } else {
                return node; // elemento encontrado
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
                throw out_of_range("Elemento no encontrado");
            }
            if (e < node->elem) {
                node->left = remove(node->left, e);
            } else if (e > node->elem) {
                node->right = remove(node->right, e);
            } else {
                // nodo encontrado
                if (node->left == nullptr) {
                    BSNode<T> *temp = node->right;
                    delete node;
                    return temp;
                } else if (node->right == nullptr) {
                    BSNode<T> *temp = node->left;
                    delete node;
                    return temp;
                }
                // nodo con dos hijos
                BSNode<T> *temp = searchMin(node->right);
                node->elem = temp->elem;
                node->right = remove(node->right, temp->elem);
            }
            return node;
        }
        T max(BSNode<T>* n) const {
            if (n == nullptr) {
                throw out_of_range("Árbol vacío");
            }
            while (n->right != nullptr) {
                n = n->right;
            }
            return n->elem;
        }
        BSNode<T>* removeMax(BSNode<T>* n) {
            if (n == nullptr) {
                throw out_of_range("Árbol vacío");
            }
            if (n->right == nullptr) {
                BSNode<T>* leftChild = n->left;
                delete n;
                return leftChild;
            }
            n->right = removeMax(n->right);
            return n;
        }
        public:
        // miembros públicos
        BSTree() : nelem(0), root(nullptr) {}
        int size() const {
            return nelem;
        }
        T search (T e) const {
            BSNode<T> *node = search(root, e);
            return node->elem;
        }
        void remove (T e) {
            root = remove(root, e);
            nelem--;
        }
        ~BSTree() {
            delete_cascade(root);
        }
};

#endif
