// https://acm.timus.ru/problem.aspx?space=1&num=1215
// Лучше везде испльзовать double. Тесты очень чувствительны к конвертациям из double в int, и обратно

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <cstdio>

using namespace std;

template <typename T>
struct Pair {
    T x;
    T y;
};

using Point = Pair<double>;
using Vector = Pair<double>;

using Side = pair<Point, Point>;

double sq(double x) {
    return x * x;
}

double getDistSq(const Point& p1, const Point& p2) {
    return sq(p2.x - p1.x) + sq(p2.y - p1.y);
}

// Если образуемый прямоугольник - тупоугольный, то ближайшая точка на прямой будет за пределами отрезка
bool isAside(const Point& point, const Side& side) {
    return getDistSq(point, side.first) > getDistSq(point, side.second) + getDistSq(side.first, side.second)
        || getDistSq(point, side.second) > getDistSq(point, side.first) + getDistSq(side.first, side.second);
}

double getDistSq(const Point& point, const Side& side) {
    // (x - x1)/(x2 - x1) = (y - y1)/(y2 - y1) -> Ax + By + C = 0;
    const double A = side.second.y - side.first.y;
    const double B = side.first.x - side.second.x;
    const double C = - side.first.x * A - side.first.y * B;

    return sq(A * point.x + B * point.y + C)/(sq(A) + sq(B));
}

bool isInside(const Point& point, const Side& nearestSide, double distToSideSq) {
    Vector sideVector = {
        nearestSide.second.x - nearestSide.first.x,
        nearestSide.second.y - nearestSide.first.y
    };

    double mod = sqrt(getDistSq(nearestSide.first, nearestSide.second));
    double distFromP1 = sqrt(getDistSq(point, nearestSide.first) - distToSideSq);

    Point nearestPoint = {
        nearestSide.first.x + sideVector.x / mod * distFromP1,
        nearestSide.first.y + sideVector.y / mod * distFromP1
    };

    Vector vectorToNearestPoint = {
        nearestPoint.x - point.x,
        nearestPoint.y - point.y
    };

    // Координаты вращения вектора против часовой:
    // x' = x * cos(t) - y * sin(t)
    // y' = x * sin(t) + y * cos(t)
    // Повернуть нужно на 90 по часовой (нормаль наружу), т.е. на 270 против часовой
    // sin(270) = -1
    // cos(270) = 0

    Vector normalToSide = {
        sideVector.y,
        -sideVector.x
    };

    double scalar = normalToSide.x * vectorToNearestPoint.x + normalToSide.y * vectorToNearestPoint.y;

    return scalar > 0;
}

int main()
{
    Point hitPoint;
    cin >> hitPoint.x;
    cin >> hitPoint.y;

    unsigned short N;
    cin >> N;

    vector<Point> polygon(N);
    for (unsigned short i = 0; i < N; ++i) {
        cin >> polygon[i].x;
        cin >> polygon[i].y;
    }

    const double MAX_DIST_SQ = getDistSq({-2000, -2000}, {2000, 2000});
    double minDistToPointSq = MAX_DIST_SQ;
    Point nearestPoint;

    for (const auto& p : polygon) {
        double distSq = getDistSq(hitPoint, p);
        if (distSq < minDistToPointSq) {
            minDistToPointSq = distSq;
            nearestPoint = p;
        }
    }

    double minDistToSideSq = MAX_DIST_SQ;
    Side nearestSide;

    for (unsigned short i = 0; i < N; ++i) {
        const Side side{i == 0 ? polygon.back() : polygon[i - 1], polygon[i]};

        if (isAside(hitPoint, side)) {
            continue;
        }

        double distSq = getDistSq(hitPoint, side);
        if (distSq < minDistToSideSq) {
            minDistToSideSq = distSq;
            nearestSide = side;
        }
    }

    const double res = minDistToPointSq < minDistToSideSq
        ? 2 * sqrt(minDistToPointSq)
        : isInside(hitPoint, nearestSide, minDistToSideSq)
            ? 0 : 2 * sqrt(minDistToSideSq);

    printf("%.3f\n", res);

    return 0;
}
