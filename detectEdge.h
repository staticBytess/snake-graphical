#pragma once
#include "detectEdge.h"
bool atEdge(const int cellRow, const int cellCol, const int dimension);
bool atTopEdge(const int cellRow);
bool atBottomEdge(const int cellRow, const int dimension);
bool atLeftEdge(const int cellCol);
bool atRightEdge(const int cellCol, const int dimension);