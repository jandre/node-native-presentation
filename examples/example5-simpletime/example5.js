var Time = require('./simpletime').Time;

var time = new Time();
console.log("Epoch is", time.epoch());  
console.log("Time is", time.string()); 
time.addSeconds(10);
console.log("Epoch is", time.epoch()); 
console.log("Time is", time.string()); 

// Epoch is 1371486877
// Time is Mon Jun 17 12:34:37 2013
// Epoch is 1371486887
// Time is Mon Jun 17 12:34:47 2013

