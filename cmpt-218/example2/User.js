module.exports = function(fname,lname,age){
  this.fname = fname;
  this.lname = lname;
  this.age = age;
  this.fullName = function(){
    console.log(this.fname + ' ' + this.lname);
  }
}
