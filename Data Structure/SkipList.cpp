#include <bits/stdc++.h>
using namespace std;

class SkipNode {
public:
    int key;
    vector<SkipNode*> forward;

    SkipNode(int key, int level) {
        this->key = key;
        this->forward.resize(level, nullptr);
    }
};

class SkipList {
private:
    int maxLevel;
    float probability;
    int level;
    SkipNode* header;

    int randomLevel() {
        int lvl = 1;
        while((float)rand() / RAND_MAX < probability && lvl < maxLevel) {
            lvl++;
        }
        return lvl;
    }

public:
    SkipList(int maxLevel, float probability) {
        this->maxLevel = maxLevel;
        this->probability = probability;
        this->level = 1;
        header = new SkipNode(-1, maxLevel);
    }

    bool search(int key) {
        SkipNode* current = header;
        for (int i = level - 1; i >= 0; --i) {
            while(current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }

        current = current->forward[0];
        return current && current->key == key;
    }

    void insert(int key) {
        vector<SkipNode*> update(maxLevel, nullptr);
        SkipNode* current = header;

        for (int i = level - 1; i >= 0; --i) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if (!current || current->key != key) {
            int newLevel = randomLevel();
            if (newLevel > level) {
                for (int i = level; i < newLevel; ++i) {
                    update[i] = header;
                }
                level = newLevel;
            }

            SkipNode* newNode = new SkipNode(key, newLevel);
            for (int i = 0; i < newLevel; ++i) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }

    void remove(int key) {
        vector<SkipNode*> update(maxLevel, nullptr);
        SkipNode* current = header;

        for (int i = level - 1; i >= 0; --i) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if (current && current->key == key) {
            for (int i = 0; i < level; ++i) {
                if(update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }

            while (level > 1 && !header->forward[level - 1]) {
                level--;
            }

            delete current;
        }
    }

    void display() {
        for (int i = 0; i < level; ++i) {
            SkipNode* current = header->forward[i];
            cout << "Level " << i + 1 << ": ";
            while(current) {
                cout << current->key << " ";
                current = current->forward[i];
            }
            cout << '\n';
        }
    }

    ~SkipList() {
        SkipNode* current = header;
        while (current) {
            SkipNode* next = current->forward[0];
            delete current;
            current = next;
        }
    }
};

int main() {
    SkipList skipList(5, 0.5);

    skipList.insert(3);
    skipList.insert(6);
    skipList.insert(7);
    skipList.insert(9);
    skipList.insert(12);
    skipList.insert(19);
    skipList.insert(17);

    cout << "SkipList after insertions:\n";
    skipList.display();

    cout << "\nSearching for 7: " << (skipList.search(7) ? "Found" : "Not Found") << "\n";
    cout << "Searching for 15: " << (skipList.search(15) ? "Found" : "Not Found") << "\n";

    skipList.remove(7);
    cout << "\nSkipList after removing 7:\n";
    skipList.display();

    return 0;
}
