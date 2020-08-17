var chai = require('chai');
var chaiHttp = require('chai-http');
var server = require('../server');
var expect = chai.expect;

chai.use(chaiHttp);

suite('Users', function() {
  test('lists ALL users on /users-api GET', function(done){
    chai.request(server).get('/users-api').end(function(err,res){
      expect(res).to.have.status(200);
      expect(res).to.be.json;
      expect(res).to.be.a('Object');
      done();
    });
  });
  test('adds a SINGLE user on /users-api POST', function(done){
    chai.request(server).get('/users-api').end(function(err,res){
      var num_users0 = res.body.length;
      chai.request(server).post('/users-api').send({"fname":"testy","lname":"mctester","age":"24"})
      .end(function(err,res){
        var num_users1 = res.body.length;
        expect(num_users1-num_users0).to.equal(1);
        done();
      });
    });
  });
  test('deletes a user on /user-api/<id> DELETE');
});
