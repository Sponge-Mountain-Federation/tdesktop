#include "history/aho_corasick.h"
#include <queue>
#include <unordered_map>

// TrieNode 结构体的定义和初始化等

AhoCorasick::AhoCorasick(const std::vector<std::string>& keywords) {
    root = new TrieNode();  // 创建Trie树的根节点
    buildTrie(keywords);  // 根据关键词构建Trie树
    buildFail();  // 构建fail指针
}

bool AhoCorasick::containsAnyKeyword(const std::string& text) {
    TrieNode* currentNode = root;
    for (char ch : text) {
        while (currentNode != root && currentNode->children.find(ch) == currentNode->children.end()) {
            currentNode = currentNode->fail;
        }
        if (currentNode->children.find(ch) != currentNode->children.end()) {
            currentNode = currentNode->children[ch];
        }
        if (!currentNode->outputs.empty()) {
            return true;  // 找到匹配
        }
    }
    return false;  // 没有匹配
}

void AhoCorasick::buildTrie(const std::vector<std::string>& keywords) {
    for (int i = 0; i < keywords.size(); ++i) {
        TrieNode* currentNode = root;
        for (char ch : keywords[i]) {
            if (currentNode->children.find(ch) == currentNode->children.end()) {
                currentNode->children[ch] = new TrieNode();
            }
            currentNode = currentNode->children[ch];
        }
        currentNode->outputs.push_back(i);  // 在叶节点存储关键词的索引
    }
}

void AhoCorasick::buildFail() {
    std::queue<TrieNode*> q;
    for (auto& pair : root->children) {
        pair.second->fail = root;
        q.push(pair.second);
    }

    while (!q.empty()) {
        TrieNode* currentNode = q.front();
        q.pop();

        for (auto& pair : currentNode->children) {
            char ch = pair.first;
            TrieNode* nextNode = pair.second;
            TrieNode* failNode = currentNode->fail;

            while (failNode != root && failNode->children.find(ch) == failNode->children.end()) {
                failNode = failNode->fail;
            }

            if (failNode->children.find(ch) != failNode->children.end()) {
                nextNode->fail = failNode->children[ch];
            } else {
                nextNode->fail = root;
            }

            nextNode->outputs.insert(nextNode->outputs.end(),
                                     nextNode->fail->outputs.begin(),
                                     nextNode->fail->outputs.end());

            q.push(nextNode);
        }
    }
}
