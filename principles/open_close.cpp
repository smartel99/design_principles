/**
 * @file    open_close.cpp
 * @author  Samuel Martel
 * @p       https://github.com/smartel99
 * @date    2021-11-10
 *
 * @brief
 ******************************************************************************
 * Copyright (C) 2021  Samuel Martel
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
 * The open-closed principle conveys the idea that a module should always be open to expansion, but closed to
 * modification.
 *
 * In short, this means that the code of the module should be written in a way that allows for features to be added and
 * expanded without the need of going back into old code, which might necessitate re-testing, re-deployment or other
 * annoying things we would prefer avoid doing.
 */

#include <string>
#include <vector>
#include <iostream>


enum class Color
{
    red, green, blue
};

enum class Size
{
    small, medium, large
};

struct Product
{
    std::string name;
    Color       color;
    Size        size;
};


/*--------------------------------------------------------------------------------------------------------------------*/
/* The Problem: */

/**
 * @brief The "wrong" way of doing it.
 *
 * In itself, this way is not bad. It however does not utilize the concepts of an open-closed module, because if we
 * would like to add a feature, for example filtering by name, we would need to go ahead and modify this class
 * instead of expanding it.
 */
class ProductFilter
{
public:
    using Items = std::vector<Product*>;

    /**
     * @brief Filters a list of item by colors.
     * @param items The items to filter
     * @param color The color we want
     * @return A list of the items that matches the color
     */
    Items ByColor(const Items& items, const Color color)
    {
        Items result;
        for (const auto& i:items)
        {
            if (i->color == color)
            {
                result.push_back(i);
            }
        }

        return result;
    }

    /**
     * @brief Filters a list of item by size.
     * @param items The items to filter
     * @param size The size we want
     * @return A list of the items that matches the size
     */
    Items BySize(const Items& items, Size size)
    {
        Items result;
        for (const auto& i:items)
        {
            if (i->size == size)
            {
                result.push_back(i);
            }
        }

        return result;
    }

    /**
     * @brief Filters a list of item by size and color.
     * @param items The items to filter
     * @param size The size we want
     * @param color The color we want
     * @return A list of the items that matches both the color and the size.
     */
    Items BySizeAndColor(const Items& items, Size size, Color color)
    {
        Items result;
        for (const auto& i:items)
        {
            if (i->size == size && i->color == color)
            {
                result.push_back(i);
            }
        }

        return result;
    }
};

/*--------------------------------------------------------------------------------------------------------------------*/
/* The Solution: */

/*
 * Templates!
 *
 * To solve this problem, we "simply" have to implement generic templates that can easily be expanded and generalized
 * without the need of going back in old code to force our shiny new feature in!
 *
 * In the case of this product filter problem, we need a minimum of two templated classes:
 *  - Specification
 *  - Filter
 *
 * The Specification's purpose is to let the user (us) define criteria that must be met by the object to be accepted
 * by the filter. The specification's job is not to do the filtration!
 *
 * The Filter's job is to do the filtration of object based on a given Specification, impartially applying it to the
 * list of objects.
 *
 *
 * Since we might want to combine specifications together to form a more specific filter, we can also add generic
 * binary operators for the Specification class, such as && (and) and || (or).
 */

template<typename T>
struct AndSpecification;

template<typename T>
struct OrSpecification;

template<typename T>
struct Specification
{
    virtual ~Specification() = default;

    /**
     * @brief Check if the specification is met.
     * @param item The item to check.
     * @returns true if the specification is met
     * @returns false if the specification is not met
     */
    virtual bool IsSatified(T* item) const = 0;

    /*
     * The naive approach might be to simply add the binary operator directly in the specification.
     * However, if it isn't planned ahead, i.e. you want to add it as a feature later on, it would break the
     * Open-Close Principle.
     * In that case, we should define the operator from outside this class.
     */
//    AndSpecification<T> operator&&(Specification<T>&& other)
//    {
//        return AndSpecification<T>(*this, other);
//    }
};

template<typename T>
AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second)
{
    return {first, second};
}

template<typename T>
OrSpecification<T> operator||(const Specification<T>& first, const Specification<T>& second)
{
    return {first, second};
}

template<typename T>
struct Filter
{
    /**
     * @brief Filters a list of objects given a certain specification.
     * @param objects The list of objects to filter.
     * @param spec The specification to be met.
     * @return The list of objects that meets the specification.
     */
    virtual std::vector<T*> FilterObjects(const std::vector<T*>& objects, Specification<T>& spec) = 0;
};


template<typename T>
struct AndSpecification : public Specification<T>
{
    const Specification<T>& first;
    const Specification<T>& second;

    AndSpecification(const Specification<T>& first, const Specification<T>& second)
            : first(first), second(second)
    {
    }

    virtual bool IsSatified(T* item) const override
    {
        return first.IsSatified(item) && second.IsSatified(item);
    }
};

template<typename T>
struct OrSpecification : public Specification<T>
{
    const Specification<T>& first;
    const Specification<T>& second;

    OrSpecification(const Specification<T>& first, const Specification<T>& second)
            : first(first), second(second)
    {
    }

    virtual bool IsSatified(T* item) const override
    {
        return first.IsSatified(item) || second.IsSatified(item);
    }
};


/*
 * Now that these generic classes have been defined, we can now add our own more specialized version to implement our
 * filtering features!
 */

struct BetterProductFilter : Filter<Product>
{
    virtual std::vector<Product*> FilterObjects(const std::vector<Product*>& objects, Specification<Product>& spec)
    override
    {
        std::vector<Product*> results;

        for (const auto& obj: objects)
        {
            if (spec.IsSatified(obj))
            {
                results.push_back(obj);
            }
        }

        return results;
    }
};

struct ColorSpecification : Specification<Product>
{
    Color color;

    ColorSpecification(Color color) : color(color)
    {
    }

    virtual bool IsSatified(Product* item) const override
    {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product>
{
    Size size;

    SizeSpecification(Size size) : size(size)
    {
    }

    virtual bool IsSatified(Product* item) const override
    {
        return item->size == size;
    }
};


/*--------------------------------------------------------------------------------------------------------------------*/
/* Test Program: */
int main()
{
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};

    const std::vector<Product*> products{&apple, &tree, &house};

    BetterProductFilter bf;
    ColorSpecification  green{Color::green};
    auto                greenThings         = bf.FilterObjects(products, green);
    for (const auto& p:greenThings)
    {
        std::cout << p->name << " is green!" << std::endl;
    }

    SizeSpecification         large(Size::large);
    AndSpecification<Product> greenAndLarge = green && large;
    for (const auto& p:bf.FilterObjects(products, greenAndLarge))
    {
        std::cout << p->name << " is big and large!" << std::endl;
    }

    std::getchar();
    return 0;
}
