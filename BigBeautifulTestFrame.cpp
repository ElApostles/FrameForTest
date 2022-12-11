/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigBeautifulTestFrame.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdoo <hdoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:32:08 by hdoo              #+#    #+#             */
/*   Updated: 2022/12/11 19:20:34 by hdoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BigBeautifulTestFrame.hpp"
#include <iostream>

BigBeautifulTestFrame::BigBeautifulTestFrame()
{
	color_.foreground = NOCOLOR;
	color_.background = GREEN;
	width_            = 30;
	verticalFrameSeg_ = '-';
	leftVertax_       = '/';
	rightVertax_      = '\\';
	wall_             = '|';
	field_            = 1;
	padding_          = 0;
}

BigBeautifulTestFrame::BigBeautifulTestFrame(size_t width)
{
	color_.foreground = NOCOLOR;
	color_.background = GREEN;
	width_            = width;
	verticalFrameSeg_ = '-';
	leftVertax_       = '/';
	rightVertax_      = '\\';
	wall_             = '|';
	field_            = 1;
	padding_          = 0;
}

BigBeautifulTestFrame::~BigBeautifulTestFrame()
{
}

void BigBeautifulTestFrame::printMessageLine()
{
	size_t leftPedding;

	leftPedding = (width_ - message_.length()) / 2 + message_.length();
	if (leftPedding > width_)
	{
		leftPedding = message_.length();
	}
	std::cout << wall_;
	std::cout << color_.foreground;
	std::cout.width(leftPedding);
	std::cout.fill(' ');
	std::cout << message_;
	std::cout << color_.background;
	std::cout.width(width_ - leftPedding);
	std::cout.fill(' ');
	std::cout << wall_ << std::endl;
}
void BigBeautifulTestFrame::printEmptyLine()
{
	std::cout << wall_;
	std::cout.width(width_);
	std::cout.fill(' ');
	std::cout << wall_ << std::endl;
}

void BigBeautifulTestFrame::printVerticalFrame()
{
	std::cout << leftVertax_;
	for (size_t i = 0; i < field_; i++)
	{
		std::cout.width(width_);
		std::cout.fill(verticalFrameSeg_);
		std::cout << wall_;
	}
	std::cout << "\b" << rightVertax_ << std::endl;
}
void BigBeautifulTestFrame::printVerticalFrameReversed()
{
	std::cout << rightVertax_;
	for (size_t i = 0; i < field_; i++)
	{
		std::cout.width(width_);
		std::cout.fill(verticalFrameSeg_);
		std::cout << wall_;
	}
	std::cout << "\b" << leftVertax_ << std::endl;
}

BigBeautifulTestFrame& BigBeautifulTestFrame::setForeGroundColor(std::string color)
{
	color_.foreground = color;
	return (*this);
}

BigBeautifulTestFrame& BigBeautifulTestFrame::setBackGroundColor(std::string color)
{
	color_.background = color;
	return (*this);
}

BigBeautifulTestFrame& BigBeautifulTestFrame::print(std::string message)
{
	message_ = message;
	if (width_ < message_.length())
	{
		width_ = message_.length() + 3;
	}
	std::cout << color_.background;
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
	std::cout << NOCOLOR;
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
	leftVertax_  = c;
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
