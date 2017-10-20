var express = require('express');
var router = express.Router();
var xml2js = require('xml2js');
var parser = new xml2js.Parser();
var fs = require('fs-extra');
var Article = require('./model/article.js');
var bodyParser = require('body-parser');
var _publicPath = '../public';
var mkdirp = require('mkdirp');
var multer = require('multer'); // multer모듈 적용 (for 파일업로드)
var rmdir = require('rimraf');


router.post('/articleRegist', function (req, res, next) {
  console.log("프로젝트 등록 API 호출");
  console.log(req.body);
  var storage = multer.diskStorage({
     // 서버에 저장할 폴더
     destination: function (req, file, cb) {
       cb(null, _publicPath);
     },

     // 서버에 저장할 파일 명
     filename: function (req, file, cb) {
       file.uploadedFile = {
         name: req.params.filename,
         ext: file.mimetype.split('/')[1]
       };
       cb(null, file.uploadedFile.name + '.' + file.uploadedFile.ext);
     }
   });

   var upload = multer({ storage: storage }).array('file');
   upload(req, res, function (err) {
     if(err) throw err;
     var title = req.body.title;
     var start_date = new Date();
     var end_date = req.body.date;
     var content = req.body.content;
     var file = req.files;
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

     var article = new Article({
       title: title,
       start_date: start_date,
       end_date: end_date,
       content: content,
       file: file,
       author: author
     });
     console.log(article);
     if(title) {
       mkdirp(_publicPath+'/'+title+'/info', function (err) {
         if(err) throw err;
         fs.writeFile(_publicPath+'/'+title+'/info/'+title+'.json',
         JSON.stringify(jsonToFramework), 'utf8', function (err) {
           console.log("프로젝트 생성 & info 파일 등록 완료.");
         });
       })
       mkdirp(_publicPath+'/'+title+'/data', function (err) {});
       mkdirp(_publicPath+'/'+title+'/result', function (err) {});

       article.save(function (err, doc) {
         if (err) throw err;
         else console.log("DB에 성공적으로 저장되었습니다.");
       });
     }

   })

  console.log("프로젝트 등록 API 종료");
  res.redirect('/');
})

router.post('/articleUpdate', function (req, res, next) {
  console.log("프로젝트 수정 API 호출");

  console.log("프로젝트 수정 API 종료");
  res.redirect('/');
});

router.post('/articleDelete', function (req, res, next) {
  console.log("프로젝트 삭제 API 호출");
  var title = req.body.title;
  Article.deleteOne({title: title}, function (err, doc) {
      if (err) console.log(err);
      else console.log("DB에서 성공적으로 삭제되었습니다.");
  });

  rmdir(_publicPath+'/'+title, function(err){
      if(err) throw err;
      else console.log("프로젝트가 디렉토리에서 삭제 되었습니다.");
  });
  console.log("프로젝트 삭제 API 종료");
  res.redirect('/');
});

router.post('/assignmentRegist', function (req, res, next) {
  console.log("과제 등록 API 호출");
  console.log("바디 내용"+req.body.name);
  console.log(req.form);
  var title = req.body.title;
  var idx = req.body.idx;
  console.log(title+":"+idx);

  mkdirp(_publicPath+'/'+title+'/data/'+idx, function (err) {
    if(err) throw err;
    var storage = multer.diskStorage({
      // 서버에 저장할 폴더
      destination: function (req, file, cb) {
        cb(null, _publicPath+'/'+title+'/data/'+idx);
      },
      filename: function (req, file, cb) {
        cb(null, file.originalname);
      }
      //서버에 저장할 파일 명
      // filename: function (req, file, cb) {
      //   file.uploadedFile = {
      //     name: req.params.filename,
      //     ext: file.mimetype.split('/')[1]
      //   };
      // cb(null, file.uploadedFile.name + '.' + file.uploadedFile.ext);
      // }
    });
    var upload = multer({ storage: storage }).array('stu_file');
    upload(req, res, function (err) {
      console.log(req.files);
      // if(err) throw err;
      // else
      console.log("과제가 성공적으로 업로드 되었습니다.");
    })
  })
  console.log("과제 등록 API 종료");
  res.redirect('/');
})



module.exports = router;
