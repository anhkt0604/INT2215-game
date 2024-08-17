#include "header/utils.h"

string getPath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find("cmake-build-debug");
    string path = string(buffer).substr(0, pos);
    for (int i = 0; i < path.size(); i++) {
        if (path[i] == '\\') {
            path[i] = '/';
        }
    }
    return path;
}

bool utils::CheckCollision(TilePos object1, TilePos object2) {
    int o2_x = object2.x / TILE_SIZE;
    int o2_y = object2.y / TILE_SIZE;
    if (object1.x == o2_x && object1.y == o2_y) {
        return true;
    }
    return false;
}

//bool utils::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
//{
//    int left_a = object1.x;
//    int right_a = object1.x + object1.w;
//    int top_a = object1.y;
//    int bottom_a = object1.y + object1.h;
//
//    int left_b = object2.x;
//    int right_b = object2.x + object2.w;
//    int top_b = object2.y;
//    int bottom_b = object2.y + object2.h;
//
//    // Case 1: size object 1 < size object 2
//    if (left_a > left_b && left_a < right_b)
//    {
//        if (top_a > top_b && top_a < bottom_b)
//        {
//            return true;
//        }
//    }
//
//    if (left_a > left_b && left_a < right_b)
//    {
//        if (bottom_a > top_b && bottom_a < bottom_b)
//        {
//            return true;
//        }
//    }
//
//    if (right_a > left_b && right_a < right_b)
//    {
//        if (top_a > top_b && top_a < bottom_b)
//        {
//            return true;
//        }
//    }
//
//    if (right_a > left_b && right_a < right_b)
//    {
//        if (bottom_a > top_b && bottom_a < bottom_b)
//        {
//            return true;
//        }
//    }
//
//    // Case 2: size object 1 < size object 2
//    if (left_b > left_a && left_b < right_a)
//    {
//        if (top_b > top_a && top_b < bottom_a)
//        {
//            return true;
//        }
//    }
//
//    if (left_b > left_a && left_b < right_a)
//    {
//        if (bottom_b > top_a && bottom_b < bottom_a)
//        {
//            return true;
//        }
//    }
//
//    if (right_b > left_a && right_b < right_a)
//    {
//        if (top_b > top_a && top_b < bottom_a)
//        {
//            return true;
//        }
//    }
//
//    if (right_b > left_a && right_b < right_a)
//    {
//        if (bottom_b > top_a && bottom_b < bottom_a)
//        {
//            return true;
//        }
//    }
//
//    // Case 3: size object 1 = size object 2
//    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
//    {
//        return true;
//    }
//
//    return false;
//}