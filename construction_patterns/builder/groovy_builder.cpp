/**
 * @file    groovy_builder.cpp
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

#include <iostream>

#include "groovy_builder/img.h"
#include "groovy_builder/tags.h"

int main()
{
    // clang-format off
    std::cout <<
        Html {
            Head {
                Title {"My Page"}
            },
            Body {
                H1 {"My Title"},
                H2 {"My Subtitle"},
                P {"Some text"},
                Img {"link/to/an/image.jpg"},
                Blockquote {
                    "This is my image",
                    "This is my source"
                }
            }
        }
        << std::endl;
    // clang-format on
    return 0;
}