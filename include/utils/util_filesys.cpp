#include "util_filesys.h"
#include <fstream>
#include <sys/stat.h>

// ----------------------------------------------------------------------------
bool file_exists(string path)
{
    FILE *file = fopen(path.c_str(), "r");
    if(file != NULL)
    {
        fclose(file);
        return true;
    }
    return false;
}

// ----------------------------------------------------------------------------
bool is_directory(string pathname)
{
    struct stat sb;

    if (stat(pathname.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
    {
        return true;
    }
    return false;
}

// ----------------------------------------------------------------------------
bool is_file(string pathname)
{
    return !is_directory(pathname);
}

// ----------------------------------------------------------------------------
unsigned long get_file_size(const char * filepath)
{
    FILE * f = fopen(filepath, "r");

    if(f == NULL)
    {
        return 0;
    }

    fseek(f, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(f);
    fclose(f);
    return len;
}

// ----------------------------------------------------------------------------
unsigned long get_file_time_last_modified(const char *filepath)
{
    struct stat b;
    if (!stat(filepath, &b))
    {
        return b.st_mtime;
    }
    return 0;
}

// ----------------------------------------------------------------------------
unsigned long get_file_time_create(const char *filepath)
{
    struct stat b;
    if (!stat(filepath, &b))
    {
        return b.st_ctime;
    }
    return 0;
}
//------------------------------------------------------------------------------
vector<string> directory_glob(const string& pat)
{
    glob_t glob_result;
    glob(pat.c_str(),GLOB_TILDE,NULL,&glob_result);
    vector<string> ret;

    for(unsigned int i=0; i < glob_result.gl_pathc; ++i)
    {
        ret.push_back(string(glob_result.gl_pathv[i]));
    }

    globfree(&glob_result);
    return ret;
}
//------------------------------------------------------------------------------
std::string get_file_contents(const char *filename)
{
    std::ifstream ifs( filename );
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );

    return content;
/*
   string result = "";
   char *buffer = NULL;
   int string_size,read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       //seek the last byte of the file
       fseek(handler,0,SEEK_END);
       //offset from the first to the last byte, or in other words, filesize
       string_size = ftell (handler);
       //go back to the start of the file
       rewind(handler);

       //allocate a string that can hold it all
       buffer = (char*) malloc (sizeof(char) * (string_size + 1) );
       //read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);
       //fread doesnt set it so put a \0 in the last position
       //and buffer is now officialy a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           //something went wrong, throw away the memory and set
           //the buffer to NULL
           free(buffer);
           buffer = NULL;
       }
    }

    fclose(handler);

    if(buffer != NULL)
    {
        result.append(buffer);
    }

    if(buffer != NULL)
    {
        free(buffer);
        buffer = NULL;
    }

    return result;

    /*std::ifstream ifs(filename);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );

    return content;*/

    /*string result = "";

    char* buffer = NULL;
    long length;
    FILE* f = fopen (filename, "rb");

    if (f)
    {
      fseek (f, 0, SEEK_END);
      length = ftell (f);
      fseek (f, 0, SEEK_SET);

      buffer = (char*) malloc (length);

      if (buffer)
      {
        fread (buffer, 1, length, f);
      }

      fclose (f);
    }

    if (buffer)
    {
      result.append( buffer, length );

      free(buffer);
      buffer = NULL;
    }

    return result;*/
}

const char *humanSize(uint64_t bytes)
{
    char *suffix[] = {"B", "KB", "MB", "GB", "TB"};
    char length = sizeof(suffix) / sizeof(suffix[0]);

    int i = 0;
    double dblBytes = bytes;

    if (bytes > 1024) {
            for (i = 0; (bytes / 1024) > 0 && i<length-1; i++, bytes /= 1024)
                    dblBytes = bytes / 1024.0;
    }

    static char output[200];
    sprintf(output, "%.02lf %s", dblBytes, suffix[i]);
    return output;
}