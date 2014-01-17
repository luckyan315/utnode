var path = './build/Release/struct.node'
var ladd = require(path).add(1,2);
console.log(ladd);

var dadd = require(path).add_d(0.7, 8.1);
console.log(dadd);


var dminus = require(path).minus_d(10.3, 9.2);
console.log(dminus);
