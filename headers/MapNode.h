#pragma once

template <typename T1, typename T2>
struct MapNode {
    T1 key;
    T2 value;
    bool black;
    MapNode<T1, T2>* parent;
    MapNode<T1, T2>* left;
    MapNode<T1, T2>* right;
    MapNode(T1 key, T2 value, bool black, MapNode<T1, T2>* parent,
            MapNode<T1, T2>* left, MapNode<T1, T2>* right)
        : key(key),
          value(value),
          black(black),
          parent(parent),
          left(left),
          right(right) {}
};
