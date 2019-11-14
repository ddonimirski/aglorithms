#if !defined TWO_STACK_H
#define TWO_STACK_H
#include <string_view>
#include "stack.hpp"


int get_int(std::string_view str, int& s)
{
    int ret = 0;
    while (s < str.size())
    {
        switch(str[s])
        {
            default: break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            ret = 10 * ret + (str[s++]-'0');
        }
    }
    return ret;
}

//Dikstrji alorithm
int two_stacks(std::string_view str)
{
   stack<char> op; 
   stack<int> val;

   auto comp = [&]()
   {
       auto const op = op.pop();
       auto const v1 = val.pop();
       auto const v2 = val.pop();
       if (op == '*') return v1 * v2;
       if (op == '+') return v1 + v2;
       if (op == '-') return v1 - v2;
      //throw 
       return 0;
   };


   for (int i = 0; i < str.size(); i++)
   {
       auto const v = str[i];
       if (v == '(' || v == ' ')
       {
           continue;
       }
       else if (v == ')')
       {
           val.push(comp());
       }
       else if (v == '*' || v == '+' || v == '-')
       {
           op.push(v);
       }
       else //TODO: check input for errors
       {
            val.push(vv);
       }
   }

   return val.top();
}


#endif //TWO_STACK_H
