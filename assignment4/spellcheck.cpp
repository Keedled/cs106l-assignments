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
    //����һ����������Χ����Χ�ڵ�Ԫ���ǿո��ַ���λ��
    std::vector<std::string::iterator> spaces = find_all(begin,end,[](char c) { return std::isspace(c); });
    
    // //�����һ��
    // spaces.emplace_back(source,begin,spaces[1]);
    //����tokens
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

//     // �������пո�λ�ã���ȷ�� std::isspace ��ȷƥ�䣩
//     auto spaces = find_all(begin, end, [](char c) { return std::isspace(c); });

//     if (!spaces.empty()) {
//         // ��ӵ�һ�� Token����ͷ����һ���ո�
//         if (spaces.front() != begin) {
//             tokens.emplace_back(source, begin, spaces.front());
//         }

//         // �����м� Token�����ڿո�֮�䣩
//         std::transform(
//             spaces.begin(), std::prev(spaces.end()), // ���뷶Χ1�������һ���ո�
//             std::next(spaces.begin()),               // ���뷶Χ2���ӵڶ����ո�ʼ
//             std::back_inserter(tokens),
//             [&source](auto start_space, auto end_space) {
//                 auto token_begin = std::next(start_space);
//                 auto token_end = end_space;
//                 return Token(source, token_begin, token_end);
//             }
//         );

//         // ������һ�� Token�����һ���ո񵽽�β��
//         if (spaces.back() != end) {
//             tokens.emplace_back(source, std::next(spaces.back()), end);
//         }
//     } else {
//         // �޿ո������ַ�����Ϊһ�� Token
//         tokens.emplace_back(source, begin, end);
//     }

//     // �Ƴ��� Token
//     tokens.erase(
//         std::remove_if(tokens.begin(), tokens.end(), [](const Token& t) {
//             return t.content.empty();
//         }),
//         tokens.end()
//     );

//     return Corpus(tokens.begin(), tokens.end());
// }



std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
    //���˵�ƴд��ȷ��
    auto misspellings = std::ranges::views::filter(source,[&dictionary](const Token& t){
        return !dictionary.contains(t.content);
    });
    //��ӽ���
    auto misspellings2 = std::ranges::views::transform(misspellings,[&dictionary](const Token& t){
        auto suggestions = std::ranges::views::filter(dictionary,[&t](const std::string& s){
            return levenshtein(t.content,s) == 1;
        });
        return Misspelling{t, std::set<std::string>(suggestions.begin(),suggestions.end())};
    });
    //���˵�û�н����
    auto misspellings3 = std::ranges::views::filter(misspellings2,[&dictionary](const Misspelling& m){
        return !m.suggestions.empty();
    });
    return std::set<Misspelling>(misspellings3.begin(),misspellings3.end());
};


/* Helper methods */

#include "utils.cpp"