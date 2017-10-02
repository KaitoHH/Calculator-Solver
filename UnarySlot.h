#pragma once

#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

namespace _unary {
	class UnaryFactory;

	class Unary;
	class SingleArgUnary;
	class DoubleArgUnary;
	class AddUnary;
	class MinusUnary;
	class MultiUnary;
	class DivUnary;
	class DelUnary;
	class InputUnary;
	class ConvertUnary;
	class ReverseUnary;
	class SumUnary;
	class PowUnary;
	class RShiftUnary;
	class LShiftUnary;
	class MirrorUnary;

	typedef Unary *(*UnaryFactoryFunc)(const std::vector<int> &);

	typedef std::map<std::string, UnaryFactoryFunc> UnaryMap;

	extern UnaryMap funcMap;

	const int IMPOSSIBLE_VALUE = -1u >> 1;
}

class _unary::Unary {
public:
	virtual int calc(int) = 0;
};

class _unary::SingleArgUnary : public _unary::Unary {
protected:
	int arg;
public:
	explicit SingleArgUnary(int arg) : arg(arg) {}
};

class _unary::DoubleArgUnary : public _unary::Unary {
protected:
	int arg;
	int arg2;
public:
	explicit DoubleArgUnary(int arg, int arg2) : arg(arg), arg2(arg2) {}
};

class _unary::AddUnary : public _unary::SingleArgUnary {
public:
	explicit AddUnary(int arg) : SingleArgUnary(arg) {}

	int calc(int num) override {
		return num + arg;
	}

};

class _unary::MinusUnary : public _unary::SingleArgUnary {
public:
	explicit MinusUnary(int arg) : SingleArgUnary(arg) {}

	int calc(int num) override {
		return num - arg;
	}

};

class _unary::MultiUnary : public _unary::SingleArgUnary {
public:
	explicit MultiUnary(int arg) : SingleArgUnary(arg) {}


	int calc(int num) override {
		return num * arg;
	}

};

class _unary::DivUnary : public _unary::SingleArgUnary {
public:
	explicit DivUnary(int arg) : SingleArgUnary(arg) {}

	int calc(int num) override {
		if (num % arg) {
			return IMPOSSIBLE_VALUE;
		}
		return num / arg;
	}

};

class _unary::DelUnary : public _unary::Unary {
public:
	int calc(int num) override {
		return num / 10;
	}

};

class _unary::InputUnary : public _unary::SingleArgUnary {
public:
	explicit InputUnary(int arg) : SingleArgUnary(arg) {}

	int calc(int num) override {
		int temp = arg;
		do {
			num *= 10;
			temp /= 10;
		} while (temp);
		return num + (num < 0 ? -arg : arg);
	}

};

class _unary::ConvertUnary : public _unary::DoubleArgUnary {
public:
	ConvertUnary(int arg, int arg2) : DoubleArgUnary(arg, arg2) {}

	int calc(int num) override {
		// not efficient, but simple
		std::string temp = std::to_string(num);
		temp = ReplaceAll(temp, std::to_string(arg), std::to_string(arg2));
		return std::stoll(temp);
	}

	static std::string ReplaceAll(std::string str, const std::string &from, const std::string &to) {
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
		return str;
	}

};

class _unary::ReverseUnary : public _unary::Unary {
public:
	int calc(int num) override {
		// not efficient, but simple
		std::string num_string = std::to_string(num);
		std::reverse(num_string.begin(), num_string.end());
		return std::stoll(num_string) * (num < 0 ? -1 : 1);
	}
};

class _unary::SumUnary : public _unary::Unary {
public:
	int calc(int num) override {
		int sum = 0;
		while (num) {
			sum += num % 10;
			num /= 10;
		}
		return sum;
	}
};

class _unary::LShiftUnary : public _unary::Unary {
public:
	int calc(int num) override {
		int old = num;
		int temp = 1;
		int last = 0;
		while (num) {
			last = num % 10;
			temp *= 10;
			num /= 10;
		}
		return (old * 10 - temp * last) + last;
	}
};

class _unary::RShiftUnary : public _unary::Unary {
public:
	int calc(int num) override {
		int old = num;
		int temp = 1;
		int last = num % 10;
		while (num) {
			temp *= 10;
			num /= 10;
		}
		return old / 10 + last * temp / 10;
	}
};

class _unary::PowUnary : public _unary::SingleArgUnary {
public:
	explicit PowUnary(int arg) : SingleArgUnary(arg) {}

	int calc(int num) override {
		int ans = 1;
		for (int i = 1; i <= arg; i++) {
			ans *= num;
		}
		return ans;
	}
};

class _unary::MirrorUnary : public _unary::Unary {
public:
	int calc(int num) override {
		std::string s1 = std::to_string(num);
		std::string rs = s1;
		std::reverse(rs.begin(), rs.end());
		std::string ans = s1 + rs;
		if (ans.length() >= 7) {
			return IMPOSSIBLE_VALUE;
		}
		return std::stoll(ans);
	}
};

class _unary::UnaryFactory {
public:
	static Unary *createUnaryFunction(const char *method, const std::vector<int> &array) {
		auto f = _unary::funcMap[method];
		return f(array);
	}

	static Unary *createAddFunction(const std::vector<int> &array) {
		return new AddUnary(array[0]);
	}

	static Unary *createMinusFunction(const std::vector<int> &array) {
		return new MinusUnary(array[0]);
	}

	static Unary *createMultiFunction(const std::vector<int> &array) {
		return new MultiUnary(array[0]);
	}

	static Unary *createDivFunction(const std::vector<int> &array) {
		return new DivUnary(array[0]);
	}

	static Unary *createDelFunction(const std::vector<int> &array) {
		return new DelUnary();
	}

	static Unary *createInputFunction(const std::vector<int> &array) {
		return new InputUnary(array[0]);
	}

	static Unary *createConvertFunction(const std::vector<int> &array) {
		return new ConvertUnary(array[0], array[1]);
	}

	static Unary *createReverseFunction(const std::vector<int> &array) {
		return new ReverseUnary();
	}

	static Unary *createSumFunction(const std::vector<int> &array) {
		return new SumUnary();
	}

	static Unary *createPowFunction(const std::vector<int> &array) {
		return new PowUnary(array[0]);
	}

	static Unary *createRShiftFunction(const std::vector<int> &array) {
		return new RShiftUnary();
	}

	static Unary *createLShiftFunction(const std::vector<int> &array) {
		return new LShiftUnary();
	}

	static Unary *createMirrorFunction(const std::vector<int> &array) {
		return new MirrorUnary();
	}
};


_unary::UnaryMap _unary::funcMap = ([]() -> _unary::UnaryMap & {
	using namespace _unary;
	static UnaryMap funcMap;
	funcMap["+"] = UnaryFactory::createAddFunction;
	funcMap["++"] = UnaryFactory::createAddFunction;
	funcMap["-"] = UnaryFactory::createMinusFunction;
	funcMap["--"] = UnaryFactory::createMinusFunction;
	funcMap["*"] = UnaryFactory::createMultiFunction;
	funcMap["/"] = UnaryFactory::createDivFunction;
	funcMap["in"] = UnaryFactory::createInputFunction;
	funcMap["<<"] = UnaryFactory::createDelFunction;
	funcMap["=>"] = UnaryFactory::createConvertFunction;
	funcMap["r"] = UnaryFactory::createReverseFunction;
	funcMap["s"] = UnaryFactory::createSumFunction;
	funcMap["^"] = UnaryFactory::createPowFunction;
	funcMap[">"] = UnaryFactory::createRShiftFunction;
	funcMap["<"] = UnaryFactory::createLShiftFunction;
	funcMap["m"] = UnaryFactory::createMirrorFunction;
	return funcMap;
})();
