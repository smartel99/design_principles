/**
 * @file    basic_builder.cpp
 * @author  Samuel Martel
 * @p       https://github.com/smartel99
 * @date    2022-07-07
 *
 * @brief
 ******************************************************************************
 * Copyright (C) 2022  Samuel Martel
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *****************************************************************************/
/**
 * This example shows how a simple builder can be structured.
 *
 * In this example, we build a fake html page containing a paragraph and an unordered list.
 */

#include <iostream>

#include <string>
#include <string_view>

#include "basic_builder/html_builder.h"

int main()
{
    using namespace std::string_view_literals;
    HtmlElement elem =
      HtmlElement::Create("ul"sv).AddChild("li"sv, "hello"sv).AddChild("li"sv, "world"sv).Build();

    std::cout << elem.ToStr() << std::endl;
}