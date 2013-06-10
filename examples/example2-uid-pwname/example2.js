/**
* Get the uid for username.
*/

var pwname = require('./pwname');

var username = process.argv[2] || 'root';

try {
  console.log("Uid for", username, "is", pwname.uid(username));
} catch (err) {
  console.error("User does not exist:", username, err);
}

