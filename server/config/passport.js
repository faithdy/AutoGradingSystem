var LocalStrategy = require('passport-local').Strategy
var User = require('../models/user');
var mongoose = require('mongoose');

module.exports = function(passport) {

    passport.serializeUser(function(user, done) {
        done(null, user._id);
    });
    passport.deserializeUser(function(id, done) {
      var userId = mongoose.Types.ObjectId(id);
        User.findById(userId, function(err, user) {
            done(err, user);
        });
    });
    //프로그램 작성

    passport.use('signup', new LocalStrategy({
        usernameField : 'id',
        passwordField : 'password',
        session: true, // 세션에 저장 여부
        passReqToCallback : true
    },
    function(req,id, password, done) {
        User.findOne({ 'id' : id }, function(err, user) {
            if (err) return done(err);
            if (user) {
                return done(null, false, req.flash('signupMessage', '학번이 존재합니다.'));
            } else {
                var newUser = new User();
                newUser.id = id;
                newUser.password = newUser.generateHash(password);
                newUser.save(function(err) {
                    if (err)
                        throw err;
                    return done(null, newUser);
                });
            }
        });
    }));

    passport.use('login', new LocalStrategy({
            usernameField : 'id',
            passwordField : 'password',
            passReqToCallback : true
        },
        function(req, id, password, done) {
            User.findOne({ 'id' : id }, function(err, user) {
                if (err)
                    return done(err);
                if (!user)
                    return done(null, false, req.flash('loginMessage', '사용자를 찾을 수 없습니다.'));
                if (!user.validPassword(password))
                    return done(null, false, req.flash('loginMessage', '비밀번호가 다릅니다.'));
                return done(null, user);
            });
        }));
};
