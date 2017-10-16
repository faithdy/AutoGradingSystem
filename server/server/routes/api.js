var express = require('express');
var router = express.Router();
var xml2js = require('xml2js');
var parser = new xml2js.Parser();
var fs = require('fs');
var Article = require('./model/article.js');
var bodyParser = require('body-parser');
var _publicPath = '../public';
var mkdirp = require('mkdirp');

router.post('/articleRegist', function (req, res, next) {
  var title = req.body.title;
  var start_date = new Date();
  var end_date = req.body.date;
  var content = req.body.content;
  var file = req.body.file;
  var author = req.body.author;

  var module_1 = req.body.module_1;
  var module_2 = req.body.module_2;
  var module_3 = req.body.module_3;
  var module_4 = req.body.module_4;
  var module_5 = req.body.module_5;
  var jsonToFramework = new Object();
  jsonToFramework.compile = module_1? true : false;
  jsonToFramework.comapatibility = module_2? true : false;
  jsonToFramework.oop = module_3? true : false;
  jsonToFramework.death = module_4? true : false;
  jsonToFramework.unit = module_5? true : false;

  if(title) {
    mkdirp(_publicPath+'/'+title+'/info', function (err) {
      fs.writeFile(_publicPath+'/'+title+'/info/'+title+'.json',
      JSON.stringify(jsonToFramework), 'utf8', function (err) {
        console.log("write success");
      });
    })

    var article = new Article({
      title: title,
      start_date: start_date,
      end_date: end_date,
      content: content,
      file: file,
      author: author
    });

    article.save(function (err, doc) {
      if (err) console.log(err);
      else console.log("save DB");
    });
  }
  res.redirect('/');
  
})

module.exports = router;
