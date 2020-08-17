var MongoClient = require('mongodb').MongoClient

var url = 'mongodb://root:root@ds135983.mlab.com:35983/cmpt218-lab7'; 
// Use connect method to connect to the server
MongoClient.connect(url, function(err, client) {
  console.log("Connected successfully to server");
  // Get the documents collection
  var database = client.db('users');
  var collection = database.collection('documents');
  // Insert some documents
  collection.insertMany([ {a : 1}, {a : 2}, {a : 3} ], function(err, result) {
    console.log("Inserted 3 docs into the documents collection");
    collection.update({a:2},{$set:{b:1}}, function(err,result){
      collection.find().forEach(function(mydoc){
        console.log(mydoc);
      });
      client.close();
    });
  });
});


