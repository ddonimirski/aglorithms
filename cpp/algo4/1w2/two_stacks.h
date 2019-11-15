#if !defined TWO_STACK_H
#define TWO_STACK_H
#include <string_view>
#include "stack.hpp"
#include "pr.hpp"

static int to_int(std::string_view str, int& s)
{
    int ret = 0;
    while (s < str.size())
    {
        switch(str[s])
        {
            default: return ret;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            ret = 10 * ret + (str[s++]-'0');
        }
    }
    return ret;
}

//Dikstrji algorithm
static int two_stacks(std::string_view str)
{
   stack<char> op; 
   stack<int> val;

   auto comp = [&]()
   {
       auto const o = op.pop();
       auto const v1 = val.pop();
       auto const v2 = val.pop();
       if (!o || !v1 || !v2)
           return 0;
       if (o == '*') return *v1 * *v2;
       if (o == '+') return *v1 + *v2;
       if (o == '-') return *v1 - *v2;
      //throw 
       return 0;
   };

   
   for (int i = 0, step = 1; i < str.size(); i+=step, step=1)
   {
       char v = str[i];
       if (v == '(' || v == ' ')
       {
           continue;
       }
       else if (v == ')')
       {
            if (val.size() < 2)
                pr("throw exception");
                
            val.push(comp());

       }
       else if (v == '*' || v == '+' || v == '-')
       {
           op.push(std::move(v));
       }
       else //TODO: check input for errors
       {
            val.push(to_int(str, i));
            step = 0;
       }
   }

   if (val.size() == 2)
        val.push(comp());

   return *val.top();
}


#endif //TWO_STACK_H
