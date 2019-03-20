#include <iostream>
#include <ftw.h>
#include <sys/types.h>
#include <sys/stat.h>

static double VERSION = 1.2;

#include "version.cpp"

// Ive added a comment
long directoryCount, fileCount, byteCount;

int logEntry(const char* filePath, const struct stat* info, const int typeFlag, struct FTW* pathInfo)
{
    if (typeFlag == FTW_F)
    {
        fileCount += 1;
        byteCount += (long long) info->st_size;
    }

    if (typeFlag == FTW_D)
        directoryCount += 1;

    return 0;
}

void exploreDirectory(char* path)
{
    if (path == NULL || *path == '\0')
        return;

    nftw(path, logEntry, 15, FTW_PHYS);
}

int main(int argc, char* argv[])
{
    displayVersion();

    struct stat dirStat;

    // check if argv[1] is a directory
    // check if argv[1] is accessible
    // recursively explore argv[1] and count files, directories, and total bytes
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " " << "DIRECTORY" << std::endl;
        return EXIT_FAILURE;
    }

    if (stat(argv[1], &dirStat) == -1)
    {
        std::perror(argv[0]);
        return EXIT_FAILURE;
    }

    if (S_ISDIR(dirStat.st_mode) == 0)
    {
        std::cerr << argv[0] << ": Argument is not a directory" << std::endl;
        return EXIT_FAILURE;
    }

    if ((dirStat.st_mode & S_IROTH) == 0)
    {
        std::cerr << argv[0] << ": Cannot access directory" << std::endl;
        return EXIT_FAILURE;
    }

    // ntfw counts the directory provided
    directoryCount = -1;
    fileCount = 0;
    byteCount = 0;

    exploreDirectory(argv[1]);

    std::cout << "The total number of directories in directory \'" << argv[1] << "\' is: " << directoryCount << std::endl;
    std::cout << "The total number of files in directory \'" << argv[1] << "\' is: " << fileCount << std::endl;
    std::cout << "The total number of bytes occupied by every file in directory \'" << argv[1] << "\' is: " << byteCount << std::endl;

    return EXIT_SUCCESS;
}
