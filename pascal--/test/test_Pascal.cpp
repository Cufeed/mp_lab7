#include <gtest/gtest.h>
#include "Pascal.h"
#include <fstream>
#include <iostream>
#include <string>
#include <codecvt>
#include <locale>
using namespace std;
TEST(Pascal, ParseSampleFile) {
    setlocale(LC_ALL, "Russian");
    ifstream file("../../../pascal--/samples/sample.pmm");

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    HierarchicalList<string> list;
    Pascal::parseToHierarchicalList(content, list);

    //list.print();
    OrderedTable<std::string, std::any> constants;
    OrderedTable<std::string, std::any> variables;

    vector<std::string> tmp = Pascal::listtovector(list);
    Pascal::parseVar(list, variables);
    Pascal::parseConst(list, constants);
    // Пример проверки констант
    ASSERT_TRUE(constants.Find("Pi")); // Проверяем, что в таблице констант есть константа "Pi"
    //ASSERT_EQ(constants.Find('Pi'), "3.1415926"); // Проверяем, что значение константы "Pi" равно "3.1415926"

    // Пример проверки переменных
    ASSERT_TRUE(variables.Find("num1")); // Проверяем, что в таблице переменных есть переменная "num1"
    //ASSERT_EQ(variables.Find("num1"), "integer"); // Проверяем, что тип переменной "num1" равен "integer"

    file.close();
}
