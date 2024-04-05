#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;


struct Node {
    int value;
    int sum;
    Node* left;
    Node* right;
};

Node* create_node(int value) {
    Node* node = new Node;
    node->value = value;
    node->sum = 0;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

//Generating new binary tree
void generate_tree(Node* root, int depth) {
    if (depth == 0) {
        return;
    }
    root->left = create_node(rand() % 100);
    root->right = create_node(rand() % 100);
    generate_tree(root->left, depth - 1);
    generate_tree(root->right, depth - 1);
}

//Calculating sums of node's parents
void calculate_parent_sums(Node* root, int parent_sum) {
    if (root == nullptr) {
        return;
    }

    root->sum = parent_sum + root->value;
    calculate_parent_sums(root->left, root->sum);
    calculate_parent_sums(root->right, root->sum);
}

//Printing binary tree nodes with sums of ancestoers 
void print_tree(Node* root, int level, int parent_sum) {
    if (root == nullptr) {
        return;
    }

    print_tree(root->right, level + 1, root->sum);

    string spaces(level * 4, ' ');
    cout << spaces << "(" << parent_sum << ") " << setw(2) << root->value << " (" << root->sum << ")" << endl << endl;

    print_tree(root->left, level + 1, root->sum);
}

//Save binary tree values into tree.txt file
void save_tree_to_file(Node* root, ofstream& file) {
    if (root == nullptr) {
        file << "#\n";
        return;
    }
    file << root->value << "\n";
    save_tree_to_file(root->left, file);
    save_tree_to_file(root->right, file);
}

//Loading binary tree values from tree.txt file
Node* load_tree_from_file(ifstream& file) {
    string value;
    if (!getline(file, value)) {
        return nullptr;
    }
    if (value == "#") {
        return nullptr;
    }
    Node* node = create_node(stoi(value));
    node->left = load_tree_from_file(file);
    node->right = load_tree_from_file(file);

    return node;
}

int main() {
    srand(time(nullptr));

    clock_t start_time = clock();

    //Loading binary tree values from file
    //ifstream infile("tree.txt");
    //Node* root = load_tree_from_file(infile);
    //infile.close();

    //Generating root and tree, if not loading from file
    Node* root = create_node(rand() % 100);
    generate_tree(root, 18);

    calculate_parent_sums(root, 0);
    //print_tree(root, 0, 0);

    //Saving binary tree values into file
    ofstream outfile("tree.txt");
    save_tree_to_file(root, outfile);
    outfile.close();

    clock_t end_time = clock();
    double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    cout << "Time taken by program: " << elapsed_time << " seconds" << endl;

    return 0;
}