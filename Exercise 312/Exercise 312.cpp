#include <iostream>
#include <algorithm>
#include <map>

const int64_t M = 815730721;
const int64_t phi1_M = 752982204;
const int64_t phi2_M = 231686832;
const int64_t two_phi3_M = 2*71288256;
const int64_t phi_two_phi3_M = 43869696;

int64_t mod_pow(int64_t a, int64_t b, int64_t m) {
  if (b == 0) return 1;
  if (b == 1) return a % m;
  if (b % 2 == 0) return mod_pow(a*a % m, b >> 1, m);
  return a * mod_pow(a, b - 1, m) % m;
}

struct Z_phi2_M_adjoin_sqrt3 { int64_t a, b; };
struct Z_phi_two_phi3_M_adjoin_sqrt3 { int64_t a, b; };

Z_phi2_M_adjoin_sqrt3 operator+(
  const Z_phi2_M_adjoin_sqrt3& lhs,
  const Z_phi2_M_adjoin_sqrt3& rhs)
{
  return {(lhs.a + rhs.a) % phi2_M,
          (lhs.b + rhs.b) % phi2_M};
}

Z_phi_two_phi3_M_adjoin_sqrt3 operator+(
  const Z_phi_two_phi3_M_adjoin_sqrt3& lhs,
  const Z_phi_two_phi3_M_adjoin_sqrt3& rhs)
{
  return {(lhs.a + rhs.a) % phi_two_phi3_M,
          (lhs.b + rhs.b) % phi_two_phi3_M};
}

Z_phi2_M_adjoin_sqrt3 operator*(
  const Z_phi2_M_adjoin_sqrt3& lhs,
  const Z_phi2_M_adjoin_sqrt3& rhs)
{
  return {(lhs.a*rhs.a + 3*lhs.b*rhs.b) % phi2_M,
          (lhs.a*rhs.b + lhs.b*rhs.a) % phi2_M};
}

Z_phi_two_phi3_M_adjoin_sqrt3 operator*(
  const Z_phi_two_phi3_M_adjoin_sqrt3& lhs,
  const Z_phi_two_phi3_M_adjoin_sqrt3& rhs)
{
  return {(lhs.a*rhs.a + 3*lhs.b*rhs.b) % phi_two_phi3_M,
          (lhs.a*rhs.b + lhs.b*rhs.a) % phi_two_phi3_M};
}

Z_phi2_M_adjoin_sqrt3 mod_pow(const Z_phi2_M_adjoin_sqrt3& a, int64_t x) {
  if (x == 0) return {1, 0};
  if (x == 1) return a;
  if (x % 2 == 0) return mod_pow(a * a, x >> 1);
  return a * mod_pow(a, x - 1);
}

Z_phi_two_phi3_M_adjoin_sqrt3 mod_pow(const Z_phi_two_phi3_M_adjoin_sqrt3& a, int64_t x) {
  if (x == 0) return {1, 0};
  if (x == 1) return a;
  if (x % 2 == 0) return mod_pow(a * a, x >> 1);
  return a * mod_pow(a, x - 1);
}

int64_t C_mod_phi_two_phi3_M(int64_t n) {
  const int64_t z1 = mod_pow(3, n-2, 2*phi_two_phi3_M);
  const int64_t z2 = (z1 - 3 + 2*phi_two_phi3_M) % (2*phi_two_phi3_M);
  auto two = Z_phi_two_phi3_M_adjoin_sqrt3{2, 0};
  auto sqrt3 = Z_phi_two_phi3_M_adjoin_sqrt3{0, 1};
  auto res = mod_pow(two, z1) * mod_pow(sqrt3, z2);
  return res.a;
}

int64_t C2_mod_phi2_M(int64_t n) {
  const int64_t x = (C_mod_phi_two_phi3_M(n) - 2 + phi_two_phi3_M) % phi_two_phi3_M;
  const int64_t z1 = mod_pow(3, x, two_phi3_M);
  const int64_t z2 = (z1 - 3 + two_phi3_M) % two_phi3_M;
  auto two = Z_phi2_M_adjoin_sqrt3{2, 0};
  auto sqrt3 = Z_phi2_M_adjoin_sqrt3{0, 1};
  auto res = mod_pow(two, z1) * mod_pow(sqrt3, z2);
  return res.a;
}

// Computes C(C(C(n))) mod M.
int64_t C3_mod_M(int64_t n) {
  const int64_t x = (C2_mod_phi2_M(n) - 2 + phi2_M) % phi2_M;
  const int64_t z1 = mod_pow(3, x, phi1_M);
  const int64_t z2 = (z1 - 3 + phi1_M) % phi1_M;
  
  // 245063243 is sqrt(3) mod M.
  return mod_pow(2, z1, M) * mod_pow(245063243, z2, M) % M;
}

int main() {
  std::cout << C3_mod_M(10000) << '\n';
}