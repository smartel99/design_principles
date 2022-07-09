/**
 * @file    html_element.h
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

#ifndef DESIGN_PATTERNS_HTML_ELEMENT_H
#define DESIGN_PATTERNS_HTML_ELEMENT_H

#include <sstream>
#include <string>
#include <string_view>
#include <vector>

class HtmlBuilder;

/**
 * This structure represents a simple HTML element.
 */
class HtmlElement
{
public:
    [[nodiscard]] std::string ToStr(int indent = 0) const
    {
        std::ostringstream oss;
        std::string        i(IndentSize * indent, ' ');
        oss << i << "<" << Name << ">" << std::endl;
        if (!Text.empty())
        {
            oss << std::string(IndentSize * (indent + 1), ' ') << Text << std::endl;
        }

        for (const auto& e : Elements)
        {
            oss << e.ToStr(indent + 1);
        }

        oss << i << "</" << Name << ">" << std::endl;

        return oss.str();
    }

    // This function hints to the user that they should use the builder instead of this directly.
    static HtmlBuilder Create(std::string_view name);

private:
    friend class HtmlBuilder;
    std::string_view Name;
    std::string_view Text;

    std::vector<HtmlElement> Elements;

    static constexpr const size_t IndentSize = 2;

    HtmlElement() = default;
    HtmlElement(std::string_view name) : Name(name) {}
    HtmlElement(std::string_view name, std::string_view text) : Name(name), Text(text) {}
};

#endif    // DESIGN_PATTERNS_HTML_ELEMENT_H
