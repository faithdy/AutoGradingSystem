var express = require('express');
var router = express.Router();
var xml2js = require('xml2js');
var parser = new xml2js.Parser();
var fs = require('fs');
var _publicPath = '../public';
var Article = require('./model/article');
var Auth = true;

//show article list
router.get('/', function (req, res, next) {
  Article.find({}, function (err, docs) {
    res.render('articleList', {list: docs});
  });
})

//write atricle
router.post('/', function (req, res, next) {
  var list = new Object();
  list.title = req.body.title;
  list.end_date = req.body.end_date;
  list.module_1 = req.body.module_1? 1 : 0;
  list.module_2 = req.body.module_2? 1 : 0;
  list.module_3 = req.body.module_3? 1 : 0;
  list.module_4 = req.body.module_4? 1 : 0;
  list.module_5 = req.body.module_5? 1 : 0;
  list.content = req.body.content;
  list.file = req.body.file;
  list.author = req.body.author;


  res.render('articleRegist', {list : list});
})

router.get('/:idx', function(req, res, next) {
  var idx = req.params.idx;
  Article.find({'title' : idx}, function (err, docs) {
    if(err) console.log("error");
    res.render('article', {list: docs[0]});
  });
});



module.exports = router;
