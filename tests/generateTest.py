"""
This python script generate the test for Tests.cpp using
the json from this link : https://gbdev.io/gb-opcodes/optables/
"""

import json


def get_number(token: str):
    if token == "n8":
        return "27", "0x1B"
    elif token == "n16":
        return "$ABCD", "0xCD", "0xAB"
    elif token == "a8":
        return "27", "0x1B"
    elif token == "a16":
        return "$ABCD", "0xCD", "0xAB"
    elif token == "e8":
        return "-27", "0xF9"


def make_string(opcode: dict, mnemonic: dict, operands: list) -> [str, str]:
    """
    create a string that represent a command

    :param opcode:
    :param mnemonic: A dict with the name of the op code
    :param operands: A list with all the operands
    :return: a string of the command
    """
    op_string: str = str(mnemonic)
    op_list: list = []
    bin_list: list = [str(opcode)]


    op: dict
    for op in operands:
        if op_string == "STOP":
            bin_list.append("0x00")
            continue
        name: str = str(op["name"])
        immediate: dict = op["immediate"]

        if name in ["n8", "n16", "a8", "a16", "e8"]:
            if len(get_number(name)) == 2:
                bin_list.append(get_number(name)[1])
            else:
                bin_list.append(get_number(name)[1])
                bin_list.append(get_number(name)[2])
            name = get_number(name)[0]


        if immediate:
            op_list.append(name)
        elif "increment" in op and op["increment"]:
            op_list.append("[" + name + "+]")
        elif "decrement" in op and op["decrement"]:
            op_list.append("[" + name + "-]")
        else:
            op_list.append("[" + name + "]")

    op_string += " " + ", ".join(op_list)
    if op_string == "LD HL, SP, -27":
        op_string = "LD HL, SP + -27"

    bin_string = "{" + ", ".join(bin_list) + "}"

    return [op_string, bin_string]


# get the json file
data: dict
with open('tests/Opcodes.json', 'r') as file:
    data = json.load(file)

# handle unprefixed command
opcode: dict
output: str = ""

output += "#ifndef GB_ASSEMBLER_GENERATEDTESTS_H\n"
output += "#define GB_ASSEMBLER_GENERATEDTESTS_H\n"
output += "\n"
output += "#include \"Tests.h\"\n"
output += "\n"
output += "std::vector<OpTest> vectorTestGenerated = {\n"

for opcode in data["unprefixed"]:
    mnemonic: dict = data["unprefixed"][opcode]["mnemonic"]
    operands: list = data["unprefixed"][opcode]["operands"]

    if str(mnemonic).startswith("ILLEGAL") or str(mnemonic).startswith("PREFIX"):
        continue

    [op_string, bin_string] = make_string(opcode, mnemonic, operands)

    output += "    {\n"
    output += "        \"" + op_string + "\",\n"
    output += "        " + bin_string + "\n"
    output += "    },\n"

    # print(opcode, op_string(mnemonic, operands))

output += "};\n\n"
output += "#endif //GB_ASSEMBLER_GENERATEDTESTS_H"

with open("tests/GeneratedTests.h", "w") as file:
    # Write the string to the file
    file.write(output)

print("File GeneratedTests.h done !")