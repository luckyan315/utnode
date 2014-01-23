var path = './build/Release/obj.node'


var obj_addon = require(path)

var obj = new obj_addon.MyObject(10.01, 20, 'string');
console.log( obj.plusOne() ); // 11
console.log( obj.plusOne() ); // 12
console.log( obj.plusOne() ); // 13


obj.print();


var ebmobj = new obj_addon.EmbObject(obj, 1)
ebmobj.print();
