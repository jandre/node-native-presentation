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
exports.get = function(username) {
  return _pwname.get(username);
};



/**
 * Get uid for user.
 *
 * @param {String} username - username
 *
 * @return {Integer} user id of user 
 *
 */
exports.uid = function(username) {
  return _pwname.get(username).uid;
};

