/**
 * base-n, 1.0
 * Copyright (C) 2012 Andrzej Zawadzki (azawadzki@gmail.com)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/
#include <cassert>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>

#include "basen.hpp"

int main()
{
    using namespace std;
    string in = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
    cout << in << endl;

    {
        string encoded;
        bn::encode_b64(in.begin(), in.end(), back_inserter(encoded));
        bn::decode_b64(encoded.begin(), encoded.end(), ostream_iterator<char>(cout, ""));
        cout << endl;
    }
    {
        string encoded;
        bn::encode_b32(in.begin(), in.end(), back_inserter(encoded));
        bn::decode_b32(encoded.begin(), encoded.end(), ostream_iterator<char>(cout, ""));
        cout << endl;
    }
    {
        string encoded;
        bn::encode_b16(in.begin(), in.end(), back_inserter(encoded));
        bn::decode_b16(encoded.begin(), encoded.end(), ostream_iterator<char>(cout, ""));
        cout << endl;
    }
    {
        string encoded = "#TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz\n"
            "IHNpbmd1bGFyIHBhc3Npb24gZnJvbS@BvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg\n"
            " dGhlIG1(pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu\n"
            "\rdWVkIGFuZCBpbmRlZmF0aWdhY*mxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo\n"
            "ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4";
        bn::decode_b64(encoded.begin(), encoded.end(), ostream_iterator<char>(cout, ""));
        cout << endl;
    }
    {
        // move the struct definition outside of main() for non-C++11 compilers
        struct b8_custom
        {
            static size_t group_length()
            {
               return 3;
            }

            static char encode(unsigned int index)
            {
                const char* const dictionary = "01234567";
                assert(index < strlen(dictionary));
                return dictionary[index];
            }

            static char decode(char c)
            {
                if (c >= '0' && c <= '7') {
                    return c - '0';
                }
                return -1;
            }
        };
        string encoded;
        bn::impl::encode<b8_custom>(in.begin(), in.end(), back_inserter(encoded));
        bn::impl::decode<b8_custom>(encoded.begin(), encoded.end(), ostream_iterator<char>(cout, ""));
        cout << endl;
    }
}

