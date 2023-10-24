/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:45:20 by zwong             #+#    #+#             */
/*   Updated: 2023/10/24 14:45:20 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const std::string str) { (void)str; }

RPN::RPN(const RPN &copy) { this->_stack = copy.getStack(); }

RPN::~RPN() {}

//  RPN &RPN::operator=(const RPN &other) {
//     std::stack<>::operator=(other); // to ensure the base class is assigned (=) properly also
//     // Cannot just use *this = other (shallow copy, base class is not assigned)
//     return (*this);
// };
RPN &RPN::operator=(const RPN &other) {
    this->_stack = other.getStack();
    return (*this);
}

// Functions
void RPN::solveRPN(std::string input) {
    std::string token;
    std::stringstream sinput(input);

	while (std::getline(sinput, token, ' ')) {
        float num1;
        float num2;

        // Validate operand < 9, single character only
        if (token.length() != 1)
            throw InvalidOperandException();

        switch (token[0])
        {
        case '+':
            if (_stack.size() < 2)
                throw OperatorOverloadException();
            num1 = _stack.top();
            _stack.pop();
            num2 = _stack.top();
            _stack.pop();
            _stack.push(num1 + num2);
            break;
        case '-':
            if (_stack.size() < 2)
                throw OperatorOverloadException();
            num1 = _stack.top();
            _stack.pop();
            num2 = _stack.top();
            _stack.pop();
            _stack.push(num2 - num1);
            break;
        case '*':
            if (_stack.size() < 2)
                throw OperatorOverloadException();
            num1 = _stack.top();
            _stack.pop();
            num2 = _stack.top();
            _stack.pop();
            _stack.push(num1 * num2);
            break;
        case '/':
            if (_stack.size() < 2)
                throw OperatorOverloadException();
            num1 = _stack.top();
            _stack.pop();
            num2 = _stack.top();
            _stack.pop();
            _stack.push(num2 / num1);
            break;
        default:
            // If it is not "+ - * /", it has to be a number from 0-9
            try {
                _stack.push(std::stof(token));
                break;
            } catch (std::exception &err) {
                throw InvalidOperandException();
            }
        }
    }
    // Validate stack still have numbers means notation not complete!
    if (_stack.size() > 1)
        throw IncompleteNotationException();

    std::cout << GREEN << _stack.top() << std::endl << RESET;
}

const char *RPN::IncompleteNotationException::what() const throw() {
    return ("Reversed Polish Notation given is incomplete! Cannot be calculated!");
};

const char *RPN::InvalidOperandException::what() const throw() {
    return ("An operand/operator is invalid, please make sure operands are numbers from (0 - 9) only!");
};

const char *RPN::OperatorOverloadException::what() const throw() {
    return ("Operator has not enough numbers to work on! Error!");
};
