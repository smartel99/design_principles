/**
 * @file    CodeBuilder.h
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

#ifndef DESIGN_PATTERNS_CODEBUILDER_H
#define DESIGN_PATTERNS_CODEBUILDER_H


#include <sstream>
#include <string>
#include <vector>
#include <ostream>

class CodeBuilder
{
    using Field = std::pair<std::string, std::string>;

public:
    CodeBuilder(std::string name);

    CodeBuilder& add_field(const std::string& name, const std::string& type);


    friend std::ostream& operator<<(std::ostream& os, const CodeBuilder& builder);

private:
    std::string        m_name;
    std::vector<Field> m_fields;
};



#endif    // DESIGN_PATTERNS_CODEBUILDER_H
