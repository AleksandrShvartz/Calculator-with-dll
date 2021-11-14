#include "Calculator.h"

void Calculator::loadLibs(std::vector<fs::path> dllFiles)
{

    std::cout << "Find " << dllFiles.size()+4<<" functions\n";
    for (auto file : dllFiles) {
        HINSTANCE hDLL=nullptr;               // Handle to DLL
        funcWithOneArg func=nullptr;
        funcWithTwoArg func2=nullptr;
        funcName nameOfFunc = nullptr;
        funcPriority priority = nullptr;
        std::string name = file.filename().string().
            substr(0, file.filename().string().length() - 4);
        hDLL = LoadLibrary(name.c_str());
        if (nullptr != hDLL)
        {
            if(file.filename().string()[file.filename().string().length() - 5]=='2')
                 func2 = reinterpret_cast<funcWithTwoArg>(GetProcAddress(hDLL, "calculate"));
            else
                func = reinterpret_cast<funcWithOneArg>(GetProcAddress(hDLL, "calculate"));
            nameOfFunc = reinterpret_cast<funcName>(GetProcAddress(hDLL, "name"));
            priority = reinterpret_cast<funcPriority>(GetProcAddress(hDLL, "priority"));
            if (func != nullptr)
            {
                info.funcOne.push_back(func);
                if (nameOfFunc != nullptr)
                {
                    info.namesOne.push_back(nameOfFunc());
                    std::cout << nameOfFunc() << std::endl;
                }
                else  throw "Pointer to function name is null";
            }
            else if (func2 != nullptr) 
            {
                info.funcTwo.push_back(func2);
                if (nameOfFunc != nullptr)
                {
                    info.namesTwo.push_back(nameOfFunc());
                    std::cout << nameOfFunc() << std::endl;
                }
                else  throw "Pointer to function name is null";
                if (priority != nullptr)
                {
                    info.prioritiesTwo.push_back(priority());
                }
                else  throw "Pointer to function priority is null";
            } else
            {
                throw "Pointer to function is null";
            }

        }
        else throw "Handle is null";
        handles.push_back(hDLL);
    }
    info.namesTwo.push_back("+");
    std::cout << "+ for 2 args" << std::endl;
    info.namesTwo.push_back("-");
    std::cout << "- for two args" << std::endl;
    info.funcTwo.push_back([](double a, double b) {return a + b; });
    info.funcTwo.push_back([](double a, double b) {return a - b; });
    info.prioritiesTwo.push_back(1);
    info.prioritiesTwo.push_back(1);
    info.namesOne.push_back("+");
    std::cout << "+ for 1 arg" << std::endl;
    info.namesOne.push_back("-");
    std::cout << "- for 1 arg" << std::endl;
    info.funcOne.push_back([](double a) {return a; });
    info.funcOne.push_back([](double a) {return -a; });
    info.namesOne.push_back("(");
    info.namesOne.push_back(")");
}

Calculator::Calculator()
{
    std::vector<fs::path> dllFiles;
    const fs::path workdir = fs::current_path();
    fs::recursive_directory_iterator begin(workdir.string());
    fs::recursive_directory_iterator end;
    std::copy_if(begin, end, std::back_inserter(dllFiles), [](const fs::path& path) {
        return fs::is_regular_file(path) && (path.extension() == ".dll");
        });
    loadLibs(dllFiles);
}

Calculator::~Calculator()
{
    for (auto handle: handles) {
        FreeLibrary(handle);
  }
}

double Calculator::calculate(std::string equation)
{
    std::string s;
    int count = 0;
    int j = 0;
    for (int i = 0; i != equation.length(); ++i)
        if (equation.at(i) != ' ')
            count++;
    s.resize(count);
    for (int i = 0; i != equation.length(); ++i)
        if (equation.at(i) != ' ')
            s.at(j++)=equation.at(i);
    Parser parser(s.c_str(),&info);
    return parser.parse();
}

