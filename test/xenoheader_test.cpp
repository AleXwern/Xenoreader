/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoheader_test.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 01:06:12 by AleXwern          #+#    #+#             */
/*   Updated: 2022/12/26 22:58:09 by AleXwern         ###   ########.fr       */
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
	xenodata.setPosition(0);
	xeno.parseDataChunck(xenodata);
	REQUIRE(xeno.length() == 4);
	xeno.outputFile("peepee.txt");
}

TEST_CASE("handleHeaderFile")
{
	Xenoheader	parser;
	Xenoheader	reader;

	xenodata.setPosition(0);
	parser.parseDataChunck(xenodata);
	parser.outputFile("demo.txt");

	reader.inputFile("demo.txt");
	REQUIRE(reader.length() == 4);
	REQUIRE(reader.get(3).first == parser.get(3).first);
	REQUIRE(ft_strequ(reader.get(3).second, "maybe this will work"));
}
