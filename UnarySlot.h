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

	typedef Unary *(*UnaryFactoryFunc)(const std::vector<int> &);

	typedef std::map<std::string, UnaryFactoryFunc> UnaryMap;

	extern UnaryMap funcMap;

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
		// stub for invalid operation
		if (num % arg) {
			return 999;
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
		std::string temp = std::to_string(num);
		std::replace(temp.begin(), temp.end(), arg + '0', arg2 + '0');
		return std::stoi(temp);
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
};


_unary::UnaryMap _unary::funcMap = ([]() -> _unary::UnaryMap & {
	using namespace _unary;
	static UnaryMap funcMap;
	funcMap["add"] = UnaryFactory::createAddFunction;
	funcMap["minus"] = UnaryFactory::createMinusFunction;
	funcMap["multi"] = UnaryFactory::createMultiFunction;
	funcMap["div"] = UnaryFactory::createDivFunction;
	funcMap["input"] = UnaryFactory::createInputFunction;
	funcMap["delete"] = UnaryFactory::createDelFunction;
	funcMap["convert"] = UnaryFactory::createConvertFunction;
	return funcMap;
})();
