var express = require('express');
var router = express.Router();
var xml2js = require('xml2js');
var parser = new xml2js.Parser();
var fs = require('fs');

/* GET home page. */
router.get('/', function (req, res, next) {
  fs.readdir('.', 'utf-8', function (err, data) {
    var list = [];
    for(i=0; i<data.length; i++) {
      if(data[i].indexOf("201")!=-1) {
          list.push(data[i]);
      }
    }
    console.log(list);
    res.render('list', {list: list});
  })
/*
디렉토리 탐색 후, 디렉토리 리스트 테이블로 보여주고 a링크로 파라미터 보내기
*/
})

router.get('/:idx', function(req, res, next) {
  var idx = req.params.idx;
  var publicPath = __dirname + '/../' + idx;
  console.log(publicPath);
  fs.readFile(publicPath + '/UnitReport.xml', 'utf-8', function (err, data) {
    var xml = data;
    if(err) {
      res.render('error',{});
    } else {
      parser.parseString(xml, function (err, result) {
        var info = new Object();
        info.name = idx;
        info.tests = result['testsuites']['$']['tests'];
        info.failures = result['testsuites']['$']['failures'] ;
        info.timestamp = result['testsuites']['$']['timestamp'];
        info.time = result['testsuites']['$']['time'];

        var testsuites = [];
        for(i=0; i<result['testsuites']['testsuite'].length; i++) {
          var testsuite = new Object();
          var testsuite_info = new Object();
          testsuite_info.name = result['testsuites']['testsuite'][i]['$']['name'];
          testsuite_info.tests = result['testsuites']['testsuite'][i]['$']['tests'];
          testsuite_info.failures = result['testsuites']['testsuite'][i]['$']['failures'];
          testsuite_info.time = result['testsuites']['testsuite'][i]['$']['time'];

          testsuite.info = testsuite_info;
          // console.log(result['testsuites']['testsuite'][i]['testcase'][j]['$']);

          var testcase = [];
          for(j=0; j<result['testsuites']['testsuite'][i]['testcase'].length; j++) {
            var testcaseObject = new Object();
            testcaseObject.name = result['testsuites']['testsuite'][i]['testcase'][j]['$']['name'];
            if(result['testsuites']['testsuite'][i]['testcase'][j]['failure']) {
              testcaseObject.state = 'Failed';
            } else {
              testcaseObject.state = 'Pass';
            }
            testcaseObject.time = result['testsuites']['testsuite'][i]['testcase'][j]['$']['time'];
            testcase.push(testcaseObject);
          }
          testsuite.testcase = testcase;
          testsuites.push(testsuite);
        }
        res.render('report', { info : info, testsuites : testsuites });
      });
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
