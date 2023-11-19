#include <iostream>
#include <fstream>
#include <regex>

std::string fix_variable_order(std::string &input)
{
    std::regex pattern(R"(\b(\w+)\s*:\s*(\w+(?:::\w+)*)\b)");
    return std::regex_replace(input, pattern, R"($2 $1)");
}

std::string fix_pointer_order(std::string &input)
{
    std::regex pattern("([a-zA-Z_][a-zA-Z0-9_]*)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*([*&])");
    return std::regex_replace(input, pattern, "$1 $3$2");
}

std::string fix_method_order(std::string &input)
{
    std::regex pattern(R"(\b(\w+)\(([^)]*)\)\s*:\s*(\w+)\b)");
    return std::regex_replace(input, pattern, R"($3 $1($2))");
}

std::string fix_case_order(std::string &input)
{
    std::regex pattern(R"(PCASE (\w+) (\w+))");
    return std::regex_replace(input, pattern, R"(case $2: $1)");
}

std::string replace_keywords(std::string &input)
{
    std::regex int8_patter("\\bpenistiger8\\b");
    std::regex int16_patter("\\bpenistiger16\\b");
    std::regex int32_patter("\\bpenistiger32\\b");
    std::regex int64_patter("\\bpenistiger64\\b");

    std::regex uint8_patter("\\bupenistiger8\\b");
    std::regex uint16_patter("\\bupenistiger16\\b");
    std::regex uint32_patter("\\bupenistiger32\\b");
    std::regex uint64_patter("\\bupenistiger64\\b");

    std::regex char_patter("\\bpenischar\\b");
    std::regex bool_patter("\\bpenisool\\b");
    std::regex float_patter("\\bpenisfloat\\b");
    std::regex double_patter("\\bpenisdouble\\b");

    std::regex struct_patter("\\penistruct\\b");
    std::regex enum_patter("\\penum\\b");
    std::regex void_patter("\\penisoid\\b");

    std::regex var_patter("\\penisariable\\s*\\b");
    std::regex comment_pattern("8==D");

    std::regex return_patter("\\bCUM\\b");
    std::regex elseif_patter("\\PELSIF\\b");
    std::regex if_patter("\\PENIF\\b");
    std::regex else_patter("\\PELSE\\b");
    std::regex while_patter("\\WET\\b");
    std::regex for_patter("\\CONDOM\\b");
    std::regex switch_patter("\\GOGETTHEMILK\\b");
    std::regex break_patter("\\PULLOUT\\b");

    std::regex namespace_patter("\\btesticle\\b");

    std::regex include_patter("\\bpinclude\\b");

    std::string result;
    result = std::regex_replace(input, int8_patter, "int8_t");
    result = std::regex_replace(result, int16_patter, "int16_t");
    result = std::regex_replace(result, int32_patter, "int32_t");
    result = std::regex_replace(result, int64_patter, "int64_t");

    result = std::regex_replace(result, uint8_patter, "uint8_t");
    result = std::regex_replace(result, uint16_patter, "uint16_t");
    result = std::regex_replace(result, uint32_patter, "uint32_t");
    result = std::regex_replace(result, uint64_patter, "uint64_t");

    result = std::regex_replace(result, char_patter, "char");
    result = std::regex_replace(result, bool_patter, "bool");
    result = std::regex_replace(result, float_patter, "float");
    result = std::regex_replace(result, double_patter, "double");

    result = std::regex_replace(result, char_patter, "char");
    result = std::regex_replace(result, bool_patter, "bool");
    result = std::regex_replace(result, float_patter, "float");
    result = std::regex_replace(result, double_patter, "double");

    result = std::regex_replace(result, struct_patter, "struct");
    result = std::regex_replace(result, enum_patter, "enum");
    result = std::regex_replace(result, void_patter, "void");

    result = std::regex_replace(result, var_patter, "");
    result = std::regex_replace(result, comment_pattern, "//");

    result = std::regex_replace(result, return_patter, "return");
    result = std::regex_replace(result, elseif_patter, "else if");
    result = std::regex_replace(result, if_patter, "if");
    result = std::regex_replace(result, else_patter, "else");
    result = std::regex_replace(result, while_patter, "while");
    result = std::regex_replace(result, for_patter, "for");
    result = std::regex_replace(result, switch_patter, "switch");
    result = std::regex_replace(result, break_patter, "break");

    result = std::regex_replace(result, namespace_patter, "namespace");

    result = std::regex_replace(result, include_patter, "#include");
    return result;
}

std::string fix_structs(std::string &input)
{
    std::regex pattern(R"((struct|enum)\s+\w+\s*\{[^\}]*\})");
    return std::regex_replace(input, pattern, "$&;");
}

std::string fix_main(std::string &input)
{
    std::regex pattern(R"(precum\s*\{([^\}]*)\})");
    return std::regex_replace(input, pattern, "int main(void)\n{$1}");
}

int main(int argc, const char **argv)
{
    std::ifstream t(argv[1]);
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

    std::string result;
    result = fix_variable_order(str);
    result = fix_method_order(result);
    result = fix_pointer_order(result);
    result = fix_case_order(result);
    result = replace_keywords(result);
    result = fix_structs(result);
    result = fix_main(result);

    std::ofstream output_file("output.cpp");
    output_file << "#include <iostream>\n#include <stdint.h>\n\n";
    output_file << result;
    output_file.close();

    system("g++ output.cpp");

    return EXIT_SUCCESS;
}