#pragma once
#ifndef AHOCORASICK_H
#define AHOCORASICK_H

#include <vector>
#include <string>
#include <unordered_map>

class AhoCorasick {
public:
    AhoCorasick(const std::vector<std::string>& keywords);  // 构造函数，接受关键词列表
    bool containsAnyKeyword(const std::string& text);  // 检查文本中是否包含任何关键词

private:
    // TrieNode 结构，用于构建 Trie 树
    struct TrieNode {
        std::unordered_map<char, TrieNode*> children;  // 存储字符的子节点
        TrieNode* fail = nullptr;  // fail指针，用于跳转
        std::vector<int> outputs;  // 匹配到的关键词的索引
    };

    TrieNode* root;  // Trie树的根节点

    void buildTrie(const std::vector<std::string>& keywords);  // 构建Trie树
    void buildFail();  // 构建fail指针
};

#endif // AHOCORASICK_H
