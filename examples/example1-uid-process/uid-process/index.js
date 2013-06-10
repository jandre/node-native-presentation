var exec = require('child_process').exec;

exports.uid = function(username, cb) {

  exec('id -u ' + username, function(err, stdout, stderr) {
      cb(err, stdout);
    });

}
