var path = require('path');
var _fibonacci = require(path.join(__dirname, '../build/Release/fibonacci.node'));

exports.calculate = _fibonacci.calculate;
