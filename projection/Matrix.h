class Point
{
 public:
  float x;
  float y;
  float z;
  float w;

  Point(float px = 0, float py = 0, float pz = 0, float pw = 1) : x(px), y(py), z(pz), w(pw) {}
  Point(const Point& p) : x(p.x), y(p.y), z(p.z), w(p.w) {}
  Point& operator=(const Point& p) { x = p.x; y = p.y; z = p.z; w = p.w; }

  void normalize()
  {
    x /= -w;
    y /= -w;
    z /= -w;
    w /= -w;
  }
    
  Point operator+(const Point& p) const { return Point(x + p.x, y + p.y, z + p.z, w + p.w); }
  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y, z - p.z, w - p.w); }
};

class Matrix
{
 private:
  float* mData;
  int mR;
  int mC;

 public:
  Matrix() : mR(0), mC(0)  {}
  Matrix(int r, int c) : mR(r), mC(c), mData(new float[mR*mC])  {}

  Matrix& operator=(Matrix& m) { mR = m.mR; mC = m.mC; delete[] mData; mData = new float[mR*mC]; }
  Matrix& operator=(Matrix m) { mR = m.mR; mC = m.mC; delete[] mData; mData = new float[mR*mC]; }

  float& at(int i, int j) const { return mData[i*mR + j]; }
  //  float& operator()(int i, int j) const { return mData[i*mR + j]; }

  friend Point operator*(const Matrix& m, const Point& p);
  friend Matrix operator*(const Matrix& a, const Matrix& b);
};
