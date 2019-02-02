#include <iostream>
#include <ostream>

#include "goinglogging/goinglogging.h"
#include "test/test.h"

#define PERM(n, p) \
    for (gl::prefix (n) = gl::prefix::NONE; (n) <= (p); \
        (n) = static_cast<gl::prefix>(static_cast<uint32_t>((n)) + \
                                      static_cast<uint32_t>((p))))

int main(int argc, const char** argv) {
    if (argc != 1) {
        std::cout << "Usage: " << *argv << std::endl;
        return EXIT_SUCCESS;
    }

    test t;
    t.setup(__FILE__);

    // Outputs
    int i       = 0;
    int a[1]    = {0};
    int m[1][1] = {{0}};

    // Test all combinations
    PERM(fi, gl::prefix::FILE) {
        PERM(l, gl::prefix::LINE) {
            PERM(fu, gl::prefix::FUNCTION) {
                PERM(ti, gl::prefix::TIME) {
                    PERM(th, gl::prefix::THREAD) {
                        PERM(tn, gl::prefix::TYPE_NAME) {
                            gl::prefix p = (fi | l | fu | ti | th | tn);
                            gl::set_prefixes(p);
                            if (p != gl::get_prefixes()) {
                                std::cout << "Failed to set prefixes" << std::endl;
                                return EXIT_FAILURE;
                            }
                            l(i);
                            l_arr(a, 1);
                            l_mat(m, 1, 1);
                        }
                    }
                }
            }
        }
    }

    // Test type name output
    //uint8_t     u8  = 8;
    uint16_t    u16 = 16;
    uint32_t    u32 = 32;
    uint64_t    u64 = 64;
    //int8_t      i8  = 8;
    int16_t     i16 = 16;
    int32_t     i32 = 32;
    int64_t     i64 = 64;
    float       f32 = 32.0f;
    double      f64 = 64.0;
    char16_t    c16 = '4';
    char32_t    c32 = '5';
    wchar_t     wc = 'w';
    const char* s1 = "s1";
    std::string s2 = "s2";

    gl::set_prefixes(gl::prefix::TYPE_NAME);

    //l(u8);
    l(u16);
    l(u32);
    l(u64);
    //l(i8);
    l(i16);
    l(i32);
    l(i64);
    l(f32);
    l(f64);
    l(c16);
    l(c32);
    l(wc);
    l(s1);
    l(s2);
    l(/*u8, */u16, u32, u64, /*i8, */i16, i32, i64, f32, f64, c16, c32, wc, s1, s2);

    return t.compare_output(true);
}
