/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:25:37 by AleXwern          #+#    #+#             */
/*   Updated: 2022/06/19 19:50:13 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "catch_amalgamated.hpp"
#include "libft.h"

TEST_CASE("Number manipulation", "[require]")
{
    REQUIRE(ft_abs(0) == 0);
	REQUIRE(ft_abs(-10) == 10);
	REQUIRE(ft_abs(110) == 110);
	REQUIRE(ft_fabs(0.0) == 0.0);
	REQUIRE(ft_fabs(-10.5) == 10.5);
	REQUIRE(ft_fabs(110.25) == 110.25);
}
