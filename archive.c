#include <stdio.h>
#include <string.h>

struct FileHeader{
    char name[256];
    long size;


};

int main(){
    FILE *file=fopen("test.txt","rb");
    fseek(file,0,SEEK_END);
    long siz=ftell(file);
    printf("Size: %ld\n",siz);
    // char name_temp[256]=strcpy(file,sizeof(char))

  
    struct FileHeader file1;
    strcpy(file1.name,"test.txt");
    file1.size=siz;

    printf("Size: %zu bytes\n",sizeof(file1));

    FILE *arch=fopen("archive.data","wb");

    fwrite(&file1,sizeof(struct FileHeader),1,arch);
    rewind(file);
    char buffer[256];
    size_t bytes_read;
    while((bytes_read=fread(buffer,1,sizeof(buffer),file))>0){
        fwrite(buffer,1,bytes_read,arch);
    }

    fclose(arch);
    fclose(file);

    arch=fopen("archive.data","rb");
    struct FileHeader header;
    size_t passp=fread(&header,sizeof(struct FileHeader),1,arch);
    printf("%zu\n",passp);
    FILE *dest=fopen(header.name, "wb");
    char buff[256];
    long remain=header.size;
    while(remain>0){
        long to_read=(remain<sizeof(buff)) ? remain: sizeof(buff);

        size_t bytes_read = fread(buff, 1, to_read, arch);
        if (bytes_read == 0) break;

        fwrite(buff, 1, bytes_read, dest);
        remain -= bytes_read; 
    }
    fclose(dest);
    fclose(arch);

    return 0;
}