#include <string>
#include <iostream>
#include <fmt/format.h>
#include <cmath>

#include "BigInt.hpp"

BigInt karatsuba(const BigInt& a, const BigInt &b) {
    return a * b;

    if (a < 1000 && b < 1000) {
        return a * b;
    }

    auto sa = a.to_string();
    auto sb = b.to_string();

    auto m = sa.length() / 2;
    auto sa1 = sa.substr(0, m);
    auto sa2 = sa.substr(m);

    auto sbl = sb.length();
    auto sb1 = sb.substr(0, m);
    auto sb2 = sb.substr(m);

    auto z2 = karatsuba(BigInt(sa1), BigInt(sb1));
    auto z0 = karatsuba(BigInt(sa2), BigInt(sb2));
    auto z1 = karatsuba(BigInt(sa1) + BigInt(sa2), BigInt(sb1) + BigInt(sb2)) - z2 - z0;

    auto res =
        z2 * pow(10, 2 * m) +
        z1 * pow(10, m) +
        z0;

    fmt::print("{} * {} = {}\n", sa, sb, res.to_string());

    return res;
}


//int main(int argc, char **argv) {
//    // fmt::print("{}\n", karatsuba(12, 23).to_string()); // 276
//    // fmt::print("{}\n", karatsuba(BigInt("897123897123789123"), BigInt("12378912378912370789123")).to_string()); // 11105418115523781410926397046167354109129
//    fmt::print("{}\n", karatsuba(BigInt("3141592653589793238462643383279502884197169399375105820974944592"), BigInt("2718281828459045235360287471352662497757247093699959574966967627")).to_string());
//}