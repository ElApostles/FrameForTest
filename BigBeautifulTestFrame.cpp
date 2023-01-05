/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigBeautifulTestFrame.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdoo <hdoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:32:08 by hdoo              #+#    #+#             */
/*   Updated: 2023/01/01 11:02:45 by hdoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BigBeautifulTestFrame.hpp"
#ifdef VERBOSE
#include <iomanip>
#include <iostream>

BigBeautifulTestFrame::BigBeautifulTestFrame()
{
	color_.strColor = NOCOLOR;
	color_.frameColor = GREEN;
	width_ = 45;
	verticalFrameSeg_ = '-';
	leftVertax_ = '/';
	rightVertax_ = '\\';
	wall_ = '|';
	field_ = 1;
	padding_ = 0;
}

BigBeautifulTestFrame::BigBeautifulTestFrame(size_t width)
{
	color_.strColor = NOCOLOR;
	color_.frameColor = GREEN;
	width_ = width;
	verticalFrameSeg_ = '-';
	leftVertax_ = '/';
	rightVertax_ = '\\';
	wall_ = '|';
	field_ = 1;
	padding_ = 0;
}

BigBeautifulTestFrame::~BigBeautifulTestFrame()
{
}

void BigBeautifulTestFrame::printMessageLine()
{
	size_t leftPedding;

	leftPedding = (width_ - 2 - message_.length()) / 2;
	if (leftPedding > width_)
	{
		leftPedding = message_.length();
	}
	printColoredRawWall();
	std::cout.width(leftPedding + color_.strColor.length());
	std::cout.fill(' ');
	std::cout << color_.strColor;
	printColoredRawMessage();
	std::cout.width(width_ - leftPedding + color_.frameColor.length() - message_.length() - 1);
	std::cout.fill(' ');
	std::cout << color_.frameColor;
	std::cout << wall_ << std::endl;
}

void BigBeautifulTestFrame::printEmptyLine()
{
	printColoredRawWall();
	std::cout.width(width_ + color_.frameColor.length() - 1);
	std::cout.fill(' ');
	printColoredRawWall();
	std::cout << std::endl;
}

void BigBeautifulTestFrame::printVerticalFrame()
{
	std::cout << color_.frameColor;
	std::cout << leftVertax_;
	for (size_t i = 0; i < field_; i++)
	{
		std::cout.width(width_);
		std::cout.fill(verticalFrameSeg_);
		std::cout << wall_;
	}
	std::cout << "\b" << rightVertax_ << std::endl;
	std::cout << NOCOLOR;
}

void BigBeautifulTestFrame::printVerticalFrameReversed()
{
	std::cout << color_.frameColor;
	std::cout << rightVertax_;
	for (size_t i = 0; i < field_; i++)
	{
		std::cout.width(width_);
		std::cout.fill(verticalFrameSeg_);
		std::cout << wall_;
	}
	std::cout << "\b" << leftVertax_;
	std::cout << NOCOLOR;
}

void BigBeautifulTestFrame::printColoredRawMessage()
{
	std::cout << color_.strColor << message_ << NOCOLOR;
}

void BigBeautifulTestFrame::printColoredRawWall()
{
	std::cout << color_.frameColor << wall_ << NOCOLOR;
}

BigBeautifulTestFrame& BigBeautifulTestFrame::setStrColor(std::string color)
{
	color_.strColor = color;
	return (*this);
}

BigBeautifulTestFrame& BigBeautifulTestFrame::setBackGroundColor(std::string color)
{
	color_.frameColor = color;
	return (*this);
}

BigBeautifulTestFrame& BigBeautifulTestFrame::print(std::string message)
{
	message_ = message;
	if (width_ < message_.length())
	{
		width_ = message_.length() + 3;
	}
	printVerticalFrame();
	for (size_t i = 0; i < padding_; i++)
	{
		printEmptyLine();
	}
	printMessageLine();
	for (size_t i = 0; i < padding_; i++)
	{
		printEmptyLine();
	}
	printVerticalFrameReversed();
	return (*this);
}

BigBeautifulTestFrame& BigBeautifulTestFrame::setField(size_t n)
{
	field_ = n;
	return (*this);
}
BigBeautifulTestFrame& BigBeautifulTestFrame::setPadding(size_t n)
{
	padding_ = n;
	return (*this);
}
BigBeautifulTestFrame& BigBeautifulTestFrame::setVerticalFrameSeg(char c)
{
	verticalFrameSeg_ = c;
	return (*this);
}
BigBeautifulTestFrame& BigBeautifulTestFrame::setVertax(char c)
{
	leftVertax_ = c;
	rightVertax_ = c;
	return (*this);
}
BigBeautifulTestFrame& BigBeautifulTestFrame::setLeftVertax(char c)
{
	leftVertax_ = c;
	return (*this);
}
BigBeautifulTestFrame& BigBeautifulTestFrame::setRightVertax(char c)
{
	rightVertax_ = c;
	return (*this);
}
BigBeautifulTestFrame& BigBeautifulTestFrame::setWall(char c)
{
	wall_ = c;
	return (*this);
}

#endif

void printVerbose(const std::string& str, const std::string& color)
{
#ifdef VERBOSE
	std::cout << color << str << NOCOLOR << std::endl;
#else
	(void)str;
	(void)color;
#endif // DEBUG
}

void printVerboseTitle(const std::string& str, const std::string& color, int padding)
{
#ifdef VERBOSE
	static BigBeautifulTestFrame f;

	f.setVertax('#').setPadding(padding);
	f.setStrColor(color);
	f.print(str);
	std::cout << std::endl;
#else
	(void)str;
	(void)padding;
	(void)color;
#endif // DEBUG
}

void printVerboseTitleEnter(const std::string& str, const std::string& color, int padding)
{
#ifdef VERBOSE
	std::string enter;

	static BigBeautifulTestFrame f;
	getline(std::cin, enter);
	system("clear");
	f.setVertax('#').setPadding(padding);
	f.setStrColor(color);
	f.print(str);
	getline(std::cin, enter);
#else
	(void)str;
	(void)padding;
	(void)color;
#endif // DEBUG
}

std::string itoaStream(int i)
{
	std::stringstream ss;
	std::string temp;

	ss << i;
	ss >> temp;
	return (temp);
}
