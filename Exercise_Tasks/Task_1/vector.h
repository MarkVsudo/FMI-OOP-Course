#pragma once

// 3d vector -> (x,y,z)
struct Vector
{
  double x, y, z;
};

void createVector(Vector &vector);

void printVector(const Vector &vector);

Vector addVectors(const Vector &vector1, const Vector &vector2);

Vector subtractVectors(const Vector &vector1, const Vector &vector2);

Vector multiplyVectorByScalar(const Vector &vector, double scalar);

double findScalarProduct(const Vector &vector1, const Vector &vector2);