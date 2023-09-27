#ifndef GB_ASSEMBLER_TESTS_H
#define GB_ASSEMBLER_TESTS_H

#include <vector>
#include <cstdint>
#include "../src/Lexer.hpp"

void testAllBasicOperation();

struct OpTest {
    std::string op;
    std::vector<Token> tokens;
    std::vector<uint8_t> bin;
};

std::vector<OpTest> vectorOpTest = {
        {
            "NOP",
            {
                {OP, "NOP"}
            },
            {0x00}
        },

        {
            "LD BC,$ABCD",
            {
                {OP, "LD"},
                {R16, "BC"},
                {COM, ","},
                {NUM, "43981"}
            },
            {0x01, 0xCD, 0xAB}
        },

        {
            "LD [BC], A",
            {
                {OP, "LD"},
                {LBR, "["},
                {R16, "BC"},
                {RBR, "]"},
                {COM, ","},
                {R8,  "A"}
            },
            {0x02}
        },

        {
            "INC BC",
            {
                {OP, "INC"},
                {R16, "BC"}
            },
            {0x03}
        },

        {
            "INC B",
            {
                {OP, "INC"},
                {R8,  "B"}
            },
            {0x04}
        },

        {
            "DEC B",
            {
                {OP, "DEC"},
                {R8,  "B"}
            },
            {0x05}
        },

        {
            "LD B, 27",
            {
                {OP, "LD"},
                {R8,  "B"},
                {COM, ","},
                {NUM, "27"}
            },
            {0x06, 0x1B}
        },

        {
            "RLCA",
            {
                {OP, "RLCA"}
            },
            {0x07}
        },

        {
            "LD [$ABCD], SP",
            {
                {OP, "LD"},
                {LBR, "["},
                {NUM, "43981"},
                {RBR, "]"},
                {COM, ","},
                {R16, "SP"}
            },
            {0x08, 0xCD, 0xAB}
        },

        {
            "ADD HL, BC",
            {
                {OP, "ADD"},
                {R16, "HL"},
                {COM, ","},
                {R16, "BC"}
            },
            {0x09}
        },

        {
            "LD A, [BC]",
            {
                {OP, "LD"},
                {R8,  "A"},
                {COM, ","},
                {LBR, "["},
                {R16, "BC"},
                {RBR, "]"}
            },
            {0x0A}
        },

        {
            "DEC BC",
            {
                {OP, "DEC"},
                {R16, "BC"}
            },
            {0x0B}
        },

        {
            "INC C",
            {
                {OP, "INC"},
                {R8,  "C"}
            },
            {0x0C}
        },

        {
            "DEC C",
            {
                {OP, "DEC"},
                {R8,  "C"}
            },
            {0x0D}
        },

        {
            "LD C, 27",
            {
                {OP, "LD"},
                {R8,  "C"},
                {COM, ","},
                {NUM, "27"}
            },
            {0x0E, 0x1B}
        },

        {
            "RRCA",
            {
                {OP, "RRCA"}
            },
            {0x0F}
        },

        {
            "STOP",
            {
                {OP, "STOP"}
            },
            {0x10, 0x00}
        },

        {
            "LD DE, $ABCD",
            {
                {OP, "LD"},
                {R16, "DE"},
                {COM, ","},
                {NUM, "43981"}
            },
            {0x11, 0xCD, 0xAB}
        },

        {
            "LD [DE], A",
            {
                {OP, "LD"},
                {LBR, "["},
                {R16, "DE"},
                {RBR, "]"},
                {COM, ","},
                {R8, "A"}
            },
            {0x12}
        },

        {
            "INC DE",
            {
                {OP, "INC"},
                {R16, "DE"}
            },
            {0x13}
        },

        {
            "INC D",
            {
                {OP, "INC"},
                {R8, "D"}
            },
            {0x14}
        },

        {
            "DEC D",
            {
                {OP, "DEC"},
                {R8, "D"}
            },
            {0x15}
        },

        {
            "LD D, 9",
            {
                {OP, "LD"},
                {R8, "D"},
                {COM, ","},
                {NUM, "9"}
            },
            {0x16, 0x09}
        },

        {
            "RLA",
            {
                {OP, "RLA"}
            },
            {0x17}
        },

        {
            "JR 12",
            {
                {OP, "JR"},
                {NUM, "12"}
            },
            {0x18, 0x0C}
        },

        {
            "ADD HL, DE",
            {
                {OP, "ADD"},
                {R16, "HL"},
                {COM, ","},
                {R16, "DE"}
            },
            {0x19}
        },

        {
            "LD A, [DE]",
            {
                {OP, "LD"},
                {R8, "A"},
                {COM, ","},
                {LBR, "["},
                {R16, "DE"},
                {RBR, "]"}
            },
            {0x1A}
        },

        {
            "DEC DE",
            {
                {OP, "DEC"},
                {R16, "DE"}
            },
            {0x1B}
        },

        {
            "INC E",
            {
                {OP, "INC"},
                {R8, "E"}
            },
            {0x1C}
        },

        {
            "DEC E",
            {
                {OP, "DEC"},
                {R8, "E"}
            },
            {0x1D}
        },

        {
            "LD E, 32",
            {
                {OP, "LD"},
                {R8, "E"},
                {COM, ","},
                {NUM, "32"}
            },
            {0x1E, 0x20}
        },

        {
            "RRA",
            {
                {OP, "RRA"}
            },
            {0x1F}
        },

        {
            "JR NZ, 27",
            {
                {OP, "JR"},
                {COND, "NZ"},
                {COM, ","},
                {NUM, "27"}
            },
            {0x20, 0x1B}
        },

        {
            "LD HL, $ABCD",
            {
                {OP, "LD"},
                {R16, "HL"},
                {COM, ","},
                {NUM, "43981"}
            },
            {0x21, 0xCD, 0xAB}
        },

        {
            "LD [HL+], A",
            {
                {OP, "LD"},
                {LBR, "["},
                {R16, "HL"},
                {PLU, "+"},
                {RBR, "]"},
                {COM, ","},
                {R8, "A"}
            },
            {0x22}
        },

        {
            "INC HL",
            {
                {OP, "INC"},
                {R16, "HL"}
            },
            {0x23}
        },

        {
            "INC H",
            {
                {OP, "INC"},
                {R8, "H"}
            },
            {0x24}
        },

        {
            "DEC H",
            {
                {OP, "DEC"},
                {R8, "H"}
            },
            {0x25}
        },

        {
            "LD H, 38",
            {
                {OP, "LD"},
                {R8, "H"},
                {COM, ","},
                {NUM, "38"}
            },
            {0x26, 0x26}
        },

        {
            "DAA",
            {
                {OP, "DAA"}
            },
            {0x27}
        },

        {
            "JR Z, -12",
            {
                {OP, "JR"},
                {COND, "Z"},
                {COM, ","},
                {NUM, "-12"}
            },
            {0x28, 0xf4}
        },

        {
            "ADD HL, HL",
            {
                {OP, "ADD"},
                {R16, "HL"},
                {COM, ","},
                {R16, "HL"}
            },
            {0x29}
        },

        {
            "LD A, [HL+]",
            {
                {OP, "LD"},
                {R8, "A"},
                {COM, ","},
                {LBR, "["},
                {R16, "HL"},
                {PLU, "+"},
                {RBR, "]"}
            },
            {0x2A}
        },

        {
            "DEC HL",
            {
                {OP, "DEC"},
                {R16, "HL"}
            },
            {0x2B}
        },

        {
            "INC L",
            {
                {OP, "INC"},
                {R8, "L"}
            },
            {0x2C}
        },

        {
            "DEC L",
            {
                {OP, "DEC"},
                {R8, "L"}
            },
            {0x2D}
        },

        {
            "LD L, 6",
            {
                {OP, "LD"},
                {R8, "L"},
                {COM, ","},
                {NUM, "6"}
            },
            {0x2E, 0x06}
        },

        {
            "CPL",
            {
                {OP, "CPL"}
            },
            {0x2F}
        },
};


#endif //GB_ASSEMBLER_TESTS_H
