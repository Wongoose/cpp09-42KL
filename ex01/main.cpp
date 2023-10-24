/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:33:28 by zwong             #+#    #+#             */
/*   Updated: 2023/10/24 14:21:21 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv) {
    // Validate input count
    if (argc != 2) {
        std::cout << RED << "Invalid argument count. Please try again!" << std::endl << RESET;
        return (1);
    }
    try {
        RPN().solveRPN(argv[1]);
    } catch (std::exception &err) {
        std::cout << RED << err.what() << std::endl << RESET;
    }
    return (0);
}