/**
 * @file    CodeBuilder.cpp
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

#include "CodeBuilder.h"
#include <iomanip>


CodeBuilder::CodeBuilder(std::string name) : m_name(std::move(name))
{
}

CodeBuilder& CodeBuilder::add_field(const std::string& name, const std::string& type)
{
    m_fields.emplace_back(type, name);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const CodeBuilder& obj)
{
    static constexpr int indentation = 2;

    os << "class " << obj.m_name << "\n"
       << "{"
       << "\n";

    for (const auto& field: obj.m_fields)
    {
        os << std::setw(indentation) << field.first << " " << field.second << ";" << std::endl;
    }

    os << "};";

    return os;
}
