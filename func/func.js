var ladd = require('./build/Release/func.node').add(1,2);
console.log(ladd);

var dadd = require('./build/Release/func.node').add_d(0.7, 8.1);
console.log(dadd);


var dminus = require('./build/Release/func.node').minus_d(10.3, 9.2);
console.log(dminus);
