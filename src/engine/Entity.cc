
#include "Entity.h"
#include <cmath>

Entity::Entity(int x, int y) : pos(x, y), radius(10) {
}

void Entity::move(Vector<int> input, Map map) {

    if (input.x == 0 && input.y == 0) return;

    Vector<int> pos = this->pos.add(input);

    printf("\nmotion: %d, %d\n", input.x, input.y);

    int rad = this->radius ? this->radius : 1;

    for (MapSegment wall : map.segments) {
        LineSegment<int> segment(map.points[wall.a], map.points[wall.b]);
        bool endpoint;
        double dist = segment.dist(pos, endpoint);
        if (dist < rad) {
            if (endpoint) {
                // if we hit the endpoint and the input is not parallel to the vector,
                // don't bother correcting (because we're going right past it)
                double angle_diff = std::abs(segment.v1.sub(segment.v2).angle() - input.angle());
                if (angle_diff > M_PI_4 && angle_diff < 3 * M_PI_4) {
                    continue;
                }
            }
            int side = segment.side(this->pos);
            printf("side: %d\n", side);
            Vector<double> normal = segment.normal(side).normalise();
            printf("normal: %f, %f\n", normal.x, normal.y);
            // correct position
            pos = pos.add(normal.scale(rad - dist + 1).toInt());
        }
    }
    // printf("final: %d, %d\n", input.x, input.y);
    this->pos = pos;
}

