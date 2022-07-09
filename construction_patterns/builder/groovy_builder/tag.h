/**
 * @file    tag.h
 * @author  Samuel Martel
 * @p       https://github.com/smartel99
 * @date    2022-07-09
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

#ifndef DESIGN_PATTERNS_TAG_H
#define DESIGN_PATTERNS_TAG_H

#include <iomanip>
#include <string>
#include <utility>
#include <vector>

/**
 * Represents an HTML tag.
 *
 * This will translate into:
 *  <Name Attributes>
 *      Text
 *      <!-- Children -->
 *  </Name>
 */
struct Tag
{
    using Attribute = std::pair<std::string, std::string>;

    //! Name of the tag.
    std::string Name;
    //! Text contained in the tag.
    std::string Text;

    std::vector<Tag>       Children;
    std::vector<Attribute> Attributes;

    friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
    {
        const int width = static_cast<int>(os.width());
        os << std::setw(width) << ""
           << "<" << tag.Name;

        for (const auto& attribute : tag.Attributes)
        {
            os << " " << attribute.first << "=\"" << attribute.second << "\"";
        }

        if (tag.Children.empty() && tag.Text.empty())
        {
            os << "/>" << std::endl;
        }
        else
        {
            os << ">" << std::endl;

            if (!tag.Text.empty())
            {
                os << std::setw((width + 4)) << "" << tag.Text << std::endl;
            }

            for (const auto& child : tag.Children)
            {
                os << std::setw(width + 4) << child;
            }

            os << std::setw(width) << ""
               << "</" << tag.Name << ">" << std::endl;
        }

        return os;
    }

protected:
public:
    Tag(std::string name, std::string text) : Name(std::move(name)), Text(std::move(text)) {}
    Tag(std::string name, std::vector<Tag> children)
    : Name(std::move(name)), Children(std::move(children))
    {
    }
};
#endif    // DESIGN_PATTERNS_TAG_H
