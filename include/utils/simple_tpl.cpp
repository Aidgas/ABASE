#include "simple_tpl.h"


string tpl_file(string filename, TplMap map_data)
{
    string result = "";

    if(!file_exists(filename) || ! is_file(filename))
    {
        return result;
    }

    // load file
    FILE *fp = fopen(filename.c_str(), "rb");

    if(fp == NULL)
    {
        return result;
    }

    char buffer[5024] = "";
    int num_read;

    while(true)
    {
        num_read = fread(buffer, 1, 5024, fp);

        if(num_read == 0)
        { break; }

        result.append(buffer, num_read);
    }

    fclose(fp);
    
    for(TplMap_Iter iter = map_data.begin(); iter != map_data.end(); iter++)
    {
        if((*iter).second.length() > 0)
        {
            result = string_replace(result, string_format("{%s}", (*iter).first.c_str()), (*iter).second);
        }
    }

    /*string find_str = "";
    bool add_str = false, find_replace = false;

    while(true)
    {
            find_replace = false;

            for(unsigned int i=0; i<result.length(); i++)
            {
                if( result[i] == '{' && i+1<result.length() && (result[i+1] >= 'A') && (result[i+1] <= 'Z') )
                {
                    if(add_str == true)
                    {
                        find_str = "";
                    }
                    add_str = true;
                }
                else if( ( result[i] == '}' ) && (add_str == true) )
                {
                    result = string_replace(result, string_format("{%s}", find_str.c_str()), "");
                    find_str = "";

                    add_str = false;
                    find_replace = true;
                    break;
                }
                else if(add_str == true)
                {
                    if(    (result[i] >= 'A' && result[i] <= 'Z')
                        || (result[i] >= '0' && result[i] <= '9')
                        || result[i] == '_'
                       )
                    {
                       find_str += result[i];
                    }
                    else
                    {
                        add_str = false;
                        find_str = "";
                        find_replace = false;
                    }
                }
            }

            if(! find_replace)
            {
                break;
            }
            printf("next find\n");
    }*/

    return result;
}
