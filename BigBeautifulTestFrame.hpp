/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigBeautifulTestFrame.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdoo <hdoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:31:23 by hdoo              #+#    #+#             */
/*   Updated: 2022/12/31 04:55:19 by hdoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sstream>
#include <string>

#define BLACK "\x1b[38;2;255;255;255m"
#define PUPLE "\x1b[38;2;172;146;235m"
#define RED "\x1b[38;2;236;86;101m"
#define BLUE "\x1b[38;2;114;191;228m"
#define ORANGE "\x1b[38;2;248;145;76m"
#define YELLOW "\x1b[38;2;254;206;83m"
#define GREEN "\x1b[38;2;172;210;118m"
#define NOCOLOR "\x1b[0;0m"
#ifdef VERBOSE
#include <sys/_types/_size_t.h>

class BigBeautifulTestFrame
{
  private:
	typedef struct s_color
	{
		std::string strColor;
		std::string frameColor;
	} t_color;
	size_t width_;
	size_t field_;
	size_t padding_;
	char verticalFrameSeg_;
	char leftVertax_;
	char rightVertax_;
	char wall_;
	std::string message_;
	t_color color_;
	void printVerticalFrame();
	void printEmptyLine();
	void printVerticalFrameReversed();
	void printMessageLine();
	void printColoredRawMessage();
	void printColoredRawWall();

  public:
	BigBeautifulTestFrame& print(std::string message);
	BigBeautifulTestFrame& setField(size_t n);
	BigBeautifulTestFrame& setPadding(size_t n);
	BigBeautifulTestFrame& setVerticalFrameSeg(char c);
	BigBeautifulTestFrame& setLeftVertax(char c);
	BigBeautifulTestFrame& setRightVertax(char c);
	BigBeautifulTestFrame& setWall(char c);
	BigBeautifulTestFrame& setVertax(char c);
	BigBeautifulTestFrame& setStrColor(std::string color);
	BigBeautifulTestFrame& setBackGroundColor(std::string color);
	BigBeautifulTestFrame();
	BigBeautifulTestFrame(size_t width);
	~BigBeautifulTestFrame();
};

typedef BigBeautifulTestFrame btf;
#endif

void printVerbose(const std::string& str, const std::string& color = NOCOLOR);
void printVerboseTitle(const std::string& str, const std::string& color = NOCOLOR, int padding = 1);
void printVerboseTitleEnter(const std::string& str = "TEST", const std::string& color = NOCOLOR, int padding = 1);
std::string itoaStream(int n);
