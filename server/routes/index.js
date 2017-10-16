var express = require('express');
var router = express.Router();
var xml2js = require('xml2js');
var parser = new xml2js.Parser();
var fs = require('fs');
var _publicPath = '../public';
var Article = require('./model/article');

/* GET home page. */

router.get('/', function (req, res, next) {
  Article.find({}, function (err, docs) {
    res.render('articleList', {list: docs});
  });
})

router.post('/', function (req, res, next) {
  res.render('articleRegist', {});
})

router.get('/:idx', function(req, res, next) {
  var idx = req.params.idx;
  var path = _publicPath + '/' + idx;
  fs.readdir(path, 'utf-8', function (err, data) {
    var xml = data;
    if(err) {
      res.render('error',{});
    } else {
      res.render('article',{});
      // parser.parseString(xml, function (err, result) {
      //   var info = new Object();
      //   info.name = idx;
      //   info.tests = result['testsuites']['$']['tests'];
      //   info.failures = result['testsuites']['$']['failures'] ;
      //   info.timestamp = result['testsuites']['$']['timestamp'];
      //   info.time = result['testsuites']['$']['time'];
      //
      //   var testsuites = [];
      //   for(i=0; i<result['testsuites']['testsuite'].length; i++) {
      //     var testsuite = new Object();
      //     var testsuite_info = new Object();
      //     testsuite_info.name = result['testsuites']['testsuite'][i]['$']['name'];
      //     testsuite_info.tests = result['testsuites']['testsuite'][i]['$']['tests'];
      //     testsuite_info.failures = result['testsuites']['testsuite'][i]['$']['failures'];
      //     testsuite_info.time = result['testsuites']['testsuite'][i]['$']['time'];
      //
      //     testsuite.info = testsuite_info;
      //     // console.log(result['testsuites']['testsuite'][i]['testcase'][j]['$']);
      //
      //     var testcase = [];
      //     for(j=0; j<result['testsuites']['testsuite'][i]['testcase'].length; j++) {
      //       var testcaseObject = new Object();
      //       testcaseObject.name = result['testsuites']['testsuite'][i]['testcase'][j]['$']['name'];
      //       if(result['testsuites']['testsuite'][i]['testcase'][j]['failure']) {
      //         testcaseObject.state = 'Failed';
      //       } else {
      //         testcaseObject.state = 'Pass';
      //       }
      //       testcaseObject.time = result['testsuites']['testsuite'][i]['testcase'][j]['$']['time'];
      //       testcase.push(testcaseObject);
      //     }
      //     testsuite.testcase = testcase;
      //     testsuites.push(testsuite);
      //   }
      //  res.render('report', { info : info, testsuites : testsuites });
      //});
    }
  });
});



module.exports = router;




//
// parser.parseString(xml, function (err, result) {
//   // console.log(result);
//
//   // console.log('::total tests, failures, timestamp, time::');
//   // console.log(result['testsuites']['$']);
//   var info = new Object();
//   info.name = __dirname;
//   info.tests = result['testsuites']['$']['tests'];
//   info.failures = result['testsuites']['$']['failures'] ;
//   info.timestamp = result['testsuites']['$']['timestamp'];
//   info.time = result['testsuites']['$']['time'];
//
//
//   // console.log("::total test suites::");
//   // console.log(result['testsuites']['testsuite']);
//
//   // console.log("::each test suite info, test case::");
//   // console.log(result['testsuites']['testsuite'][0]['$']);
//   // console.log(result['testsuites']['testsuite'][0]['testcase']);
//   var testsuites = [];
//   for(i=0; i<result['testsuites']['testsuite'].length; i++) {
//       var testsuite = new Object();
//       var testsuite_info = new Object();
//       var testcase = [];
//       testsuite_info.name = result['testsuites']['testsuite'][i]['$']['name'];
//       testsuite_info.tests = result['testsuites']['testsuite'][i]['$']['tests'];
//       testsuite_info.failures = result['testsuites']['testsuite'][i]['$']['failures'];
//       testsuite_info.time = result['testsuites']['testsuite'][i]['$']['time'];
//
//       testsuite.info = testsuite_info;
//
//       // console.log(result['testsuites']['testsuite'][0]['testcase'][0]['$']);
//       testsuites.push(testsuite);
//   }
//   // console.log(testsuites);
//   // console.log("::each test case::");
//   // console.log(result['testsuites']['testsuite'][0]['testcase'][0]['$']);
//
//
//
//   // var data = JSON.parse(result);
//   // console.log(data);
//   // console.log("TESTSUITES: " +JSON.stringrify(result));
//
// });
