#ifndef _MOST_FREQUENT_HPP_
#define _MOST_FREQUENT_HPP_

#include "../Trees/IDictionarySingle.hpp"
#include "../Utility/SimplePair.hpp"
#include <string>
#include <fstream>


IDictionary<std::string, int> MostFrequentSubsequences(const std::string &in, int lmin, int lmax) {
    IDictionary<std::string, int> result;

    for (size_t i = 0; i < in.length(); ++i) {
        for (int j = lmin; j < lmax; ++j) {
            if (i + j <= in.length()) {
                std::string word = in.substr(i, j);
                if (result.ContainsKey(word)) {
                    result[word] += 1;
                } else {
                    result.Add(word, 1);
                }
            }
        }
    }

    return result;
}

void FindTheMostFrequentSubsequence(const std::string& in, int lmin, int lmax) {
    IDictionary<std::string, int> result = MostFrequentSubsequences(in, lmin, lmax);
    std::string path = "D:/LabWorks/ThirdLab/Subsequence.txt";

    std::ofstream outFile(path);

    if (!outFile) {
        throw std::runtime_error("Can't open the file");
    }

    return;
}




#endif