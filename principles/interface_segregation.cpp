/**
 * @file    interface_segregation.cpp
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
 * The interface segregation principle recommends minimizing the sizes of
 * interfaces so simplify their implementation for both the implementer and the
 * user.
 *
 * In this example, we must implement an interface that can work with documents,
 * as well as implement various kinds of machines implementing that interface.
 */

#include <iostream>

struct Document
{
};

/*--------------------------------------------------------------------------------------------------------------------*/
/* The Problem: */

/**
 * @brief This naive interface offers all the features we need for our
 * documents. It is a valid interface, however every methods needs to be
 * implemented, even if their functionalities are not available on every
 * possible machines.
 */
struct INaiveMachine
{
    virtual void Print(Document& doc) = 0;
    virtual void Scan(Document& doc)  = 0;
    virtual void Fax(Document& doc)   = 0;
};

/**
 * This implementation is fine because it implements every methods.
 */
struct NaiveAllInOne : INaiveMachine
{
    void Print(Document& doc) override { std::cout << "Printing the document!" << std::endl; }
    void Scan(Document& doc) override { std::cout << "Scanning the document!" << std::endl; }
    void Fax(Document& doc) override { std::cout << "Faxing the document!" << std::endl; }
};

/**
 * In itself, this implementation is not too bad. However, it is weird and unnatural.
 * Why are Print and Fax there if they are not supported features?
 */
struct NaiveScanner : INaiveMachine
{
    void Print(Document& doc) override
    {
        // Scanner cannot print!
        throw std::exception();
    }
    void Scan(Document& doc) override { std::cout << "Scanning the document!" << std::endl; }
    void Fax(Document& doc) override
    {
        // Scanner cannot fax!
        throw std::exception();
    }
};

/*--------------------------------------------------------------------------------------------------------------------*/
/* The Solution: */

/**
 * The interface should be broken down into smaller interfaces, each presenting unique features
 * for that interface. They can then be combined through multiple inheritance to define an
 * implementation that uses more than one of those interfaces.
 */

/**
 * The INaiveMachine interface is broken down into three interfaces:
 * - IPrinter
 * - IScanner
 * - IFax
 */
struct IPrinter
{
    virtual void Print(Document& doc) = 0;
};

struct IScanner
{
    virtual void Scan(Document& doc) = 0;
};

struct IFax
{
    virtual void Fax(Document& doc) = 0;
};

/**
 * Then we can have our implementations
 */

struct MyPrinterScanner : IPrinter, IScanner
{
    void Print(Document& doc) override { std::cout << "Printing the document!" << std::endl; }
    void Scan(Document& doc) override { std::cout << "Scanning the document!" << std::endl; }
    // No need to implement Fax
};

struct MyAllInOne : IPrinter, IScanner, IFax
{
    void Print(Document& doc) override { std::cout << "Printing the document!" << std::endl; }
    void Scan(Document& doc) override { std::cout << "Scanning the document!" << std::endl; }
    void Fax(Document& doc) override { std::cout << "Faxing the document!" << std::endl; }
};

/*--------------------------------------------------------------------------------------------------------------------*/
/* Test Program: */
int main()
{
    Document doc;

    // Before, we had:
    NaiveScanner naiveScanner;
    naiveScanner.Scan(doc);     // This is fine, we're a scanner!
    naiveScanner.Print(doc);    // This isn't fine, we're a scanner, not a printer? It still
                                // compiles tho...

    // Now, only the functions that actually exist are presented to us!
    MyPrinterScanner printerScanner;
    printerScanner.Print(doc);    // OK!
    printerScanner.Scan(doc);     // OK!

    std::getchar();
    return 0;
}
