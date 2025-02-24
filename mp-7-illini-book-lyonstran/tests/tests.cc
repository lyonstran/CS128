// clang-format off
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2023/06/02                      Compiler ...: clang++                  //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// clang-format on

///////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
///////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

///////////////////////////////////////////////////////////////////////////////
//                                 Includes //
///////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

///////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
///////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

///////////////////////////////////////////////////////////////////////////////