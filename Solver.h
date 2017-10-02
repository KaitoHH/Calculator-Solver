#include "rapidjson/document.h"
#include "UnarySlot.h"
#include <queue>
#include <set>
#include <iostream>
#include <fstream>
#include <memory>

class Solver;
class SolverConfig;

typedef std::shared_ptr<SolverConfig> config_ptr;
using namespace rapidjson;

class SolverConfig {
private:
	SolverConfig() = default;

	int begin;
	int target;
	std::vector<std::shared_ptr<_unary::Unary>> runnerList;
	friend Solver;

public:
	static config_ptr readConfigFromFile(const char *fileName) {
		std::ifstream ifs(fileName);
		std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		return readConfigFromJson(content);
	}

	static config_ptr readConfigFromJson(const std::string &content) {
		Document document;
		document.Parse(content.c_str());

		config_ptr config(new SolverConfig());
		config->begin = document["begin"].GetInt();
		config->target = document["target"].GetInt();

		for (auto &x : document["methods"].GetArray()) {
			std::vector<int> argList;
			if (x.FindMember("param") != x.MemberEnd())
				for (auto &y:x["param"].GetArray())
					argList.push_back(y.GetInt());
			config->runnerList.emplace_back(
					_unary::UnaryFactory::createUnaryFunction(x["type"].GetString(), argList));
		}

		return config;
	}

	static config_ptr readConfigFromStream(std::istream &in) {
		config_ptr config(new SolverConfig());
		in >> config->begin >> config->target;
		std::string type;
		while (in >> type) {
			if (type == ".") break;
			int arg;
			std::vector<int> argList;
			while (in >> arg) argList.push_back(arg);
			config->runnerList.emplace_back(
					_unary::UnaryFactory::createUnaryFunction(type.c_str(), argList));
			in.clear();
		}
		return config;
	}
};

class Solver {
private:
	config_ptr config;
public:
	explicit Solver(config_ptr config) {
		this->config = config;
	}

	void solve() {
		std::queue<int> q;
		std::set<int> vis;
		std::map<int, int> fa;
		q.push(config->begin);
		vis.insert(config->begin);
		while (!q.empty()) {
			int cur = q.front();
			if (cur == config->target) {
				break;
			}
			q.pop();
			for (auto &f : config->runnerList) {
				int new_cur = f->calc(cur);
				if (new_cur == _unary::IMPOSSIBLE_VALUE) continue;
				if (vis.find(new_cur) == vis.end()) {
					fa[new_cur] = cur;
					vis.insert(new_cur);
					q.push(new_cur);
				}
			}
		}
		std::vector<int> ans;
		int cur = config->target;
		while (cur != config->begin) {
			ans.push_back(cur);
			cur = fa[cur];
		}
		ans.push_back(cur);
		for (auto it = ans.rbegin(); it != ans.rend(); it++) {
			std::cout << *it << std::endl;
		}
	}
};
