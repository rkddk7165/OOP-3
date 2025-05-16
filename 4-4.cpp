#include <iostream>
#include <string>

using namespace std;

class Folder {
private:
    string filename;
    Folder* down[10];
    int count;


public:
    Folder(string fn){
        filename = fn;
        count = 0;
        for (int i = 0; i < 10; i++) {
            down[i] = nullptr;
        }
    }

    ~Folder() {
        for (int i = 0; i < count; i++) {
            delete down[i];
        }
    }

    bool addFolder(Folder* newFolder) {
        if (count >= 10) return false;
        down[count++] = newFolder;
        return true;
    }

    Folder* findFolder(string target) {
        if (filename == target) return this;

        for (int i = 0; i < count; i++) {
            Folder* result = down[i]->findFolder(target);
            if (result) return result;
        } 
        return nullptr;

    }
    void print(int depth = 0) {

        for (int i = 0; i < depth *2; i++) {
            cout << " ";
        }

        cout << filename << endl;

        for (int i = 0; i < count; i++) {
            down[i]->print(depth + 1);
        }
    }
};

int main() {
    string command;
    Folder* root = new Folder("root");

    while (1) {
        cin >> command;
        
        if (command == "ADD") {
            string parent, child;
            cin >> parent >> child;

            Folder* parentP = root->findFolder(parent);
            Folder* newFolder = new Folder(child);
            parentP->addFolder(newFolder);

        }

        else if (command == "PATH") {
            string path;
            cin >> path;
            Folder* start = root->findFolder(path);
            start->print();
        }

        else if (command == "EXIT") {
            break;
        }
        
    }

    delete root;
    return 0;
}