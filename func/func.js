var path = './build/Release/func.node'
var ladd = require(path).add(1,2);
console.log(ladd);

var ladd2= require(path).add(1,3);
console.log(ladd2);

var dadd = require(path).add_d(0.7, 8.1);
console.log(dadd);


var dminus = require(path).minus_d(10.3, 9.2);
console.log(dminus);

var str_t_len = require(path).str_t('hello')
console.log("string length is : " + str_t_len);
