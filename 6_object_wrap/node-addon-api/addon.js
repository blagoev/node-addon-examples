var addon = require('bindings')('addon');

try {
    var obj = addon.MyObject.create();
    }
    catch (e) {
        console.error("Incorrect expected exception message:" + e.message);
    }
    
    global.gc()
    global.gc()
    global.gc()
/*
try {
var obj = new addon.MyObject();
}
catch (e) {
    if (e.message != "Number expected") {
        console.error("Incorrect expected exception message:" + e.message);
    }
}

var obj = new addon.MyObject(10);
try {
    //NAPI: should fail with `Not implemented` exception
    obj.multiply();
}
catch(e) {
    if (e.message != "Not implemented") {
        throw new Error("Incorrect expected exception message: " + e.message);
    }
}

try {
    //NAPI: should fail with `Not implemented` exception
    var val = obj.value;
}
catch(e) {
    if (e.message != "Not implemented") {
        throw new Error("Incorrect expected exception message: " + e.message);
    }
}

try {
    //NAPI: should fail with `Not implemented` exception. 
    var val = obj.plusOne(obj);
}
catch(e) {
    if (e.message != "Not implemented") {
        throw new Error("Incorrect expected exception message: " + e.message);
    }
}

console.log("Success");


// console.log( obj.plusOne() ); // 11
// console.log( obj.plusOne() ); // 12
// console.log( obj.plusOne() ); // 13

// console.log( obj.multiply().value() ); // 13
// console.log( obj.multiply(10).value() ); // 130

// var newobj = obj.multiply(-1);
// console.log( newobj.value() ); // -13
// console.log( obj === newobj ); // false
*/