#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

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

void generate_tree(Node* root, int depth) {
    if (depth == 0) {
        return;
    }
    root->left = create_node(rand() % 100);
    root->right = create_node(rand() % 100);
    generate_tree(root->left, depth - 1);
    generate_tree(root->right, depth - 1);
}

void calculate_sums(Node* root, int parent_sum) {
    if (root == nullptr) {
        return;
    }
    root->sum = parent_sum + root->value;
    calculate_sums(root->left, root->sum);
    calculate_sums(root->right, root->sum);
}

void print_tree(Node* root) {
    if (root == nullptr) {
        return;
    }
    cout << "Value: " << root->value << ", Sum: " << root->sum << endl;
    print_tree(root->left);
    print_tree(root->right);
}

int main() {
    srand(time(nullptr));

    auto start_time = high_resolution_clock::now();

    Node* root = create_node(rand() % 100);
    generate_tree(root, 18);
    calculate_sums(root, 0);
    //print_tree(root);

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);

    cout << "Time taken by program: " << duration.count() << " milliseconds" << endl;

    return 0;
}
