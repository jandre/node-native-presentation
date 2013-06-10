var path = require('path');
var _pwname = require(path.join(__dirname, '../build/Release/pwname.node'));

/**
 * Get uid for user.
 *
 * @param {String} username - username
 *
 * @return {Integer} user id of user 
 *
 */
exports.uid = function(username) {
  return _pwname.uid(username);
};

