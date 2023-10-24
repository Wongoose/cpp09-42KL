/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:33:46 by zwong             #+#    #+#             */
/*   Updated: 2023/10/24 13:33:46 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
    (void)argc;
    BitcoinExchange instance = BitcoinExchange();
    // instance.printExchangeRateMap();
    std::cout << YELLOW << "Loading..." << std::endl << RESET;
    instance.readCSV();
    std::cout << GREEN << "DONE & CONVERTED!" << std::endl << RESET;
    instance.calculateValueFromInput(argv[1]);
    return (0);
}