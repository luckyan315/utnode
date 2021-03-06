function User(cd,passwd, phone_no, email){
    this._cd = cd;
    this._passwd = passwd;
    this._phone_no = phone_no;
    this._email = email;

    this._is_model_created = false;

    User.ModelName = 'User';
    User.Model = {
        cd         :String,
        passwd     :String,
        phone_no   :String,
        email      :String,
    };
}


User.prototype.toString = function(){
    return this._cd ;
}

//TODO: interface for app use
//register 
//login
//logout
//changePasswd




// Db related code 
//TODO: will be extrace to single model for dbPool manager
function getDbConnnection(){
   var mongoose = require("mongoose");
   mongoose.connect('mongodb://localhost/test');
   return mongoose
}


User.prototype.createModel = function (){
    if(this._is_model_created == false){
        var dbConnect = getDbConnnection()
        this._model =  dbConnect.model(User.ModelName, User.Model);
        this._is_model_created = true;
    }
}

User.prototype.save = function(){
    this.createModel();

    this._doc = new this._model({
        cd         :this._cd,
        passwd     :this._passwd,
        phone_no   :this._phone_no,
        email      :this._email,
    });
    function __save_err(err){
        if(err)
            console.log("save data error");
    }
    return this._doc.save(__save_err);
}

// Test Code
var u = new User("zero", '123456');
console.log(u.toString());
u.save();
