/*
 *  author  :   Gu-hwan Bae
 *  date    :   27 May 2018
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

#include "my_record.h"

#define NRECORDS (100)

void init_record(const char*);
void change_record(const char*, int, int);
void change_record_mmap(const char*, int, int);

int main() {
    const char* file_rec = "records.dat";

    init_record(file_rec);
    change_record(file_rec, 43, 143);
    change_record(file_rec, 43, 243);

    return 0;
}

void init_record(const char* file_rec) {
    record rec;
    FILE* fp;
    fp = fopen(file_rec, "w+");
    int i;
    for(i = 0; i < NRECORDS; ++i) {
        rec.number = i;
        sprintf(rec.string, "RECORD-%d", rec.number);
        fwrite(&rec, sizeof(rec), 1, fp);
    }
    fclose(fp);
}

void change_record(const char* file_rec, int before, int after) {
    record rec;
    FILE* fp;
    fp = fopen(file_rec, "r+");
    fseek(fp, before*sizeof(rec), SEEK_SET);
    fread(&rec, sizeof(rec), 1, fp);

    rec.number = after;
    sprintf(rec.string, "RECORD-%d", rec.number);

    fseek(fp, before*sizeof(rec), SEEK_SET);
    fwrite(&rec, sizeof(rec), 1, fp);
    fclose(fp);
}

void change_record_mmap(const char* file_rec, int before, int after) {
    record rec;
    record* mapped;
    int fd = -1;
    fd = open(file_rec, O_RDWR);
    mapped = (record*) mmap(0, NRECORDS*sizeof(rec), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    mapped[before].number = after;
    sprintf(mapped[before].string, "RECORD-%d", mapped[before].number);
    msync((void*)mapped, NRECORDS*sizeof(rec), MS_ASYNC);
    munmap((void*)mapped, NRECORDS*sizeof(rec));
    close(fd);
}
