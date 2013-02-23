//
// Parse.cpp for avm in /home/chirou_t//tek2/projets/c++/abstract/AbstractVM
//
// Made by thomas chiroussot-chambeaux
// Login   <chirou_t@epitech.net>
//
// Started on  Fri Feb 15 15:54:05 2013 thomas chiroussot-chambeaux
// Last update Sat Feb 23 15:36:15 2013 thomas chiroussot-chambeaux
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include "Parse.hpp"
#include "Operand.hpp"
#include "Parse.hpp"

Parse::Parse()
{
  this->_list.clear();
}

Parse::~Parse()
{

}

std::list<std::string> const & Parse::getList() const
{
  return (this->_list);
}

void	Parse::setList(std::list<std::string> const &list)
{
  this->_list = list;
}

std::list<std::string>  Parse::get_form(std::string ligne, std::list<std::string> list)
{
  int   i;
  int   flag;
  std::string new_string;

  i = -1;
  flag = 0;
  while (ligne.c_str()[++i])
    {
      if (ligne.c_str()[i] == ' ' || ligne.c_str()[i] == '(' || ligne.c_str()[i] == ')')
        {
          flag++;
          i++;
          list.push_back(new_string);
          new_string.clear();
        }
      new_string += ligne.c_str()[i];
    }
  if (flag == 0)
    {
      list.push_back(new_string);
      list.push_back("-1");
      list.push_back("-1");
    }
  return list;
}

int     Parse::check_line(std::string ligne)
{
  int   i;
  int   j;

  i = -1;
  j = -1;
  if (ligne == "pop" || ligne == "dump" || ligne == "add" || ligne == "sub"
      || ligne == "mul" || ligne == "div" || ligne == "mod" || ligne == "print"
      || ligne == "exit" || ligne == ";;")
    return 1;
  else if (!strncmp(ligne.c_str(), "push ", 5) || !strncmp(ligne.c_str(), "assert ", 7))
    while (!g_OperandTypeInfo[++i].type_name.empty())
      if (strstr(ligne.c_str(), g_OperandTypeInfo[i].type_name.c_str()) != 0)
        {
          if (!strncmp(ligne.c_str(), "push ", 5))
            j = 5 + g_OperandTypeInfo[i].type_name.length();
          else
            j = 7 + g_OperandTypeInfo[i].type_name.length();
          if (ligne.c_str()[j] != '(')
            return 0;
          while (isdigit(ligne[++j]));
          if ((g_OperandTypeInfo[i].type_name == "double"
               || g_OperandTypeInfo[i].type_name == "float") && ligne.c_str()[j] == '.')
            while (isdigit(ligne[++j]));
          if (ligne.c_str()[j] == ')' && ligne.c_str()[j + 1] == '\0')
            return 1;
        }
  return 0;
}


void    Parse::my_parse(std::istream *is)
{
  std::string ligne;
  int   i;
  int	flag;

  i = 0;
  flag = 0;
  while (!(*is).eof() && ligne.compare(";;"))
    {
      i++;
      std::getline((*is), ligne);
      if (check_line(ligne))
        _list = get_form(ligne, _list);
      else
        {
	  std::cout << "Syntax Error : Line " << i << " : " << ligne << std::endl;
          exit(1);
        }
      if (ligne == "exit" || ligne == ";;")
	flag = 1;
    }
  if (!flag)
    {
      std::cout << "Error : No exit found" << std::endl;
      exit(1);
    }
  return 1;
}
