/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoreader_test.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:14:46 by AleXwern          #+#    #+#             */
/*   Updated: 2022/12/24 00:04:44 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xenoreader.hpp"
#include "../catch2/extras/catch_amalgamated.hpp"

TEST_CASE("TestFile1HasLengthOf47")
{
	Xenoreader xeno("./test/test_file1.txt", true);
	REQUIRE(xeno.getLength() == 47);
}

TEST_CASE("StringIsValidArea")
{
	Xenoreader xeno("./test/test_file1.txt", true);
	REQUIRE(xeno.isValidRange(0));
	REQUIRE(!xeno.isValidRange(2));
}

TEST_CASE("byteIsValid")
{
	Xenoreader xeno("./test/test_file1.txt", true);
	REQUIRE((int)xeno.getByte(45) == 46);
	REQUIRE((int)xeno.getByte(0) == '-');
}

TEST_CASE("byteIsinInvalidArea")
{
	Xenoreader xeno("./test/test_file1.txt", true);
	REQUIRE((int)xeno.getByte(xeno.getLength()) == -1);
}

TEST_CASE("instertBytesAndCheckCorrectLength")
{
	Xenoreader xeno("./test/test_file1.txt", true);
	xeno.insertBytes(0, 51);
	REQUIRE(xeno.getByte(0) == 51);
	REQUIRE(xeno.isValidRange(0));
}

TEST_CASE("instertBytesAtInvalidArea")
{
	Xenoreader xeno("./test/test_file1.txt", true);
	xeno.insertBytes(2, 51);
	REQUIRE(xeno.getLength() == 47);
	REQUIRE(xeno.isValidRange(0));
}

TEST_CASE("InsertNewStringLong")
{
	const char	*str = "This is a new string and idk but there should be some bytes";
	
	Xenoreader xeno("./test/test_file1.txt", true);
	xeno.strcpy(0, str);
	REQUIRE(xeno.getByte(0) == 59);
	REQUIRE(xeno.getLength() == 61);
	REQUIRE(xeno.isValidRange(0));
}

TEST_CASE("reduceAreaSize")
{
	Xenoreader xeno("./test/test_file1.txt", true);
	xeno.insertBytes(0, 30);
	REQUIRE(xeno.getByte(0) == 30);
	REQUIRE(xeno.getLength() == 32);
	REQUIRE(xeno.isValidRange(0));
}

TEST_CASE("InsertNewStringShort")
{
	const char	*str = "This is a new string";
	
	Xenoreader xeno("./test/test_file1.txt", true);
	xeno.strcpy(0, str);
	REQUIRE(xeno.getByte(0) == 20);
	REQUIRE(xeno.getLength() == 22);
	REQUIRE(xeno.isValidRange(0));
}

TEST_CASE("retrieveDefaultString")
{
	char	*str = NULL;

	Xenoreader xeno("./test/test_file1.txt", true);
	REQUIRE(xeno.getNextLine(str) == 0);
	REQUIRE(ft_strequ(str, "hello this is a normal file with some length."));
	if (str)
		free(str); //Let's free this just in case
}

TEST_CASE("failingToGetLineReturnsError")
{
	char	*str = NULL;

	Xenoreader xeno("./test/test_file1.txt", true);
	xeno.setPosition(1);
	REQUIRE(xeno.getNextLine(str) == -1);
	REQUIRE(str == NULL);
}

TEST_CASE("chainGNLReturnsMultipleLines")
{
	char	*str = NULL;

	Xenoreader xeno("./test/test_file2.txt", true);
	REQUIRE(xeno.getNextLine(str) == 0);
	REQUIRE(ft_strequ(str, "hello"));
	REQUIRE(xeno.getNextLine(str) == 7);
	REQUIRE(ft_strequ(str, "This is water"));
}
