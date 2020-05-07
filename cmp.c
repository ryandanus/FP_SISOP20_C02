#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"


int space = 0;

void check(int file1,int file2);

int main(int argc, char const *argv[])
{
    if(argc < 3)
    {
        printf(2, "Usage: cmp 2 files...\n");
        exit();
    }
    else
    {
        int file1, file2;
        if ((file1 = open(argv[1], 0)) < 0)
        { // Error handling : cannot read file 1
            printf(1, "Failed to read files %s\n", argv[1]);
            exit();
        }
        if ((file2 = open(argv[2], 0)) < 0)
        { // Error handling : cannot read file 2
            printf(1, "failed to read %s\n", argv[2]);
            exit();
        }
        check(file1,file2);
        close(file1);
        close(file2);
        exit();
    }
}

void check(int file1,int file2)
{
    int n = 0;
    int m = 0;
    int totalbyte = 0;
    struct stat st;
    fstat(file1,&st);
    int size = st.size;
    char buf1[st.size];
    fstat(file2,&st);
    int size2 = st.size; 
    char buf2[st.size];

    if(size > size2)    totalbyte = size;
    else                totalbyte = size2;

    while (((n = read(file1, buf1, sizeof(buf1))) > 0) && ((m = read(file2, buf2, sizeof(buf2))) > 0))
    {
        if (write(1, buf1, n) != n)
        {
            printf(1, "cat: write error buf1\n");
            exit();
        } 
        if (write(1, buf2, m) != m)
        {
            printf(1, "cat: write error buf2\n");
            exit();
        }
    }
    if (n < 0)
    {
        printf(1, "cat: read error\n");
        exit();
    }

    if (m < 0)
    {
        printf(1, "cat: read error\n");
        exit();
    }
    
    int loop = 0;
    int byte = -1;
    int baris = 0;
    while (loop < totalbyte)
    {
        byte = 0;
        if(buf1[loop] != buf2[loop])
        {
            byte = loop;
            break;
        }

        if(buf1[loop] == '\n')
        {
            baris++;
        }
        loop++;
    }

    
    if(byte == -1){
        printf(2,"File matched\n");
        exit();
    }
    else{
        printf(2,"Error on %d line %d",byte+1,baris);
    }
}
