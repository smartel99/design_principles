/**
 * @file    abbr.h
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

#ifndef DESIGN_PATTERNS_ABBR_H
#define DESIGN_PATTERNS_ABBR_H

#include "../tag.h"

/**
 * Defines an abbreviation or an acronym.
 * https://www.w3schools.com/TAgs/tag_abbr.asp
 */
struct Abbr : Tag
{
    Abbr(std::string acronym, std::string definition) : Tag("abbr", acronym)
    {
        Attributes.emplace_back("title", definition);
    }
};

#endif    // DESIGN_PATTERNS_ABBR_H
