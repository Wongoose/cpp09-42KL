#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(int argc, char **argv) {
    std::list<unsigned int> list;
    std::vector<unsigned int> vector;

    for (int i = 1; i < argc; i++) {
        long num = std::atol(argv[i]);
        if (num <= 0) {
            std::cout << RED << "Found invalid input! Must be a positive number (>0): " << num << std::endl;
            return;
        }
        list.push_back(static_cast<unsigned int>(num));
        vector.push_back(static_cast<unsigned int>(num));
    }

    // Printing
    std::cout << GREY << "Before: ";
    displayList(list);

    // Merge sort here for 2 different containers
    clock_t listStart = clock();
    clock_t vectorStart = clock();
    list = mainSplitList(list);
    vector = mainSplitVector(vector);
    clock_t listEnd = clock();
    clock_t vectorEnd = clock();

    // Calculate timing
    unsigned long listDuration = listEnd - listStart;
    unsigned long vectorDuration = vectorEnd - vectorStart;
    
    std::cout << GREEN << "After: ";
    displayList(list);

    std::cout << "Time to process a range of " << list.size() << " elements with std::list container: " << listDuration << " us" << std::endl;
    std::cout << "Time to process a range of " << vector.size() << " elements with std::vector container: " << vectorDuration << " us" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &copy) {
    *this = copy;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &copy) {
    (void)copy;
    return (*this);
}

PmergeMe::~PmergeMe() {}

// Functions
// LIST
void PmergeMe::displayList(std::list<unsigned int> &list) const {
    std::list<unsigned int>::iterator head = list.begin();
    std::list<unsigned int>::iterator end = list.end();
    for (; head != end; ++head) {
        std::cout << *head << " ";
    }
    std::cout << std::endl << RESET;
}

std::list<unsigned int> PmergeMe::sortAndMergeLeftRightList(std::list<unsigned int> &left, std::list<unsigned int> &right) {
    std::list<unsigned int> newSortedList;

    // Compare numbers from left and right list, sort into new list
    while (!left.empty() && !right.empty()) {
        if (left.front() <= right.front()) {
            newSortedList.push_back(left.front());
            left.pop_front();
        } else {
            newSortedList.push_back(right.front());
            right.pop_front();
        }
    }

    // At this point, at least one side will be EMPTY
    // So just push the remaining numbers to newSortedList
    if (!left.empty()) {
        while (!left.empty()) {
            newSortedList.push_back(left.front());
            left.pop_front();
        }
    } else {
        while (!right.empty()) {
            newSortedList.push_back(right.front());
            right.pop_front();
        }
    }
    return (newSortedList);
}

std::list<unsigned int> PmergeMe::mainSplitList(std::list<unsigned int> &list) {
    // Already sorted because it is just 1 element
    if (list.size() <= 1)
        return (list);

    // Divide to 2 halves
    int split_i = list.size() / 2;
    std::list<unsigned int> left;
    std::list<unsigned int> right;

    // copy number from top of list until midpoint, and remove number from original list
    for (int i = 0; i < split_i; i++) {
        left.push_back(list.front());
        list.pop_front();
    }

    right = list;
    // Recursive - keep splitting in halves, work from bottom of bottom
    left = mainSplitList(left);
    right = mainSplitList(right);

    return (sortAndMergeLeftRightList(left, right));
}

// VECTOR
void PmergeMe::displayVector(std::vector<unsigned int> &vector) const {
    std::vector<unsigned int>::iterator head = vector.begin();
    std::vector<unsigned int>::iterator end = vector.end();
    for (; head != end; ++head) {
        std::cout << *head << " ";
    }
    std::cout << std::endl << RESET;
}

std::vector<unsigned int> PmergeMe::sortAndMergeLeftRightVector(std::vector<unsigned int> &left, std::vector<unsigned int> &right) {
    std::vector<unsigned int> newSortedVector;

    // Compare numbers from left and right vector, sort into new vector
    while (!left.empty() && !right.empty()) {
        if (left.front() <= right.front()) {
            newSortedVector.push_back(left.front());
            left.erase(left.begin());
        } else {
            newSortedVector.push_back(right.front());
            right.erase(right.begin());
        }
    }

    // At this point, at least one side will be EMPTY
    // So just push the remaining numbers to newSortedvector
    if (!left.empty()) {
        while (!left.empty()) {
            newSortedVector.push_back(left.front());
            left.erase(left.begin());
        }
    } else {
        while (!right.empty()) {
            newSortedVector.push_back(right.front());
            right.erase(right.begin());
        }
    }
    return (newSortedVector);
}

std::vector<unsigned int> PmergeMe::mainSplitVector(std::vector<unsigned int> &vector) {
    // Already sorted because it is just 1 element
    if (vector.size() <= 1)
        return (vector);

    // Divide to 2 halves
    int split_i = vector.size() / 2;
    std::vector<unsigned int> left;
    std::vector<unsigned int> right;

    // copy number from top of vector until midpoint, and remove number from original vector
    for (int i = 0; i < split_i; i++) {
        left.push_back(vector.front());
        vector.erase(vector.begin());
    }

    right = vector;
    // Recursive - keep splitting in halves, work from bottom of bottom
    left = mainSplitVector(left);
    right = mainSplitVector(right);

    return (sortAndMergeLeftRightVector(left, right));
}

// EXAMPLE OF INSERTION SORT
// void PmergeMe::insertionSort(std::list<int> &list) {
//     std::list<int>::iterator step = list.begin() + 1;
//     std::list<int>::iterator end = list.end();
//     std::list<int>::iterator needle;

//     for (; step != end; ++step) {
//         int temp = *step;
//         needle = step;
//         while (needle != list.begin() && *std::prev(needle) > temp) {
//             *needle = *std::prev(needle);
//             std::advance(needle, -1);
//         }
//         *needle = temp;
//     }
// }
