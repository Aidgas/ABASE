#include <iostream>

#include "include/database.h"

using namespace std;

string pathApp;

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    pathApp = getPathAppBin(argv[0]);
    
    printf("-pathApp: %s\n", pathApp.c_str());
    
    Database db(pathApp + "/../../DATA/");
    
    ResultParseCmd* result_cmd = db.parseCmd("CREATE_DATABASE \"base.db\" table1 {c1-int8;c2-str;c3-str;c4-int32;c5-int16;c6-uint16}");
    
    result_cmd->debug_print();
    delete result_cmd;
    
    result_cmd = db.parseCmd("CREATE_DATABASE \"base2.db\" table3 {c1-int8;c2-str}");
    delete result_cmd;
    
    result_cmd = db.parseCmd("OPEN_DATABASE \"base.db\"");
    result_cmd->debug_print();
    delete result_cmd;
    
    result_cmd = db.parseCmd("OPEN_DATABASE \"base2.db\"");
    result_cmd->debug_print();
    delete result_cmd;
    
    result_cmd = db.parseCmd("INFO_DATABASE");
    delete result_cmd;
    
    /*result_cmd = db.parseCmd("INSERT table1 (10, 'str110', 'str110', 15, 24, 0 )");
    delete result_cmd;
    /*result_cmd = db.parseCmd("INSERT table1 (5, 'str6', 'str6', 60, 70, 200 )");
    delete result_cmd;
    
    result_cmd = db.parseCmd("INSERT table3 (10, '5fghghgfhghfd h dhh' )");
    delete result_cmd;
    
    result_cmd = db.parseCmd("INSERT table3 (15, 'qwqwq e rr h dhh' )");
    delete result_cmd;/**/
    
    /*result_cmd = db.parseCmd(
            "UPDATE table1 SET "
            "c1 = c1 + 10, "
            "c4 = c4 + 1, "
            "c6 = c6 + 1, "
            "c5 = c5 - 1, "
            "c2 = genarateText(1, '%^*=') + genarateAZ09Text(2) + string_limit(c3 + '_', 32), "
            "c3 = genarateText(1, '%^*=') + genarateAZ09Text(2) + string_limit(c2 + '_', 32) "
            //"WHERE colum3 > 897"
            );
    result_cmd->debug_print();
    delete result_cmd;/**/
    
    result_cmd = db.parseCmd(
            " SELECT table1.*"
            //"SELECT * "
            " FROM table1"
            //"WHERE c1 == 80 && (c3 == 5 || c3 == 7) && c4 == 'text55' "
            //"WHERE colum1 < 30 "
            //"OFFSET 1 "
            //"LIMIT 5"
            " ORDER c1 DESC, c6"
            );/**/
    
    /*result_cmd = db.parseCmd(
            " SELECT table1.*, table3.c1 as d1, table3.c2 as d2"
            //"SELECT * "
            " FROM table1, table3"
            //"WHERE c1 == 80 && (c3 == 5 || c3 == 7) && c4 == 'text55' "
            //"WHERE colum1 < 30 "
            //"OFFSET 1 "
            //"LIMIT 5"
            " ORDER c1 DESC, c2 "
            );
    
    result_cmd->debug_print();
    delete result_cmd;/**/
    
    /*result_cmd = db.parseCmd(
            "SELECT *"
            //"SELECT * "
            " FROM table3 "
            //"WHERE c1 == 80 && (c3 == 5 || c3 == 7) && c4 == 'text55' "
            //"WHERE colum1 < 30 "
            //"OFFSET 1 "
            //"LIMIT 5"
            );
    result_cmd->debug_print();
    delete result_cmd;/**/
    
    
    /*result_cmd = db.parseCmd("DELETE table1 WHERE colum2 == '=='");
    delete result_cmd;/**/
    
    result_cmd = db.parseCmd("CLOSE_DATABASE");
    delete result_cmd;
    
    
    return 0;
}
