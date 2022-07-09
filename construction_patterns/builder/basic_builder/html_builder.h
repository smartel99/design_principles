/**
 * @file    html_builder.h
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

#ifndef DESIGN_PATTERNS_HTML_BUILDER_H
#define DESIGN_PATTERNS_HTML_BUILDER_H

#include <string>
#include <string_view>

#include "html_element.h"

/**
 * The builder that allows us to simply and neatly create our HTML elements.
 */
class HtmlBuilder
{
public:
    HtmlBuilder(std::string_view rootName) : Root(rootName) {}

    HtmlBuilder& AddChild(std::string_view name, std::string_view text);

    [[nodiscard]] std::string ToStr() const { return Root.ToStr(); }

    [[nodiscard]] HtmlElement Build() const { return Root; }

    operator HtmlElement() const { return Root; }

private:
    HtmlElement Root;
};


#endif    // DESIGN_PATTERNS_HTML_BUILDER_H
