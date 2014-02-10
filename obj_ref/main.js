var path= './build/Release/obj_ref.node'
var hello = require(path).hello();
console.log(hello);


var plugin = require(path);
var user = plugin.CreateUser();
console.log(user)
console.log(plugin.DeleteUser(user));


