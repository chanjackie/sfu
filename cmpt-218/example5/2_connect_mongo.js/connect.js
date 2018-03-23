var MongoClient = require('mongodb').MongoClient;

var url = "mongodb://localhost/c218";

MongoClient.connect(url, function(err, client){
  if (err) console.log(err);
  //console.log('connected');
  var database = client.db('c218'); // use
  var collection = database.collection('documents'); // db.documents
  collection.insertMany([{a:1,b:2},{a:3,b:4}], function(err, result){
    collection.find().forEach(function(mydoc){
      console.log(mydoc);
    });

  });
});
