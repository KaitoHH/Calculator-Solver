#include "UnarySlot.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <memory>
class Solver;
class SolverConfig;
typedef std::shared_ptr<SolverConfig> config_ptr;
using namespace rapidjson;

class SolverConfig
{
private:
    SolverConfig() {};
    int begin;
    int target;
    std::vector<unary>runnerList;
    friend Solver;

public:
    static config_ptr readConfigFromFile(const char *fileName) {
        std::ifstream ifs(fileName);
        std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
        Document document;
        document.Parse(content.c_str());

        config_ptr config(new SolverConfig());
        config->begin = document["begin"].GetInt();
        config->target = document["target"].GetInt();
        
        
        
        return config;
    }
};

class Solver
{
private:
    config_ptr config;
public:
    Solver(config_ptr config) {
        this->config = config;
    }
    solve() {

    }
};
