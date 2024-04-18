#pragma once
#include "L2/Lib/imgui/MyImGui.h"
#include "L1/Lib/Math/math.h"
bool is_point_inside_rectangle(ImVec2 point,ImVec2  rect_center, float rect_width, float rect_height, float rect_angle){
    auto half_width = rect_width / 2;
    auto half_height = rect_height / 2;
    

    auto rad = rect_angle*(3.14159f/180.f);

    auto cos1 = cosf(rad);
    auto sin1 = sinf(rad);
    

    auto delta_x = point[0] - rect_center[0];
    auto delta_y = point[1] - rect_center[1];

    auto local_x = cos1*delta_x-sin1*delta_y;
    auto local_y = sin1*delta_x+cos1*delta_y;

    //debug("----> {}, {} || {}, {} || {}\n",local_x,local_y,half_width,half_height,rad);

    return (
        local_x >= -half_width &&
        local_x <= half_width &&
        local_y >= -half_height &&
        local_y <= half_height
    );
}

bool is_point_inside_rectangle2(ImVec2 point, ImVec2 topleft, ImVec2 bottomright) {
    return (point.x >= topleft.x && point.x <= bottomright.x &&
            point.y <= topleft.y && point.y >= bottomright.y);
}

float distance(const ImVec2& p1, const ImVec2& p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

float distanceToSegment(const ImVec2& A, const ImVec2& B, const ImVec2& C) {
    float ABx = B.x - A.x;
    float ABy = B.y - A.y;
    float ACx = C.x - A.x;
    float ACy = C.y - A.y;
    float BCx = C.x - B.x;
    float BCy = C.y - B.y;
    
    float dotProduct = ACx * ABx + ACy * ABy;

    if (dotProduct <= 0) {
        return distance(A, C);
    }

    float squareLengthAB = ABx * ABx + ABy * ABy;
    if (dotProduct >= squareLengthAB) {
        return distance(B, C);
    }

    float crossProduct = ABx * ACy - ABy * ACx;
    return std::abs(crossProduct) / sqrt(squareLengthAB);
}

bool isPointOnSegment(const ImVec2& A, const ImVec2& B, const ImVec2& C, float tolerance) {
    float dist = distanceToSegment(A, B, C);
    return dist <= tolerance;
}