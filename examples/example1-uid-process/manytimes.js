var m = require('./uid-process');

var counter = process.argv[2] || 1000;

console.log("getting uid", counter, "times");

for (var i = 0; i < counter; i++) {
  m.uid('root', function(err,uid) {
    if (err) return console.error("got error:", err);
  }); 
};

