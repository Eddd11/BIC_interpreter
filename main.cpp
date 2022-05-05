#include <iostream>
#include <string>
#include <fstream>
#include <vector>


struct tools
{
    std::string name;                   //------------ type for vars or containers             
    std::string value;                 //------------ value for string
    int value1;                           //------------ value for int
    int bulv;
};
int line_count = 0;
//-------------------------------------------------//       protortypes
const std::string type [] {"line","ints","buly","if__","loop", "out_"};

void similarity(std::string);

void separate(std::string);                               //for separating words in imported line

void struct_call(std::string, std::string);               //for declaring type and name of type

const int vars = 4;

void string_check(std::string);

void error();

void arguments(std::string);

int switch_call(std::string read, char , int, int*, std::string);

int check_sign(std::string, int, int*);

void print_value(std::string);
//--------------------------------------------------------//
std::vector <tools> vec_struct;

std::vector <std::string> vec_STRING;
//--------------------------------------------------------//
int main()
{
    std::string read {};                                     // based string for importing from txt file
    std::ifstream fread;                                     // Fstream declaration
    fread.open("text.txt");
    while(!fread.eof())
    {
    std::getline(fread, read);
    //std::cout << read <<"\n" << std::endl;
    if(fread.eof())
        break;
    separate(read);
    }
    fread.clear();
    fread.close();
}
//--------------------------------------------------------------------//
void error()
{
    std::cout << "ERROR" << std::endl;
    exit(0);
}
//--------------------------------------------------------------------//
void separate(std::string read)
{    
       size_t found =  read.find('=');
       if(found != std::string::npos)
       {
            arguments(read);
       }
       else
       {
            string_check(read);
       }
}
//------------------------------------------------------------------//
int args = 6;

void arguments(std::string read)
{       
        int count = 0;
        int *vp = new int [args];
        if(count > 0)
        {vp[0] = 0;}
        int result = 0;
        std::string arg {};
        for(int i = 0; i < read.size(); ++i)
        {
            if(read[i] == ' ')
            {
                for(int j = 0; j < vec_struct.size(); ++j)
                {
                    if(arg == vec_struct[j].name)
                        {
                            vp[0] = vec_struct[j].value1;
                            count++;
                            break;
                        }
                    else
                    {
                        vp[0] = 0;    
                    }
                }
            break;
            }
            arg += read[i];
        }
        int range = arg.size();
        for(char j : read)
        {

            if(j == '+' || j == '-' || j == '*' || j == '/' || j == '<' || j == '>' || j == '?' || j == '|')
            {
               result = switch_call(read, j, range,vp, arg);
               result = vp[0];

               break;
            }
    
        }

        delete[] vp;
        vp = nullptr;
}
//------------------------------------------------------------------//
int switch_call(std::string read, char j, int range, int *vp, std::string arg)
{  
        int ret = 0;
        char sym = j;
        range += 3;
        std::string num{};
        std::string num2 {};
                    for(int i = range; i < read.size(); ++i)
                     {
                         if (read[i] == ' ')
                         {
                                 for(int j = 0; j < vec_struct.size(); ++j)
                                 {
                                     if(num == vec_struct[j].name)
                                     {
                                         vp[1] = vec_struct[j].value1;
                                     }
                                     break;
                                 }
                                 break;
                         }
                         num += read[i];
                     }
                     for(int i = range + (num.size()+ 3);i < read.size(); ++i)
                     {
                             if(read[i] == ';')
                             {
                                     for(int j = 0; j < vec_struct.size(); ++j)
                                     {
                                         if(num2 == vec_struct[j].name)
                                         {
                                             vp[2] = vec_struct[j].value1;
                                             break;  // internal for brake
                                         }
                                     }
                                     break;  // for i brake
                             }
                             num2 += read[i];
                     }

    /*                 std::cout <<"vp[0] " <<  vp[0] << std::endl;
                     std::cout <<"vp[1] " <<  vp[1] << std::endl;
                     std::cout <<"vp[2] " <<  vp[2] << std::endl; */
        switch(sym)
        {
        case '+':
                     ret = vp[1] + vp[2];
            //         std::cout << "result : " << ret << std::endl;
                     break;
        case '-':
                     ret = vp[1] - vp[2];
              //       std::cout << "result : " << ret << std::endl;
                     break;
        case '*':
                     ret = vp[1] * vp[2];
                //     std::cout << "result : " << ret << std::endl;
                     break;
        case '/':
                    ret = vp[1] / vp[2];
                  //  std::cout << "result : " << ret;
                    break;
        case'<':    
                    if(vp[1] < vp[2])
                    {
                        ret = vp[1];
                        if(arg == "if__")
                        {  
                            ret = 1;
                            std::cout << ret << " ";
                        }
                    }
                    else
                    {
                        ret = vp[2];
                        if(arg == "if__")
                        {
                            ret = 0;
                            std::cout << ret << " ";
                        }
                    }
//                    std::cout << "result : " << ret << std::endl;;
                    break;
        case'>':
                    if(vp[1] > vp[2])
                    {
                        ret = vp[1];
                        if(arg == "if__")
                        {  
                            ret = 1;
                            std::cout << ret << " ";
                        }
                     }
                    else
                    {
                        ret = vp[2];
                        if(arg == "if__")
                        {
                            ret = 0;
                            std::cout << ret << " ";
                        }
                    }
  //                  std::cout << "result : " << ret << std::endl;;
                    break;
        case'?':
                    if(vp[1] != vp[2])
                    {
                        ret = 1;
                        vp[0] = ret;
                    }
                    else
                    {
                        ret = 0;
                        vp[0] = ret;
                    }
    //                std::cout << "result : " << ret << std::endl;
        case'|':
                    ret = check_sign(read, range, vp);
                    ret = vp[0];
                    break;
        }           
    return ret;
}
//------------------------------------------------------------------//
int check_sign(std::string read, int range, int *vp)
{
    int ret = 0;
    int one = vp[1];
    int two = vp[2];

//    std::cout << one <<" "<< two;
    for(int i = range; i < read.size(); ++i)
    {
       if(read[i] == '-')
       {
            while(one != two)
            {
                one -= 1;
                std::cout << one << " ";
            }
            break;
       }
       if(read[i] == '+')   
       {    
            while(one!= two)
            {
               one += 1;
               std::cout << one << " ";
            }
            break;
       }
    }
    ret = one;
    vp[0] = one;
  //  std::cout <<" " << one;
    return ret;
}
//------------------------------------------------------------------//
void string_check(std::string read)
{
    ++line_count;
    std::string check {};
    for(int i = 0; i < vars; ++i)
    {
        check += read[i];
    }
 //   std::cout << check << "\n";
    
            if (check == type[0] || check == type[1] || check == type[2] || check ==type[3] || check == type[4] || check == type[5])
            {
                struct_call(check, read);
            }
            else
            {
                std::cout << "INVALID TYPE \nCHECK LINE N " << line_count << std::endl;
                error();
            }
}               
//------------------------------------------------------------// main function call
void print_value(std::string read)
{
        std::string print {};
        for(int i = vars + 1; i < read.size(); ++i)
        {
            if(read[i] == ';')
            {

                for(int j = 0; j < vec_struct.size(); ++j)
                {
                     if(vec_struct[j].name == print)
                             if(vec_struct[j].value == "")
                            {
                                std::cout << vec_struct[j].value1 << " ";
                                break;
                            }
                            else
                            {
                                std::cout << vec_struct[j].value << " ";
                                break;
                            }
                }
            }
            print += read[i];
        }
}
//------------------------------------------------------------//
void struct_call(std::string check, std::string read)
{

    int tmp = 0;
    std::string second {};
    std::string third {};
    if(check == "out_")
    {
        print_value(read);
    }
//-------------------------------------------------------------------------------------------//
    if(check == "loop")
    {
       arguments(read); 
    }
//-------------------------------------------------------------------------------------------//
    if(check == "if__")
    {
       arguments(read); 
    }
//-------------------------------------------------------------------------------------------//
    if(check == "line")
    {
        for(int i = vars + 1 ; i < read.size(); ++i)
        {
            if(read[i] == ' ')
                {
                    if(read[i + 1] == ' ')
                    {
                        std::cout << "YOU SHOULD WRITE CORRECTLY\n WITH NOT MORE AND NOT LESS WHITESPACES " << std::endl;
                    }
                    break;
                }
                second += read[i];
        }
        for(int i = 0; i < vec_struct.size(); ++i)
        {
            if(second == vec_struct[i].name)
            {
                std::cout << "CANNOT DECLARE SIMILAR NAME TO VARIABLE\nCHECK THE LINE N " << line_count << std::endl;
                error();
            }
        }
        
        tmp = second.size() + (vars + 2); 
        for(int i = tmp; i < read.size(); ++i)
        {
            if(read[i] !=';')
            {
                third += read[i];
            }
        }
        tools line; 
        line.name = second;
        line.value = third;
        //std::cout << line.name << " " <<  line.value << "\n";
        vec_struct.push_back(line);
        return;
    }
//-----------------------------------------// for ints
    if(check == "ints")
    {
        for(int i = vars + 1 ; i < read.size(); ++i)
         {
                     if(read[i] == ' ')
                     {
                        if(read[i + 1] == ' ')
                        {
                        std::cout << "YOU SHOULD WRITE CORRECTLY\n WITH NOT MORE AND NOT LESS WHITESPACES " << std::endl;
                        }
                         break;
                     }
                     second += read[i];
                
         }
         for(int i = 0; i < vec_struct.size(); ++i)
         {
             if(second == vec_struct[i].name)
             {
                 std::cout << "CANNOT DECLARE SIMILAR NAME TO VARIABLE\nCHECK THE LINE N " << line_count << std::endl;
                 error();
             }
         }
         tmp = second.size() + (vars + 2);
         for(int i = tmp; i < read.size(); ++i) 
         {
             if(read[i] !=';')
             {
                       if(read[i] < '0' || read[i] > '9')
                 {
                     std::cout << "YOUR DECLARED  ints TYPE\nCAN HOLD ONLY DIGITS CHECK THE LINE N " << line_count;
                     error();
                }

                 third += read[i];
             }
         }
         tools ints;                                             // detecting the type
         ints.name = second;                                     //detecting types name
         ints.value1 = stoi(third);                             //detecting types value
      //   std::cout << ints.name << " " <<  ints.value1 << "\n";
         vec_struct.push_back(ints);
         return;
    }
//----------------------------------------// for bools
    if(check == "buly")
    {
         
        for(int i = vars + 1 ; i < read.size(); ++i)
        {
                     if(read[i] == ' ')
                     {
                         break;
                     }
                     second += read[i];
         }
         for(int i = 0; i < vec_struct.size(); ++i)
          {
              if(second == vec_struct[i].name)
              {
                  std::cout << "CANNOT DECLARE SIMILAR NAME TO VARIABLE\nCHECK THE LINE N " << line_count << " " << std::endl;
                  error();
              }
          }
         tmp = second.size() + (vars + 2);
          for(int i = tmp; i < read.size(); ++i)
         {
              if(read[i] !=';')
              {
                  third += read[i];
              }
          }
         tools buly;
         buly.name = second;
         buly.bulv = stoi(third);
      // std::cout << flot.name << " " <<  flot.value2 << "\n";
         vec_struct.push_back(buly);
         return;
    }
}
