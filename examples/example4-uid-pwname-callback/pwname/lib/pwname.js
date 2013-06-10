var path = require('path');
var _pwname = require(path.join(__dirname, '../build/Release/pwname.node'));

/**
 * Get user information.
 *
 * @param {String} username - username
 *
 * @return {Integer} user id of user 
 *
 */
exports.get = function(username, callback) {
  return _pwname.get(username, callback);
};



