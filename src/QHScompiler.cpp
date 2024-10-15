#include <iostream>

#include "codeGenerator/Generator.cpp"
#include "utils/InputFile.cpp"
#include "utils/OutputFile.cpp"
#include "utils/argparse.hpp"

AssemblyCode* CompileFile(std::string filename)
{
    InputFile* file = new InputFile(filename);

    Generator generator = Generator(file);

    AssemblyCode* assemblyCode = generator.Generate();

    return assemblyCode;
}

void OutToFile(AssemblyCode* code, std::string filename)
{
    OutputFile outFile = OutputFile(filename);
    outFile.Write(code->ToString());
}

void Assemble(std::string inFile, std::string outFile, bool deleteInFile)
{
    Logger.Log("Assembling " + inFile + " to " + outFile, Logger::INFO);

    std::string command = "nasm -felf64 " + inFile + " -o " + outFile;
    system(command.c_str());

    if (deleteInFile)
    {
        std::string command = "rm " + inFile;
        system(command.c_str());
    }
}

void Link(std::string inFile, std::string outFile, bool deleteInFile)
{
    Logger.Log("Linking " + inFile + " to " + outFile, Logger::INFO);

    std::string command = "ld " + inFile + " -o " + outFile;
    system(command.c_str());

    if (deleteInFile)
    {
        std::string command = "rm " + inFile;
        system(command.c_str());
    }
}

int main(int argc, char const* argv[])
{
    argparse::ArgumentParser program("QHS compiler");

    program.add_argument("file").help("The file to compile");
    program.add_argument("-o", "--output")
        .help("The output file. If none is specified the output will be stored in a.out")
        .default_value("a.out");

    program.add_argument("-c", "--compile")
        .help("Only compile, do not assemble and link")
        .default_value(false)
        .implicit_value(true);
    program.add_argument("-s", "--assemble")
        .help("Only compile and assemble, do not link")
        .default_value(false)
        .implicit_value(true);
    program.add_argument("-k", "--keep").help("Keep temporary files").default_value(false).implicit_value(true);

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err)
    {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }

    std::string filePath = program.get<std::string>("file");
    AssemblyCode* outCode = CompileFile(filePath);
    bool deleteTempFiles = !program.get<bool>("--keep");

    if (program["--compile"] == true)
    {
        OutToFile(outCode, program.get<std::string>("--output"));
    }
    else if (program["--assemble"] == true)
    {
        OutToFile(outCode, "a.s");
        Assemble("a.s", program.get<std::string>("--output"), deleteTempFiles);
    }
    else
    {
        OutToFile(outCode, "a.s");
        Assemble("a.s", "a.o", deleteTempFiles);
        Link("a.o", program.get<std::string>("--output"), deleteTempFiles);
    }

    delete outCode;

    return 0;
}
