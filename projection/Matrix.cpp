#include "Matrix.h"
#include <stdexcept>

Matrix operator*(const Matrix& a, const Matrix& b)
{
  if(a.mC != b.mR)
    throw std::runtime_error("Dimension mismatch.");

  int rows1 = a.mR;
  int cols1 = a.mC;
  int cols2 = b.mC;

  Matrix result(rows1, cols2);

  for (int k = 0; k < rows1; k++)
    for (int i = 0; i < cols2; i++)
      for (int j = 0; j < cols1; j++)
	result.at(k, i) += a.at(k, j) * b.at(j, i);

  return result;
}

Point operator*(const Matrix& m, const Point& p)
{
  Point r;

  r.x = m.at(0,0)*p.x + m.at(0,1)*p.y + m.at(0,2)*p.z + m.at(0,3)*p.w;
  r.y = m.at(1,0)*p.x + m.at(1,1)*p.y + m.at(1,2)*p.z + m.at(1,3)*p.w;
  r.z = m.at(2,0)*p.x + m.at(2,1)*p.y + m.at(2,2)*p.z + m.at(2,3)*p.w;
  r.w = m.at(3,0)*p.x + m.at(3,1)*p.y + m.at(3,2)*p.z + m.at(3,3)*p.w;
  
  return r;
}
