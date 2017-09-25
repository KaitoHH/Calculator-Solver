# Calculator-Solver

[![Build Status](https://semaphoreci.com/api/v1/kaitohh/calculator-solver/branches/master/shields_badge.svg)](https://semaphoreci.com/kaitohh/calculator-solver)
[![GitHub version](https://badge.fury.io/gh/KaitoHH%2FCalculator-Solver.svg)](https://badge.fury.io/gh/KaitoHH%2FCalculator-Solver)

Program for solving [Calculator: The Game](https://itunes.apple.com/us/app/calculator-the-game/id1243055750) - a game of using calculator to solve various number puzzles. 

This game is very suitable for practising your programming skill, from not only your ability to write an algorithm that performs well, but also your ability to refactor your code, keep your code tidy and extensible with the game going on, which is more important in this project.

I write this program just for fun, a good suggestion is that you can first download this game (both iOS and Android are available), and then play several levels to see what this game like. After that, you can write some simple snippets to see whether you can solve each level using programming. By keeping playing this game, you will find that more and more new buttons in the game will be introduced, and now it's time to completely refactor your code in order to keep your program extensible to continuous new features!
 
 ## Solution
 What I do in solving this game is use a design pattern called [Strategy Pattern](https://en.wikipedia.org/wiki/Strategy_pattern) to make my program extensible and simply use [Breadth First Search](https://en.wikipedia.org/wiki/Breadth-first_search) to find the solution. I've also used many C++11 features like lambda expression, smarter pointer to practise my C++ skills. Finally, I use a json format file to give my program game config of each level.
 
## Built with
- [RapidJSON](http://rapidjson.org/) [![GitHub version](https://badge.fury.io/gh/Tencent%2Frapidjson.svg)](https://badge.fury.io/gh/Tencent%2Frapidjson) - a fast json parser
