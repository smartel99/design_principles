/**
 * @file    no_builder.cpp
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
 * This example shows how messy a builder-less approach can be.
 *
 * In this example, we build a fake html page containing a paragraph and an unordered list.
 */

#include <iostream>
#include <sstream>

int main()
{
    // Builds the paragraph.
    // This is messy and error-prone, since there are no guarantee on the safety and structure of
    // what's being added to the output.
    const char* text = "hello";
    std::string output;
    output += "<p>";
    output += text;
    output += "</p>";
    std::cout << output << std::endl;

    // Builds the unordered-list.
    // This works, but once again, it is error-prone and messy.
    std::string        words[] = {"Hello", "World"};
    std::ostringstream oss;
    oss << "<ul>";
    for (auto& word : words)
    {
        oss << "  <li>" << word << "</li>";
    }
    oss << "</ul>";
    std::cout << oss.str() << std::endl;
}