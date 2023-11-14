#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
#include <vector>

#define RESET "\033[39m"
#define BLACK "\033[30m"
#define GREY "\033[90m"
#define RED "\033[31m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[94m"
#define MAGENTA "\033[35m"

class PmergeMe {
    public:
        // Constructors
        PmergeMe();
        PmergeMe(int argc, char **argv);
        PmergeMe(const PmergeMe &copy);
        PmergeMe &operator=(const PmergeMe &copy);

        // Destructor
        ~PmergeMe();

        // Functions
        void displayList(std::list<unsigned int> &list) const;
        std::list<unsigned int> mainSplitList(std::list<unsigned int> &list);
        std::list<unsigned int> sortAndMergeLeftRightList(std::list<unsigned int> &left, std::list<unsigned int> &right);
        
        void displayVector(std::vector<unsigned int> &list) const;
        std::vector<unsigned int> mainSplitVector(std::vector<unsigned int> &list);
        std::vector<unsigned int> sortAndMergeLeftRightVector(std::vector<unsigned int> &left, std::vector<unsigned int> &right);

};

#endif