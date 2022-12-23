/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoheader_test.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 01:06:12 by AleXwern          #+#    #+#             */
/*   Updated: 2022/12/24 01:43:08 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xenoheader.hpp"
#include "../catch2/extras/catch_amalgamated.hpp"

Xenoreader xenodata("./test/test_file3.txt", true);

TEST_CASE("lengthIsZero")
{
	Xenoheader	xeno;
	REQUIRE(xeno.length() == 0);
}

TEST_CASE("insertEmptyLine")
{
	Xenoheader	xeno;
	xeno.insert({0, strdup("")});
	REQUIRE(xeno.length() == 1);
}

TEST_CASE("getFirstLine")
{
	Xenoheader	xeno;
	xeno.insert({5, strdup("Hi")});
	REQUIRE(xeno.get(0).first == 5);
	REQUIRE(ft_strequ(xeno.get(0).second, "Hi"));
}

TEST_CASE("lastLineIsLastPushed")
{
	Xenoheader	xeno;
	xeno.insert({1, strdup("Hi")});
	xeno.insert({5, strdup("Hello")});
	xeno.insert({2, strdup("Bye")});
	REQUIRE(xeno.get(2).first == 2);
	REQUIRE(ft_strequ(xeno.get(2).second, "Bye"));
}

TEST_CASE("parseFourPartFile")
{
	Xenoheader	xeno;
	xeno.parseDataChunck(xenodata);
	REQUIRE(xeno.length() == 4);
}
