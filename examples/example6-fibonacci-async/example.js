var fibonacci = require('./fibonacci');

var n = 20;

fibonacci.calculate(n, function(err, result) {
  console.log("Fibonacci for n", n, "is", result);
});

console.log("Hey! fibonacci is async! ...");
