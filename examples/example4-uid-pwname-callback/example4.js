var pwname = require('./pwname');

var username = process.argv[2] || 'root';

pwname.get(username, function(err, data) {

  if (err) return console.error("User does not exist:", username, err);

  console.log("pwname info for", username, "is", data);
});

