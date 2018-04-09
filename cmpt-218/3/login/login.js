var express = require("express");
var app = express();
var flash = require('express-flash');
var session = require('express-session');

var port = process.env.PORT || 3000;

users = [
  { "id":1, "uname":"bobbyc", "password":"1234" },
  { "id":2, "uname":"admin", "password":"1234" }
];

var head = `<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="minimum-scale=1.0, width=device-width, maximum-scale=1.0, user-scalable=no"/>
    <meta charset="utf-8">
    <title>Users</title>
    <link rel="stylesheet" href="./css/style.css"/>
</head>
<body>`;

var _head = `
</body>
</html>`;

app.use(flash());

function logReq(req,res,next){
  console.log(`${req.method} request for ${req.url} - ${JSON.stringify(req.body)}`);
  next();
}

function isLoggedIn(req,res,next){
  if (req.session.user){
    var sid = req.sessionID;
    console.log('SID:',sid);
    next();
  } else {
    req.flash('error','login first!!!');
    res.redirect('/login');
  }
}

app.use('/',logReq);

app.use(session({
  name:"session",
  secret: "zordon",
  maxAge: 1000 * 60 * 30
}));

app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.use(express.static('./pub_html'));

app.get('/login', function(req,res){
  var error = req.flash('error');
  var form = `<h1>LOGIN</h1>
  <section>
    <form action="/login" method="post">
        <input type="text" id="uname" name="uname" placeholder="username" required /> <br />
        <input type="password" id="password" name="password" placeholder="password" required /> <br />
        <button>LOGIN</button>
    </form>
  </section>`;
  form = head + '<p id="error">'+error+'</p>'+ form + _head;
  res.end(form);
});

app.get('/dashboard', isLoggedIn, function(req,res){
  user = req.session.user;
  dash = user.uname + ' <a href="/logout">LOGOUT</a>';
  res.end(head+dash+_head);
});

app.get('/logout', function(req,res){
  req.session.regenerate(function(err){
    req.flash('error','logged out');
    res.redirect('/login');
  });
});

app.post('/login', function(req,res){
  // find user
  var user = null;
  users.forEach(function(u){
    if(u.uname===req.body.uname){
      user = u;
    }
  });

  if (!user){
    req.flash('error','No user found');
    res.redirect('/login');
  } else {
    if (req.body.password === user.password){
      // success
      req.session.user = user;
      res.redirect('/dashboard');
    } else {
      req.flash('error','Wrong Password');
      res.redirect('/login');
    }
  }
});


app.listen(port);
console.log("app running on", port);
