
// --------- prints hello0, hello1, hello2, ... -----//
// --------- onclick --------------------------------//
var a = 0;
function runCommand(){
  console.log("hello"+a);
  a++;
}
document.getElementById('button1').onclick = runCommand;

// ---------- calls run command every 2 sec ---------//
// var int = setInterval(runCommand,2000);


// ---------- logs mouse event type ----------------//
// document.getElementById('button2').onmousedown = runCommand2;
// document.getElementById('button2').onmouseup = runCommand2;
// function runCommand2(evt){
//   console.log("type: "+evt.type+"button: "+evt.button);
// }

// ---------- logs "hello", then "world" for button2 ------//
// ---------- use event listeners instead ------------------//

// var hello = function(){
//   console.log("hello");
// }
// document.getElementById('button2').addEventListener('click', hello);
//
// document.getElementById('button2').addEventListener('click', world);
//
// function world(){
//   console.log("world");
// }

// --- third param ----//

window.addEventListener('click',function(){console.log("hello")},false);
window.addEventListener('click',function(){console.log("world")},true);


// ---------- removing an eventlistener -----------------//

function remove(){
  document.getElementById('button2').removeEventListener('click', hello);
}

// ------------ keypress ----------------------------//

window.addEventListener('keypress', (e)=>{console.log(e.keyCode)});

// ---------- JS objects ------------------------------//

// var user = { "name":"bobby", "age":24 };
//
// user.email = "bobbyc@sfu.ca";
// user.about = function(){
//   console.log(user.name);
//   console.log(user["age"]);
// }

// constructor

function User(fname,lname,age){
  this.firstname = fname;
  this.lastname = lname;
  this.age = age;

  this.fullName = function(){
    return this.firstname + " " + this.lastname
  };
}

var u1 = new User("Bobby","Chan", 24);
u1.email = "bobbyc@sfu.ca";
var u2 = new User("Rachel","Chan", 20);

var family = [];
family.push(u1);
family.push(u2);

for (user of family){
  for (item in user){
    console.log(item + " " + user[item]);
  }
}


// ---------- JSON -------------------------------//

myObj = { "name":"bobby", "age":24 };

var str = JSON.stringify(myObj);
// console.log(str);

// send it to server

var obj = JSON.parse(str);
// console.log(obj.name);
