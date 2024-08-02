bool atTopEdge(const int cellRow) {
    return (cellRow == 0);
}

bool atBottomEdge(const int cellRow, const int dimension) {
    return (cellRow == dimension - 1);
}

bool atLeftEdge(const int cellCol) {
    return(cellCol == 0);
}

bool atRightEdge(const int cellCol, const int dimension) {
    return(cellCol == dimension - 1);
}

bool atEdge(const int cellRow, const int cellCol, const int dimension) {
    return (atTopEdge(cellRow) || atBottomEdge(cellRow, dimension) || atLeftEdge(cellCol) || atRightEdge(cellCol, dimension));
}