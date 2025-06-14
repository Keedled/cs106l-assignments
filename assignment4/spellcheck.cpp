#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>
#include <iterator>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  /* TODO: Implement this method */
    std::vector<Token> tokens;
    std::string::iterator begin = source.begin();
    std::string::iterator end = source.end();
    //生成一个迭代器范围，范围内的元素是空格字符的位置
    std::vector<std::string::iterator> spaces = find_all(begin,end,[](char c) { return std::isspace(c); });
    
    // //处理第一个
    // spaces.emplace_back(source,begin,spaces[1]);
    //处理tokens
    std::transform(
        spaces.begin(),std::prev(spaces.end()),
        std::next(spaces.begin()),
        std::inserter(tokens,tokens.begin()),
        [&source](std::string::iterator start_space, std::string::iterator end_space){
            return Token(source,start_space,end_space);
        }
    );
    std::erase_if(tokens,[](Token t){
        return t.content.empty();
    });
    return Corpus(tokens.begin(), tokens.end());
}

// Corpus tokenize(std::string& source) {
//     std::vector<Token> tokens;
//     auto begin = source.begin();
//     auto end = source.end();

//     // 查找所有空格位置（需确保 std::isspace 正确匹配）
//     auto spaces = find_all(begin, end, [](char c) { return std::isspace(c); });

//     if (!spaces.empty()) {
//         // 添加第一个 Token（开头到第一个空格）
//         if (spaces.front() != begin) {
//             tokens.emplace_back(source, begin, spaces.front());
//         }

//         // 处理中间 Token（相邻空格之间）
//         std::transform(
//             spaces.begin(), std::prev(spaces.end()), // 输入范围1：除最后一个空格
//             std::next(spaces.begin()),               // 输入范围2：从第二个空格开始
//             std::back_inserter(tokens),
//             [&source](auto start_space, auto end_space) {
//                 auto token_begin = std::next(start_space);
//                 auto token_end = end_space;
//                 return Token(source, token_begin, token_end);
//             }
//         );

//         // 添加最后一个 Token（最后一个空格到结尾）
//         if (spaces.back() != end) {
//             tokens.emplace_back(source, std::next(spaces.back()), end);
//         }
//     } else {
//         // 无空格，整个字符串作为一个 Token
//         tokens.emplace_back(source, begin, end);
//     }

//     // 移除空 Token
//     tokens.erase(
//         std::remove_if(tokens.begin(), tokens.end(), [](const Token& t) {
//             return t.content.empty();
//         }),
//         tokens.end()
//     );

//     return Corpus(tokens.begin(), tokens.end());
// }



std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
    //过滤掉拼写正确的
    auto misspellings = std::ranges::views::filter(source,[&dictionary](const Token& t){
        return !dictionary.contains(t.content);
    });
    //添加建议
    auto misspellings2 = std::ranges::views::transform(misspellings,[&dictionary](const Token& t){
        auto suggestions = std::ranges::views::filter(dictionary,[&t](const std::string& s){
            return levenshtein(t.content,s) == 1;
        });
        return Misspelling{t, std::set<std::string>(suggestions.begin(),suggestions.end())};
    });
    //过滤掉没有建议的
    auto misspellings3 = std::ranges::views::filter(misspellings2,[&dictionary](const Misspelling& m){
        return !m.suggestions.empty();
    });
    return std::set<Misspelling>(misspellings3.begin(),misspellings3.end());
};


/* Helper methods */

#include "utils.cpp"