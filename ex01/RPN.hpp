/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:45:30 by zwong             #+#    #+#             */
/*   Updated: 2023/10/24 14:45:31 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <stack>
#include <list>
#include <sstream>

#define RESET "\033[39m"
#define BLACK "\033[30m"
#define GREY "\033[90m"
#define RED "\033[31m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[94m"
#define MAGENTA "\033[35m"

class RPN {
    public:
        // Constructors
        RPN();
        RPN(const std::string str);
        RPN(const RPN &copy);

        // Destructor
        ~RPN();

        // Operators
        RPN &operator=(const RPN &other);

        // Getter
        std::stack<float> getStack() const { return (_stack); };

        // Functions
        void solveRPN(std::string input);

        // Exceptions
        class InvalidOperandException : public std::exception {
            public:
                virtual const char *what() const throw();
        };

        class IncompleteNotationException : public std::exception {
            public:
                virtual const char *what() const throw();
        };

        class OperatorOverloadException : public std::exception {
            public:
                virtual const char *what() const throw();
        };

    private:
        std::stack<float> _stack;
};
#endif