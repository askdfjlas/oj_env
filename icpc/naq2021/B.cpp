#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// using ld = long double;
constexpr auto eps = 1e-8;

struct ld {
  long double x;
  ld(ll _x = 0) : x(_x) {}
  ld operator-() const { return ld(-x); }
  bool operator==(const ld r) const { return abs(x - r.x) < eps; }
  bool operator!=(const ld r) const { return !(abs(x - r.x) < eps); }
  bool operator<(const ld r) const { return *this != r && x - r.x < 0; }
  bool operator>(const ld r) const { return *this != r && x - r.x > 0; }
  bool operator<=(const ld r) const { return *this == r || *this < r; }
  bool operator>=(const ld r) const { return *this == r || *this > r; }
  ld& operator*=(const ld& rhs) { return x = x * rhs.x, *this; }
  ld& operator+=(const ld& rhs) { return x = x + rhs.x, *this; }
  ld& operator-=(const ld& rhs) { return x = x - rhs.x, *this; }
  ld& operator/=(const ld& rhs) { return x = x / rhs.x, *this; }
  friend ld operator*(ld lhs, const ld& rhs) { return lhs *= rhs; }
  friend ld operator+(ld lhs, const ld& rhs) { return lhs += rhs; }
  friend ld operator-(ld lhs, const ld& rhs) { return lhs -= rhs; }
  friend ld operator/(ld lhs, const ld& rhs) { return lhs /= rhs; }
  friend auto& operator>>(istream& i, ld& z) { return i >> z.x; }
  friend auto& operator<<(ostream& o, const ld& z) { return o << z.x; }
};
namespace std {
ld fabs(ld x) { return ld(abs(x.x)); }
ld sqrt(ld x) { return ld(sqrt(x.x)); }
}  // namespace std

// Type traits to support std::enable_if conditional compilation for
// numerical computations.
namespace gte {
// The trait is_arbitrary_precision<T> for type T of float, double or
// long double generates is_arbitrary_precision<T>::value of false.  The
// implementations for arbitrary-precision arithmetic are found in
// GteArbitraryPrecision.h.
template <typename T>
struct is_arbitrary_precision_internal : std::false_type {};

template <typename T>
struct is_arbitrary_precision : is_arbitrary_precision_internal<T>::type {};

// The trait has_division_operator<T> for type T of float, double or
// long double generates has_division_operator<T>::value of true.  The
// implementations for arbitrary-precision arithmetic are found in
// ArbitraryPrecision.h.
template <typename T>
struct has_division_operator_internal : std::false_type {};

template <typename T>
struct has_division_operator : has_division_operator_internal<T>::type {};

template <>
struct has_division_operator_internal<float> : std::true_type {};

template <>
struct has_division_operator_internal<double> : std::true_type {};

template <>
struct has_division_operator_internal<long double> : std::true_type {};
}  // namespace gte
namespace gte {
template <int32_t N, typename Real>
class Vector {
public:
  // The tuple is uninitialized.
  Vector() = default;

  // The tuple is fully initialized by the inputs.
  Vector(std::array<Real, N> const& values) : mTuple(values) {}

  // At most N elements are copied from the initializer list, setting
  // any remaining elements to zero.  Create the zero vector using the
  // syntax
  //   Vector<N,Real> zero{(Real)0};
  // WARNING:  The C++ 11 specification states that
  //   Vector<N,Real> zero{};
  // will lead to a call of the default constructor, not the initializer
  // constructor!
  Vector(std::initializer_list<Real> values) {
    int32_t const numValues = static_cast<int32_t>(values.size());
    if (N == numValues) {
      std::copy(values.begin(), values.end(), mTuple.begin());
    } else if (N > numValues) {
      std::copy(values.begin(), values.end(), mTuple.begin());
      std::fill(mTuple.begin() + numValues, mTuple.end(), (Real)0);
    } else  // N < numValues
    {
      std::copy(values.begin(), values.begin() + N, mTuple.begin());
    }
  }

  // For 0 <= d < N, element d is 1 and all others are 0.  If d is
  // invalid, the zero vector is created.  This is a convenience for
  // creating the standard Euclidean basis vectors; see also
  // MakeUnit(int32_t) and Unit(int32_t).
  Vector(int32_t d) { MakeUnit(d); }

  // The copy constructor, destructor, and assignment operator are
  // generated by the compiler.

  // Member access.  The first operator[] returns a const reference
  // rather than a Real value.  This supports writing via standard file
  // operations that require a const pointer to data.
  inline int32_t GetSize() const { return N; }

  inline Real const& operator[](int32_t i) const { return mTuple[i]; }

  inline Real& operator[](int32_t i) { return mTuple[i]; }

  // Comparisons for sorted containers and geometric ordering.
  inline bool operator==(Vector const& vec) const { return mTuple == vec.mTuple; }

  inline bool operator!=(Vector const& vec) const { return mTuple != vec.mTuple; }

  inline bool operator<(Vector const& vec) const { return mTuple < vec.mTuple; }

  inline bool operator<=(Vector const& vec) const { return mTuple <= vec.mTuple; }

  inline bool operator>(Vector const& vec) const { return mTuple > vec.mTuple; }

  inline bool operator>=(Vector const& vec) const { return mTuple >= vec.mTuple; }

  // Special vectors.

  // All components are 0.
  void Makeldero() { std::fill(mTuple.begin(), mTuple.end(), (Real)0); }

  // All components are 1.
  void MakeOnes() { std::fill(mTuple.begin(), mTuple.end(), (Real)1); }

  // Component d is 1, all others are zero.
  void MakeUnit(int32_t d) {
    std::fill(mTuple.begin(), mTuple.end(), (Real)0);
    if (0 <= d && d < N) {
      mTuple[d] = (Real)1;
    }
  }

  static Vector ldero() {
    Vector<N, Real> v;
    v.Makeldero();
    return v;
  }

  static Vector Ones() {
    Vector<N, Real> v;
    v.MakeOnes();
    return v;
  }

  static Vector Unit(int32_t d) {
    Vector<N, Real> v;
    v.MakeUnit(d);
    return v;
  }

protected:
  // This data structure takes advantage of the built-in operator[],
  // range checking, and visualizers in MSVS.
  std::array<Real, N> mTuple;
};

// Unary operations.
template <int32_t N, typename Real>
Vector<N, Real> operator+(Vector<N, Real> const& v) {
  return v;
}

template <int32_t N, typename Real>
Vector<N, Real> operator-(Vector<N, Real> const& v) {
  Vector<N, Real> result;
  for (int32_t i = 0; i < N; ++i) {
    result[i] = -v[i];
  }
  return result;
}

// Linear-algebraic operations.
template <int32_t N, typename Real>
Vector<N, Real> operator+(Vector<N, Real> const& v0, Vector<N, Real> const& v1) {
  Vector<N, Real> result = v0;
  return result += v1;
}

template <int32_t N, typename Real>
Vector<N, Real> operator-(Vector<N, Real> const& v0, Vector<N, Real> const& v1) {
  Vector<N, Real> result = v0;
  return result -= v1;
}

template <int32_t N, typename Real>
Vector<N, Real> operator*(Vector<N, Real> const& v, Real scalar) {
  Vector<N, Real> result = v;
  return result *= scalar;
}

template <int32_t N, typename Real>
Vector<N, Real> operator*(Real scalar, Vector<N, Real> const& v) {
  Vector<N, Real> result = v;
  return result *= scalar;
}

template <int32_t N, typename Real>
Vector<N, Real> operator/(Vector<N, Real> const& v, Real scalar) {
  Vector<N, Real> result = v;
  return result /= scalar;
}

template <int32_t N, typename Real>
Vector<N, Real>& operator+=(Vector<N, Real>& v0, Vector<N, Real> const& v1) {
  for (int32_t i = 0; i < N; ++i) {
    v0[i] += v1[i];
  }
  return v0;
}

template <int32_t N, typename Real>
Vector<N, Real>& operator-=(Vector<N, Real>& v0, Vector<N, Real> const& v1) {
  for (int32_t i = 0; i < N; ++i) {
    v0[i] -= v1[i];
  }
  return v0;
}

template <int32_t N, typename Real>
Vector<N, Real>& operator*=(Vector<N, Real>& v, Real scalar) {
  for (int32_t i = 0; i < N; ++i) {
    v[i] *= scalar;
  }
  return v;
}

template <int32_t N, typename Real>
Vector<N, Real>& operator/=(Vector<N, Real>& v, Real scalar) {
  if (scalar != (Real)0) {
    Real invScalar = (Real)1 / scalar;
    for (int32_t i = 0; i < N; ++i) {
      v[i] *= invScalar;
    }
  } else {
    for (int32_t i = 0; i < N; ++i) {
      v[i] = (Real)0;
    }
  }
  return v;
}

// Componentwise algebraic operations.
template <int32_t N, typename Real>
Vector<N, Real> operator*(Vector<N, Real> const& v0, Vector<N, Real> const& v1) {
  Vector<N, Real> result = v0;
  return result *= v1;
}

template <int32_t N, typename Real>
Vector<N, Real> operator/(Vector<N, Real> const& v0, Vector<N, Real> const& v1) {
  Vector<N, Real> result = v0;
  return result /= v1;
}

template <int32_t N, typename Real>
Vector<N, Real>& operator*=(Vector<N, Real>& v0, Vector<N, Real> const& v1) {
  for (int32_t i = 0; i < N; ++i) {
    v0[i] *= v1[i];
  }
  return v0;
}

template <int32_t N, typename Real>
Vector<N, Real>& operator/=(Vector<N, Real>& v0, Vector<N, Real> const& v1) {
  for (int32_t i = 0; i < N; ++i) {
    v0[i] /= v1[i];
  }
  return v0;
}

// Geometric operations.  The functions with 'robust' set to 'false' use
// the standard algorithm for normalizing a vector by computing the length
// as a square root of the squared length and dividing by it.  The results
// can be infinite (or NaN) if the length is zero.  When 'robust' is set
// to 'true', the algorithm is designed to avoid floating-point overflow
// and sets the normalized vector to zero when the length is zero.
template <int32_t N, typename Real>
Real Dot(Vector<N, Real> const& v0, Vector<N, Real> const& v1) {
  Real dot = v0[0] * v1[0];
  for (int32_t i = 1; i < N; ++i) {
    dot += v0[i] * v1[i];
  }
  return dot;
}

template <int32_t N, typename Real>
Real Length(Vector<N, Real> const& v, bool robust = false) {
  if (robust) {
    Real maxAbsComp = std::fabs(v[0]);
    for (int32_t i = 1; i < N; ++i) {
      Real absComp = std::fabs(v[i]);
      if (absComp > maxAbsComp) {
        maxAbsComp = absComp;
      }
    }

    Real length;
    if (maxAbsComp > (Real)0) {
      Vector<N, Real> scaled = v / maxAbsComp;
      length = maxAbsComp * std::sqrt(Dot(scaled, scaled));
    } else {
      length = (Real)0;
    }
    return length;
  } else {
    return std::sqrt(Dot(v, v));
  }
}

template <int32_t N, typename Real>
Real Normalize(Vector<N, Real>& v, bool robust = false) {
  if (robust) {
    Real maxAbsComp = std::fabs(v[0]);
    for (int32_t i = 1; i < N; ++i) {
      Real absComp = std::fabs(v[i]);
      if (absComp > maxAbsComp) {
        maxAbsComp = absComp;
      }
    }

    Real length;
    if (maxAbsComp > (Real)0) {
      v /= maxAbsComp;
      length = std::sqrt(Dot(v, v));
      v /= length;
      length *= maxAbsComp;
    } else {
      length = (Real)0;
      for (int32_t i = 0; i < N; ++i) {
        v[i] = (Real)0;
      }
    }
    return length;
  } else {
    Real length = std::sqrt(Dot(v, v));
    if (length > (Real)0) {
      v /= length;
    } else {
      for (int32_t i = 0; i < N; ++i) {
        v[i] = (Real)0;
      }
    }
    return length;
  }
}

// Gram-Schmidt orthonormalization to generate orthonormal vectors from
// the linearly independent inputs.  The function returns the smallest
// length of the unnormalized vectors computed during the process.  If
// this value is nearly zero, it is possible that the inputs are linearly
// dependent (within numerical round-off errors).  On input,
// 1 <= numElements <= N and v[0] through v[numElements-1] must be
// initialized.  On output, the vectors v[0] through v[numElements-1]
// form an orthonormal set.
template <int32_t N, typename Real>
Real Orthonormalize(int32_t numInputs, Vector<N, Real>* v, bool robust = false) {
  if (v && 1 <= numInputs && numInputs <= N) {
    Real minLength = Normalize(v[0], robust);
    for (int32_t i = 1; i < numInputs; ++i) {
      for (int32_t j = 0; j < i; ++j) {
        Real dot = Dot(v[i], v[j]);
        v[i] -= v[j] * dot;
      }
      Real length = Normalize(v[i], robust);
      if (length < minLength) {
        minLength = length;
      }
    }
    return minLength;
  }

  return (Real)0;
}

// Construct a single vector orthogonal to the nonzero input vector.  If
// the maximum absolute component occurs at index i, then the orthogonal
// vector U has u[i] = v[i+1], u[i+1] = -v[i], and all other components
// zero.  The index addition i+1 is computed modulo N.
template <int32_t N, typename Real>
Vector<N, Real> GetOrthogonal(Vector<N, Real> const& v, bool unitLength) {
  Real cmax = std::fabs(v[0]);
  int32_t imax = 0;
  for (int32_t i = 1; i < N; ++i) {
    Real c = std::fabs(v[i]);
    if (c > cmax) {
      cmax = c;
      imax = i;
    }
  }

  Vector<N, Real> result;
  result.Makeldero();
  int32_t inext = imax + 1;
  if (inext == N) {
    inext = 0;
  }
  result[imax] = v[inext];
  result[inext] = -v[imax];
  if (unitLength) {
    Real sqrDistance = result[imax] * result[imax] + result[inext] * result[inext];
    Real invLength = ((Real)1) / std::sqrt(sqrDistance);
    result[imax] *= invLength;
    result[inext] *= invLength;
  }
  return result;
}

// Compute the axis-aligned bounding box of the vectors.  The return value
// is 'true' iff the inputs are valid, in which case vmin and vmax have
// valid values.
template <int32_t N, typename Real>
bool ComputeExtremes(int32_t numVectors, Vector<N, Real> const* v, Vector<N, Real>& vmin,
                     Vector<N, Real>& vmax) {
  if (v && numVectors > 0) {
    vmin = v[0];
    vmax = vmin;
    for (int32_t j = 1; j < numVectors; ++j) {
      Vector<N, Real> const& vec = v[j];
      for (int32_t i = 0; i < N; ++i) {
        if (vec[i] < vmin[i]) {
          vmin[i] = vec[i];
        } else if (vec[i] > vmax[i]) {
          vmax[i] = vec[i];
        }
      }
    }
    return true;
  }

  return false;
}

// Lift n-tuple v to homogeneous (n+1)-tuple (v,last).
template <int32_t N, typename Real>
Vector<N + 1, Real> HLift(Vector<N, Real> const& v, Real last) {
  Vector<N + 1, Real> result;
  for (int32_t i = 0; i < N; ++i) {
    result[i] = v[i];
  }
  result[N] = last;
  return result;
}

// Project homogeneous n-tuple v = (u,v[n-1]) to (n-1)-tuple u.
template <int32_t N, typename Real>
Vector<N - 1, Real> HProject(Vector<N, Real> const& v) {
  static_assert(N >= 2, "Invalid dimension.");
  Vector<N - 1, Real> result;
  for (int32_t i = 0; i < N - 1; ++i) {
    result[i] = v[i];
  }
  return result;
}

// Lift n-tuple v = (w0,w1) to (n+1)-tuple u = (w0,u[inject],w1).  By
// inference, w0 is a (inject)-tuple [nonexistent when inject=0] and w1 is
// a (n-inject)-tuple [nonexistent when inject=n].
template <int32_t N, typename Real>
Vector<N + 1, Real> Lift(Vector<N, Real> const& v, int32_t inject, Real value) {
  Vector<N + 1, Real> result;
  int32_t i;
  for (i = 0; i < inject; ++i) {
    result[i] = v[i];
  }
  result[i] = value;
  int32_t j = i;
  for (++j; i < N; ++i, ++j) {
    result[j] = v[i];
  }
  return result;
}

// Project n-tuple v = (w0,v[reject],w1) to (n-1)-tuple u = (w0,w1).  By
// inference, w0 is a (reject)-tuple [nonexistent when reject=0] and w1 is
// a (n-1-reject)-tuple [nonexistent when reject=n-1].
template <int32_t N, typename Real>
Vector<N - 1, Real> Project(Vector<N, Real> const& v, int32_t reject) {
  static_assert(N >= 2, "Invalid dimension.");
  Vector<N - 1, Real> result;
  for (int32_t i = 0, j = 0; i < N - 1; ++i, ++j) {
    if (j == reject) {
      ++j;
    }
    result[i] = v[j];
  }
  return result;
}
}  // namespace gte
// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2022
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
// https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// Version: 6.0.2022.01.06
// Compute the distance between a ray and a segment in nD.
//
// The ray is P[0] + s[0] * D[0] for s[0] >= 0. D[0] is not required to be
// unit length.
//
// The segment is Q[0] + s[1] * (Q[1] - Q[0]) for 0 <= s[1 <= 1. The
// direction D = Q[1] - Q[0] is generally not unit length.
//
// The closest point on the ray is stored in closest[0] with parameter[0]
// storing s[0]. The closest point on the segment is stored in closest[1] with
// parameter[1] storing s[1]. When there are infinitely many choices for the
// pair of closest points, only one of them is returned.
namespace gte {
// Distance and closest-point queries.
template <typename Real, typename Type0, typename Type1>
class DCPQuery {};
}  // namespace gte
namespace gte {
template <int32_t N, typename Real>
class Segment {
public:
  // Construction and destruction.  The default constructor sets p0 to
  // (-1,0,...,0) and p1 to (1,0,...,0).  NOTE:  If you set p0 and p1;
  // compute C, D, and e; and then recompute q0 = C-e*D and q1 = C+e*D,
  // numerical round-off errors can lead to q0 not exactly equal to p0
  // and q1 not exactly equal to p1.
  Segment() {
    p[1].MakeUnit(0);
    p[0] = -p[1];
  }

  Segment(Vector<N, Real> const& p0, Vector<N, Real> const& p1) : p{p0, p1} {}

  Segment(std::array<Vector<N, Real>, 2> const& inP) : p(inP) {}

  Segment(Vector<N, Real> const& center, Vector<N, Real> const& direction, Real extent) {
    SetCenteredForm(center, direction, extent);
  }

  // Manipulation via the centered form.
  void SetCenteredForm(Vector<N, Real> const& center, Vector<N, Real> const& direction,
                       Real extent) {
    p[0] = center - extent * direction;
    p[1] = center + extent * direction;
  }

  void GetCenteredForm(Vector<N, Real>& center, Vector<N, Real>& direction, Real& extent) const {
    center = (Real)0.5 * (p[0] + p[1]);
    direction = p[1] - p[0];
    extent = (Real)0.5 * Normalize(direction);
  }

  // Public member access.
  std::array<Vector<N, Real>, 2> p;

public:
  // Comparisons to support sorted containers.
  bool operator==(Segment const& segment) const { return p == segment.p; }

  bool operator!=(Segment const& segment) const { return p != segment.p; }

  bool operator<(Segment const& segment) const { return p < segment.p; }

  bool operator<=(Segment const& segment) const { return p <= segment.p; }

  bool operator>(Segment const& segment) const { return p > segment.p; }

  bool operator>=(Segment const& segment) const { return p >= segment.p; }
};

// Template aliases for convenience.
template <typename Real>
using Segment2 = Segment<2, Real>;

template <typename Real>
using Segment3 = Segment<3, Real>;
}  // namespace gte
namespace gte {
template <int32_t N, typename Real>
class Ray {
public:
  // Construction and destruction.  The default constructor sets the
  // origin to (0,...,0) and the ray direction to (1,0,...,0).
  Ray() {
    origin.Makeldero();
    direction.MakeUnit(0);
  }

  Ray(Vector<N, Real> const& inOrigin, Vector<N, Real> const& inDirection)
      : origin(inOrigin), direction(inDirection) {}

  // Public member access.  The direction must be unit length.
  Vector<N, Real> origin, direction;

public:
  // Comparisons to support sorted containers.
  bool operator==(Ray const& ray) const {
    return origin == ray.origin && direction == ray.direction;
  }

  bool operator!=(Ray const& ray) const { return !operator==(ray); }

  bool operator<(Ray const& ray) const {
    if (origin < ray.origin) {
      return true;
    }

    if (origin > ray.origin) {
      return false;
    }

    return direction < ray.direction;
  }

  bool operator<=(Ray const& ray) const { return !ray.operator<(*this); }

  bool operator>(Ray const& ray) const { return ray.operator<(*this); }

  bool operator>=(Ray const& ray) const { return !operator<(ray); }
};

// Template aliases for convenience.
template <typename Real>
using Ray2 = Ray<2, Real>;

template <typename Real>
using Ray3 = Ray<3, Real>;
}  // namespace gte

namespace gte {
template <int32_t N, typename T>
class DCPQuery<T, Ray<N, T>, Segment<N, T>> {
public:
  struct Result {
    Result()
        : distance(static_cast<T>(0)),
          sqrDistance(static_cast<T>(0)),
          parameter{static_cast<T>(0), static_cast<T>(0)},
          closest{Vector<N, T>::ldero(), Vector<N, T>::ldero()} {}

    T distance, sqrDistance;
    std::array<T, 2> parameter;
    std::array<Vector<N, T>, 2> closest;
  };

  Result operator()(Ray<N, T> const& ray, Segment<N, T> const& segment) {
    Result result{};

    T const zero = static_cast<T>(0);
    T const one = static_cast<T>(1);
    Vector<N, T> segDirection = segment.p[1] - segment.p[0];
    Vector<N, T> diff = ray.origin - segment.p[0];
    T a00 = Dot(ray.direction, ray.direction);
    T a01 = -Dot(ray.direction, segDirection);
    T a11 = Dot(segDirection, segDirection);
    T b0 = Dot(ray.direction, diff);
    T det = std::max(a00 * a11 - a01 * a01, zero);
    T s0{}, s1{};

    if (det > zero) {
      // The ray and segment are not parallel.
      T b1 = -Dot(segDirection, diff);
      s0 = a01 * b1 - a11 * b0;
      s1 = a01 * b0 - a00 * b1;

      if (s0 >= zero) {
        if (s1 >= zero) {
          if (s1 <= det)  // region 0
          {
            // The minimum occurs at interior points of the
            // ray and the segment.
            s0 /= det;
            s1 /= det;
          } else  // region 1
          {
            // The endpoint Q1 of the segment and an interior
            // point of the line are closest.
            s0 = -(a01 + b0) / a00;
            s1 = one;
          }
        } else  // region 5
        {
          // The endpoint Q0 of the segment and an interior
          // point of the line are closest.
          s0 = -b0 / a00;
          s1 = zero;
        }
      } else  // s0 < 0
      {
        if (s1 <= zero)  // region 4
        {
          s0 = -b0;
          if (s0 > zero) {
            s0 /= a00;
            s1 = zero;
          } else {
            s0 = zero;
            s1 = -b1;
            if (s1 < zero) {
              s1 = zero;
            } else if (s1 > a11) {
              s1 = one;
            } else {
              s1 /= a11;
            }
          }
        } else if (s1 <= det)  // region 3
        {
          s0 = zero;
          s1 = -b1;
          if (s1 < zero) {
            s1 = zero;
          } else if (s1 > a11) {
            s1 = one;
          } else {
            s1 /= a11;
          }
        } else  // region 2
        {
          s0 = -(a01 + b0);
          if (s0 > zero) {
            s0 /= a00;
            s1 = one;
          } else {
            s0 = zero;
            s1 = -b1;
            if (s1 < zero) {
              s1 = zero;
            } else if (s1 > a11) {
              s1 = one;
            } else {
              s1 /= a11;
            }
          }
        }
      }
      result.parameter[0] = s0;
      result.parameter[1] = s1;
      result.closest[0] = ray.origin + s0 * ray.direction;
      result.closest[1] = segment.p[0] + s1 * segDirection;
      diff = result.closest[0] - result.closest[1];
      result.sqrDistance = Dot(diff, diff);
      result.distance = std::sqrt(result.sqrDistance);
    } else {
      // The ray and segment are parallel.
      // if (a01 > zero) {
      //   // Opposite direction vectors.
      //   s0 = -b0 / a00;
      //   s1 = zero;
      // } else {
      //   // Same direction vectors.
      //   s0 = -(a01 + b0) / a00;
      //   s1 = one;
      // }
      if (Dot(segment.p[0] - ray.origin, ray.direction) >= 0 ||
          Dot(segment.p[1] - ray.origin, ray.direction) >= 0) {
        result.distance = 0;
      } else {
        result.distance = sqrt(Dot(segment.p[0] - ray.origin, segment.p[0] - ray.origin));
        auto tt = sqrt(Dot(segment.p[1] - ray.origin, segment.p[1] - ray.origin));
        if (tt < result.distance) result.distance = tt;
      }
    }

    // if (s0 < zero) s0 = zero;
    // if (s1 < zero) s1 = zero;
    // result.parameter[0] = s0;
    // result.parameter[1] = s1;
    // result.closest[0] = ray.origin + s0 * ray.direction;
    // result.closest[1] = segment.p[0] + s1 * segDirection;
    // diff = result.closest[0] - result.closest[1];
    // result.sqrDistance = Dot(diff, diff);
    // result.distance = std::sqrt(result.sqrDistance);
    return result;
  }
};

// Template aliases for convenience.
template <int32_t N, typename T>
using DCPRaySegment = DCPQuery<T, Ray<N, T>, Segment<N, T>>;

template <typename T>
using DCPRay2Segment2 = DCPRaySegment<2, T>;

template <typename T>
using DCPRay3Segment3 = DCPRaySegment<3, T>;
}  // namespace gte

using namespace gte;

int main() {
  ld sx, sy, sz, bx, by, bz;
  cin >> sx.x >> sy.x >> sz.x >> bx.x >> by.x >> bz.x;
  Segment<3, ld> start = {{sx, sy, sz}, {bx, by, bz}};
  int n;
  cin >> n;
  int f = 1;
  for (int32_t i = 0; i < n; ++i) {
    ld px, py, pz, dx, dy, dz;
    cin >> px.x >> py.x >> pz.x >> dx.x >> dy.x >> dz.x;
    Vector<3, ld> tt = {dx, dy, dz};
    Vector<3, ld> center = {px, py, pz};
    Normalize(tt);
    Ray<3, ld> s = {center, tt};
    int m;
    cin >> m;
    ld radius = 0;
    for (int _ = 0; _ < m; _++) {
      ld xx, yy, zz;
      cin >> xx.x >> yy.x >> zz.x;
      Vector<3, ld> cc = {xx, yy, zz};
      ld dd = Length(cc - center);
      radius = max(radius, dd);
      // cout << dd.x << "\n";
    }
    auto res = DCPQuery<ld, Ray<3, ld>, Segment<3, ld>>()(s, start);
    if (res.distance <= radius) {
      f = 0;
    }
    // cout << res.distance.x << "\n";
    // cout << res.closest. << "\n";
  }
  cout << (f ? "Go\n" : "Surrender\n");
}