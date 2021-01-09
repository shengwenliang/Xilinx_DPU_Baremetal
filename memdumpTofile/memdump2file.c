#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <phys_addr> <offset>\n", argv[0]);
        return 0;
    }

    off_t offset = strtoul(argv[1], NULL, 0);
    size_t len = strtoul(argv[2], NULL, 0);

    // Truncate offset to a multiple of the page size, or mmap will fail.
    size_t pagesize = sysconf(_SC_PAGE_SIZE);
    off_t page_base = (offset / pagesize) * pagesize;
    off_t page_offset = offset - page_base;

    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    unsigned char *mem = mmap(NULL, page_offset + len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, page_base);
    if (mem == MAP_FAILED) {
        perror("Can't map memory");
        return -1;
    }
    char *buffer;
    buffer = malloc(len);
    printf("length is :%d",len);
    if (buffer == NULL) {
        printf(stderr, "Failed to allocate memory\n");
    }

    memcpy(buffer, (char *)mem + page_offset, len);
	
    /* Write your buffer to disk. */
    FILE* pFile;
    pFile = fopen("./dump.bin","wb");

    if (pFile){
        fwrite(buffer, len, 1, pFile);
	printf("Wrote to file!i\n");
    }
    else{
	printf("Something wrong writing to File.\n");
    }

    fclose(pFile);

    free(buffer);

								
    size_t i;
    for (i = 0; i < len; ++i){
	if(i!=0 && i%16==0)
	    printf("\n");
        printf("%02x ", (int)mem[page_offset + i]);
    }

    return 0;
}
