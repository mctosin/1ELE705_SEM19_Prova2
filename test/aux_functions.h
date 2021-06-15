#pragma once
#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

#include "gtest/gtest.h"
#include <cstdint>

extern "C"
{
    #include "../src/main.h"
    #include "../src/Aux_Func.h"
    extern const char polar[];
    extern const char cartesian[];
    extern const char* face[];
    extern const char* suit[];
}


template<size_t size>
::testing::AssertionResult ArraysMatch(const uint8_t(&expected)[size],
    const uint8_t(&actual)[size])
{
    for (size_t i(0); i < size; ++i)
    {
        if (expected[i] != actual[i])
        {
            return ::testing::AssertionFailure() <<
                "expected[" << i << "] ("
                << print_uint8_hex(expected[i]) <<
                ") != actual[" << i << "] ("
                << print_uint8_hex(actual[i]) << ")";
        }
    }

    return ::testing::AssertionSuccess();
}

template<size_t size>
::testing::AssertionResult ArraysMatch(const uint64_t(&expected)[size],
    const uint64_t(&actual)[size])
{
    for (size_t i(0); i < size; ++i)
    {
        if (expected[i] != actual[i])
        {
            return ::testing::AssertionFailure() <<
                "expected[" << i << "] ("
                << print_uint64_hex(expected[i]) <<
                ") != actual[" << i << "] ("
                << print_uint64_hex(actual[i]) << ")";
        }
    }

    return ::testing::AssertionSuccess();
}

template<size_t size>
::testing::AssertionResult ArraysMatch(const int(&expected)[size],
    const int(&actual)[size])
{
    for (size_t i(0); i < size; ++i)
    {
        if (expected[i] != actual[i])
        {
            return ::testing::AssertionFailure() //<<
                //"expected[" << i << "] ("
               // << print_uint64_hex(expected[i]) <<
               // ") != actual[" << i << "] ("
               // << print_uint64_hex(actual[i]) << ")"
                ;
        }
    }

    return ::testing::AssertionSuccess();
}

template<size_t size>
::testing::AssertionResult ArraysMatch(const Card(&expected)[size],
    const Card(&actual)[size])
{
    for (size_t i(0); i < size; ++i)
    {
        if ((expected[i].face != actual[i].face) ||
            (expected[i].suit != actual[i].suit) ||
            (expected[i].face_number != actual[i].face_number) ||
            (expected[i].suit_number != actual[i].suit_number))
        {
            char erro[1024];
            sprintf(
                erro,
                "professor[%d] (face_number = %d, suit_number = %d)"
                " != aluno[%d] (face_number = %d, suit_number = %d)",
                (int)i, expected[i].face_number, expected[i].suit_number,
                (int)i, actual[i].face_number, actual[i].suit_number);
            return ::testing::AssertionFailure() << erro;
        }
    }

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult ArraysMatch(const Card* expected,
    const Card* actual,
    size_t size)
{
    for (size_t i(0); i < size; ++i)
    {
        if ((expected[i].face != actual[i].face) ||
            (expected[i].suit != actual[i].suit) ||
            (expected[i].face_number != actual[i].face_number) ||
            (expected[i].suit_number != actual[i].suit_number))
        {
            char erro[1024];
            sprintf(
                erro,
                "professor[%d] (face_number = %d, suit_number = %d)"
                " != aluno[%d] (face_number = %d, suit_number = %d)",
                (int)i, expected[i].face_number, expected[i].suit_number,
                (int)i, actual[i].face_number, actual[i].suit_number);
            return ::testing::AssertionFailure() << erro;
        }
    }

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult CartNear(Cart expected, Cart actual, double tolerance)
{
    if (fabs(expected.a - actual.a) > tolerance || fabs(expected.b - actual.b) > tolerance)
    {
        return ::testing::AssertionFailure() <<
                "expected (" << expected.a << " + j*" << expected.b << 
                ") != actual (" << actual.a << " + j*" << actual.b <<
                ")";
    }

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult PolNear(Pol expected, Pol actual, double tolerance)
{
    if (fabs(expected.r - actual.r) > tolerance || fabs(expected.g - actual.g) > tolerance)
    {
        return ::testing::AssertionFailure() <<
            "expected (" << expected.r << " <_" << expected.g <<
            ") != actual (" << actual.r << " <_" << actual.g <<
            ")";
    }

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult ComplexNumberNear(CplxNum expected, CplxNum actual, double tolerance)
{
    if (strcmp(expected.mode, cartesian)==0 && strcmp(actual.mode, cartesian)==0) {
        if (fabs(expected.s.cart.a - actual.s.cart.a) > tolerance || fabs(expected.s.cart.b - actual.s.cart.b) > tolerance)
        {
            return ::testing::AssertionFailure() <<
                "expected (" << expected.s.cart.a << " + j*" << expected.s.cart.b <<
                ") != actual (" << actual.s.cart.a << " + j*" << actual.s.cart.b <<
                ")";
        }
    }
    else if (strcmp(expected.mode, polar) == 0 && strcmp(actual.mode, polar) == 0) {
        if (fabs(expected.s.pol.r - actual.s.pol.r) > tolerance || fabs(expected.s.pol.g - actual.s.pol.g) > tolerance)
        {
            return ::testing::AssertionFailure() <<
                "expected (" << expected.s.pol.r << " <_" << expected.s.pol.g <<
                ") != actual (" << actual.s.pol.r << " <_" << actual.s.pol.g <<
                ")";
        }
    }
    else {
        // falha
        return ::testing::AssertionFailure() << "(expected.mode == " << expected.mode
            << " != " << "actual.mode == " << actual.mode << " )";
    }

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult ListMatch(ListCardNodePtr actualListPtr, ListCardNodePtr expectedListPtr)
{
    ListCardNodePtr actualPtr = actualListPtr;
    ListCardNodePtr expectedPtr = expectedListPtr;

    while (actualPtr != NULL) {
        if (strcmp(actualPtr->card.face, expectedPtr->card.face) ||
            (actualPtr->card.face_number != expectedPtr->card.face_number) ||
            strcmp(actualPtr->card.suit, expectedPtr->card.suit) ||
            (actualPtr->card.suit_number != expectedPtr->card.suit_number)) {
            return ::testing::AssertionFailure() << "List Match Fail";
        }
        actualPtr = actualPtr->nextPtr;
        expectedPtr = expectedPtr->nextPtr;
    }
    if (expectedPtr != NULL) {
        // No match!
        return ::testing::AssertionFailure() << "List Match Fail";
    }
    return ::testing::AssertionSuccess();
}

::testing::AssertionResult ListNodeAddressesMismatch(ListCardNodePtr actualListPtr, ListCardNodePtr expectedListPtr)
{
    ListCardNodePtr actualPtr = actualListPtr;
    ListCardNodePtr expectedPtr = expectedListPtr;

    while (actualPtr != NULL) {   
        if (actualPtr == expectedPtr) {
            return ::testing::AssertionFailure() << "List Node Address Mismatch Fail";
        }
        actualPtr = actualPtr->nextPtr;
        expectedPtr = expectedPtr->nextPtr;
    }
    if (expectedPtr != NULL) {
        // No match!
        return ::testing::AssertionFailure() << "Last Link NULL Match Fail";
    }
    return ::testing::AssertionSuccess();
}

::testing::AssertionResult NullPointerTest(ListCardNodePtr actualListPtr, ListCardNodePtr expectedListPtr)
{
    if (expectedListPtr == NULL || actualListPtr == NULL) {
        // Some pointer is NULL
        return ::testing::AssertionFailure() << "FAIL, Some pointer is NULL";
    }
    return ::testing::AssertionSuccess();
}

::testing::AssertionResult ListNodeAddressesArrayMismatch(int* actualAddrSeq, int* expectedAddrSeq)
{
    int i;
    int igual = 0;
    for (i = 0; i < 52 && actualAddrSeq[i] != NULL; i++) {
        if (actualAddrSeq[i] == expectedAddrSeq[i]) {
            igual++;
        }
    }
    if (igual > 4) {
        return ::testing::AssertionFailure() << "List Node Address Mismatch Fail";
    }
    if (actualAddrSeq[i] != NULL || expectedAddrSeq[i] != NULL) {
        return ::testing::AssertionFailure() << "Last Link NULL Match Fail";
    }
    if (i != 52) {
        return ::testing::AssertionFailure() << "Deck has not 52 cards";
    }
    return ::testing::AssertionSuccess();
}

#endif // AUX_FUNCTIONS_H
