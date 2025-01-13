#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread>
#include <vector>
#include <chrono>

typedef pthread_mutex_t Mutex;

struct Node {
    Node* parent;
    std::vector<Node*> children;
    int value;
    pthread_mutex_t mutex;

    Node(Node* parent, int value) : parent(parent), value(value) {
        pthread_mutex_init(&mutex, NULL);
    }
};

struct ThreadArgs {
    Node* node;
    int value;
};

Node* createNode(Node* parent, int value) {
    Node* node = new Node(parent, value);
    return node;
}

void addChild(Node* parent, Node* child){
    pthread_mutex_lock(&parent->mutex);
    parent->children.push_back(child);
    pthread_mutex_unlock(&parent->mutex);
}

/*
            13
            /\
           5  8
          /\ /|\
         2 3 1 3 4
orders:  0 1 2 3 4 (for leaves)
*/
Node* createTree(){
    Node* root = createNode(nullptr, 13);
    Node* left = createNode(root, 5);
    Node* right = createNode(root, 8);
    Node* leftLeft = createNode(left, 2);
    Node* leftRight = createNode(left, 3);
    Node* rightLeft = createNode(right, 1);
    Node* rightMiddle = createNode(right, 3);
    Node* rightRight = createNode(right, 4);
    addChild(root, left);
    addChild(root, right);
    addChild(left, leftLeft);
    addChild(left, leftRight);
    addChild(right, rightLeft);
    addChild(right, rightMiddle);
    addChild(right, rightRight);
    return root;
}

void addValue(Node* node, int value){
    pthread_mutex_lock(&node->mutex);
    node->value += value;
    Node* parent = node->parent;
    while(parent != nullptr){
        pthread_mutex_lock(&parent->mutex);
        parent->value += value;
        pthread_mutex_unlock(&parent->mutex);
        parent = parent->parent;
    }
    pthread_mutex_unlock(&node->mutex);
}

// void modifyValue(Node* node, int value){
//     pthread_mutex_lock(&node->mutex);
//     int oldValue = node->value;
//     node->value = value;
//     int diff = value - oldValue;
//     Node* parent = node->parent;
//     while(parent != nullptr){
//         pthread_mutex_lock(&parent->mutex);
//         parent->value += diff;
//         pthread_mutex_unlock(&parent->mutex);
//         parent = parent->parent;
//     }
//     pthread_mutex_unlock(&node->mutex);
// }

void* modifyValue(void* args){
    ThreadArgs* threadArgs = (ThreadArgs*)args;
    Node* node = threadArgs->node;
    int value = threadArgs->value;
    pthread_mutex_lock(&node->mutex);
    int diff = value - node->value;
    node->value = value;
    Node* parent = node->parent;
    while(parent != nullptr){
        pthread_mutex_lock(&parent->mutex);
        parent->value += diff;
        pthread_mutex_unlock(&parent->mutex);
        parent = parent->parent;
    }
    pthread_mutex_unlock(&node->mutex);
    return nullptr;
}


// DFS
std::vector<Node*> getLeaves(Node* node){
    std::vector<Node*> leaves;
    if(node->children.size() == 0){
        leaves.push_back(node);
    }else{
        for(Node* child : node->children){
            std::vector<Node*> childLeaves = getLeaves(child);
            leaves.insert(leaves.end(), childLeaves.begin(), childLeaves.end());
        }
    }
    return leaves;
}

Node* getLeaf(Node* node, int order){
    std::vector<Node*> leaves = getLeaves(node);
    if(order < 0 || order >= leaves.size()){
        return nullptr;
    }
    return leaves[order];

}

void lockTree(Node* node){
    pthread_mutex_lock(&node->mutex);
    for(Node* child : node->children){
        lockTree(child);
    }
}

void unlockTree(Node* node){
    for(Node* child : node->children){
        unlockTree(child);
    }
    pthread_mutex_unlock(&node->mutex);
}

void* verifyConsistency(void* args){
    Node* root = (Node*)args;
    while(true){
    lockTree(root);
        std::vector<Node*> leaves = getLeaves(root);
        for(Node* leaf : leaves){
            Node* parent = leaf->parent;
            int sum = 0;
            for(Node* child : parent->children){
                sum += child->value;
            }
            if(sum != parent->value){
                printf("Inconsistency detected!\n");
                unlockTree(root);
                exit(1);
            }
        }
        printf("Consistency verified\n");
    unlockTree(root);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return nullptr;
}

void printTree(Node* node, int depth){
    for(int i = 0; i < depth; i++){
        printf("  ");
    }
    printf("%d\n", node->value);
    for(Node* child : node->children){
        printTree(child, depth + 1);
    }   
}

void freeTree(Node* node){
    for(Node* child : node->children){
        freeTree(child);
    }
    delete node;
}

int main(){
    Node* root = createTree();
    int newValue1, newValue2, order1, order2;
    pthread_t thread1, thread2, threadConsistency;
    ThreadArgs args1, args2;
    printTree(root, 2);
    while(true){
        // printf("Enter the order of the first leaf you want to modify: ");
        // scanf("%d", &order1);
        // if(order1 == -1){
        //     freeTree(root);
        //     return 0;
        // }
        // printf("Enter the new value for the first leaf: ");
        // scanf("%d", &newValue1);
        // printf("Enter the order of the second leaf you want to modify: ");
        // scanf("%d", &order2);
        // printf("Enter the new value for the second leaf: ");
        // scanf("%d", &newValue2);

        order1 = rand() % 5;
        newValue1 = rand() % 21 - 10;
        order2 = rand() % 5;
        newValue2 = rand() % 21 - 10;

        args1.node = getLeaf(root, order1);
        args1.value = newValue1;
        args2.node = getLeaf(root, order2);
        args2.value = newValue2;
        pthread_create(&thread1, NULL, modifyValue, (void*)&args1);
        pthread_create(&thread2, NULL, modifyValue, (void*)&args2);
        pthread_create(&threadConsistency, NULL, verifyConsistency, root);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        pthread_detach(threadConsistency);
        printf("The tree after modification:\n");
        printTree(root, 2);
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1001 + 500));
    }
    return 0;
}