#pragma once
#include <iostream>
#include <chrono>

using namespace std;

/*
 * Compara si dos textos son iguales de manera recursiva
 */
constexpr bool compare(const char* word1, const char* word2, int idx);