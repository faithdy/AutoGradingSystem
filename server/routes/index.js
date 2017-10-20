var express = require('express');
var router = express.Router();
var xml2js = require('xml2js');
var parser = new xml2js.Parser();
var fs = require('fs');
var _publicPath = '../public';
var Article = require('./model/article');
var passport = require('passport');
var LocalStrategy = require('passport-local').Strategy;
var User = require('../models/user');
var mongoose = require('mongoose');

// require('./config/passport')(passport);
/* GET home page. */
function isLoggedIn(req, res, next) {
    if (req.isAuthenticated()){
        return next();
    } else {
        res.redirect('/login');
    }
}
router.get('/', isLoggedIn,function (req, res, next) {
  var _user = req.session.passport.user;
  var user_idx;
  console.log(_user);
  User.find({}, function (err, docs) {
    if(err) throw err;
    for(var i=0; i<docs.length; i++) {
       if(docs[i]['_id'] == _user) {
        user_idx = docs[i]['id'];
        break;
      }
    }
  });
  Article.find({}, function (err, docs) {
    res.render('articleList', {list: docs, req : req, user_idx : user_idx});
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

router.get('/login',function(req, res, next) {
  res.render('login', {});
});

router.get('/logout', function(req, res){
  req.logout();
  res.redirect('/'); //Can fire before session is destroyed?
});
router.post('/signup', passport.authenticate('signup', {

    successRedirect : '/',
    failureRedirect : '/login', //가입 실패시 redirect할 url주소
    failureFlash : true
}))
router.post('/login', passport.authenticate('login', {

    successRedirect : '/',
    failureRedirect : '/login', //로그인 실패시 redirect할 url주소
    failureFlash : true

}))




router.get('/profile',isLoggedIn , function(req, res, next) {
    res.render('index', { title: 'You are logged in.' });
});

router.get('/:idx', function(req, res, next) {
  var idx = req.params.idx;
  // var object_id = mongoose.Types.ObjectId(req.session.passport.user);
  // console.log(object_id);
  var _user = req.session.passport.user;
  var user_idx;
  console.log(_user);
  User.find({}, function (err, docs) {
    if(err) throw err;
    for(var i=0; i<docs.length; i++) {
       if(docs[i]['_id'] == _user) {
        user_idx = docs[i]['id'];
        break;
      }
    }

    Article.find({'title' : idx}, function (err, docs) {
      if(err) console.log("error");
      res.render('article', {list: docs[0], user_idx : user_idx});
    });
  });
});



module.exports = router;
