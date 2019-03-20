#include <iostream>
#include <string>

// Ive added a comment

int main(int argc, char* argv[])
{
    std::string directories("directories"), files("files"), bytes("bytes"), line, filter;

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " " << "[-d -f -b]" << std::endl;
        return EXIT_FAILURE;
    }

    if (std::string(argv[1]) == "-d")
        filter = directories;
    else if (std::string(argv[1]) == "-f")
        filter = files;
    else if (std::string(argv[1]) == "-b")
        filter = bytes;
    else
    {
        std::cerr << "Usage: " << argv[0] << " " << "[-d -f -b]" << std::endl;
        return EXIT_FAILURE;
    }

    bool match = false;

    while (std::getline(std::cin, line))
    {
        if (line.find(filter) != std::string::npos)
        {
            match = true;
            std::cout << line << std::endl;
        }
    }

    if (match)
        return EXIT_SUCCESS;
        
    std::cerr << "The input did not have any lines containing \'" << filter << "\'" << std::endl;

    return EXIT_FAILURE;
}
