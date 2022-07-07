/**
 * @file    dependency_inversion.cpp
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
 * The dependency inversion principle dictates that:
 * A: High-level modules should not depend on low-level modules.
 *      Both should depend on abstractions.
 * B: Abstractions should not depend on details.
 *      Details should also depend on abstractions.
 */

#include <iostream>
#include <string_view>
#include <tuple>
#include <vector>

enum class Relationship
{
    Parent,
    Child,
    Sibling
};

struct Person
{
    std::string_view Name;
};

/**
 * Low-level abstracted interface allowing the browsing of a list of Relations.
 */
struct RelationshipBrowser
{
    virtual std::vector<Person> FindAllChildrenOf(const std::string_view& name) = 0;
};

/**
 * Low-level module that implements the relationship browsing interface.
 *
 * This is where the data resides. Because of this, any changes to the way the data is stored
 * only needs to be reflected in this struct, not in the entire codebase.
 */
struct Relationships : RelationshipBrowser
{
    void AddParentAndChild(const Person& parent, const Person& child)
    {
        Relations.emplace_back(parent, Relationship::Parent, child);
        Relations.emplace_back(child, Relationship::Child, parent);
    }

    std::vector<Person> FindAllChildrenOf(const std::string_view& name) override
    {
        std::vector<Person> result;
        for (auto&& [first, rel, second] : Relations)
        {
            if (first.Name == name && rel == Relationship::Parent)
            {
                result.push_back(second);
            }
        }
        return result;
    }

    std::vector<std::tuple<Person, Relationship, Person>> Relations;
};

/**
 * High-level module that only handles searching into a relation list.
 */
struct Research
{
    Research(RelationshipBrowser& browser, std::string_view name)
    : Matches(browser.FindAllChildrenOf(name))
    {
    }

    std::vector<Person> Matches;

    /**
     * Implementing the search function here would create a dependency on the low-level module,
     * which we want to avoid.
     */
    //    Research(const Relationships& relationships, std::string_view name)
    //    {
    //        auto& relations = relationships.Relations;
    //        for (auto&& [first, rel, second] : relations)
    //        {
    //            if (first.Name == name && rel == Relationship::Parent)
    //            {
    //                Matches.push_back(second);
    //            }
    //        }
    //    }
};

int main()
{
    Person parent {"John"};
    Person child1 {"Chris"};
    Person child2 {"Matt"};

    Relationships relationships;
    relationships.AddParentAndChild(parent, child1);
    relationships.AddParentAndChild(parent, child2);

    Research r(relationships, "John");

    std::cout << "Found " << r.Matches.size() << " child for John:" << std::endl;
    auto& matches = r.Matches;
    for (const auto& [name] : matches)
    {
        std::cout << "- " << name << std::endl;
    }

    std::getchar();
    return 0;
}