#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        printf(2,"Usage: rmdir files...\n");
        exit();
    }
    for (int i = 1; i < argc; i++)
    {
        int fd;
        struct stat st;
        struct  dirent de;
        char buf[1024], *p;
        
        
        if((fd = open(argv[i],0))<0){
            printf(2, "failed to remove'%s':Path error\n", argv[i]);
            exit();
        }
        if (fstat(fd,&st) < 0)
        {
            printf(2, "failed to remove'%s':Stat error\n", argv[i]);
            exit();
        }

        if(st.type == 2){
            printf(1,"Error:Not a directory\n");
            exit();
        }
        
        else{
            if(st.size < 32) printf(2,"failed to remove'%s':Directory not empty\n",argv[i]);
            else{
                if (strlen(argv[i]) + 1 + DIRSIZ + 1 > sizeof buf)
                {
                    printf(1, "ls: path too long\n");
                    break;
                }
                strcpy(buf, argv[i]);
                p = buf + strlen(buf);
                *p++ = '/';
                int counter = 0;
                while (read(fd, &de, sizeof(de)) == sizeof(de))
                {
                    if (de.inum == 0)
                        continue;
                    memmove(p, de.name, DIRSIZ);
                    p[DIRSIZ] = 0;
                    if (stat(buf, &st) < 0)
                    {
                        printf(1, "ls: cannot stat %s\n", buf);
                        continue;
                    }
                    counter++;
                }
                if (counter > 2)
                {
                    printf(1, "failed to remove'%s':Directory not empty\n", argv[i]);
                }
                else
                {
                    if (unlink(argv[i]) < 0)
                    {
                        printf(1, "Error:Directory not empty\nError Code = %d\n", counter);
                        exit();
                    }
                    printf(1, "Remove %s complete\n", argv[i]);
                }
            }
        }
        
    }
    exit();
}