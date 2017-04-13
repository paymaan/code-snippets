#include <functional>
#include <iostream>

namespace my {
struct TreeNode {
    int value;
    TreeNode* leftChild;
    TreeNode* rightChild;
};

/// @brief Visit function that defines the action upon visiting a given node
void visit(const TreeNode& /*aNode*/);

/// @brief Populate a generic binary tree
/// NOTE: Can use smart pointers here but not doing it for now since this is
/// just a snippet
TreeNode* populateTree();

/// @brief Counter part of populateTree which frees up the earlier allocated
/// memory
/// NOTE: Can use smart pointers here but not doing it for now since this is
/// just a snippet
void deleteTree(TreeNode* /*aRootNode*/);

/// @brief Depth First Traversal: Inorder (Left, Root, Right)
void dfs_inorder(const TreeNode* /*aNode*/,
                 std::function<void(const TreeNode&)> /*aVisitor*/);

/// @brief Depth First Traversal: Preorder (Root, Left, Right)
void dfs_preorder(const TreeNode* /*aNode*/,
                  std::function<void(const TreeNode&)> /*aVisitor*/);

/// @brief Depth First Traversal: Postorder (Left, Right, Root)
void dfs_postorder(const TreeNode* /*aNode*/,
                   std::function<void(const TreeNode&)> /*aVisitor*/);

/// @brief Breadth First Traversal (aka level Order Traversal)
void bfs_levelorder(const TreeNode* /*aNode*/,
                    std::function<void(const TreeNode&)> /*aVisitor*/);
}

int main() {
    using namespace my;

    const auto treeRootNode = populateTree();
    std::function<void(const TreeNode&)> visitor = my::visit;
    std::cout << "Depth First Traversal - Inorder: ";
    dfs_inorder(treeRootNode, visitor);
    std::cout << std::endl;
    std::cout << "Depth First Traversal - Preorder: ";
    dfs_preorder(treeRootNode, visitor);
    std::cout << std::endl;
    std::cout << "Depth First Traversal - Postorder: ";
    dfs_postorder(treeRootNode, visitor);
    std::cout << std::endl;
    std::cout << "Breadth First Traversal / Levelorder: ";
    bfs_levelorder(treeRootNode, visitor);
    std::cout << std::endl;

    return 0;
}

void my::visit(const my::TreeNode& aNode) {
    std::cout << aNode.value << " ";
    return;
}

void my::dfs_inorder(const my::TreeNode* aNode,
                     std::function<void(const TreeNode&)> aVisitor) {
    if (aNode == nullptr)
        return;
    dfs_inorder(aNode->leftChild, aVisitor);
    aVisitor(*aNode);
    dfs_inorder(aNode->rightChild, aVisitor);
    return;
}

void my::dfs_preorder(const my::TreeNode* aNode,
                      std::function<void(const TreeNode&)> aVisitor) {
    if (aNode == nullptr)
        return;
    aVisitor(*aNode);
    dfs_preorder(aNode->leftChild, aVisitor);
    dfs_preorder(aNode->rightChild, aVisitor);
    return;
}

void my::dfs_postorder(const my::TreeNode* aNode,
                       std::function<void(const TreeNode&)> aVisitor) {
    if (aNode == nullptr)
        return;
    dfs_postorder(aNode->leftChild, aVisitor);
    dfs_postorder(aNode->rightChild, aVisitor);
    aVisitor(*aNode);
    return;
}

void my::bfs_levelorder(const my::TreeNode* aNode,
                        std::function<void(const TreeNode&)> aVisitor) {
    // todo
    if (aNode)
        aVisitor(*aNode);
    return;
}

my::TreeNode* my::populateTree() {
    auto nodeArray = new my::TreeNode[11];
    nodeArray[0].value = 77;
    nodeArray[1].value = 8;
    nodeArray[2].value = 6;
    nodeArray[3].value = 10;
    nodeArray[4].value = 5;
    nodeArray[5].value = 40;
    nodeArray[6].value = 5;
    nodeArray[7].value = 13;
    nodeArray[8].value = 7;
    nodeArray[9].value = 35;
    nodeArray[10].value = 11;

    for (size_t arrayIndex = 0; arrayIndex <= 10; ++arrayIndex) {
        nodeArray[arrayIndex].leftChild = nullptr;
        nodeArray[arrayIndex].rightChild = nullptr;
    }

    nodeArray[0].leftChild = &nodeArray[1];
    nodeArray[0].rightChild = &nodeArray[2];
    nodeArray[1].leftChild = &nodeArray[3];
    nodeArray[1].rightChild = &nodeArray[4];
    nodeArray[2].leftChild = &nodeArray[5];
    nodeArray[2].rightChild = &nodeArray[6];
    nodeArray[3].leftChild = &nodeArray[7];
    nodeArray[5].leftChild = &nodeArray[8];
    nodeArray[5].rightChild = &nodeArray[9];
    nodeArray[6].rightChild = &nodeArray[10];

    return &nodeArray[0];
}

void my::deleteTree(TreeNode* aRootNode) {
    // delete raw pointers in a post-order fashion
    if (aRootNode == nullptr)
        return;
    deleteTree(aRootNode->leftChild);
    deleteTree(aRootNode->rightChild);
    delete aRootNode;
}
