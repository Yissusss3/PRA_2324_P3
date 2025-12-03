#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <string>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

using namespace std;

template <typename V>
class BSTreeDict : public Dict<V> {
    private:

        BSTree<TableEntry<V>>* tree;

    public:

        BSTreeDict() {
            tree = new BSTree<TableEntry<V>>();
        }


        ~BSTreeDict() {
            delete tree;
        }


        void insert(string key, V value) override {
            TableEntry<V> entry(key, value);
            tree->insert(entry);
        }


        V search(string key) const override {
            TableEntry<V> entry(key);
            return tree->search(entry).value; 
        }


        V remove(string key) override {
            TableEntry<V> entry(key);


            V val = tree->search(entry).value;
            

            tree->remove(entry);
            
            return val;
        }


        int entries() const override {
            return tree->size();
        }



        friend ostream& operator<<(ostream &out, const BSTreeDict<V> &dict) {
            out << *(dict.tree);
            return out;
        }


        V operator[](string key) {
            return search(key);
        }
};

#endif
