var mongoose = require('mongoose');
mongoose.Promise = global.Promise;

var db = mongoose.connection;
db.on('error', console.error);
db.once('open', function(){
    // CONNECTED TO MONGODB SERVER
    console.log("Connected to mongod server");
});

mongoose.connect('mongodb://localhost/AGS' , { useMongoClient: true });

var article = mongoose.Schema({
    "title": String,
    "start_date" : Date,
    "end_date" : Date,
    "content" : String,
    "file" : Array,
    "author" : String
}, {versionKey: false}/*__v버전키 필드 제거*/);
module.exports = mongoose.model('article', article);
